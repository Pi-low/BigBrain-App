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
 * @file    Scheduler.c
 * @author  Nello Chommanivong
 * @date    14 février 2023, 14:31
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
#include "../02 - LIN_MNG/LIN_mng.h"
#include "../04 - CAN_MNG/CAN_mng.h"
#include "../07 - APP/App.h"
#include "SystemTicks.h"
#include "Task_mng.h"
#include "Scheduler.h"

/******************************************************************************
 * Private variable definitions
 *****************************************************************************/
static uint32_t su32Timeout_5ms = 0, su32Timeout_10ms = 0, su32Timeout_100ms = 0, su32Timeout_1000ms = 0;

/******************************************************************************
 * Private funtion prototypes
 *****************************************************************************/

/******************************************************************************
 * Public APIs & functions
 *****************************************************************************/
void Scheduler_mng(void)
{
    App_Init();
#if _CONF_ENABLE_CAN
    CAN_mng_Init();
#endif
    
#if _CONF_ENABLE_LIN
    LIN_EnableHW();
#endif
    
    while (true)
    {
        if (su32Timeout_5ms > SystemTicks_Get())
        {
            su32Timeout_5ms = SystemTicks_Get() + 5;
            Task_5ms();
        }

        if (su32Timeout_10ms > SystemTicks_Get())
        {
            su32Timeout_10ms = SystemTicks_Get() + 10;
            Task_10ms();
        }

        if (su32Timeout_100ms > SystemTicks_Get())
        {
            su32Timeout_100ms = SystemTicks_Get() + 100;
            Task_100ms();
        }

        if (su32Timeout_1000ms > SystemTicks_Get())
        {
            su32Timeout_1000ms = SystemTicks_Get() + 1000;
            Task_1000ms();
        }
    };
}

/******************************************************************************
 * Private functions
 *****************************************************************************/
