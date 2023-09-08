/**
 * @file    Config.h
 * @author  Nello Chommanivong
 * @date    February 13, 2023, 11:12 PM
 * 
 */

#ifndef CONFIG_H
#define	CONFIG_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "system.h"
#include "clock.h"
#include "pin_manager.h"
#include "system_types.h"
#include "reset.h"
#include "watchdog.h"
#include "interrupt_manager.h"
#include "traps.h"
#include "dma.h"
#include "adc1.h"
#include "tmr1.h"
#include "uart1.h"
#include "uart2.h"
#include "can_types.h"
#include "can1.h"
#include "can2.h"

/******************************************************************************
 * Definitions and macros
 *****************************************************************************/

#define _CONF_ENABLE_CAN    1

#define _CONF_ENABLE_LIN    1

/******************************************************************************
 * Type definitions
 *****************************************************************************/

/******************************************************************************
 * Extern/global variables
 *****************************************************************************/

/******************************************************************************
 * Public function prototypes
 *****************************************************************************/

#endif	/* CONFIG_H */

