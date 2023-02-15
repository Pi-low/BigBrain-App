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
 * @file    CAN_mng.c
 * @author  Nello Chommanivong
 * @date    February 13, 2023, 10:35 PM
 * 
 */

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <xc.h>
#include "../01 - CONFIG/Config.h"
#include "../01 - CONFIG/Types.h"
#include "CAN_mng.h"

/******************************************************************************
 * Private variable definitions
 *****************************************************************************/

/******************************************************************************
 * Private function prototypes
 *****************************************************************************/
static void CAN1_Receive_MSG(void);
static void CAN2_Receive_MSG(void);

/******************************************************************************
 * Public APIs & functions
 *****************************************************************************/

/**
 * 
 */
void CAN_mng_Init(void)
{
    CAN1_TransmitEnable();
    CAN1_ReceiveEnable();
    CAN2_TransmitEnable();
    CAN2_ReceiveEnable();
    CAN1_SetRxBufferInterruptHandler(&CAN1_Receive_MSG);
    CAN2_SetRxBufferInterruptHandler(&CAN2_Receive_MSG);
}

void CAN1_Receive_MSG(void)
{
    if(CAN1_Receive(&CAN1_RX))
    {
        if(CAN1_RX.msgId == 0x1A)
        {
            CAN2_TX.data[7] = CAN1_RX.data[7];
        }
    }
}

void CAN2_Receive_MSG(void)
{
    if(CAN2_Receive(&CAN2_RX))
    {
        if(CAN2_RX.msgId == 0x2B)
        {
            CAN1_TX.data[7] = CAN2_RX.data[7];
        }
    }
}

/******************************************************************************
 * Private functions
 *****************************************************************************/
