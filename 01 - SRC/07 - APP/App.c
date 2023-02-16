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
#include <xc.h>
#include "../01 - CONFIG/Config.h"
#include "../01 - CONFIG/Types.h"
#include "../03 - UTILS/Utils.h"
#include "../06 - SYSTEM/SystemTicks.h"
#include "App.h"

/******************************************************************************
 * Private variable definitions
 *****************************************************************************/
static uint8_t su8VehicleRxCnt;
static CAN_MSG_FIELD stnCanMsgField_std;

static CAN_MSG_OBJ stsTxVehicle;
static CAN_MSG_OBJ stsTxSeat;

static CAN_MSG_OBJ stsRxVehicle;
static CAN_MSG_OBJ stsRxSeat;

static uint8_t spu8TxDataVehicle[8];
static uint8_t spu8TxDataSeat[8];
static uint8_t spu8RxDataVehicle[8];
static uint8_t spu8RxDataSeat[8];

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
    stnCanMsgField_std.frameType = CAN_FRAME_DATA;
    stnCanMsgField_std.idType = CAN_FRAME_STD;
    stnCanMsgField_std.dlc = CAN_DLC_8;
    
    stsTxVehicle.msgId = APP_CAN_ID_100;
    stsTxVehicle.field = stnCanMsgField_std;
    stsTxVehicle.data = spu8TxDataVehicle;
    
    stsTxSeat.msgId = APP_CAN_ID_500;
    stsTxSeat.field = stnCanMsgField_std;
    stsTxSeat.data = spu8TxDataSeat;
    
    stsRxVehicle.data = spu8RxDataVehicle;
    stsRxSeat.data = spu8RxDataSeat;
    
    su32Timeout1 = 0;
    s832Timeout2 = 0;
    su8Flag1 = 0;
    su8Flag2 = 0;
}

void App_CbOnCanVehicleRx(void)
{
    if (DmVehicleCanRx(&stsRxVehicle))
    {
        if (stsRxVehicle.msgId == APP_CAN_ID_500)
        {
            if (stsRxSeat.data[7] == 0x2B)
            {
                su32Timeout1 = SystemTicks_Get() + APP_RX_FRAME_TIMEOUT;
            }
        }
    }
}

void App_CbOnCanSeatRx(void)
{
    if (DmSeatCanRx(&stsRxSeat))
    {
        if (stsRxSeat.msgId == APP_CAN_ID_100)
        {
            if (stsRxSeat.data[7] == 0x2C)
            {
                s832Timeout2 = SystemTicks_Get() + APP_RX_FRAME_TIMEOUT;
            }
        }
    }
}

void App_RunTask10ms(void)
{
    stsTxVehicle.data[7] = 0x2C;
    stsTxSeat.data[7] = 0x2B;
    
    DmVehicleCanTx(CAN_PRIORITY_LOW, &stsTxVehicle);
    DmSeatCanTx(CAN_PRIORITY_LOW, &stsTxSeat);
    
    if (SystemTicks_Get() > su32Timeout1)  
    {
        if (su8Flag1 != 1)// <-- on rising edge
        {
            su8Flag1 = 1;
            Utils_PrintStr("High speed CAN side rx OFF\r\n");
        }
    }
    else
    {
        if (su8Flag1 != 0) // <-- on falling edge
        {
            su8Flag1 = 0;
            Utils_PrintStr("High speed CAN side rx ON\r\n");
        }
    }
    
    if (SystemTicks_Get() > s832Timeout2) 
    {
        if (su8Flag2 != 1) // <-- on rising edge
        {
            su8Flag2 = 1;
            Utils_PrintStr("Low speed CAN side rx OFF\r\n");
        }
    }
    else
    {
        if (su8Flag2 != 0) // <-- on falling edge
        {
            su8Flag2 = 0;
            Utils_PrintStr("Low speed CAN side rx ON\r\n");
        }
    }
}

/******************************************************************************
 * Private functions
 *****************************************************************************/
