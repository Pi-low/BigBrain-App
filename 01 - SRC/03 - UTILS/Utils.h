/**
 * @file    Utils.h
 * @author  Nello Chommanivong
 * @date    February 13, 2023, 11:15 PM
 * 
 */

#ifndef UTILS_H
#define	UTILS_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>
#include "../01 - CONFIG/Config.h"

#define DmPrintDebug(str) Utils_PrintStr(str)

/******************************************************************************
 * Public API prototypes
 *****************************************************************************/
void Utils_PrintStr(const uint8_t * Fpu8Str);
void Utils_PrintStrSize(const uint8_t * Fpu8Str, uint32_t Fu32Len);

#endif	/* UTILS_H */

