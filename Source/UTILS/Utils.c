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
#include "Config.h"
#include "Types.h"
#include "Utils.h"

cli_t g_TsCliDef;

/******************************************************************************
 * Private variable definitions
 *****************************************************************************/

/******************************************************************************
 * Private function prototypes
 *****************************************************************************/

/******************************************************************************
 * Public APIs & functions
 *****************************************************************************/
void Utils_Init(void)
{
    g_TsCliDef.println = Utils_PrintStr;
    g_TsCliDef.cmd_cnt = 2;
    g_TsCliDef.cmd_tbl = tsCliCommands;
    cli_init(&g_TsCliDef);
}

void Utils_PrintStr(char * Fpu8Str)
{
    uint8_t *pu8Tmp = NULL;
    pu8Tmp = Fpu8Str;
    while ((*(pu8Tmp) != '\0') && (pu8Tmp != NULL))
    {
        UART1_Write((uint8_t) *pu8Tmp);
        pu8Tmp++;
    }
}

void Utils_PrintStrSize(const char * Fpu8Str, uint32_t Fu32Len)
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
