/*******************************************************************************
* File Name: .h
* Version 2.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
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

#if !defined(CY_SCB_PVT_Arduino_UART_H)
#define CY_SCB_PVT_Arduino_UART_H

#include "Arduino_UART.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define Arduino_UART_SetI2CExtClkInterruptMode(interruptMask) Arduino_UART_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define Arduino_UART_ClearI2CExtClkInterruptSource(interruptMask) Arduino_UART_CLEAR_INTR_I2C_EC(interruptMask)
#define Arduino_UART_GetI2CExtClkInterruptSource()                (Arduino_UART_INTR_I2C_EC_REG)
#define Arduino_UART_GetI2CExtClkInterruptMode()                  (Arduino_UART_INTR_I2C_EC_MASK_REG)
#define Arduino_UART_GetI2CExtClkInterruptSourceMasked()          (Arduino_UART_INTR_I2C_EC_MASKED_REG)

#if (!Arduino_UART_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define Arduino_UART_SetSpiExtClkInterruptMode(interruptMask) \
                                                                Arduino_UART_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define Arduino_UART_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                Arduino_UART_CLEAR_INTR_SPI_EC(interruptMask)
    #define Arduino_UART_GetExtSpiClkInterruptSource()                 (Arduino_UART_INTR_SPI_EC_REG)
    #define Arduino_UART_GetExtSpiClkInterruptMode()                   (Arduino_UART_INTR_SPI_EC_MASK_REG)
    #define Arduino_UART_GetExtSpiClkInterruptSourceMasked()           (Arduino_UART_INTR_SPI_EC_MASKED_REG)
#endif /* (!Arduino_UART_CY_SCBIP_V1) */

#if(Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void Arduino_UART_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if !defined (CY_REMOVE_Arduino_UART_CUSTOM_INTR_HANDLER)
    extern cyisraddress Arduino_UART_customIntrHandler;
#endif /* !defined (CY_REMOVE_Arduino_UART_CUSTOM_INTR_HANDLER) */

extern Arduino_UART_BACKUP_STRUCT Arduino_UART_backup;

#if(Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 Arduino_UART_scbMode;
    extern uint8 Arduino_UART_scbEnableWake;
    extern uint8 Arduino_UART_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 Arduino_UART_mode;
    extern uint8 Arduino_UART_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * Arduino_UART_rxBuffer;
    extern uint8   Arduino_UART_rxDataBits;
    extern uint32  Arduino_UART_rxBufferSize;

    extern volatile uint8 * Arduino_UART_txBuffer;
    extern uint8   Arduino_UART_txDataBits;
    extern uint32  Arduino_UART_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 Arduino_UART_numberOfAddr;
    extern uint8 Arduino_UART_subAddrSize;
#endif /* (Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define Arduino_UART_SCB_MODE_I2C_RUNTM_CFG     (Arduino_UART_SCB_MODE_I2C      == Arduino_UART_scbMode)
    #define Arduino_UART_SCB_MODE_SPI_RUNTM_CFG     (Arduino_UART_SCB_MODE_SPI      == Arduino_UART_scbMode)
    #define Arduino_UART_SCB_MODE_UART_RUNTM_CFG    (Arduino_UART_SCB_MODE_UART     == Arduino_UART_scbMode)
    #define Arduino_UART_SCB_MODE_EZI2C_RUNTM_CFG   (Arduino_UART_SCB_MODE_EZI2C    == Arduino_UART_scbMode)
    #define Arduino_UART_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (Arduino_UART_SCB_MODE_UNCONFIG == Arduino_UART_scbMode)

    /* Defines wakeup enable */
    #define Arduino_UART_SCB_WAKE_ENABLE_CHECK       (0u != Arduino_UART_scbEnableWake)
#endif /* (Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!Arduino_UART_CY_SCBIP_V1)
    #define Arduino_UART_SCB_PINS_NUMBER    (7u)
#else
    #define Arduino_UART_SCB_PINS_NUMBER    (2u)
#endif /* (!Arduino_UART_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_Arduino_UART_H) */


/* [] END OF FILE */
