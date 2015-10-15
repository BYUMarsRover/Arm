/*******************************************************************************
* File Name: Arduino_UART_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_Arduino_UART_H)
#define CY_SCB_SPI_UART_PVT_Arduino_UART_H

#include "Arduino_UART_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if(Arduino_UART_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  Arduino_UART_rxBufferHead;
    extern volatile uint32  Arduino_UART_rxBufferTail;
    extern volatile uint8   Arduino_UART_rxBufferOverflow;
#endif /* (Arduino_UART_INTERNAL_RX_SW_BUFFER_CONST) */

#if(Arduino_UART_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  Arduino_UART_txBufferHead;
    extern volatile uint32  Arduino_UART_txBufferTail;
#endif /* (Arduino_UART_INTERNAL_TX_SW_BUFFER_CONST) */

#if(Arduino_UART_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 Arduino_UART_rxBufferInternal[Arduino_UART_RX_BUFFER_SIZE];
#endif /* (Arduino_UART_INTERNAL_RX_SW_BUFFER) */

#if(Arduino_UART_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 Arduino_UART_txBufferInternal[Arduino_UART_TX_BUFFER_SIZE];
#endif /* (Arduino_UART_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(Arduino_UART_SCB_MODE_SPI_CONST_CFG)
    void Arduino_UART_SpiInit(void);
#endif /* (Arduino_UART_SCB_MODE_SPI_CONST_CFG) */

#if(Arduino_UART_SPI_WAKE_ENABLE_CONST)
    void Arduino_UART_SpiSaveConfig(void);
    void Arduino_UART_SpiRestoreConfig(void);
#endif /* (Arduino_UART_SPI_WAKE_ENABLE_CONST) */

#if(Arduino_UART_SCB_MODE_UART_CONST_CFG)
    void Arduino_UART_UartInit(void);
#endif /* (Arduino_UART_SCB_MODE_UART_CONST_CFG) */

#if(Arduino_UART_UART_WAKE_ENABLE_CONST)
    void Arduino_UART_UartSaveConfig(void);
    void Arduino_UART_UartRestoreConfig(void);
    #define Arduino_UART_UartStop() \
        do{                             \
            Arduino_UART_UART_RX_CTRL_REG &= ~Arduino_UART_UART_RX_CTRL_SKIP_START; \
        }while(0)
#else
        #define Arduino_UART_UartStop() do{ /* Does nothing */ }while(0)

#endif /* (Arduino_UART_UART_WAKE_ENABLE_CONST) */

/* Interrupt processing */
#define Arduino_UART_SpiUartEnableIntRx(intSourceMask)  Arduino_UART_SetRxInterruptMode(intSourceMask)
#define Arduino_UART_SpiUartEnableIntTx(intSourceMask)  Arduino_UART_SetTxInterruptMode(intSourceMask)
uint32  Arduino_UART_SpiUartDisableIntRx(void);
uint32  Arduino_UART_SpiUartDisableIntTx(void);


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in Arduino_UART_SetPins() */
#define Arduino_UART_UART_RX_PIN_ENABLE    (Arduino_UART_UART_RX)
#define Arduino_UART_UART_TX_PIN_ENABLE    (Arduino_UART_UART_TX)

/* UART RTS and CTS position to be used in  Arduino_UART_SetPins() */
#define Arduino_UART_UART_RTS_PIN_ENABLE    (0x10u)
#define Arduino_UART_UART_CTS_PIN_ENABLE    (0x20u)

#endif /* (CY_SCB_SPI_UART_PVT_Arduino_UART_H) */


/* [] END OF FILE */
