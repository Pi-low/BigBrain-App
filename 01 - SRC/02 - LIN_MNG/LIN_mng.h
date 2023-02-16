/**
 * @file    LIN_mng.h
 * @author  Nello Chommanivong
 * @date    February 13, 2023, 11:14 PM
 * 
 */

#ifndef LIN_MNG_H
#define	LIN_MNG_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>
#include "../01 - CONFIG/Config.h"
#include "../01 - CONFIG/Types.h"

/******************************************************************************
 * Definitions and macros
 *****************************************************************************/
#define NB_LIN_FRAMES (2)

/******************************************************************************
 * Type definitions
 *****************************************************************************/
typedef struct
{
    uint8_t u8ID;
    uint8_t *pu8Data;
    uint8_t u8Length;
    uint8_t u8Type;
} tsLinFrame;

typedef enum
{
    eLinMaster = 0,
    eLinSlave
} teLinType;

/******************************************************************************
 * Extern/global variables
 *****************************************************************************/

/******************************************************************************
 * Public function prototypes
 *****************************************************************************/
void LIN_EnableHW(void);
void LIN_DisableHW(void);
void LIN_SendHeader(tsLinFrame *FptsFrame);

#endif	/* LIN_MNG_H */

