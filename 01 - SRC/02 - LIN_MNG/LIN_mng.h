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
#define LIN_FRAME_TIMEOUT (8) // <- ms

/******************************************************************************
 * Type definitions
 *****************************************************************************/
typedef enum
{
    eLinSlave = 0,
    eLinMaster
} teLinType;

typedef struct
{
    teLinType teType;
    uint8_t u8ID;
    uint8_t pu8Data[8];
    uint8_t u8Length;
    uint32_t u32Timeout;
} tsLinFrame;

/******************************************************************************
 * Extern/global variables
 *****************************************************************************/

/******************************************************************************
 * Public function prototypes
 *****************************************************************************/
void LIN_EnableHW(void);
void LIN_DisableHW(void);
void LIN_SendHeader(tsLinFrame *FptsFrame);
void LIN_CbSoF(void);
void LIN_CbRxMng(void);
#endif	/* LIN_MNG_H */

