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
 * @file    Task_mng.c
 * @author  Nello Chommanivong
 * @date    14 février 2023, 14:09
 * 
 */

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include "Config.h"
#include "Types.h"
#include "App.h"
#include "Task_mng.h"

/******************************************************************************
 * Private variable definitions
 *****************************************************************************/

/******************************************************************************
 * Private funtion prototypes
 *****************************************************************************/

/******************************************************************************
 * Public APIs & functions
 *****************************************************************************/
void Task_5ms(void)
{
    
}

void Task_10ms(void)
{
    App_RunTask10ms();
}

void Task_100ms(void)
{
}

void Task_1000ms(void)
{
    App_RunTask1000ms();
}

/******************************************************************************
 * Private functions
 *****************************************************************************/

