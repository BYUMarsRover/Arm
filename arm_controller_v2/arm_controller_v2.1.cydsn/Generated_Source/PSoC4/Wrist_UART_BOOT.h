/*******************************************************************************
* File Name: Wrist_UART_BOOT.h
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

#if !defined(CY_SCB_BOOT_Wrist_UART_H)
#define CY_SCB_BOOT_Wrist_UART_H

#include "Wrist_UART_PVT.h"

#if (Wrist_UART_SCB_MODE_I2C_INC)
    #include "Wrist_UART_I2C.h"
#endif /* (Wrist_UART_SCB_MODE_I2C_INC) */

#if (Wrist_UART_SCB_MODE_EZI2C_INC)
    #include "Wrist_UART_EZI2C.h"
#endif /* (Wrist_UART_SCB_MODE_EZI2C_INC) */

#if (Wrist_UART_SCB_MODE_SPI_INC || Wrist_UART_SCB_MODE_UART_INC)
    #include "Wrist_UART_SPI_UART.h"
#endif /* (Wrist_UART_SCB_MODE_SPI_INC || Wrist_UART_SCB_MODE_UART_INC) */


/***************************************
*        Function Prototypes
***************************************/

/* Bootloader communication interface enable */
#define Wrist_UART_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Wrist_UART) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#if (Wrist_UART_SCB_MODE_I2C_INC)

    #define Wrist_UART_I2C_BTLDR_COMM_ENABLED     (Wrist_UART_BTLDR_COMM_ENABLED && \
                                                            (Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             Wrist_UART_I2C_SLAVE_CONST))

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Wrist_UART_I2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void Wrist_UART_I2CCyBtldrCommStart(void);
    void Wrist_UART_I2CCyBtldrCommStop (void);
    void Wrist_UART_I2CCyBtldrCommReset(void);
    cystatus Wrist_UART_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Wrist_UART_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Size of Read/Write buffers for I2C bootloader  */
    #define Wrist_UART_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
    #define Wrist_UART_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)
    #define Wrist_UART_I2C_MIN_UINT16(a, b)           ( ((uint16)(a) < (uint16) (b)) ? \
                                                                    ((uint32) (a)) : ((uint32) (b)) )
    #define Wrist_UART_WAIT_1_MS                      (1u)
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Wrist_UART_I2C_BTLDR_COMM_ENABLED) */

#endif /* (Wrist_UART_SCB_MODE_I2C_INC) */


#if (Wrist_UART_SCB_MODE_EZI2C_INC)

    /* Provide EMPTY bootloader communication functions. EZI2C is NOT supported yet */
    #define Wrist_UART_EZI2C_BTLDR_COMM_ENABLED   (Wrist_UART_BTLDR_COMM_ENABLED && \
                                                         Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Wrist_UART_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void Wrist_UART_EzI2CCyBtldrCommStart(void);
    void Wrist_UART_EzI2CCyBtldrCommStop (void);
    void Wrist_UART_EzI2CCyBtldrCommReset(void);
    cystatus Wrist_UART_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Wrist_UART_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Wrist_UART_EZI2C_BTLDR_COMM_ENABLED) */

#endif /* (Wrist_UART_SCB_MODE_EZI2C_INC) */

#if (Wrist_UART_SCB_MODE_SPI_INC || Wrist_UART_SCB_MODE_UART_INC)
    /* Provide EMPTY bootloader communication functions. SPI and UART is NOT supported yet */
    #define Wrist_UART_SPI_BTLDR_COMM_ENABLED     (Wrist_UART_BTLDR_COMM_ENABLED && \
                                                        Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    #define Wrist_UART_UART_BTLDR_COMM_ENABLED    (Wrist_UART_BTLDR_COMM_ENABLED && \
                                                        Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Wrist_UART_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void Wrist_UART_SpiCyBtldrCommStart(void);
    void Wrist_UART_SpiCyBtldrCommStop (void);
    void Wrist_UART_SpiCyBtldrCommReset(void);
    cystatus Wrist_UART_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Wrist_UART_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Wrist_UART_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Wrist_UART_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void Wrist_UART_UartCyBtldrCommStart(void);
    void Wrist_UART_UartCyBtldrCommStop (void);
    void Wrist_UART_UartCyBtldrCommReset(void);
    cystatus Wrist_UART_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Wrist_UART_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Wrist_UART_UART_BTLDR_COMM_ENABLED) */

#endif /* (Wrist_UART_SCB_MODE_SPI_INC || Wrist_UART_SCB_MODE_UART_INC) */

#if !defined (Wrist_UART_I2C_BTLDR_COMM_ENABLED)
    #define Wrist_UART_I2C_BTLDR_COMM_ENABLED     (0u)
#endif /* (Wrist_UART_I2C_BTLDR_COMM_ENABLED) */

#if !defined (Wrist_UART_EZI2C_BTLDR_COMM_ENABLED)
    #define Wrist_UART_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (Wrist_UART_EZI2C_BTLDR_COMM_ENABLED) */

#if !defined (Wrist_UART_SPI_BTLDR_COMM_ENABLED)
    #define Wrist_UART_SPI_BTLDR_COMM_ENABLED     (0u)
#endif /* (Wrist_UART_SPI_BTLDR_COMM_ENABLED) */

#if !defined (Wrist_UART_UART_BTLDR_COMM_ENABLED)
    #define Wrist_UART_UART_BTLDR_COMM_ENABLED    (0u)
#endif /* (Wrist_UART_UART_BTLDR_COMM_ENABLED) */

/* Bootloader enabled condition for each mode */
#define Wrist_UART_BTLDR_COMM_MODE_ENABLED    (Wrist_UART_I2C_BTLDR_COMM_ENABLED   || \
                                                     Wrist_UART_EZI2C_BTLDR_COMM_ENABLED || \
                                                     Wrist_UART_SPI_BTLDR_COMM_ENABLED   || \
                                                     Wrist_UART_UART_BTLDR_COMM_ENABLED)

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Wrist_UART_BTLDR_COMM_ENABLED)
    #if (Wrist_UART_BTLDR_COMM_MODE_ENABLED)
        /* Bootloader physical layer functions */
        void Wrist_UART_CyBtldrCommStart(void);
        void Wrist_UART_CyBtldrCommStop (void);
        void Wrist_UART_CyBtldrCommReset(void);
        cystatus Wrist_UART_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus Wrist_UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (Wrist_UART_BTLDR_COMM_MODE_ENABLED) */

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Wrist_UART)
        #define CyBtldrCommStart    Wrist_UART_CyBtldrCommStart
        #define CyBtldrCommStop     Wrist_UART_CyBtldrCommStop
        #define CyBtldrCommReset    Wrist_UART_CyBtldrCommReset
        #define CyBtldrCommWrite    Wrist_UART_CyBtldrCommWrite
        #define CyBtldrCommRead     Wrist_UART_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Wrist_UART) */
#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Wrist_UART_BTLDR_COMM_ENABLED) */

#endif /* (CY_SCB_BOOT_Wrist_UART_H) */

/* [] END OF FILE */
