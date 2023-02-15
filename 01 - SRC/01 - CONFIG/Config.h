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
#include "../../mcc_generated_files/system.h"
#include "../../mcc_generated_files/clock.h"
#include "../../mcc_generated_files/pin_manager.h"
#include "../../mcc_generated_files/system_types.h"
#include "../../mcc_generated_files/reset.h"
#include "../../mcc_generated_files/watchdog.h"
#include "../../mcc_generated_files/interrupt_manager.h"
#include "../../mcc_generated_files/traps.h"
#include "../../mcc_generated_files/dma.h"
#include "../../mcc_generated_files/adc1.h"
#include "../../mcc_generated_files/tmr1.h"
#include "../../mcc_generated_files/uart1.h"
#include "../../mcc_generated_files/uart2.h"
#include "../../mcc_generated_files/can1.h"
#include "../../mcc_generated_files/can2.h

/******************************************************************************
 * Definitions and macros
 *****************************************************************************/
#define _CONF_ENABLE_CAN    1
#define _CONF_ENABLE_LIN    1
#define _CONF_ENABLE_UART   1

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

