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
 * @file    Utils.c
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
#include "Utils.h"

/******************************************************************************
 * Private variable definitions
 *****************************************************************************/

/******************************************************************************
 * Private function prototypes
 *****************************************************************************/

/******************************************************************************
 * Public APIs & functions
 *****************************************************************************/
void Utils_PrintStr(const uint8_t * Fpu8Str)
{
    uint8_t *pu8Tmp = Fpu8Str;
    while (*pu8Tmp != '\0')
    {
        UART1_Write((uint8_t) *pu8Tmp);
        pu8Tmp++;
    }
}

void Utils_PrintStrSize(const uint8_t * Fpu8Str, uint32_t Fu32Len)
{
    uint32_t u32Cnt = 0;
    for (u32Cnt = 0; u32Cnt < Fu32Len; u32Cnt++)
    {
        UART1_Write((uint8_t) *(Fpu8Str + u32Cnt));
    }
}

/******************************************************************************
 * Private functions
 *****************************************************************************/
