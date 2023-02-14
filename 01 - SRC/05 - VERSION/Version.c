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
 * @file    Version.c
 * @author  Nello Chommanivong
 * @date    February 13, 2023, 11:34 PM
 * 
 */

#include <stdint.h>
#include "Version.h"

/******************************************************************************
 * Private variable definitions
 *****************************************************************************/

/******************************************************************************
 * Private function prototypes
 *****************************************************************************/

const char __attribute__((address(0x280), space(prog))) text[128] = __DATE__" "__TIME__" : BigBrain tester software";
const uint16_t SWVersion __attribute__((address(0x300), space(prog))) = 0x0100;
