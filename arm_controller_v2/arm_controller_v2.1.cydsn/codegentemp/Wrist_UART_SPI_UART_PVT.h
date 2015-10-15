/*******************************************************************************
* File Name: Wrist_UART_SPI_UART_PVT.h
* Version 2.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_Wrist_UART_H)
#define CY_SCB_SPI_UART_PVT_Wrist_UART_H

#include "Wrist_UART_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if(Wrist_UART_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  Wrist_UART_rxBufferHead;
    extern volatile uint32  Wrist_UART_rxBufferTail;
    extern volatile uint8   Wrist_UART_rxBufferOverflow;
#endif /* (Wrist_UART_INTERNAL_RX_SW_BUFFER_CONST) */

#if(Wrist_UART_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  Wrist_UART_txBufferHead;
    extern volatile uint32  Wrist_UART_txBufferTail;
#endif /* (Wrist_UART_INTERNAL_TX_SW_BUFFER_CONST) */

#if(Wrist_UART_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 Wrist_UART_rxBufferInternal[Wrist_UART_RX_BUFFER_SIZE];
#endif /* (Wrist_UART_INTERNAL_RX_SW_BUFFER) */

#if(Wrist_UART_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 Wrist_UART_txBufferInternal[Wrist_UART_TX_BUFFER_SIZE];
#endif /* (Wrist_UART_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(Wrist_UART_SCB_MODE_SPI_CONST_CFG)
    void Wrist_UART_SpiInit(void);
#endif /* (Wrist_UART_SCB_MODE_SPI_CONST_CFG) */

#if(Wrist_UART_SPI_WAKE_ENABLE_CONST)
    void Wrist_UART_SpiSaveConfig(void);
    void Wrist_UART_SpiRestoreConfig(void);
#endif /* (Wrist_UART_SPI_WAKE_ENABLE_CONST) */

#if(Wrist_UART_SCB_MODE_UART_CONST_CFG)
    void Wrist_UART_UartInit(void);
#endif /* (Wrist_UART_SCB_MODE_UART_CONST_CFG) */

#if(Wrist_UART_UART_WAKE_ENABLE_CONST)
    void Wrist_UART_UartSaveConfig(void);
    void Wrist_UART_UartRestoreConfig(void);
    #define Wrist_UART_UartStop() \
        do{                             \
            Wrist_UART_UART_RX_CTRL_REG &= ~Wrist_UART_UART_RX_CTRL_SKIP_START; \
        }while(0)
#else
        #define Wrist_UART_UartStop() do{ /* Does nothing */ }while(0)

#endif /* (Wrist_UART_UART_WAKE_ENABLE_CONST) */

/* Interrupt processing */
#define Wrist_UART_SpiUartEnableIntRx(intSourceMask)  Wrist_UART_SetRxInterruptMode(intSourceMask)
#define Wrist_UART_SpiUartEnableIntTx(intSourceMask)  Wrist_UART_SetTxInterruptMode(intSourceMask)
uint32  Wrist_UART_SpiUartDisableIntRx(void);
uint32  Wrist_UART_SpiUartDisableIntTx(void);


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in Wrist_UART_SetPins() */
#define Wrist_UART_UART_RX_PIN_ENABLE    (Wrist_UART_UART_RX)
#define Wrist_UART_UART_TX_PIN_ENABLE    (Wrist_UART_UART_TX)

/* UART RTS and CTS position to be used in  Wrist_UART_SetPins() */
#define Wrist_UART_UART_RTS_PIN_ENABLE    (0x10u)
#define Wrist_UART_UART_CTS_PIN_ENABLE    (0x20u)

#endif /* (CY_SCB_SPI_UART_PVT_Wrist_UART_H) */


/* [] END OF FILE */
