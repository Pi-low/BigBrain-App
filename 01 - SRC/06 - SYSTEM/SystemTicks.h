/** 
 * @file    SystemTicks.h
 * @author  Nello Chommanivong
 * @date 14 février 2023, 15:29
 * 
 */

#ifndef SYSTEMTICKS_H
#define	SYSTEMTICKS_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <xc.h>
#include "../01 - CONFIG/Config.h"
#include "../01 - CONFIG/Types.h"
#include "SystemTicks.h"

/******************************************************************************
 * Public API prototypes
 *****************************************************************************/
void SystemTicks_Init(void);
uint32_t SystemTicks_Get(void);

#endif	/* SYSTEMTICKS_H */

