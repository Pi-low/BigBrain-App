/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.169.0
        Device            :  dsPIC33EP512GM604
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.40
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "01 - CONFIG/Config.h"
#include "02 - LIN_MNG/LIN_mng.h"
#include "03 - UTILS/Utils.h"
#include "04 - CAN_MNG/CAN_mng.h"
#include "05 - VERSION/Version.h"
/*
                         Main application
 */
void My_IRS_TMR1(void);
uint32_t SendLIN(uint8_t FrameID);
uint8_t ManageLIN(uint8_t * Payload);
void SendUart1(uint8_t *Fpu8String);

enum
{
    CAN1_ACTV_DATA = 0,
    CAN2_ACTV_DATA = 1,
    CAN1_TX_DATA = 2,
    CAN2_TX_DATA = 3,
    CAN1_RX_DATA = 4,
    CAN2_RX_DATA = 5
};


typedef struct
{
    uint8_t SendFlag;
    uint32_t Timeout;
}LIN_Flags_t;

CAN_MSG_OBJ CAN1_RX, CAN1_TX, CAN2_RX, CAN2_TX, CAN1_ACTV, CAN2_ACTV;
CAN_MSG_FIELD StdField;
LIN_Flags_t MyLINStatus;
const uint8_t GEN_0 = 0b010111;
const uint8_t GEN_1 = 0b111010;
uint8_t Payload[6][8] = {{0}};

uint8_t LIN_Payload[11];
uint8_t Counter, MasterID, LINupdate;
uint32_t TimerTick, Timeout_1000ms, Timeout_100ms, Timeout_10ms, Timeout_20ms;

int main(void)
{
    uint8_t pu8String[256] = {0};
    TimerTick = 0;
    Counter = 0;
    MasterID = 0;
    LINupdate = 0;
    TMR1_SetInterruptHandler(My_IRS_TMR1);
    //initialize the device
    SYSTEM_Initialize();
    
    TMR1_Start();
    
    StdField.idType = CAN_FRAME_STD;
    StdField.frameType = CAN_FRAME_DATA;
    StdField.dlc = 8;
    
    CAN1_ACTV = (CAN_MSG_OBJ) {0xC1, StdField, Payload[CAN1_ACTV_DATA]};
    CAN2_ACTV = (CAN_MSG_OBJ) {0xC2, StdField, Payload[CAN2_ACTV_DATA]};
    
    CAN1_TX =   (CAN_MSG_OBJ) {0x1B, StdField, Payload[CAN1_TX_DATA]};
    CAN2_TX =   (CAN_MSG_OBJ) {0x2A, StdField, Payload[CAN2_TX_DATA]};
    
    CAN1_RX.data = Payload[CAN1_RX_DATA];
    CAN2_RX.data = Payload[CAN2_RX_DATA];
    
    CAN1_TX.data[7] = 0x7;
    CAN2_TX.data[7] = 0x7;
    FPWM_SetHigh();
    LIN_CS_SetHigh();
    
    
    sprintf((char *)pu8String, "Application start !\r\n");
    SendUart1(pu8String);

    while (1)
    {
        LINupdate = ManageLIN(LIN_Payload);
        if (TimerTick > Timeout_10ms)
        {
            Timeout_10ms = TimerTick + 10;
            CAN1_Transmit(CAN_PRIORITY_MEDIUM, &CAN1_TX);
            CAN2_Transmit(CAN_PRIORITY_MEDIUM, &CAN2_TX);
        }
        if (TimerTick > Timeout_20ms)
        {
            Timeout_20ms = TimerTick + 20;
            MasterID++;
            SendLIN(0x0B);
        }
        if (TimerTick > Timeout_100ms)
        {
            Timeout_100ms = TimerTick + 100;
            Counter ++;
            if (LINupdate != 0)
            {
                CAN2_ACTV.data[1] = LIN_Payload[1];
                CAN2_ACTV.data[2] = LIN_Payload[2];
                CAN2_ACTV.data[3] = LIN_Payload[3];
                CAN2_ACTV.data[4] = LIN_Payload[4];
                CAN2_ACTV.data[5] = LIN_Payload[5];
                CAN2_ACTV.data[6] = LIN_Payload[6];
                CAN2_ACTV.data[7] = LIN_Payload[7];
                LINupdate = 0;
            }
            CAN1_ACTV.data[0] = Counter;
            CAN2_ACTV.data[0] = Counter;
            CAN1_Transmit(CAN_PRIORITY_LOW, &CAN1_ACTV);
            CAN2_Transmit(CAN_PRIORITY_LOW, &CAN2_ACTV);
        }
        if (TimerTick >Timeout_1000ms)
        {
            Timeout_1000ms = TimerTick + 1000;
            sprintf((char *)pu8String, "Tick: %u\r\n", (uint16_t)TimerTick);
            SendUart1(pu8String);
        }
    }
    return 1; 
}

void My_IRS_TMR1(void)
{
    TimerTick++;
}

uint32_t SendLIN(uint8_t FrameID, uint8_t Length)
{
    uint8_t PID, P0, P1, Checksum;
    uint32_t RxTimeout = TimerTick + 10;
    
    PID = FrameID & 0x3F;
    
    P0 = (PID & 1);
    P0 ^= (PID >> 1) & 1;
    P0 ^= (PID >> 2) & 1;
    P0 ^= (PID >> 4) & 1;
    
    P1 = (PID >> 1) & 1;
    P1 ^= (PID >> 3) & 1;
    P1 ^= (PID >> 4) & 1;
    P1 ^= (PID >> 5) & 1;
    P1 ^= 1;
    
    PID |= (P0 & 1) << 6;
    PID |= (P1 & 1) << 7;
    //Checksum = Payload[0] + Payload[1] + PID;
    //Checksum ^= 0xFF;
    
    U2STAbits.UTXBRK = 1;
    UART2_Write(0); /* Break */
    UART2_Write(0x55); /* Sync byte */
    UART2_Write(PID);
    return RxTimeout;
}
uint8_t ManageLIN(uint8_t * Payload)
{
    uint8_t i;
    uint8_t NewData = 0;
    if (TimerTick >= MyLINStatus.Timeout)
    {
        for (i = 0; i < 11; i++)
        {
            Payload[i] = 0;
        }
        i = 0;
        while ((i < 11) && UART2_IsRxReady())
        {
            Payload[i] = UART2_Read();
            i++;
            NewData = 1;
        }
    }
    return NewData;
}

void SendUart1(uint8_t *Fpu8String)
{
    while (*Fpu8String != 0)
    {
        UART1_Write(*Fpu8String);
        Fpu8String++;
    }
}
/**
 End of File
*/

