/* 
 * @file    App.h
 * @author  Nello Chommanivong
 * @date    14 février 2023, 16:42
 * 
 */

#ifndef APP_H
#define	APP_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <xc.h>
#include "../01 - CONFIG/Config.h"
#include "../01 - CONFIG/Types.h"

/******************************************************************************
 * Definitions and macros
 *****************************************************************************/
/* Wrap CAN Tx functions */
#define DmVehicleCanTx(prio, msg) CAN1_Transmit(prio, msg)
#define DmSeatCanTx(prio, msg) CAN2_Transmit(prio, msg)

#define DmVehicleCanRx(msg) CAN1_Receive(msg)
#define DmSeatCanRx(msg) CAN2_Receive(msg)

#define APP_CAN_ID_500 (0xA5)
#define APP_CAN_ID_100 (0xA1)

#define APP_RX_FRAME_TIMEOUT (250) //ms

/******************************************************************************
 * Type definitions
 *****************************************************************************/

/******************************************************************************
 * Extern/global variables
 *****************************************************************************/

/******************************************************************************
 * Public function prototypes
 *****************************************************************************/
void App_Init(void);
void App_CbOnCanVehicleRx(void);
void App_CbOnCanSeatRx(void);
void App_RunTask10ms(void);
void App_RunTask1000ms(void);

#endif	/* APP_H */

