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
 * @file    LIN_mng.c
 * @author  Nello Chommanivong
 * @date    February 13, 2023, 11:11 PM
 * 
 */

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../01 - CONFIG/Config.h"
#include "../01 - CONFIG/Types.h"
#include "LIN_mng.h"

/******************************************************************************
 * Private variable definitions
 *****************************************************************************/
static tsLinFrame stsLinFrame_Registered[NB_LIN_FRAMES];

/******************************************************************************
 * Private function prototypes
 *****************************************************************************/
void LIN_SendHeader(tsLinFrame *FptsFrame);
void LIN_SendPayload(tsLinFrame *FptsFrame);

/******************************************************************************
 * Public APIs & functions
 *****************************************************************************/

/******************************************************************************
 * Private functions
 *****************************************************************************/
void LIN_SendHeader(tsLinFrame *FptsFrame)
{
    uint8_t pu8Frm[3] = {0};
    uint8_t u8P0 = 0, u8P1 = 0, u8Cnt;
    
    pu8Frm[0] = 0;
    pu8Frm[1] = 0x55;
    pu8Frm[2] = FptsFrame->u8ID & 0x3F;
    
    u8P0 = (pu8Frm[2] & 1);
    u8P0 ^= (pu8Frm[2] >> 1) & 1;
    u8P0 ^= (pu8Frm[2] >> 2) & 1;
    u8P0 ^= (pu8Frm[2] >> 4) & 1;
    
    u8P1 = (pu8Frm[2] >> 1) & 1;
    u8P1 ^= (pu8Frm[2] >> 3) & 1;
    u8P1 ^= (pu8Frm[2] >> 4) & 1;
    u8P1 ^= (pu8Frm[2] >> 5) & 1;
    u8P1 ^= 1;
    
    pu8Frm[2] |= (u8P0 & 1) << 6;
    pu8Frm[2] |= (u8P1 & 1) << 7;
   
    U2STAbits.UTXBRK = 1;
    for (u8Cnt = 0; u8Cnt < 3; u8Cnt++)
    {
        UART2_Write(pu8Frm[u8Cnt]);
    }
    
    if (FptsFrame->u8Type == eLinMaster)
    {
        LIN_SendPayload(FptsFrame);
    }
}

void LIN_SendPayload(tsLinFrame *FptsFrame)
{
    uint8_t u8Checksum = 0;
    uint8_t u8Cnt = 0;
    
    for (u8Cnt = 0; u8Cnt < FptsFrame->u8Length; u8Cnt++)
    {
        UART2_Write(FptsFrame->pu8Data[u8Cnt]);
        u8Checksum += FptsFrame->pu8Data[u8Cnt];
    }
    
    u8Checksum = (u8Checksum ^ 0xFF) + 1;
    UART2_Write(u8Checksum);
}