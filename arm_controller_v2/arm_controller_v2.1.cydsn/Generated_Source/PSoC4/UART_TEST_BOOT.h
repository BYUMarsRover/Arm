/*******************************************************************************
* File Name: UART_TEST_BOOT.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the bootloader
*  communication interface of SCB component.
*
* Note:
*
********************************************************************************
* Copyright 2014, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_UART_TEST_H)
#define CY_SCB_BOOT_UART_TEST_H

#include "UART_TEST_PVT.h"

#if (UART_TEST_SCB_MODE_I2C_INC)
    #include "UART_TEST_I2C.h"
#endif /* (UART_TEST_SCB_MODE_I2C_INC) */

#if (UART_TEST_SCB_MODE_EZI2C_INC)
    #include "UART_TEST_EZI2C.h"
#endif /* (UART_TEST_SCB_MODE_EZI2C_INC) */

#if (UART_TEST_SCB_MODE_SPI_INC || UART_TEST_SCB_MODE_UART_INC)
    #include "UART_TEST_SPI_UART.h"
#endif /* (UART_TEST_SCB_MODE_SPI_INC || UART_TEST_SCB_MODE_UART_INC) */


/***************************************
*        Function Prototypes
***************************************/

/* Bootloader communication interface enable */
#define UART_TEST_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_TEST) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#if (UART_TEST_SCB_MODE_I2C_INC)

    #define UART_TEST_I2C_BTLDR_COMM_ENABLED     (UART_TEST_BTLDR_COMM_ENABLED && \
                                                            (UART_TEST_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UART_TEST_I2C_SLAVE_CONST))

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_TEST_I2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void UART_TEST_I2CCyBtldrCommStart(void);
    void UART_TEST_I2CCyBtldrCommStop (void);
    void UART_TEST_I2CCyBtldrCommReset(void);
    cystatus UART_TEST_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_TEST_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Size of Read/Write buffers for I2C bootloader  */
    #define UART_TEST_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
    #define UART_TEST_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)
    #define UART_TEST_I2C_MIN_UINT16(a, b)           ( ((uint16)(a) < (uint16) (b)) ? \
                                                                    ((uint32) (a)) : ((uint32) (b)) )
    #define UART_TEST_WAIT_1_MS                      (1u)
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_TEST_I2C_BTLDR_COMM_ENABLED) */

#endif /* (UART_TEST_SCB_MODE_I2C_INC) */


#if (UART_TEST_SCB_MODE_EZI2C_INC)

    /* Provide EMPTY bootloader communication functions. EZI2C is NOT supported yet */
    #define UART_TEST_EZI2C_BTLDR_COMM_ENABLED   (UART_TEST_BTLDR_COMM_ENABLED && \
                                                         UART_TEST_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_TEST_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void UART_TEST_EzI2CCyBtldrCommStart(void);
    void UART_TEST_EzI2CCyBtldrCommStop (void);
    void UART_TEST_EzI2CCyBtldrCommReset(void);
    cystatus UART_TEST_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_TEST_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_TEST_EZI2C_BTLDR_COMM_ENABLED) */

#endif /* (UART_TEST_SCB_MODE_EZI2C_INC) */

#if (UART_TEST_SCB_MODE_SPI_INC || UART_TEST_SCB_MODE_UART_INC)
    /* Provide EMPTY bootloader communication functions. SPI and UART is NOT supported yet */
    #define UART_TEST_SPI_BTLDR_COMM_ENABLED     (UART_TEST_BTLDR_COMM_ENABLED && \
                                                        UART_TEST_SCB_MODE_UNCONFIG_CONST_CFG)

    #define UART_TEST_UART_BTLDR_COMM_ENABLED    (UART_TEST_BTLDR_COMM_ENABLED && \
                                                        UART_TEST_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_TEST_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void UART_TEST_SpiCyBtldrCommStart(void);
    void UART_TEST_SpiCyBtldrCommStop (void);
    void UART_TEST_SpiCyBtldrCommReset(void);
    cystatus UART_TEST_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_TEST_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_TEST_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_TEST_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void UART_TEST_UartCyBtldrCommStart(void);
    void UART_TEST_UartCyBtldrCommStop (void);
    void UART_TEST_UartCyBtldrCommReset(void);
    cystatus UART_TEST_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_TEST_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_TEST_UART_BTLDR_COMM_ENABLED) */

#endif /* (UART_TEST_SCB_MODE_SPI_INC || UART_TEST_SCB_MODE_UART_INC) */

#if !defined (UART_TEST_I2C_BTLDR_COMM_ENABLED)
    #define UART_TEST_I2C_BTLDR_COMM_ENABLED     (0u)
#endif /* (UART_TEST_I2C_BTLDR_COMM_ENABLED) */

#if !defined (UART_TEST_EZI2C_BTLDR_COMM_ENABLED)
    #define UART_TEST_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (UART_TEST_EZI2C_BTLDR_COMM_ENABLED) */

#if !defined (UART_TEST_SPI_BTLDR_COMM_ENABLED)
    #define UART_TEST_SPI_BTLDR_COMM_ENABLED     (0u)
#endif /* (UART_TEST_SPI_BTLDR_COMM_ENABLED) */

#if !defined (UART_TEST_UART_BTLDR_COMM_ENABLED)
    #define UART_TEST_UART_BTLDR_COMM_ENABLED    (0u)
#endif /* (UART_TEST_UART_BTLDR_COMM_ENABLED) */

/* Bootloader enabled condition for each mode */
#define UART_TEST_BTLDR_COMM_MODE_ENABLED    (UART_TEST_I2C_BTLDR_COMM_ENABLED   || \
                                                     UART_TEST_EZI2C_BTLDR_COMM_ENABLED || \
                                                     UART_TEST_SPI_BTLDR_COMM_ENABLED   || \
                                                     UART_TEST_UART_BTLDR_COMM_ENABLED)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_TEST_BTLDR_COMM_ENABLED)
    #if (UART_TEST_BTLDR_COMM_MODE_ENABLED)
        /* Bootloader physical layer functions */
        void UART_TEST_CyBtldrCommStart(void);
        void UART_TEST_CyBtldrCommStop (void);
        void UART_TEST_CyBtldrCommReset(void);
        cystatus UART_TEST_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus UART_TEST_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (UART_TEST_BTLDR_COMM_MODE_ENABLED) */

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_TEST)
        #define CyBtldrCommStart    UART_TEST_CyBtldrCommStart
        #define CyBtldrCommStop     UART_TEST_CyBtldrCommStop
        #define CyBtldrCommReset    UART_TEST_CyBtldrCommReset
        #define CyBtldrCommWrite    UART_TEST_CyBtldrCommWrite
        #define CyBtldrCommRead     UART_TEST_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_TEST) */
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_TEST_BTLDR_COMM_ENABLED) */

#endif /* (CY_SCB_BOOT_UART_TEST_H) */

/* [] END OF FILE */
