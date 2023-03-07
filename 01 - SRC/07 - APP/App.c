/*
 *  [DESRCIPTION]
 *  Copyright (C) 2023 Nello CHOMMANIVONG
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file    App.c
 * @author  Nello Chommanivong
 * @date    14 février 2023, 16:41
 * 
 */

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <xc.h>
#include "../01 - CONFIG/Config.h"
#include "../01 - CONFIG/Types.h"
#include "../05 - VERSION/Version.h"
#include "../03 - UTILS/Utils.h"
#include "../06 - SYSTEM/SystemTicks.h"
#include "App.h"

/******************************************************************************
 * Private variable definitions
 *****************************************************************************/
static CAN_MSG_OBJ sts_CanMsg[eFrameNumber];
static uint8_t spu8_CanDataBuffer[eFrameNumber][8];
static uint16_t spu16_CanId[eFrameNumber] = {
    0x100,
    0,
    0x500,
    0,
};

static uint32_t su32Timeout1, s832Timeout2;
static uint8_t su8Flag1, su8Flag2, su8Action;

/******************************************************************************
 * Private function prototypes
 *****************************************************************************/
#ifdef _APP_TEST
static char* App_GetCanIntFlag(uint16_t Fu16Reg);
#endif
/******************************************************************************
 * Public APIs & functions
 *****************************************************************************/
void App_Init(void)
{
    uint8_t u8Cnt;
    
    CAN1_SetRxBufferInterruptHandler(&App_CbOnCanVehicleRx);
    CAN2_SetRxBufferInterruptHandler(&App_CbOnCanSeatRx);
    
    for (u8Cnt = 0; u8Cnt < eFrameNumber; u8Cnt++)
    {
        sts_CanMsg[u8Cnt].field.dlc = 8;
        sts_CanMsg[u8Cnt].field.frameType = CAN_FRAME_DATA;
        sts_CanMsg[u8Cnt].field.idType = CAN_FRAME_STD;
        sts_CanMsg[u8Cnt].data = spu8_CanDataBuffer[u8Cnt];
        sts_CanMsg[u8Cnt].msgId = spu16_CanId[u8Cnt];
    }
    
    su32Timeout1 = 0;
    s832Timeout2 = 0;
    su8Flag1 = 0;
    su8Flag2 = 0;
    
    Utils_PrintStr("\r\n------------------------------------\r\n   APPLICATION START\r\n------------------------------------\r\n");
}

void App_CbOnCanVehicleRx(void)
{
    if (DmVehicleCanRx(&sts_CanMsg[eCAN_RX_VEHICLE]))
    {

#ifdef _APP_TEST
        su32Timeout1 = SystemTicks_Get() + APP_RX_FRAME_TIMEOUT;
        if (sts_CanMsg[eCAN_RX_VEHICLE].msgId == 0xDB)
        {
            su8Action = sts_CanMsg[eCAN_RX_VEHICLE].data[1];
        }
#else
        memcpy(&sts_CanMsg[eCAN_TX_SEAT], &sts_CanMsg[eCAN_RX_VEHICLE], sizeof(CAN_MSG_OBJ));
        DmSeatCanTx(CAN_PRIORITY_NONE, &sts_CanMsg[eCAN_TX_SEAT]);
#endif
    }
}

void App_CbOnCanSeatRx(void)
{
    if (DmSeatCanRx(&sts_CanMsg[eCAN_RX_SEAT]))
    {
#ifdef _APP_TEST
        s832Timeout2 = SystemTicks_Get() + APP_RX_FRAME_TIMEOUT;
#else
        memcpy(&sts_CanMsg[eCAN_TX_VEHICLE], &sts_CanMsg[eCAN_RX_SEAT], sizeof(CAN_MSG_OBJ));
        DmVehicleCanTx(CAN_PRIORITY_NONE, &sts_CanMsg[eCAN_TX_VEHICLE]);
#endif
    }
}

void App_RunTask10ms(void)
{
#ifdef _APP_TEST
    uint32_t u32Tick = SystemTicks_Get();
    uint16_t u16Vbat = ADC1_ConversionResultGet(VBAT);
    static uint8_t u8prev = 0;
    
    sts_CanMsg[eCAN_TX_VEHICLE].data[0] = u32Tick >> 24;
    sts_CanMsg[eCAN_TX_VEHICLE].data[1] = u32Tick >> 16;
    sts_CanMsg[eCAN_TX_VEHICLE].data[2] = u32Tick >> 8;
    sts_CanMsg[eCAN_TX_VEHICLE].data[3] = u32Tick;
    sts_CanMsg[eCAN_TX_VEHICLE].data[4] = u16Vbat >> 8;
    sts_CanMsg[eCAN_TX_VEHICLE].data[5] = u16Vbat;
    
    sts_CanMsg[eCAN_TX_SEAT].data[0] = u32Tick >> 24;
    sts_CanMsg[eCAN_TX_SEAT].data[1] = u32Tick >> 16;
    sts_CanMsg[eCAN_TX_SEAT].data[2] = u32Tick >> 8;
    sts_CanMsg[eCAN_TX_SEAT].data[3] = u32Tick;
    sts_CanMsg[eCAN_TX_SEAT].data[4] = u16Vbat >> 8;
    sts_CanMsg[eCAN_TX_SEAT].data[5] = u16Vbat;
    
    DmVehicleCanTx(CAN_PRIORITY_NONE, &sts_CanMsg[eCAN_TX_VEHICLE]);
    DmSeatCanTx(CAN_PRIORITY_NONE, &sts_CanMsg[eCAN_TX_SEAT]);                                                                                                                                                                   
    
    if (SystemTicks_Get() > su32Timeout1)  
    {
        if (su8Flag1 != 1)
        {
            su8Flag1 = 1;
            Utils_PrintStr("Low speed CAN side rx OFF\r\n"); // <-- on rising edge
        }
    }
    else
    {
        if (su8Flag1 != 0)
        {
            su8Flag1 = 0;
            Utils_PrintStr("Low speed CAN side rx ON\r\n"); // <-- on falling edge
        }
    }
    
    if (SystemTicks_Get() > s832Timeout2) 
    {
        if (su8Flag2 != 1)
        {
            su8Flag2 = 1;
            Utils_PrintStr("High speed CAN side rx OFF\r\n"); // <-- on rising edge
        }
    }
    else
    {
        if (su8Flag2 != 0)
        {
            su8Flag2 = 0;
            Utils_PrintStr("High speed CAN side rx ON\r\n"); // <-- on falling edge
        }
    }
    
    if (u8prev != su8Action)
    {
        _LATA9 = su8Action & 1;         //CAN1 RS
        _LATC3 = (su8Action >> 1) & 1;  //CAN2 RS
        _LATA10 = (su8Action >> 2) & 1; //FPWM
        u8prev = su8Action;
    }
#endif
}

void App_RunTask1000ms(void)
{
#ifdef _APP_TEST
    char pcStr[768];
    uint16_t u16Reg2 = C2INTF;
    uint16_t u16Reg1 = C1INTF;
    sprintf(pcStr, "Current tick: %lu\r\n - CAN 100K: %s\r\n - CAN 500K: %s\r\nSystem voltage: %u\r\nCAN1 IF: %s\r\nCAN2 IF : %s\r\n",
            SystemTicks_Get(),
            (su8Flag1 == 1) ? "OFF" : "ON",
            (su8Flag2 == 1) ? "OFF" : "ON",
            ADC1_ConversionResultGet(VBAT),
            App_GetCanIntFlag(u16Reg1),
            App_GetCanIntFlag(u16Reg2));
    Utils_PrintStr(pcStr);
#endif
}

/******************************************************************************
 * Private functions
 *****************************************************************************/
#ifdef _APP_TEST
char* App_GetCanIntFlag(uint16_t Fu16Reg)
{
    char pcVerbose[256];
    uint8_t u8Cnt;
    uint8_t u8Tmp;
    for (u8Cnt = 0; u8Cnt < 16; u8Cnt++)
    {
        u8Tmp = (Fu16Reg >> u8Cnt) & 1;
        switch (u8Cnt)
        {
        case 0:
            if (u8Tmp != 0)
            {
                strcat(pcVerbose, "TBIF ");
            }
        case 1:
            if (u8Tmp != 0)
            {
                strcat(pcVerbose, "RBIF ");
            }
        case 2:
            if (u8Tmp != 0)
            {
                strcat(pcVerbose, "RBOVIF ");
            }
        case 3:
            if (u8Tmp != 0)
            {
                strcat(pcVerbose, "FIFOIF ");
            }
        case 4:
            if (u8Tmp != 0)
            {
                strcat(pcVerbose, "ERRIF ");
            }
        case 6:
            if (u8Tmp != 0)
            {
                strcat(pcVerbose, "WAKIF ");
            }
        case 7:
            if (u8Tmp != 0)
            {
                strcat(pcVerbose, "IVRIF ");
            }
        case 8:
            if (u8Tmp != 0)
            {
                strcat(pcVerbose, "EWARN ");
            }
        case 9:
            if (u8Tmp != 0)
            {
                strcat(pcVerbose, "RXWAR ");
            }
        case 10:
            if (u8Tmp != 0)
            {
                strcat(pcVerbose, "TXWAR ");
            }
        case 11:
            if (u8Tmp != 0)
            {
                strcat(pcVerbose, "TXWAR ");
            }
        case 12:
            if (u8Tmp != 0)
            {
                strcat(pcVerbose, "RXBP ");
            }
        case 13:
            if (u8Tmp != 0)
            {
                strcat(pcVerbose, "TXBP ");
            }
        case 14:
            if (u8Tmp != 0)
            {
                strcat(pcVerbose, "TXBO ");
            }
        }
    }
    return pcVerbose;
}
#endif