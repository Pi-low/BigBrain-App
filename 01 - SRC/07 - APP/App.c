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
#include "../06 - SYSTEM/SystemTicks.h"
#include "App.h"

/******************************************************************************
 * Private variable definitions
 *****************************************************************************/
static CAN_MSG_FIELD stnCanMsgField_std;
static CAN_MSG_OBJ stsTxVehicle;
static CAN_MSG_OBJ stsTxSeat;
static uint8_t pu8TxDataVehicle[8];
static uint8_t pu8TxDataSeat[8];

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
    stnCanMsgField_std.dlc = 8;
    
    stsTxVehicle.field = stnCanMsgField_std;
    stsTxVehicle.data = pu8TxDataVehicle;
    
    stsTxSeat.field = stnCanMsgField_std;
    stsTxSeat.data = pu8TxDataSeat;
}

void App_TxData_100ms(void)
{
    
}

/******************************************************************************
 * Private functions
 *****************************************************************************/
