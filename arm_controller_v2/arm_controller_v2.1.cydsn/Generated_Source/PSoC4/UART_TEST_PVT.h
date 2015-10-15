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

#if !defined(CY_SCB_PVT_UART_TEST_H)
#define CY_SCB_PVT_UART_TEST_H

#include "UART_TEST.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_TEST_SetI2CExtClkInterruptMode(interruptMask) UART_TEST_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_TEST_ClearI2CExtClkInterruptSource(interruptMask) UART_TEST_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_TEST_GetI2CExtClkInterruptSource()                (UART_TEST_INTR_I2C_EC_REG)
#define UART_TEST_GetI2CExtClkInterruptMode()                  (UART_TEST_INTR_I2C_EC_MASK_REG)
#define UART_TEST_GetI2CExtClkInterruptSourceMasked()          (UART_TEST_INTR_I2C_EC_MASKED_REG)

#if (!UART_TEST_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_TEST_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_TEST_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_TEST_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_TEST_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_TEST_GetExtSpiClkInterruptSource()                 (UART_TEST_INTR_SPI_EC_REG)
    #define UART_TEST_GetExtSpiClkInterruptMode()                   (UART_TEST_INTR_SPI_EC_MASK_REG)
    #define UART_TEST_GetExtSpiClkInterruptSourceMasked()           (UART_TEST_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_TEST_CY_SCBIP_V1) */

#if(UART_TEST_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_TEST_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_TEST_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if !defined (CY_REMOVE_UART_TEST_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_TEST_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_TEST_CUSTOM_INTR_HANDLER) */

extern UART_TEST_BACKUP_STRUCT UART_TEST_backup;

#if(UART_TEST_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_TEST_scbMode;
    extern uint8 UART_TEST_scbEnableWake;
    extern uint8 UART_TEST_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_TEST_mode;
    extern uint8 UART_TEST_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_TEST_rxBuffer;
    extern uint8   UART_TEST_rxDataBits;
    extern uint32  UART_TEST_rxBufferSize;

    extern volatile uint8 * UART_TEST_txBuffer;
    extern uint8   UART_TEST_txDataBits;
    extern uint32  UART_TEST_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_TEST_numberOfAddr;
    extern uint8 UART_TEST_subAddrSize;
#endif /* (UART_TEST_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_TEST_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_TEST_SCB_MODE_I2C_RUNTM_CFG     (UART_TEST_SCB_MODE_I2C      == UART_TEST_scbMode)
    #define UART_TEST_SCB_MODE_SPI_RUNTM_CFG     (UART_TEST_SCB_MODE_SPI      == UART_TEST_scbMode)
    #define UART_TEST_SCB_MODE_UART_RUNTM_CFG    (UART_TEST_SCB_MODE_UART     == UART_TEST_scbMode)
    #define UART_TEST_SCB_MODE_EZI2C_RUNTM_CFG   (UART_TEST_SCB_MODE_EZI2C    == UART_TEST_scbMode)
    #define UART_TEST_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_TEST_SCB_MODE_UNCONFIG == UART_TEST_scbMode)

    /* Defines wakeup enable */
    #define UART_TEST_SCB_WAKE_ENABLE_CHECK       (0u != UART_TEST_scbEnableWake)
#endif /* (UART_TEST_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_TEST_CY_SCBIP_V1)
    #define UART_TEST_SCB_PINS_NUMBER    (7u)
#else
    #define UART_TEST_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_TEST_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_TEST_H) */


/* [] END OF FILE */
