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
static CAN_MSG_FIELD stnCanMsgField_std;

static CAN_MSG_OBJ stsTxVehicle;
static CAN_MSG_OBJ stsTxSeat;
static CAN_MSG_OBJ DbugMSG;

static CAN_MSG_OBJ stsRxVehicle;
static CAN_MSG_OBJ stsRxSeat;

static uint8_t spu8TxDataVehicle[8] = {0};
static uint8_t spu8TxDataSeat[8] = {0};
static uint8_t spu8RxDataVehicle[8] = {0};
static uint8_t spu8RxDataSeat[8] = {0};
static uint8_t spuDebugData[8] = {0};

static uint32_t su32Timeout1, s832Timeout2;
static uint8_t su8Flag1, su8Flag2;

/******************************************************************************
 * Private function prototypes
 *****************************************************************************/

/******************************************************************************
 * Public APIs & functions
 *****************************************************************************/
void App_Init(void)
{
    CAN1_SetRxBufferInterruptHandler(&App_CbOnCanVehicleRx);
    CAN2_SetRxBufferInterruptHandler(&App_CbOnCanSeatRx);
#ifdef _APP_TEST
    stnCanMsgField_std.frameType = CAN_FRAME_DATA;
    stnCanMsgField_std.idType = CAN_FRAME_STD;
    stnCanMsgField_std.dlc = CAN_DLC_8;
    
    stsTxVehicle.msgId = APP_CAN_ID_100;
    stsTxVehicle.field = stnCanMsgField_std;
    
    stsTxSeat.msgId = APP_CAN_ID_500;
    stsTxSeat.field = stnCanMsgField_std;
    
    DbugMSG.msgId = 0xDB;
    DbugMSG.field = stnCanMsgField_std;
    DbugMSG.data = spuDebugData;
#endif
    stsTxSeat.data = spu8TxDataSeat;
    stsTxVehicle.data = spu8TxDataVehicle;
    
    stsRxVehicle.data = spu8RxDataVehicle;
    stsRxSeat.data = spu8RxDataSeat;
    
    su32Timeout1 = 0;
    s832Timeout2 = 0;
    su8Flag1 = 0;
    su8Flag2 = 0;
    
    Utils_PrintStr("\r\n------------------------------------\r\n   APPLICATION START\r\n------------------------------------\r\n");
}

void App_CbOnCanVehicleRx(void)
{
    if (DmVehicleCanRx(&stsRxVehicle))
    {

#ifdef _APP_TEST
        su32Timeout1 = SystemTicks_Get() + APP_RX_FRAME_TIMEOUT;
#else
        memcpy(&stsTxSeat, &stsRxVehicle, sizeof(CAN_MSG_OBJ));
        //stsTxSeat.data[7] = 0x15;
        DmSeatCanTx(CAN_PRIORITY_NONE, &stsTxSeat);
#endif
    }
}

void App_CbOnCanSeatRx(void)
{
    if (DmSeatCanRx(&stsRxSeat))
    {
#ifdef _APP_TEST
        s832Timeout2 = SystemTicks_Get() + APP_RX_FRAME_TIMEOUT;
#else
        memcpy(&stsTxVehicle, &stsRxSeat, sizeof(CAN_MSG_OBJ));
        //stsTxVehicle.data[7] = 0x25;
        DmVehicleCanTx(CAN_PRIORITY_NONE, &stsTxVehicle);
#endif
    }
}

void App_RunTask10ms(void)
{
#ifdef _APP_TEST
    uint32_t u32Tick = SystemTicks_Get();
    static uint8_t u8FlipFlop = 0;
    uint16_t u16Reg = 0;
    
    stsTxVehicle.data[0] = u32Tick >> 24;
    stsTxVehicle.data[1] = u32Tick >> 16;
    stsTxVehicle.data[2] = u32Tick >> 8;
    stsTxVehicle.data[3] = u32Tick;
    
    stsTxSeat.data[0] = u32Tick >> 24;
    stsTxSeat.data[1] = u32Tick >> 16;
    stsTxSeat.data[2] = u32Tick >> 8;
    stsTxSeat.data[3] = u32Tick;
    
    if (u8FlipFlop == 0)
    {
        DmVehicleCanTx(CAN_PRIORITY_MEDIUM, &stsTxVehicle);
        u8FlipFlop ^= 1;
    }
    else
    {
        DmSeatCanTx(CAN_PRIORITY_MEDIUM, &stsTxSeat);
        u8FlipFlop ^= 1;
    }                                                                                                                                                                                       
    
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
    u16Reg = C2INTF;
    
    DbugMSG.data[0] = su8Flag1 | (su8Flag2 << 1);
    DbugMSG.data[1] = u16Reg >> 8;
    DbugMSG.data[2] = u16Reg;
    DbugMSG.data[3] = stsRxSeat.msgId >> 8;
    DbugMSG.data[4] = stsRxSeat.msgId;
    DbugMSG.data[5] = stsRxSeat.data[0];
    
    DmSeatCanTx(CAN_PRIORITY_NONE, &DbugMSG);
    
#endif
}

void App_RunTask1000ms(void)
{
#ifdef _APP_TEST
    char pcStr[255];
    sprintf(pcStr, "Current tick: %lu\r\n - CAN 100K: %s\r\n - CAN 500K: %s\r\n", SystemTicks_Get(),
            (su8Flag1 == 1) ? "OFF" : "ON",
            (su8Flag2 == 1) ? "OFF" : "ON");
    Utils_PrintStr(pcStr);
#endif
}

/******************************************************************************
 * Private functions
 *****************************************************************************/
