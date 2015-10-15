/*******************************************************************************
* File Name: Arduino_UART_PINS.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_Arduino_UART_H)
#define CY_SCB_PINS_Arduino_UART_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define Arduino_UART_REMOVE_MOSI_SCL_RX_WAKE_PIN    (1u)
#define Arduino_UART_REMOVE_MOSI_SCL_RX_PIN         (1u)
#define Arduino_UART_REMOVE_MISO_SDA_TX_PIN         (1u)
#define Arduino_UART_REMOVE_SCLK_PIN                (1u)
#define Arduino_UART_REMOVE_SS0_PIN                 (1u)
#define Arduino_UART_REMOVE_SS1_PIN                 (1u)
#define Arduino_UART_REMOVE_SS2_PIN                 (1u)
#define Arduino_UART_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define Arduino_UART_REMOVE_I2C_PINS                (1u)
#define Arduino_UART_REMOVE_SPI_MASTER_PINS         (1u)
#define Arduino_UART_REMOVE_SPI_SLAVE_PINS          (1u)
#define Arduino_UART_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define Arduino_UART_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define Arduino_UART_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define Arduino_UART_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define Arduino_UART_REMOVE_UART_TX_PIN             (0u)
#define Arduino_UART_REMOVE_UART_RX_TX_PIN          (1u)
#define Arduino_UART_REMOVE_UART_RX_PIN             (0u)
#define Arduino_UART_REMOVE_UART_RX_WAKE_PIN        (1u)
#define Arduino_UART_REMOVE_UART_RTS_PIN            (1u)
#define Arduino_UART_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define Arduino_UART_MOSI_SCL_RX_WAKE_PIN   (0u == Arduino_UART_REMOVE_MOSI_SCL_RX_WAKE_PIN)
#define Arduino_UART_MOSI_SCL_RX_PIN        (0u == Arduino_UART_REMOVE_MOSI_SCL_RX_PIN)
#define Arduino_UART_MISO_SDA_TX_PIN        (0u == Arduino_UART_REMOVE_MISO_SDA_TX_PIN)
#define Arduino_UART_SCLK_PIN               (0u == Arduino_UART_REMOVE_SCLK_PIN)
#define Arduino_UART_SS0_PIN                (0u == Arduino_UART_REMOVE_SS0_PIN)
#define Arduino_UART_SS1_PIN                (0u == Arduino_UART_REMOVE_SS1_PIN)
#define Arduino_UART_SS2_PIN                (0u == Arduino_UART_REMOVE_SS2_PIN)
#define Arduino_UART_SS3_PIN                (0u == Arduino_UART_REMOVE_SS3_PIN)

/* Mode defined pins */
#define Arduino_UART_I2C_PINS               (0u == Arduino_UART_REMOVE_I2C_PINS)
#define Arduino_UART_SPI_MASTER_PINS        (0u == Arduino_UART_REMOVE_SPI_MASTER_PINS)
#define Arduino_UART_SPI_SLAVE_PINS         (0u == Arduino_UART_REMOVE_SPI_SLAVE_PINS)
#define Arduino_UART_SPI_MASTER_SS0_PIN     (0u == Arduino_UART_REMOVE_SPI_MASTER_SS0_PIN)
#define Arduino_UART_SPI_MASTER_SS1_PIN     (0u == Arduino_UART_REMOVE_SPI_MASTER_SS1_PIN)
#define Arduino_UART_SPI_MASTER_SS2_PIN     (0u == Arduino_UART_REMOVE_SPI_MASTER_SS2_PIN)
#define Arduino_UART_SPI_MASTER_SS3_PIN     (0u == Arduino_UART_REMOVE_SPI_MASTER_SS3_PIN)
#define Arduino_UART_UART_TX_PIN            (0u == Arduino_UART_REMOVE_UART_TX_PIN)
#define Arduino_UART_UART_RX_TX_PIN         (0u == Arduino_UART_REMOVE_UART_RX_TX_PIN)
#define Arduino_UART_UART_RX_PIN            (0u == Arduino_UART_REMOVE_UART_RX_PIN)
#define Arduino_UART_UART_RX_WAKE_PIN       (0u == Arduino_UART_REMOVE_UART_RX_WAKE_PIN)
#define Arduino_UART_UART_RTS_PIN           (0u == Arduino_UART_REMOVE_UART_RTS_PIN)
#define Arduino_UART_UART_CTS_PIN           (0u == Arduino_UART_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if(Arduino_UART_MOSI_SCL_RX_WAKE_PIN)
    #include "Arduino_UART_spi_mosi_i2c_scl_uart_rx_wake.h"
#endif /* (Arduino_UART_MOSI_SCL_RX_WAKE_PIN) */

#if(Arduino_UART_MOSI_SCL_RX_PIN)
    #include "Arduino_UART_spi_mosi_i2c_scl_uart_rx.h"
#endif /* (Arduino_UART_MOSI_SCL_RX_PIN) */

#if(Arduino_UART_MISO_SDA_TX_PIN)
    #include "Arduino_UART_spi_miso_i2c_sda_uart_tx.h"
#endif /* (Arduino_UART_MISO_SDA_TX_PIN_PIN) */

#if(Arduino_UART_SCLK_PIN)
    #include "Arduino_UART_spi_sclk.h"
#endif /* (Arduino_UART_SCLK_PIN) */

#if(Arduino_UART_SS0_PIN)
    #include "Arduino_UART_spi_ss0.h"
#endif /* (Arduino_UART_SS1_PIN) */

#if(Arduino_UART_SS1_PIN)
    #include "Arduino_UART_spi_ss1.h"
#endif /* (Arduino_UART_SS1_PIN) */

#if(Arduino_UART_SS2_PIN)
    #include "Arduino_UART_spi_ss2.h"
#endif /* (Arduino_UART_SS2_PIN) */

#if(Arduino_UART_SS3_PIN)
    #include "Arduino_UART_spi_ss3.h"
#endif /* (Arduino_UART_SS3_PIN) */

#if(Arduino_UART_I2C_PINS)
    #include "Arduino_UART_scl.h"
    #include "Arduino_UART_sda.h"
#endif /* (Arduino_UART_I2C_PINS) */

#if(Arduino_UART_SPI_MASTER_PINS)
    #include "Arduino_UART_sclk_m.h"
    #include "Arduino_UART_mosi_m.h"
    #include "Arduino_UART_miso_m.h"
#endif /* (Arduino_UART_SPI_MASTER_PINS) */

#if(Arduino_UART_SPI_SLAVE_PINS)
    #include "Arduino_UART_sclk_s.h"
    #include "Arduino_UART_mosi_s.h"
    #include "Arduino_UART_miso_s.h"
    #include "Arduino_UART_ss_s.h"
#endif /* (Arduino_UART_SPI_SLAVE_PINS) */

#if(Arduino_UART_SPI_MASTER_SS0_PIN)
    #include "Arduino_UART_ss0_m.h"
#endif /* (Arduino_UART_SPI_MASTER_SS0_PIN) */

#if(Arduino_UART_SPI_MASTER_SS1_PIN)
    #include "Arduino_UART_ss1_m.h"
#endif /* (Arduino_UART_SPI_MASTER_SS1_PIN) */

#if(Arduino_UART_SPI_MASTER_SS2_PIN)
    #include "Arduino_UART_ss2_m.h"
#endif /* (Arduino_UART_SPI_MASTER_SS2_PIN) */

#if(Arduino_UART_SPI_MASTER_SS3_PIN)
    #include "Arduino_UART_ss3_m.h"
#endif /* (Arduino_UART_SPI_MASTER_SS3_PIN) */

#if(Arduino_UART_UART_TX_PIN)
    #include "Arduino_UART_tx.h"
#endif /* (Arduino_UART_UART_TX_PIN) */

#if(Arduino_UART_UART_RX_TX_PIN)
    #include "Arduino_UART_rx_tx.h"
#endif /* (Arduino_UART_UART_RX_TX_PIN) */

#if(Arduino_UART_UART_RX_PIN)
    #include "Arduino_UART_rx.h"
#endif /* (Arduino_UART_UART_RX_PIN) */

#if(Arduino_UART_UART_RX_WAKE_PIN)
    #include "Arduino_UART_rx_wake.h"
#endif /* (Arduino_UART_UART_RX_WAKE_PIN) */

#if(Arduino_UART_UART_RTS_PIN)
    #include "Arduino_UART_rts.h"
#endif /* (Arduino_UART_UART_RTS_PIN) */

#if(Arduino_UART_UART_CTS_PIN)
    #include "Arduino_UART_cts.h"
#endif /* (Arduino_UART_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if(Arduino_UART_MOSI_SCL_RX_WAKE_PIN)
    #define Arduino_UART_MOSI_SCL_RX_WAKE_HSIOM_REG  \
                                                (*(reg32 *) Arduino_UART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define Arduino_UART_MOSI_SCL_RX_WAKE_HSIOM_PTR  \
                                                ( (reg32 *) Arduino_UART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define Arduino_UART_MOSI_SCL_RX_WAKE_HSIOM_MASK \
                                                (Arduino_UART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_MASK)
    #define Arduino_UART_MOSI_SCL_RX_WAKE_HSIOM_POS  \
                                                (Arduino_UART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_SHIFT)

    #define Arduino_UART_MOSI_SCL_RX_WAKE_INTCFG_REG    (*(reg32 *) \
                                                              Arduino_UART_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)
    #define Arduino_UART_MOSI_SCL_RX_WAKE_INTCFG_PTR    ( (reg32 *) \
                                                              Arduino_UART_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)

    #define Arduino_UART_INTCFG_TYPE_MASK                  (0x03u)
    #define Arduino_UART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS  (Arduino_UART_spi_mosi_i2c_scl_uart_rx_wake__SHIFT)
    #define Arduino_UART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK ((uint32)                                           \
                                                                    ((uint32) Arduino_UART_INTCFG_TYPE_MASK << \
                                                                    Arduino_UART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS))
#endif /* (Arduino_UART_MOSI_SCL_RX_WAKE_PIN) */

#if(Arduino_UART_MOSI_SCL_RX_PIN)
    #define Arduino_UART_MOSI_SCL_RX_HSIOM_REG      (*(reg32 *) Arduino_UART_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define Arduino_UART_MOSI_SCL_RX_HSIOM_PTR      ( (reg32 *) Arduino_UART_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define Arduino_UART_MOSI_SCL_RX_HSIOM_MASK     (Arduino_UART_spi_mosi_i2c_scl_uart_rx__0__HSIOM_MASK)
    #define Arduino_UART_MOSI_SCL_RX_HSIOM_POS      (Arduino_UART_spi_mosi_i2c_scl_uart_rx__0__HSIOM_SHIFT)
#endif /* (Arduino_UART_MOSI_SCL_RX_PIN) */

#if(Arduino_UART_MISO_SDA_TX_PIN)
    #define Arduino_UART_MISO_SDA_TX_HSIOM_REG      (*(reg32 *) Arduino_UART_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define Arduino_UART_MISO_SDA_TX_HSIOM_PTR      ( (reg32 *) Arduino_UART_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define Arduino_UART_MISO_SDA_TX_HSIOM_MASK     (Arduino_UART_spi_miso_i2c_sda_uart_tx__0__HSIOM_MASK)
    #define Arduino_UART_MISO_SDA_TX_HSIOM_POS      (Arduino_UART_spi_miso_i2c_sda_uart_tx__0__HSIOM_SHIFT)
#endif /* (Arduino_UART_MISO_SDA_TX_PIN_PIN) */

#if(Arduino_UART_SCLK_PIN)
    #define Arduino_UART_SCLK_HSIOM_REG     (*(reg32 *) Arduino_UART_spi_sclk__0__HSIOM)
    #define Arduino_UART_SCLK_HSIOM_PTR     ( (reg32 *) Arduino_UART_spi_sclk__0__HSIOM)
    #define Arduino_UART_SCLK_HSIOM_MASK    (Arduino_UART_spi_sclk__0__HSIOM_MASK)
    #define Arduino_UART_SCLK_HSIOM_POS     (Arduino_UART_spi_sclk__0__HSIOM_SHIFT)
#endif /* (Arduino_UART_SCLK_PIN) */

#if(Arduino_UART_SS0_PIN)
    #define Arduino_UART_SS0_HSIOM_REG      (*(reg32 *) Arduino_UART_spi_ss0__0__HSIOM)
    #define Arduino_UART_SS0_HSIOM_PTR      ( (reg32 *) Arduino_UART_spi_ss0__0__HSIOM)
    #define Arduino_UART_SS0_HSIOM_MASK     (Arduino_UART_spi_ss0__0__HSIOM_MASK)
    #define Arduino_UART_SS0_HSIOM_POS      (Arduino_UART_spi_ss0__0__HSIOM_SHIFT)
#endif /* (Arduino_UART_SS1_PIN) */

#if(Arduino_UART_SS1_PIN)
    #define Arduino_UART_SS1_HSIOM_REG      (*(reg32 *) Arduino_UART_spi_ss1__0__HSIOM)
    #define Arduino_UART_SS1_HSIOM_PTR      ( (reg32 *) Arduino_UART_spi_ss1__0__HSIOM)
    #define Arduino_UART_SS1_HSIOM_MASK     (Arduino_UART_spi_ss1__0__HSIOM_MASK)
    #define Arduino_UART_SS1_HSIOM_POS      (Arduino_UART_spi_ss1__0__HSIOM_SHIFT)
#endif /* (Arduino_UART_SS1_PIN) */

#if(Arduino_UART_SS2_PIN)
    #define Arduino_UART_SS2_HSIOM_REG     (*(reg32 *) Arduino_UART_spi_ss2__0__HSIOM)
    #define Arduino_UART_SS2_HSIOM_PTR     ( (reg32 *) Arduino_UART_spi_ss2__0__HSIOM)
    #define Arduino_UART_SS2_HSIOM_MASK    (Arduino_UART_spi_ss2__0__HSIOM_MASK)
    #define Arduino_UART_SS2_HSIOM_POS     (Arduino_UART_spi_ss2__0__HSIOM_SHIFT)
#endif /* (Arduino_UART_SS2_PIN) */

#if(Arduino_UART_SS3_PIN)
    #define Arduino_UART_SS3_HSIOM_REG     (*(reg32 *) Arduino_UART_spi_ss3__0__HSIOM)
    #define Arduino_UART_SS3_HSIOM_PTR     ( (reg32 *) Arduino_UART_spi_ss3__0__HSIOM)
    #define Arduino_UART_SS3_HSIOM_MASK    (Arduino_UART_spi_ss3__0__HSIOM_MASK)
    #define Arduino_UART_SS3_HSIOM_POS     (Arduino_UART_spi_ss3__0__HSIOM_SHIFT)
#endif /* (Arduino_UART_SS3_PIN) */

#if(Arduino_UART_I2C_PINS)
    #define Arduino_UART_SCL_HSIOM_REG     (*(reg32 *) Arduino_UART_scl__0__HSIOM)
    #define Arduino_UART_SCL_HSIOM_PTR     ( (reg32 *) Arduino_UART_scl__0__HSIOM)
    #define Arduino_UART_SCL_HSIOM_MASK    (Arduino_UART_scl__0__HSIOM_MASK)
    #define Arduino_UART_SCL_HSIOM_POS     (Arduino_UART_scl__0__HSIOM_SHIFT)

    #define Arduino_UART_SDA_HSIOM_REG     (*(reg32 *) Arduino_UART_sda__0__HSIOM)
    #define Arduino_UART_SDA_HSIOM_PTR     ( (reg32 *) Arduino_UART_sda__0__HSIOM)
    #define Arduino_UART_SDA_HSIOM_MASK    (Arduino_UART_sda__0__HSIOM_MASK)
    #define Arduino_UART_SDA_HSIOM_POS     (Arduino_UART_sda__0__HSIOM_SHIFT)
#endif /* (Arduino_UART_I2C_PINS) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define Arduino_UART_HSIOM_DEF_SEL      (0x00u)
#define Arduino_UART_HSIOM_GPIO_SEL     (0x00u)
#define Arduino_UART_HSIOM_UART_SEL     (0x09u)
#define Arduino_UART_HSIOM_I2C_SEL      (0x0Eu)
#define Arduino_UART_HSIOM_SPI_SEL      (0x0Fu)

#define Arduino_UART_MOSI_SCL_RX_PIN_INDEX      (0u) /* RX pins without interrupt */
#define Arduino_UART_MOSI_SCL_RX_WAKE_PIN_INDEX (0u) /* RX pin with interrupt     */
#define Arduino_UART_MISO_SDA_TX_PIN_INDEX      (1u)
#define Arduino_UART_SCLK_PIN_INDEX             (2u)
#define Arduino_UART_SS0_PIN_INDEX              (3u)
#define Arduino_UART_SS1_PIN_INDEX              (4u)
#define Arduino_UART_SS2_PIN_INDEX              (5u)
#define Arduino_UART_SS3_PIN_INDEX              (6u)

#define Arduino_UART_MOSI_SCL_RX_PIN_MASK      ((uint32) 0x01u << Arduino_UART_MOSI_SCL_RX_PIN_INDEX)
#define Arduino_UART_MOSI_SCL_RX_WAKE_PIN_MASK ((uint32) 0x01u << Arduino_UART_MOSI_SCL_RX_WAKE_PIN_INDEX)
#define Arduino_UART_MISO_SDA_TX_PIN_MASK      ((uint32) 0x01u << Arduino_UART_MISO_SDA_TX_PIN_INDEX)
#define Arduino_UART_SCLK_PIN_MASK             ((uint32) 0x01u << Arduino_UART_SCLK_PIN_INDEX)
#define Arduino_UART_SS0_PIN_MASK              ((uint32) 0x01u << Arduino_UART_SS0_PIN_INDEX)
#define Arduino_UART_SS1_PIN_MASK              ((uint32) 0x01u << Arduino_UART_SS1_PIN_INDEX)
#define Arduino_UART_SS2_PIN_MASK              ((uint32) 0x01u << Arduino_UART_SS2_PIN_INDEX)
#define Arduino_UART_SS3_PIN_MASK              ((uint32) 0x01u << Arduino_UART_SS3_PIN_INDEX)

#define Arduino_UART_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin DM defines */
#define Arduino_UART_PIN_DM_ALG_HIZ  (0u)
#define Arduino_UART_PIN_DM_DIG_HIZ  (1u)
#define Arduino_UART_PIN_DM_OD_LO    (4u)
#define Arduino_UART_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Set bits-mask in register */
#define Arduino_UART_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define Arduino_UART_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define Arduino_UART_SET_HSIOM_SEL(reg, mask, pos, sel) Arduino_UART_SET_REGISTER_BITS(reg, mask, pos, sel)
#define Arduino_UART_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        Arduino_UART_SET_REGISTER_BITS(reg, mask, pos, intType)
#define Arduino_UART_SET_INP_DIS(reg, mask, val) Arduino_UART_SET_REGISTER_BIT(reg, mask, val)

/* Arduino_UART_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  Arduino_UART_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if(Arduino_UART_I2C_PINS)
    #define Arduino_UART_SET_I2C_SCL_DR(val) Arduino_UART_scl_Write(val)

    #define Arduino_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                          Arduino_UART_SET_HSIOM_SEL(Arduino_UART_SCL_HSIOM_REG,  \
                                                         Arduino_UART_SCL_HSIOM_MASK, \
                                                         Arduino_UART_SCL_HSIOM_POS,  \
                                                         (sel))
    #define Arduino_UART_WAIT_SCL_SET_HIGH  (0u == Arduino_UART_scl_Read())

/* Unconfigured SCB: scl signal */
#elif(Arduino_UART_MOSI_SCL_RX_WAKE_PIN)
    #define Arduino_UART_SET_I2C_SCL_DR(val) \
                            Arduino_UART_spi_mosi_i2c_scl_uart_rx_wake_Write(val)

    #define Arduino_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                    Arduino_UART_SET_HSIOM_SEL(Arduino_UART_MOSI_SCL_RX_WAKE_HSIOM_REG,  \
                                                   Arduino_UART_MOSI_SCL_RX_WAKE_HSIOM_MASK, \
                                                   Arduino_UART_MOSI_SCL_RX_WAKE_HSIOM_POS,  \
                                                   (sel))

    #define Arduino_UART_WAIT_SCL_SET_HIGH  (0u == Arduino_UART_spi_mosi_i2c_scl_uart_rx_wake_Read())

#elif(Arduino_UART_MOSI_SCL_RX_PIN)
    #define Arduino_UART_SET_I2C_SCL_DR(val) \
                            Arduino_UART_spi_mosi_i2c_scl_uart_rx_Write(val)


    #define Arduino_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                            Arduino_UART_SET_HSIOM_SEL(Arduino_UART_MOSI_SCL_RX_HSIOM_REG,  \
                                                           Arduino_UART_MOSI_SCL_RX_HSIOM_MASK, \
                                                           Arduino_UART_MOSI_SCL_RX_HSIOM_POS,  \
                                                           (sel))

    #define Arduino_UART_WAIT_SCL_SET_HIGH  (0u == Arduino_UART_spi_mosi_i2c_scl_uart_rx_Read())

#else
    #define Arduino_UART_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define Arduino_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define Arduino_UART_WAIT_SCL_SET_HIGH  (0u)
#endif /* (Arduino_UART_MOSI_SCL_RX_PIN) */

/* SCB I2C: sda signal */
#if(Arduino_UART_I2C_PINS)
    #define Arduino_UART_WAIT_SDA_SET_HIGH  (0u == Arduino_UART_sda_Read())

/* Unconfigured SCB: sda signal */
#elif(Arduino_UART_MISO_SDA_TX_PIN)
    #define Arduino_UART_WAIT_SDA_SET_HIGH  (0u == Arduino_UART_spi_miso_i2c_sda_uart_tx_Read())

#else
    #define Arduino_UART_WAIT_SDA_SET_HIGH  (0u)
#endif /* (Arduino_UART_MOSI_SCL_RX_PIN) */

#endif /* (CY_SCB_PINS_Arduino_UART_H) */


/* [] END OF FILE */
