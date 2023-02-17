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
 * @file    SystemTicks.c
 * @author  Nello Chommanivong
 * @date    14 février 2023, 15:10
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
#include "SystemTicks.h"

/******************************************************************************
 * Private variable definitions
 *****************************************************************************/
static uint32_t su32SysTick;

/******************************************************************************
 * Private funtion prototypes
 *****************************************************************************/
static void SystemTicks_TimerCallback(void);

/******************************************************************************
 * Public APIs & functions
 *****************************************************************************/
void SystemTicks_Init(void)
{
    TMR1_SetInterruptHandler(&SystemTicks_TimerCallback);
    TMR1_Start();
}

uint32_t SystemTicks_Get(void)
{
    return su32SysTick;
}

/******************************************************************************
 * Private functions
 *****************************************************************************/
void SystemTicks_TimerCallback(void)
{
    su32SysTick++;
}