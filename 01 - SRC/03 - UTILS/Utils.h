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
#include "../01 - SRC/08 - CLI/cli.h"

extern cli_t g_TsCliDef;

#define DmPrintDebug(str) Utils_PrintStr(str)


/******************************************************************************
 * Public API prototypes
 *****************************************************************************/
void Utils_PrintStr(const char * Fpu8Str);
void Utils_PrintStrSize(const char * Fpu8Str, uint32_t Fu32Len);

#endif	/* UTILS_H */

