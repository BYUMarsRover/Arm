/*******************************************************************************
* File Name: Wrist_UART.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the SCB Component.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Wrist_UART_PVT.h"

#if(Wrist_UART_SCB_MODE_I2C_INC)
    #include "Wrist_UART_I2C_PVT.h"
#endif /* (Wrist_UART_SCB_MODE_I2C_INC) */

#if(Wrist_UART_SCB_MODE_EZI2C_INC)
    #include "Wrist_UART_EZI2C_PVT.h"
#endif /* (Wrist_UART_SCB_MODE_EZI2C_INC) */

#if(Wrist_UART_SCB_MODE_SPI_INC || Wrist_UART_SCB_MODE_UART_INC)
    #include "Wrist_UART_SPI_UART_PVT.h"
#endif /* (Wrist_UART_SCB_MODE_SPI_INC || Wrist_UART_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if(Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 Wrist_UART_scbMode = Wrist_UART_SCB_MODE_UNCONFIG;
    uint8 Wrist_UART_scbEnableWake;
    uint8 Wrist_UART_scbEnableIntr;

    /* I2C configuration variables */
    uint8 Wrist_UART_mode;
    uint8 Wrist_UART_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * Wrist_UART_rxBuffer;
    uint8  Wrist_UART_rxDataBits;
    uint32 Wrist_UART_rxBufferSize;

    volatile uint8 * Wrist_UART_txBuffer;
    uint8  Wrist_UART_txDataBits;
    uint32 Wrist_UART_txBufferSize;

    /* EZI2C configuration variables */
    uint8 Wrist_UART_numberOfAddr;
    uint8 Wrist_UART_subAddrSize;
#endif /* (Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 Wrist_UART_initVar = 0u;

#if !defined (CY_REMOVE_Wrist_UART_CUSTOM_INTR_HANDLER)
    cyisraddress Wrist_UART_customIntrHandler = NULL;
#endif /* !defined (CY_REMOVE_Wrist_UART_CUSTOM_INTR_HANDLER) */


/***************************************
*    Private Function Prototypes
***************************************/

static void Wrist_UART_ScbEnableIntr(void);
static void Wrist_UART_ScbModeStop(void);


/*******************************************************************************
* Function Name: Wrist_UART_Init
********************************************************************************
*
* Summary:
*  Initializes the SCB component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SCB_I2CInit, SCB_SpiInit, SCB_UartInit or SCB_EzI2CInit.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Wrist_UART_Init(void)
{
#if(Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    if(Wrist_UART_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        Wrist_UART_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif(Wrist_UART_SCB_MODE_I2C_CONST_CFG)
    Wrist_UART_I2CInit();

#elif(Wrist_UART_SCB_MODE_SPI_CONST_CFG)
    Wrist_UART_SpiInit();

#elif(Wrist_UART_SCB_MODE_UART_CONST_CFG)
    Wrist_UART_UartInit();

#elif(Wrist_UART_SCB_MODE_EZI2C_CONST_CFG)
    Wrist_UART_EzI2CInit();

#endif /* (Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Wrist_UART_Enable
********************************************************************************
*
* Summary:
*  Enables the SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Wrist_UART_Enable(void)
{
#if(Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if(!Wrist_UART_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        Wrist_UART_CTRL_REG |= Wrist_UART_CTRL_ENABLED;

        Wrist_UART_ScbEnableIntr();
    }
#else
    Wrist_UART_CTRL_REG |= Wrist_UART_CTRL_ENABLED;

    Wrist_UART_ScbEnableIntr();
#endif /* (Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Wrist_UART_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZ I2C. Otherwise this function does not enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Wrist_UART_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void Wrist_UART_Start(void)
{
    if(0u == Wrist_UART_initVar)
    {
        Wrist_UART_Init();
        Wrist_UART_initVar = 1u; /* Component was initialized */
    }

    Wrist_UART_Enable();
}


/*******************************************************************************
* Function Name: Wrist_UART_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component and its interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Wrist_UART_Stop(void)
{
#if(Wrist_UART_SCB_IRQ_INTERNAL)
    Wrist_UART_DisableInt();
#endif /* (Wrist_UART_SCB_IRQ_INTERNAL) */

    Wrist_UART_CTRL_REG &= (uint32) ~Wrist_UART_CTRL_ENABLED;  /* Disable scb IP */

#if(Wrist_UART_SCB_IRQ_INTERNAL)
    Wrist_UART_ClearPendingInt();
#endif /* (Wrist_UART_SCB_IRQ_INTERNAL) */

    Wrist_UART_ScbModeStop(); /* Calls scbMode specific Stop function */
}


/*******************************************************************************
* Function Name: Wrist_UART_SetRxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the RX FIFO to generate RX level interrupt.
*         The range of valid level values is between 0 and RX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void Wrist_UART_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = Wrist_UART_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~Wrist_UART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (Wrist_UART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    Wrist_UART_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: Wrist_UART_SetTxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has more entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the TX FIFO to generate TX level interrupt.
*         The range of valid level values is between 0 and TX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void Wrist_UART_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = Wrist_UART_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~Wrist_UART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (Wrist_UART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    Wrist_UART_TX_FIFO_CTRL_REG = txFifoCtrl;
}


/*******************************************************************************
* Function Name: Wrist_UART_SetCustomInterruptHandler
********************************************************************************
*
* Summary:
*  Registers a function to be called by the internal interrupt handler.
*  First the function that is registered is called, then the internal interrupt
*  handler performs any operation such as software buffer management functions
*  before the interrupt returns.  It is the user's responsibility not to break
*  the software buffer operations. Only one custom handler is supported, which
*  is the function provided by the most recent call.
*  At the initialization time no custom handler is registered.
*
* Parameters:
*  func: Pointer to the function to register.
*        The value NULL indicates to remove the current custom interrupt
*        handler.
*
* Return:
*  None
*
*******************************************************************************/
void Wrist_UART_SetCustomInterruptHandler(cyisraddress func)
{
#if !defined (CY_REMOVE_Wrist_UART_CUSTOM_INTR_HANDLER)
    Wrist_UART_customIntrHandler = func; /* Register interrupt handler */
#else
    if(NULL != func)
    {
        /* Suppress compiler warning */
    }
#endif /* !defined (CY_REMOVE_Wrist_UART_CUSTOM_INTR_HANDLER) */
}


/*******************************************************************************
* Function Name: Wrist_UART_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables an interrupt for a specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void Wrist_UART_ScbEnableIntr(void)
{
#if(Wrist_UART_SCB_IRQ_INTERNAL)
    #if(Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Enable interrupt in NVIC */
        if(0u != Wrist_UART_scbEnableIntr)
        {
            Wrist_UART_EnableInt();
        }
    #else
        Wrist_UART_EnableInt();

    #endif /* (Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (Wrist_UART_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: Wrist_UART_ScbModeStop
********************************************************************************
*
* Summary:
*  Calls the Stop function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void Wrist_UART_ScbModeStop(void)
{
#if(Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    if(Wrist_UART_SCB_MODE_I2C_RUNTM_CFG)
    {
        Wrist_UART_I2CStop();
    }
    else if (Wrist_UART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        Wrist_UART_EzI2CStop();
    }
#if (!Wrist_UART_CY_SCBIP_V1)
    else if (Wrist_UART_SCB_MODE_UART_RUNTM_CFG)
    {
        Wrist_UART_UartStop();
    }
#endif /* (!Wrist_UART_CY_SCBIP_V1) */
    else
    {
        /* Do nothing for other modes */
    }
#elif(Wrist_UART_SCB_MODE_I2C_CONST_CFG)
    Wrist_UART_I2CStop();

#elif(Wrist_UART_SCB_MODE_EZI2C_CONST_CFG)
    Wrist_UART_EzI2CStop();

#elif(Wrist_UART_SCB_MODE_UART_CONST_CFG)
    Wrist_UART_UartStop();

#endif /* (Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if(Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: Wrist_UART_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Wrist_UART_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [Wrist_UART_SCB_PINS_NUMBER];
        uint32 pinsDm   [Wrist_UART_SCB_PINS_NUMBER];

    #if (!Wrist_UART_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!Wrist_UART_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for(i = 0u; i < Wrist_UART_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = Wrist_UART_HSIOM_DEF_SEL;
            pinsDm[i]    = Wrist_UART_PIN_DM_ALG_HIZ;
        }

        if((Wrist_UART_SCB_MODE_I2C   == mode) ||
           (Wrist_UART_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[Wrist_UART_MOSI_SCL_RX_PIN_INDEX] = Wrist_UART_HSIOM_I2C_SEL;
            hsiomSel[Wrist_UART_MISO_SDA_TX_PIN_INDEX] = Wrist_UART_HSIOM_I2C_SEL;

            pinsDm[Wrist_UART_MOSI_SCL_RX_PIN_INDEX] = Wrist_UART_PIN_DM_OD_LO;
            pinsDm[Wrist_UART_MISO_SDA_TX_PIN_INDEX] = Wrist_UART_PIN_DM_OD_LO;
        }
    #if (!Wrist_UART_CY_SCBIP_V1)
        else if(Wrist_UART_SCB_MODE_SPI == mode)
        {
            hsiomSel[Wrist_UART_MOSI_SCL_RX_PIN_INDEX] = Wrist_UART_HSIOM_SPI_SEL;
            hsiomSel[Wrist_UART_MISO_SDA_TX_PIN_INDEX] = Wrist_UART_HSIOM_SPI_SEL;
            hsiomSel[Wrist_UART_SCLK_PIN_INDEX]        = Wrist_UART_HSIOM_SPI_SEL;

            if(Wrist_UART_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[Wrist_UART_MOSI_SCL_RX_PIN_INDEX] = Wrist_UART_PIN_DM_DIG_HIZ;
                pinsDm[Wrist_UART_MISO_SDA_TX_PIN_INDEX] = Wrist_UART_PIN_DM_STRONG;
                pinsDm[Wrist_UART_SCLK_PIN_INDEX]        = Wrist_UART_PIN_DM_DIG_HIZ;

            #if(Wrist_UART_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[Wrist_UART_SS0_PIN_INDEX] = Wrist_UART_HSIOM_SPI_SEL;
                pinsDm  [Wrist_UART_SS0_PIN_INDEX] = Wrist_UART_PIN_DM_DIG_HIZ;
            #endif /* (Wrist_UART_SS1_PIN) */

            #if(Wrist_UART_MISO_SDA_TX_PIN)
                /* Disable input buffer */
                 pinsInBuf |= Wrist_UART_MISO_SDA_TX_PIN_MASK;
            #endif /* (Wrist_UART_MISO_SDA_TX_PIN_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[Wrist_UART_MOSI_SCL_RX_PIN_INDEX] = Wrist_UART_PIN_DM_STRONG;
                pinsDm[Wrist_UART_MISO_SDA_TX_PIN_INDEX] = Wrist_UART_PIN_DM_DIG_HIZ;
                pinsDm[Wrist_UART_SCLK_PIN_INDEX]        = Wrist_UART_PIN_DM_STRONG;

            #if(Wrist_UART_SS0_PIN)
                hsiomSel [Wrist_UART_SS0_PIN_INDEX] = Wrist_UART_HSIOM_SPI_SEL;
                pinsDm   [Wrist_UART_SS0_PIN_INDEX] = Wrist_UART_PIN_DM_STRONG;
                pinsInBuf                                |= Wrist_UART_SS0_PIN_MASK;
            #endif /* (Wrist_UART_SS0_PIN) */

            #if(Wrist_UART_SS1_PIN)
                hsiomSel [Wrist_UART_SS1_PIN_INDEX] = Wrist_UART_HSIOM_SPI_SEL;
                pinsDm   [Wrist_UART_SS1_PIN_INDEX] = Wrist_UART_PIN_DM_STRONG;
                pinsInBuf                                |= Wrist_UART_SS1_PIN_MASK;
            #endif /* (Wrist_UART_SS1_PIN) */

            #if(Wrist_UART_SS2_PIN)
                hsiomSel [Wrist_UART_SS2_PIN_INDEX] = Wrist_UART_HSIOM_SPI_SEL;
                pinsDm   [Wrist_UART_SS2_PIN_INDEX] = Wrist_UART_PIN_DM_STRONG;
                pinsInBuf                                |= Wrist_UART_SS2_PIN_MASK;
            #endif /* (Wrist_UART_SS2_PIN) */

            #if(Wrist_UART_SS3_PIN)
                hsiomSel [Wrist_UART_SS3_PIN_INDEX] = Wrist_UART_HSIOM_SPI_SEL;
                pinsDm   [Wrist_UART_SS3_PIN_INDEX] = Wrist_UART_PIN_DM_STRONG;
                pinsInBuf                                |= Wrist_UART_SS3_PIN_MASK;
            #endif /* (Wrist_UART_SS2_PIN) */

                /* Disable input buffers */
            #if(Wrist_UART_MOSI_SCL_RX_PIN)
                pinsInBuf |= Wrist_UART_MOSI_SCL_RX_PIN_MASK;
            #endif /* (Wrist_UART_MOSI_SCL_RX_PIN) */

             #if(Wrist_UART_MOSI_SCL_RX_WAKE_PIN)
                pinsInBuf |= Wrist_UART_MOSI_SCL_RX_WAKE_PIN_MASK;
            #endif /* (Wrist_UART_MOSI_SCL_RX_WAKE_PIN) */

            #if(Wrist_UART_SCLK_PIN)
                pinsInBuf |= Wrist_UART_SCLK_PIN_MASK;
            #endif /* (Wrist_UART_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if(Wrist_UART_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[Wrist_UART_MISO_SDA_TX_PIN_INDEX] = Wrist_UART_HSIOM_UART_SEL;
                pinsDm  [Wrist_UART_MISO_SDA_TX_PIN_INDEX] = Wrist_UART_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if(0u != (Wrist_UART_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[Wrist_UART_MOSI_SCL_RX_PIN_INDEX] = Wrist_UART_HSIOM_UART_SEL;
                    pinsDm  [Wrist_UART_MOSI_SCL_RX_PIN_INDEX] = Wrist_UART_PIN_DM_DIG_HIZ;
                }

                if(0u != (Wrist_UART_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[Wrist_UART_MISO_SDA_TX_PIN_INDEX] = Wrist_UART_HSIOM_UART_SEL;
                    pinsDm  [Wrist_UART_MISO_SDA_TX_PIN_INDEX] = Wrist_UART_PIN_DM_STRONG;

                #if(Wrist_UART_MISO_SDA_TX_PIN)
                     pinsInBuf |= Wrist_UART_MISO_SDA_TX_PIN_MASK;
                #endif /* (Wrist_UART_MISO_SDA_TX_PIN_PIN) */
                }

            #if !(Wrist_UART_CY_SCBIP_V0 || Wrist_UART_CY_SCBIP_V1)
                if(Wrist_UART_UART_MODE_STD == subMode)
                {
                    if(0u != (Wrist_UART_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[Wrist_UART_SCLK_PIN_INDEX] = Wrist_UART_HSIOM_UART_SEL;
                        pinsDm  [Wrist_UART_SCLK_PIN_INDEX] = Wrist_UART_PIN_DM_DIG_HIZ;
                    }

                    if(0u != (Wrist_UART_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[Wrist_UART_SS0_PIN_INDEX] = Wrist_UART_HSIOM_UART_SEL;
                        pinsDm  [Wrist_UART_SS0_PIN_INDEX] = Wrist_UART_PIN_DM_STRONG;

                    #if(Wrist_UART_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= Wrist_UART_SS0_PIN_MASK;
                    #endif /* (Wrist_UART_SS0_PIN) */
                    }
                }
            #endif /* !(Wrist_UART_CY_SCBIP_V0 || Wrist_UART_CY_SCBIP_V1) */
            }
        }
    #endif /* (!Wrist_UART_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if(Wrist_UART_MOSI_SCL_RX_PIN)
        Wrist_UART_SET_HSIOM_SEL(Wrist_UART_MOSI_SCL_RX_HSIOM_REG,
                                       Wrist_UART_MOSI_SCL_RX_HSIOM_MASK,
                                       Wrist_UART_MOSI_SCL_RX_HSIOM_POS,
                                       hsiomSel[Wrist_UART_MOSI_SCL_RX_PIN_INDEX]);

        Wrist_UART_spi_mosi_i2c_scl_uart_rx_SetDriveMode((uint8) pinsDm[Wrist_UART_MOSI_SCL_RX_PIN_INDEX]);

    #if (!Wrist_UART_CY_SCBIP_V1)
        Wrist_UART_SET_INP_DIS(Wrist_UART_spi_mosi_i2c_scl_uart_rx_INP_DIS,
                                     Wrist_UART_spi_mosi_i2c_scl_uart_rx_MASK,
                                     (0u != (pinsInBuf & Wrist_UART_MOSI_SCL_RX_PIN_MASK)));
    #endif /* (!Wrist_UART_CY_SCBIP_V1) */
    #endif /* (Wrist_UART_MOSI_SCL_RX_PIN) */

    #if(Wrist_UART_MOSI_SCL_RX_WAKE_PIN)
        Wrist_UART_SET_HSIOM_SEL(Wrist_UART_MOSI_SCL_RX_WAKE_HSIOM_REG,
                                       Wrist_UART_MOSI_SCL_RX_WAKE_HSIOM_MASK,
                                       Wrist_UART_MOSI_SCL_RX_WAKE_HSIOM_POS,
                                       hsiomSel[Wrist_UART_MOSI_SCL_RX_WAKE_PIN_INDEX]);

        Wrist_UART_spi_mosi_i2c_scl_uart_rx_wake_SetDriveMode((uint8)
                                                               pinsDm[Wrist_UART_MOSI_SCL_RX_WAKE_PIN_INDEX]);

        Wrist_UART_SET_INP_DIS(Wrist_UART_spi_mosi_i2c_scl_uart_rx_wake_INP_DIS,
                                     Wrist_UART_spi_mosi_i2c_scl_uart_rx_wake_MASK,
                                     (0u != (pinsInBuf & Wrist_UART_MOSI_SCL_RX_WAKE_PIN_MASK)));

         /* Set interrupt on falling edge */
        Wrist_UART_SET_INCFG_TYPE(Wrist_UART_MOSI_SCL_RX_WAKE_INTCFG_REG,
                                        Wrist_UART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK,
                                        Wrist_UART_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS,
                                        Wrist_UART_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (Wrist_UART_MOSI_SCL_RX_WAKE_PIN) */

    #if(Wrist_UART_MISO_SDA_TX_PIN)
        Wrist_UART_SET_HSIOM_SEL(Wrist_UART_MISO_SDA_TX_HSIOM_REG,
                                       Wrist_UART_MISO_SDA_TX_HSIOM_MASK,
                                       Wrist_UART_MISO_SDA_TX_HSIOM_POS,
                                       hsiomSel[Wrist_UART_MISO_SDA_TX_PIN_INDEX]);

        Wrist_UART_spi_miso_i2c_sda_uart_tx_SetDriveMode((uint8) pinsDm[Wrist_UART_MISO_SDA_TX_PIN_INDEX]);

    #if (!Wrist_UART_CY_SCBIP_V1)
        Wrist_UART_SET_INP_DIS(Wrist_UART_spi_miso_i2c_sda_uart_tx_INP_DIS,
                                     Wrist_UART_spi_miso_i2c_sda_uart_tx_MASK,
                                    (0u != (pinsInBuf & Wrist_UART_MISO_SDA_TX_PIN_MASK)));
    #endif /* (!Wrist_UART_CY_SCBIP_V1) */
    #endif /* (Wrist_UART_MOSI_SCL_RX_PIN) */

    #if(Wrist_UART_SCLK_PIN)
        Wrist_UART_SET_HSIOM_SEL(Wrist_UART_SCLK_HSIOM_REG, Wrist_UART_SCLK_HSIOM_MASK,
                                       Wrist_UART_SCLK_HSIOM_POS, hsiomSel[Wrist_UART_SCLK_PIN_INDEX]);

        Wrist_UART_spi_sclk_SetDriveMode((uint8) pinsDm[Wrist_UART_SCLK_PIN_INDEX]);

        Wrist_UART_SET_INP_DIS(Wrist_UART_spi_sclk_INP_DIS,
                                     Wrist_UART_spi_sclk_MASK,
                                     (0u != (pinsInBuf & Wrist_UART_SCLK_PIN_MASK)));
    #endif /* (Wrist_UART_SCLK_PIN) */

    #if(Wrist_UART_SS0_PIN)
        Wrist_UART_SET_HSIOM_SEL(Wrist_UART_SS0_HSIOM_REG, Wrist_UART_SS0_HSIOM_MASK,
                                       Wrist_UART_SS0_HSIOM_POS, hsiomSel[Wrist_UART_SS0_PIN_INDEX]);

        Wrist_UART_spi_ss0_SetDriveMode((uint8) pinsDm[Wrist_UART_SS0_PIN_INDEX]);

        Wrist_UART_SET_INP_DIS(Wrist_UART_spi_ss0_INP_DIS,
                                     Wrist_UART_spi_ss0_MASK,
                                     (0u != (pinsInBuf & Wrist_UART_SS0_PIN_MASK)));
    #endif /* (Wrist_UART_SS1_PIN) */

    #if(Wrist_UART_SS1_PIN)
        Wrist_UART_SET_HSIOM_SEL(Wrist_UART_SS1_HSIOM_REG, Wrist_UART_SS1_HSIOM_MASK,
                                       Wrist_UART_SS1_HSIOM_POS, hsiomSel[Wrist_UART_SS1_PIN_INDEX]);

        Wrist_UART_spi_ss1_SetDriveMode((uint8) pinsDm[Wrist_UART_SS1_PIN_INDEX]);

        Wrist_UART_SET_INP_DIS(Wrist_UART_spi_ss1_INP_DIS,
                                     Wrist_UART_spi_ss1_MASK,
                                     (0u != (pinsInBuf & Wrist_UART_SS1_PIN_MASK)));
    #endif /* (Wrist_UART_SS1_PIN) */

    #if(Wrist_UART_SS2_PIN)
        Wrist_UART_SET_HSIOM_SEL(Wrist_UART_SS2_HSIOM_REG, Wrist_UART_SS2_HSIOM_MASK,
                                       Wrist_UART_SS2_HSIOM_POS, hsiomSel[Wrist_UART_SS2_PIN_INDEX]);

        Wrist_UART_spi_ss2_SetDriveMode((uint8) pinsDm[Wrist_UART_SS2_PIN_INDEX]);

        Wrist_UART_SET_INP_DIS(Wrist_UART_spi_ss2_INP_DIS,
                                     Wrist_UART_spi_ss2_MASK,
                                     (0u != (pinsInBuf & Wrist_UART_SS2_PIN_MASK)));
    #endif /* (Wrist_UART_SS2_PIN) */

    #if(Wrist_UART_SS3_PIN)
        Wrist_UART_SET_HSIOM_SEL(Wrist_UART_SS3_HSIOM_REG,  Wrist_UART_SS3_HSIOM_MASK,
                                       Wrist_UART_SS3_HSIOM_POS, hsiomSel[Wrist_UART_SS3_PIN_INDEX]);

        Wrist_UART_spi_ss3_SetDriveMode((uint8) pinsDm[Wrist_UART_SS3_PIN_INDEX]);

        Wrist_UART_SET_INP_DIS(Wrist_UART_spi_ss3_INP_DIS,
                                     Wrist_UART_spi_ss3_MASK,
                                     (0u != (pinsInBuf & Wrist_UART_SS3_PIN_MASK)));
    #endif /* (Wrist_UART_SS3_PIN) */
    }

#endif /* (Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (Wrist_UART_CY_SCBIP_V0 || Wrist_UART_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: Wrist_UART_I2CSlaveNackGeneration
    ********************************************************************************
    *
    * Summary:
    *  Sets command to generate NACK to the address or data.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Wrist_UART_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (Wrist_UART_CTRL_REG & Wrist_UART_CTRL_EC_AM_MODE)) &&
            (0u == (Wrist_UART_I2C_CTRL_REG & Wrist_UART_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            Wrist_UART_CTRL_REG &= ~Wrist_UART_CTRL_EC_AM_MODE;
            Wrist_UART_CTRL_REG |=  Wrist_UART_CTRL_EC_AM_MODE;
        }

        Wrist_UART_I2C_SLAVE_CMD_REG = Wrist_UART_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (Wrist_UART_CY_SCBIP_V0 || Wrist_UART_CY_SCBIP_V1) */


/* [] END OF FILE */
