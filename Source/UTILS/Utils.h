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
#include "Config.h"
#include "cli.h"

/******************************************************************************
 * Public API prototypes
 *****************************************************************************/
void Utils_PrintStr(char * Fpu8Str);
void Utils_PrintStrSize(const char * Fpu8Str, uint32_t Fu32Len);
cli_status_t UtilsReply(int argc, char **argv);
cli_status_t CANConfig(int argc, char **argv);
extern cli_t g_TsCliDef;

#define DmPrintDebug(str) Utils_PrintStr(str)




#endif	/* UTILS_H */

