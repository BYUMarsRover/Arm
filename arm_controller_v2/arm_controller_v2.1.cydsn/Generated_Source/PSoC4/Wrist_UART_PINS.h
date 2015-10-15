/*******************************************************************************
* File Name: Wrist_UART_PINS.h
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

#if !defined(CY_SCB_PINS_Wrist_UART_H)
#define CY_SCB_PINS_Wrist_UART_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define Wrist_UART_REMOVE_MOSI_SCL_RX_WAKE_PIN    (1u)
#define Wrist_UART_REMOVE_MOSI_SCL_RX_PIN         (1u)
#define Wrist_UART_REMOVE_MISO_SDA_TX_PIN         (1u)
#define Wrist_UART_REMOVE_SCLK_PIN                (1u)
#define Wrist_UART_REMOVE_SS0_PIN                 (1u)
#define Wrist_UART_REMOVE_SS1_PIN                 (1u)
#define Wrist_UART_REMOVE_SS2_PIN                 (1u)
#define Wrist_UART_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define Wrist_UART_REMOVE_I2C_PINS                (1u)
#define Wrist_UART_REMOVE_SPI_MASTER_PINS         (1u)
#define Wrist_UART_REMOVE_SPI_SLAVE_PINS          (1u)
#define Wrist_UART_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define Wrist_UART_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define Wrist_UART_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define Wrist_UART_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define Wrist_UART_REMOVE_UART_TX_PIN             (0u)
#define Wrist_UART_REMOVE_UART_RX_TX_PIN          (1u)
#define Wrist_UART_REMOVE_UART_RX_PIN             (0u)
#define Wrist_UART_REMOVE_UART_RX_WAKE_PIN        (1u)
#define Wrist_UART_REMOVE_UART_RTS_PIN            (1u)
#define Wrist_UART_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define Wrist_UART_MOSI_SCL_RX_WAKE_PIN   (0u == Wrist_UART_REMOVE_MOSI_SCL_RX_WAKE_PIN)
#define Wrist_UART_MOSI_SCL_RX_PIN        (0u == Wrist_UART_REMOVE_MOSI_SCL_RX_PIN)
#define Wrist_UART_MISO_SDA_TX_PIN        (0u == Wrist_UART_REMOVE_MISO_SDA_TX_PIN)
#define Wrist_UART_SCLK_PIN               (0u == Wrist_UART_REMOVE_SCLK_PIN)
#define Wrist_UART_SS0_PIN                (0u == Wrist_UART_REMOVE_SS0_PIN)
#define Wrist_UART_SS1_PIN                (0u == Wrist_UART_REMOVE_SS1_PIN)
#define Wrist_UART_SS2_PIN                (0u == Wrist_UART_REMOVE_SS2_PIN)
#define Wrist_UART_SS3_PIN                (0u == Wrist_UART_REMOVE_SS3_PIN)

/* Mode defined pins */
#define Wrist_UART_I2C_PINS               (0u == Wrist_UART_REMOVE_I2C_PINS)
#define Wrist_UART_SPI_MASTER_PINS        (0u == Wrist_UART_REMOVE_SPI_MASTER_PINS)
#define Wrist_UART_SPI_SLAVE_PINS         (0u == Wrist_UART_REMOVE_SPI_SLAVE_PINS)
#define Wrist_UART_SPI_MASTER_SS0_PIN     (0u == Wrist_UART_REMOVE_SPI_MASTER_SS0_PIN)
#define Wrist_UART_SPI_MASTER_SS1_PIN     (0u == Wrist_UART_REMOVE_SPI_MASTER_SS1_PIN)
#define Wrist_UART_SPI_MASTER_SS2_PIN     (0u == Wrist_UART_REMOVE_SPI_MASTER_SS2_PIN)
#define Wrist_UART_SPI_MASTER_SS3_PIN     (0u == Wrist_UART_REMOVE_SPI_MASTER_SS3_PIN)
#define Wrist_UART_UART_TX_PIN            (0u == Wrist_UART_REMOVE_UART_TX_PIN)
#define Wrist_UART_UART_RX_TX_PIN         (0u == Wrist_UART_REMOVE_UART_RX_TX_PIN)
#define Wrist_UART_UART_RX_PIN            (0u == Wrist_UART_REMOVE_UART_RX_PIN)
#define Wrist_UART_UART_RX_WAKE_PIN       (0u == Wrist_UART_REMOVE_UART_RX_WAKE_PIN)
#define Wrist_UART_UART_RTS_PIN           (0u == Wrist_UART_REMOVE_UART_RTS_PIN)
#define Wrist_UART_UART_CTS_PIN           (0u == Wrist_UART_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if(Wrist_UART_MOSI_SCL_RX_WAKE_PIN)
    #include "Wrist_UART_spi_mosi_i2c_scl_uart_rx_wake.h"
#endif /* (Wrist_UART_MOSI_SCL_RX_WAKE_PIN) */

#if(Wrist_UART_MOSI_SCL_RX_PIN)
    #include "Wrist_UART_spi_mosi_i2c_scl_uart_rx.h"
#endif /* (Wrist_UART_MOSI_SCL_RX_PIN) */

#if(Wrist_UART_MISO_SDA_TX_PIN)
    #include "Wrist_UART_spi_miso_i2c_sda_uart_tx.h"
#endif /* (Wrist_UART_MISO_SDA_TX_PIN_PIN) */

#if(Wrist_UART_SCLK_PIN)
    #include "Wrist_UART_spi_sclk.h"
#endif /* (Wrist_UART_SCLK_PIN) */

#if(Wrist_UART_SS0_PIN)
    #include "Wrist_UART_spi_ss0.h"
#endif /* (Wrist_UART_SS1_PIN) */

#if(Wrist_UART_SS1_PIN)
    #include "Wrist_UART_spi_ss1.h"
#endif /* (Wrist_UART_SS1_PIN) */

#if(Wrist_UART_SS2_PIN)
    #include "Wrist_UART_spi_ss2.h"
#endif /* (Wrist_UART_SS2_PIN) */

#if(Wrist_UART_SS3_PIN)
    #include "Wrist_UART_spi_ss3.h"
#endif /* (Wrist_UART_SS3_PIN) */

#if(Wrist_UART_I2C_PINS)
    #include "Wrist_UART_scl.h"
    #include "Wrist_UART_sda.h"
#endif /* (Wrist_UART_I2C_PINS) */

#if(Wrist_UART_SPI_MASTER_PINS)
    #include "Wrist_UART_sclk_m.h"
    #include "Wrist_UART_mosi_m.h"
    #include "Wrist_UART_miso_m.h"
#endif /* (Wrist_UART_SPI_MASTER_PINS) */

#if(Wrist_UART_SPI_SLAVE_PINS)
    #include "Wrist_UART_sclk_s.h"
    #include "Wrist_UART_mosi_s.h"
    #include "Wrist_UART_miso_s.h"
    #include "Wrist_UART_ss_s.h"
#endif /* (Wrist_UART_SPI_SLAVE_PINS) */

#if(Wrist_UART_SPI_MASTER_SS0_PIN)
    #include "Wrist_UART_ss0_m.h"
#endif /* (Wrist_UART_SPI_MASTER_SS0_PIN) */

#if(Wrist_UART_SPI_MASTER_SS1_PIN)
    #include "Wrist_UART_ss1_m.h"
#endif /* (Wrist_UART_SPI_MASTER_SS1_PIN) */

#if(Wrist_UART_SPI_MASTER_SS2_PIN)
    #include "Wrist_UART_ss2_m.h"
#endif /* (Wrist_UART_SPI_MASTER_SS2_PIN) */

#if(Wrist_UART_SPI_MASTER_SS3_PIN)
    #include "Wrist_UART_ss3_m.h"
#endif /* (Wrist_UART_SPI_MASTER_SS3_PIN) */

#if(Wrist_UART_UART_TX_PIN)
    #include "Wrist_UART_tx.h"
#endif /* (Wrist_UART_UART_TX_PIN) */

#if(Wrist_UART_UART_RX_TX_PIN)
    #include "Wrist_UART_rx_tx.h"
#endif /* (Wrist_UART_UART_RX_TX_PIN) */

#if(Wrist_UART_UART_RX_PIN)
    #include "Wrist_UART_rx.h"
#endif /* (Wrist_UART_UART_RX_PIN) */

#if(Wrist_UART_UART_RX_WAKE_PIN)
    #include "Wrist_UART_rx_wake.h"
#endif /* (Wrist_UART_UART_RX_WAKE_PIN) */

#if(Wrist_UART_UART_RTS_PIN)
    #include "Wrist_UART_rts.h"
#endif /* (Wrist_UART_UART_RTS_PIN) */

#if(Wrist_UART_UART_CTS_PIN)
    #include "Wrist_UART_cts.h"
#endif /* (Wrist_UART_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if(Wrist_UART_MOSI_SCL_RX_WAKE_PIN)
    #define Wrist_UART_MOSI_SCL_RX_WAKE_HSIOM_REG  \
                                                (*(reg32 *) Wrist_UART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define Wrist_UART_MOSI_SCL_RX_WAKE_HSIOM_PTR  \
                                                ( (reg32 *) Wrist_UART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define Wrist_UART_MOSI_SCL_RX_WAKE_HSIOM_MASK \
                                                (Wrist_UART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_MASK)
    #define Wrist_UART_MOSI_SCL_RX_WAKE_HSIOM_POS  \
                                                (Wrist_UART_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_SHIFT)

    #define Wrist_UART_MOSI_SCL_RX_WAKE_INTCFG_REG    (*(reg32 *) \
                                                              Wrist_UART_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)
    #define Wrist_UART_MOSI_SCL_RX_WAKE_INTCFG_PTR    ( (reg32 *) \
                                                              Wrist_UART_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)

    #define Wrist_UART_INTCFG_TYPE_MASK                  (0x03u)
    #define Wrist_UART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS  (Wrist_UART_spi_mosi_i2c_scl_uart_rx_wake__SHIFT)
    #define Wrist_UART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK ((uint32)                                           \
                                                                    ((uint32) Wrist_UART_INTCFG_TYPE_MASK << \
                                                                    Wrist_UART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS))
#endif /* (Wrist_UART_MOSI_SCL_RX_WAKE_PIN) */

#if(Wrist_UART_MOSI_SCL_RX_PIN)
    #define Wrist_UART_MOSI_SCL_RX_HSIOM_REG      (*(reg32 *) Wrist_UART_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define Wrist_UART_MOSI_SCL_RX_HSIOM_PTR      ( (reg32 *) Wrist_UART_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define Wrist_UART_MOSI_SCL_RX_HSIOM_MASK     (Wrist_UART_spi_mosi_i2c_scl_uart_rx__0__HSIOM_MASK)
    #define Wrist_UART_MOSI_SCL_RX_HSIOM_POS      (Wrist_UART_spi_mosi_i2c_scl_uart_rx__0__HSIOM_SHIFT)
#endif /* (Wrist_UART_MOSI_SCL_RX_PIN) */

#if(Wrist_UART_MISO_SDA_TX_PIN)
    #define Wrist_UART_MISO_SDA_TX_HSIOM_REG      (*(reg32 *) Wrist_UART_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define Wrist_UART_MISO_SDA_TX_HSIOM_PTR      ( (reg32 *) Wrist_UART_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define Wrist_UART_MISO_SDA_TX_HSIOM_MASK     (Wrist_UART_spi_miso_i2c_sda_uart_tx__0__HSIOM_MASK)
    #define Wrist_UART_MISO_SDA_TX_HSIOM_POS      (Wrist_UART_spi_miso_i2c_sda_uart_tx__0__HSIOM_SHIFT)
#endif /* (Wrist_UART_MISO_SDA_TX_PIN_PIN) */

#if(Wrist_UART_SCLK_PIN)
    #define Wrist_UART_SCLK_HSIOM_REG     (*(reg32 *) Wrist_UART_spi_sclk__0__HSIOM)
    #define Wrist_UART_SCLK_HSIOM_PTR     ( (reg32 *) Wrist_UART_spi_sclk__0__HSIOM)
    #define Wrist_UART_SCLK_HSIOM_MASK    (Wrist_UART_spi_sclk__0__HSIOM_MASK)
    #define Wrist_UART_SCLK_HSIOM_POS     (Wrist_UART_spi_sclk__0__HSIOM_SHIFT)
#endif /* (Wrist_UART_SCLK_PIN) */

#if(Wrist_UART_SS0_PIN)
    #define Wrist_UART_SS0_HSIOM_REG      (*(reg32 *) Wrist_UART_spi_ss0__0__HSIOM)
    #define Wrist_UART_SS0_HSIOM_PTR      ( (reg32 *) Wrist_UART_spi_ss0__0__HSIOM)
    #define Wrist_UART_SS0_HSIOM_MASK     (Wrist_UART_spi_ss0__0__HSIOM_MASK)
    #define Wrist_UART_SS0_HSIOM_POS      (Wrist_UART_spi_ss0__0__HSIOM_SHIFT)
#endif /* (Wrist_UART_SS1_PIN) */

#if(Wrist_UART_SS1_PIN)
    #define Wrist_UART_SS1_HSIOM_REG      (*(reg32 *) Wrist_UART_spi_ss1__0__HSIOM)
    #define Wrist_UART_SS1_HSIOM_PTR      ( (reg32 *) Wrist_UART_spi_ss1__0__HSIOM)
    #define Wrist_UART_SS1_HSIOM_MASK     (Wrist_UART_spi_ss1__0__HSIOM_MASK)
    #define Wrist_UART_SS1_HSIOM_POS      (Wrist_UART_spi_ss1__0__HSIOM_SHIFT)
#endif /* (Wrist_UART_SS1_PIN) */

#if(Wrist_UART_SS2_PIN)
    #define Wrist_UART_SS2_HSIOM_REG     (*(reg32 *) Wrist_UART_spi_ss2__0__HSIOM)
    #define Wrist_UART_SS2_HSIOM_PTR     ( (reg32 *) Wrist_UART_spi_ss2__0__HSIOM)
    #define Wrist_UART_SS2_HSIOM_MASK    (Wrist_UART_spi_ss2__0__HSIOM_MASK)
    #define Wrist_UART_SS2_HSIOM_POS     (Wrist_UART_spi_ss2__0__HSIOM_SHIFT)
#endif /* (Wrist_UART_SS2_PIN) */

#if(Wrist_UART_SS3_PIN)
    #define Wrist_UART_SS3_HSIOM_REG     (*(reg32 *) Wrist_UART_spi_ss3__0__HSIOM)
    #define Wrist_UART_SS3_HSIOM_PTR     ( (reg32 *) Wrist_UART_spi_ss3__0__HSIOM)
    #define Wrist_UART_SS3_HSIOM_MASK    (Wrist_UART_spi_ss3__0__HSIOM_MASK)
    #define Wrist_UART_SS3_HSIOM_POS     (Wrist_UART_spi_ss3__0__HSIOM_SHIFT)
#endif /* (Wrist_UART_SS3_PIN) */

#if(Wrist_UART_I2C_PINS)
    #define Wrist_UART_SCL_HSIOM_REG     (*(reg32 *) Wrist_UART_scl__0__HSIOM)
    #define Wrist_UART_SCL_HSIOM_PTR     ( (reg32 *) Wrist_UART_scl__0__HSIOM)
    #define Wrist_UART_SCL_HSIOM_MASK    (Wrist_UART_scl__0__HSIOM_MASK)
    #define Wrist_UART_SCL_HSIOM_POS     (Wrist_UART_scl__0__HSIOM_SHIFT)

    #define Wrist_UART_SDA_HSIOM_REG     (*(reg32 *) Wrist_UART_sda__0__HSIOM)
    #define Wrist_UART_SDA_HSIOM_PTR     ( (reg32 *) Wrist_UART_sda__0__HSIOM)
    #define Wrist_UART_SDA_HSIOM_MASK    (Wrist_UART_sda__0__HSIOM_MASK)
    #define Wrist_UART_SDA_HSIOM_POS     (Wrist_UART_sda__0__HSIOM_SHIFT)
#endif /* (Wrist_UART_I2C_PINS) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define Wrist_UART_HSIOM_DEF_SEL      (0x00u)
#define Wrist_UART_HSIOM_GPIO_SEL     (0x00u)
#define Wrist_UART_HSIOM_UART_SEL     (0x09u)
#define Wrist_UART_HSIOM_I2C_SEL      (0x0Eu)
#define Wrist_UART_HSIOM_SPI_SEL      (0x0Fu)

#define Wrist_UART_MOSI_SCL_RX_PIN_INDEX      (0u) /* RX pins without interrupt */
#define Wrist_UART_MOSI_SCL_RX_WAKE_PIN_INDEX (0u) /* RX pin with interrupt     */
#define Wrist_UART_MISO_SDA_TX_PIN_INDEX      (1u)
#define Wrist_UART_SCLK_PIN_INDEX             (2u)
#define Wrist_UART_SS0_PIN_INDEX              (3u)
#define Wrist_UART_SS1_PIN_INDEX              (4u)
#define Wrist_UART_SS2_PIN_INDEX              (5u)
#define Wrist_UART_SS3_PIN_INDEX              (6u)

#define Wrist_UART_MOSI_SCL_RX_PIN_MASK      ((uint32) 0x01u << Wrist_UART_MOSI_SCL_RX_PIN_INDEX)
#define Wrist_UART_MOSI_SCL_RX_WAKE_PIN_MASK ((uint32) 0x01u << Wrist_UART_MOSI_SCL_RX_WAKE_PIN_INDEX)
#define Wrist_UART_MISO_SDA_TX_PIN_MASK      ((uint32) 0x01u << Wrist_UART_MISO_SDA_TX_PIN_INDEX)
#define Wrist_UART_SCLK_PIN_MASK             ((uint32) 0x01u << Wrist_UART_SCLK_PIN_INDEX)
#define Wrist_UART_SS0_PIN_MASK              ((uint32) 0x01u << Wrist_UART_SS0_PIN_INDEX)
#define Wrist_UART_SS1_PIN_MASK              ((uint32) 0x01u << Wrist_UART_SS1_PIN_INDEX)
#define Wrist_UART_SS2_PIN_MASK              ((uint32) 0x01u << Wrist_UART_SS2_PIN_INDEX)
#define Wrist_UART_SS3_PIN_MASK              ((uint32) 0x01u << Wrist_UART_SS3_PIN_INDEX)

#define Wrist_UART_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin DM defines */
#define Wrist_UART_PIN_DM_ALG_HIZ  (0u)
#define Wrist_UART_PIN_DM_DIG_HIZ  (1u)
#define Wrist_UART_PIN_DM_OD_LO    (4u)
#define Wrist_UART_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Set bits-mask in register */
#define Wrist_UART_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define Wrist_UART_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define Wrist_UART_SET_HSIOM_SEL(reg, mask, pos, sel) Wrist_UART_SET_REGISTER_BITS(reg, mask, pos, sel)
#define Wrist_UART_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        Wrist_UART_SET_REGISTER_BITS(reg, mask, pos, intType)
#define Wrist_UART_SET_INP_DIS(reg, mask, val) Wrist_UART_SET_REGISTER_BIT(reg, mask, val)

/* Wrist_UART_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  Wrist_UART_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if(Wrist_UART_I2C_PINS)
    #define Wrist_UART_SET_I2C_SCL_DR(val) Wrist_UART_scl_Write(val)

    #define Wrist_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                          Wrist_UART_SET_HSIOM_SEL(Wrist_UART_SCL_HSIOM_REG,  \
                                                         Wrist_UART_SCL_HSIOM_MASK, \
                                                         Wrist_UART_SCL_HSIOM_POS,  \
                                                         (sel))
    #define Wrist_UART_WAIT_SCL_SET_HIGH  (0u == Wrist_UART_scl_Read())

/* Unconfigured SCB: scl signal */
#elif(Wrist_UART_MOSI_SCL_RX_WAKE_PIN)
    #define Wrist_UART_SET_I2C_SCL_DR(val) \
                            Wrist_UART_spi_mosi_i2c_scl_uart_rx_wake_Write(val)

    #define Wrist_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                    Wrist_UART_SET_HSIOM_SEL(Wrist_UART_MOSI_SCL_RX_WAKE_HSIOM_REG,  \
                                                   Wrist_UART_MOSI_SCL_RX_WAKE_HSIOM_MASK, \
                                                   Wrist_UART_MOSI_SCL_RX_WAKE_HSIOM_POS,  \
                                                   (sel))

    #define Wrist_UART_WAIT_SCL_SET_HIGH  (0u == Wrist_UART_spi_mosi_i2c_scl_uart_rx_wake_Read())

#elif(Wrist_UART_MOSI_SCL_RX_PIN)
    #define Wrist_UART_SET_I2C_SCL_DR(val) \
                            Wrist_UART_spi_mosi_i2c_scl_uart_rx_Write(val)


    #define Wrist_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                            Wrist_UART_SET_HSIOM_SEL(Wrist_UART_MOSI_SCL_RX_HSIOM_REG,  \
                                                           Wrist_UART_MOSI_SCL_RX_HSIOM_MASK, \
                                                           Wrist_UART_MOSI_SCL_RX_HSIOM_POS,  \
                                                           (sel))

    #define Wrist_UART_WAIT_SCL_SET_HIGH  (0u == Wrist_UART_spi_mosi_i2c_scl_uart_rx_Read())

#else
    #define Wrist_UART_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define Wrist_UART_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define Wrist_UART_WAIT_SCL_SET_HIGH  (0u)
#endif /* (Wrist_UART_MOSI_SCL_RX_PIN) */

/* SCB I2C: sda signal */
#if(Wrist_UART_I2C_PINS)
    #define Wrist_UART_WAIT_SDA_SET_HIGH  (0u == Wrist_UART_sda_Read())

/* Unconfigured SCB: sda signal */
#elif(Wrist_UART_MISO_SDA_TX_PIN)
    #define Wrist_UART_WAIT_SDA_SET_HIGH  (0u == Wrist_UART_spi_miso_i2c_sda_uart_tx_Read())

#else
    #define Wrist_UART_WAIT_SDA_SET_HIGH  (0u)
#endif /* (Wrist_UART_MOSI_SCL_RX_PIN) */

#endif /* (CY_SCB_PINS_Wrist_UART_H) */


/* [] END OF FILE */
