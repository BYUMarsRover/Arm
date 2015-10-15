/*******************************************************************************
* File Name: Wrist_UART_UART.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
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
#include "Wrist_UART_SPI_UART_PVT.h"


#if(Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const Wrist_UART_UART_INIT_STRUCT Wrist_UART_configUart =
    {
        Wrist_UART_UART_SUB_MODE,
        Wrist_UART_UART_DIRECTION,
        Wrist_UART_UART_DATA_BITS_NUM,
        Wrist_UART_UART_PARITY_TYPE,
        Wrist_UART_UART_STOP_BITS_NUM,
        Wrist_UART_UART_OVS_FACTOR,
        Wrist_UART_UART_IRDA_LOW_POWER,
        Wrist_UART_UART_MEDIAN_FILTER_ENABLE,
        Wrist_UART_UART_RETRY_ON_NACK,
        Wrist_UART_UART_IRDA_POLARITY,
        Wrist_UART_UART_DROP_ON_PARITY_ERR,
        Wrist_UART_UART_DROP_ON_FRAME_ERR,
        Wrist_UART_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        Wrist_UART_UART_MP_MODE_ENABLE,
        Wrist_UART_UART_MP_ACCEPT_ADDRESS,
        Wrist_UART_UART_MP_RX_ADDRESS,
        Wrist_UART_UART_MP_RX_ADDRESS_MASK,
        (uint32) Wrist_UART_SCB_IRQ_INTERNAL,
        Wrist_UART_UART_INTR_RX_MASK,
        Wrist_UART_UART_RX_TRIGGER_LEVEL,
        Wrist_UART_UART_INTR_TX_MASK,
        Wrist_UART_UART_TX_TRIGGER_LEVEL,
        (uint8) Wrist_UART_UART_BYTE_MODE_ENABLE,
        (uint8) Wrist_UART_UART_CTS_ENABLE,
        (uint8) Wrist_UART_UART_CTS_POLARITY,
        (uint8) Wrist_UART_UART_RTS_POLARITY,
        (uint8) Wrist_UART_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: Wrist_UART_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Wrist_UART_UartInit(const Wrist_UART_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(Wrist_UART_CY_SCBIP_V0 || Wrist_UART_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (Wrist_UART_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)         ? (Wrist_UART_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(Wrist_UART_CY_SCBIP_V0 || Wrist_UART_CY_SCBIP_V1) */

            /* Configure pins */
            Wrist_UART_SetPins(Wrist_UART_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            Wrist_UART_scbMode       = (uint8) Wrist_UART_SCB_MODE_UART;
            Wrist_UART_scbEnableWake = (uint8) config->enableWake;
            Wrist_UART_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            Wrist_UART_rxBuffer      =         config->rxBuffer;
            Wrist_UART_rxDataBits    = (uint8) config->dataBits;
            Wrist_UART_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            Wrist_UART_txBuffer      =         config->txBuffer;
            Wrist_UART_txDataBits    = (uint8) config->dataBits;
            Wrist_UART_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(Wrist_UART_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                Wrist_UART_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (Wrist_UART_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (Wrist_UART_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                Wrist_UART_CTRL_REG  = Wrist_UART_GET_CTRL_OVS(config->oversample);
            }

            Wrist_UART_CTRL_REG     |= Wrist_UART_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             Wrist_UART_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             Wrist_UART_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            Wrist_UART_UART_CTRL_REG = Wrist_UART_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            Wrist_UART_UART_RX_CTRL_REG = Wrist_UART_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        Wrist_UART_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        Wrist_UART_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        Wrist_UART_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        Wrist_UART_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(Wrist_UART_UART_PARITY_NONE != config->parity)
            {
               Wrist_UART_UART_RX_CTRL_REG |= Wrist_UART_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    Wrist_UART_UART_RX_CTRL_PARITY_ENABLED;
            }

            Wrist_UART_RX_CTRL_REG      = Wrist_UART_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                Wrist_UART_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                Wrist_UART_GET_UART_RX_CTRL_ENABLED(config->direction);

            Wrist_UART_RX_FIFO_CTRL_REG = Wrist_UART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            Wrist_UART_RX_MATCH_REG     = Wrist_UART_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                Wrist_UART_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            Wrist_UART_UART_TX_CTRL_REG = Wrist_UART_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                Wrist_UART_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(Wrist_UART_UART_PARITY_NONE != config->parity)
            {
               Wrist_UART_UART_TX_CTRL_REG |= Wrist_UART_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    Wrist_UART_UART_TX_CTRL_PARITY_ENABLED;
            }

            Wrist_UART_TX_CTRL_REG      = Wrist_UART_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                Wrist_UART_GET_UART_TX_CTRL_ENABLED(config->direction);

            Wrist_UART_TX_FIFO_CTRL_REG = Wrist_UART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(Wrist_UART_CY_SCBIP_V0 || Wrist_UART_CY_SCBIP_V1)
            Wrist_UART_UART_FLOW_CTRL_REG = Wrist_UART_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            Wrist_UART_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            Wrist_UART_GET_UART_FLOW_CTRL_RTS_POLARITY(config->rtsPolarity)   | \
                                            Wrist_UART_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(Wrist_UART_CY_SCBIP_V0 || Wrist_UART_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (Wrist_UART_ISR_NUMBER);
            CyIntSetPriority(Wrist_UART_ISR_NUMBER, Wrist_UART_ISR_PRIORITY);
            (void) CyIntSetVector(Wrist_UART_ISR_NUMBER, &Wrist_UART_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(Wrist_UART_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (Wrist_UART_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(Wrist_UART_RX_WAKE_ISR_NUMBER, Wrist_UART_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(Wrist_UART_RX_WAKE_ISR_NUMBER, &Wrist_UART_UART_WAKEUP_ISR);
        #endif /* (Wrist_UART_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            Wrist_UART_INTR_I2C_EC_MASK_REG = Wrist_UART_NO_INTR_SOURCES;
            Wrist_UART_INTR_SPI_EC_MASK_REG = Wrist_UART_NO_INTR_SOURCES;
            Wrist_UART_INTR_SLAVE_MASK_REG  = Wrist_UART_NO_INTR_SOURCES;
            Wrist_UART_INTR_MASTER_MASK_REG = Wrist_UART_NO_INTR_SOURCES;
            Wrist_UART_INTR_RX_MASK_REG     = config->rxInterruptMask;
            Wrist_UART_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            Wrist_UART_rxBufferHead     = 0u;
            Wrist_UART_rxBufferTail     = 0u;
            Wrist_UART_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            Wrist_UART_txBufferHead = 0u;
            Wrist_UART_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: Wrist_UART_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Wrist_UART_UartInit(void)
    {
        /* Configure UART interface */
        Wrist_UART_CTRL_REG = Wrist_UART_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        Wrist_UART_UART_CTRL_REG = Wrist_UART_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        Wrist_UART_UART_RX_CTRL_REG = Wrist_UART_UART_DEFAULT_UART_RX_CTRL;
        Wrist_UART_RX_CTRL_REG      = Wrist_UART_UART_DEFAULT_RX_CTRL;
        Wrist_UART_RX_FIFO_CTRL_REG = Wrist_UART_UART_DEFAULT_RX_FIFO_CTRL;
        Wrist_UART_RX_MATCH_REG     = Wrist_UART_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        Wrist_UART_UART_TX_CTRL_REG = Wrist_UART_UART_DEFAULT_UART_TX_CTRL;
        Wrist_UART_TX_CTRL_REG      = Wrist_UART_UART_DEFAULT_TX_CTRL;
        Wrist_UART_TX_FIFO_CTRL_REG = Wrist_UART_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(Wrist_UART_CY_SCBIP_V0 || Wrist_UART_CY_SCBIP_V1)
        Wrist_UART_UART_FLOW_CTRL_REG = Wrist_UART_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(Wrist_UART_CY_SCBIP_V0 || Wrist_UART_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(Wrist_UART_SCB_IRQ_INTERNAL)
        CyIntDisable    (Wrist_UART_ISR_NUMBER);
        CyIntSetPriority(Wrist_UART_ISR_NUMBER, Wrist_UART_ISR_PRIORITY);
        (void) CyIntSetVector(Wrist_UART_ISR_NUMBER, &Wrist_UART_SPI_UART_ISR);
    #endif /* (Wrist_UART_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(Wrist_UART_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (Wrist_UART_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(Wrist_UART_RX_WAKE_ISR_NUMBER, Wrist_UART_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(Wrist_UART_RX_WAKE_ISR_NUMBER, &Wrist_UART_UART_WAKEUP_ISR);
    #endif /* (Wrist_UART_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        Wrist_UART_INTR_I2C_EC_MASK_REG = Wrist_UART_UART_DEFAULT_INTR_I2C_EC_MASK;
        Wrist_UART_INTR_SPI_EC_MASK_REG = Wrist_UART_UART_DEFAULT_INTR_SPI_EC_MASK;
        Wrist_UART_INTR_SLAVE_MASK_REG  = Wrist_UART_UART_DEFAULT_INTR_SLAVE_MASK;
        Wrist_UART_INTR_MASTER_MASK_REG = Wrist_UART_UART_DEFAULT_INTR_MASTER_MASK;
        Wrist_UART_INTR_RX_MASK_REG     = Wrist_UART_UART_DEFAULT_INTR_RX_MASK;
        Wrist_UART_INTR_TX_MASK_REG     = Wrist_UART_UART_DEFAULT_INTR_TX_MASK;

    #if(Wrist_UART_INTERNAL_RX_SW_BUFFER_CONST)
        Wrist_UART_rxBufferHead     = 0u;
        Wrist_UART_rxBufferTail     = 0u;
        Wrist_UART_rxBufferOverflow = 0u;
    #endif /* (Wrist_UART_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(Wrist_UART_INTERNAL_TX_SW_BUFFER_CONST)
        Wrist_UART_txBufferHead = 0u;
        Wrist_UART_txBufferTail = 0u;
    #endif /* (Wrist_UART_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: Wrist_UART_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
* Parameters:
*  address: Address for hardware address detection.
*
* Return:
*  None
*
*******************************************************************************/
void Wrist_UART_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = Wrist_UART_RX_MATCH_REG;

    matchReg &= ((uint32) ~Wrist_UART_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & Wrist_UART_RX_MATCH_ADDR_MASK)); /* Set address  */

    Wrist_UART_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: Wrist_UART_UartSetRxAddressMask
********************************************************************************
*
* Summary:
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
* Parameters:
*  addressMask: Address mask.
*   0 - address bit does not care while comparison.
*   1 - address bit is significant while comparison.
*
* Return:
*  None
*
*******************************************************************************/
void Wrist_UART_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = Wrist_UART_RX_MATCH_REG;

    matchReg &= ((uint32) ~Wrist_UART_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << Wrist_UART_RX_MATCH_MASK_POS));

    Wrist_UART_RX_MATCH_REG = matchReg;
}


#if(Wrist_UART_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: Wrist_UART_UartGetChar
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *  This function is designed for ASCII characters and returns a char
    *  where 1 to 255 are valid characters and 0 indicates an error occurred or
    *  no data present.
    *  - The RX software buffer is disabled: returns the data element
    *    retrieved from the RX FIFO.
    *    Undefined data will be returned if the RX FIFO is empty.
    *  - The RX software buffer is enabled: returns the data element from
    *    the software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The next data element from the receive buffer.
    *  ASCII character values from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is enabled: The internal software buffer overflow
    *  does not treat as an error condition.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 Wrist_UART_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if(0u != Wrist_UART_SpiUartGetRxBufferSize())
        {
            rxData = Wrist_UART_SpiUartReadRxData();
        }

        if(Wrist_UART_CHECK_INTR_RX(Wrist_UART_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            Wrist_UART_ClearRxInterruptSource(Wrist_UART_INTR_RX_ERR);
        }

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: Wrist_UART_UartGetByte
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Bits 7-0 contain the next data element from the receive buffer and
    *  other bits contain the error condition.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is disabled: The internal software buffer overflow
    *  is not returned as status by this function.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 Wrist_UART_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;
        uint32 intSourceMask;

        intSourceMask = Wrist_UART_SpiUartDisableIntRx();

        if(0u != Wrist_UART_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            Wrist_UART_SpiUartEnableIntRx(intSourceMask);

            /* Get received byte */
            rxData = Wrist_UART_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the case
            * of empty. Otherwise the first received byte will be read.
            */
            rxData = Wrist_UART_RX_FIFO_RD_REG;

            /* Enables interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine
            * in case the byte was received and read by code above.
            */
            Wrist_UART_SpiUartEnableIntRx(intSourceMask);
        }

        /* Get and clear RX error mask */
        tmpStatus = (Wrist_UART_GetRxInterruptSource() & Wrist_UART_INTR_RX_ERR);
        Wrist_UART_ClearRxInterruptSource(Wrist_UART_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return(rxData);
    }


    #if !(Wrist_UART_CY_SCBIP_V0 || Wrist_UART_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: Wrist_UART_UartSetRtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of RTS output signal.
        *
        * Parameters:
        *  polarity: Active polarity of RTS output signal.
        *   Wrist_UART_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   Wrist_UART_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Wrist_UART_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                Wrist_UART_UART_FLOW_CTRL_REG |= (uint32)  Wrist_UART_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                Wrist_UART_UART_FLOW_CTRL_REG &= (uint32) ~Wrist_UART_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: Wrist_UART_UartSetRtsFifoLevel
        ********************************************************************************
        *
        * Summary:
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *
        * Parameters:
        *  level: Level in the RX FIFO for RTS signal activation.
        *         The range of valid level values is between 0 and RX FIFO depth - 1.
        *         Setting level value to 0 disables RTS signal activation.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Wrist_UART_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = Wrist_UART_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~Wrist_UART_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (Wrist_UART_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            Wrist_UART_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(Wrist_UART_CY_SCBIP_V0 || Wrist_UART_CY_SCBIP_V1) */

#endif /* (Wrist_UART_UART_RX_DIRECTION) */


#if(Wrist_UART_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: Wrist_UART_UartPutString
    ********************************************************************************
    *
    * Summary:
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  string: pointer to the null terminated string array to be placed in the
    *          transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Wrist_UART_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            Wrist_UART_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: Wrist_UART_UartPutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data followed by a carriage return (0x0D) and
    *  line feed (0x0A) into the transmit buffer.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  txDataByte : the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Wrist_UART_UartPutCRLF(uint32 txDataByte)
    {
        Wrist_UART_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        Wrist_UART_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        Wrist_UART_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(Wrist_UART_CY_SCBIP_V0 || Wrist_UART_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: Wrist_UARTSCB_UartEnableCts
        ********************************************************************************
        *
        * Summary:
        *  Enables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Wrist_UART_UartEnableCts(void)
        {
            Wrist_UART_UART_FLOW_CTRL_REG |= (uint32)  Wrist_UART_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: Wrist_UART_UartDisableCts
        ********************************************************************************
        *
        * Summary:
        *  Disables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Wrist_UART_UartDisableCts(void)
        {
            Wrist_UART_UART_FLOW_CTRL_REG &= (uint32) ~Wrist_UART_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: Wrist_UART_UartSetCtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of CTS input signal.
        *
        * Parameters:
        *  polarity: Active polarity of CTS output signal.
        *   Wrist_UART_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   Wrist_UART_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Wrist_UART_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                Wrist_UART_UART_FLOW_CTRL_REG |= (uint32)  Wrist_UART_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                Wrist_UART_UART_FLOW_CTRL_REG &= (uint32) ~Wrist_UART_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(Wrist_UART_CY_SCBIP_V0 || Wrist_UART_CY_SCBIP_V1) */

#endif /* (Wrist_UART_UART_TX_DIRECTION) */


#if(Wrist_UART_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: Wrist_UART_UartSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears and enables interrupt on a falling edge of the Rx input. The GPIO
    *  event wakes up the device and SKIP_START feature allows the UART continue
    *  receiving data bytes properly. The GPIO interrupt does not track in the
    *  active mode therefore requires to be cleared by this API.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Wrist_UART_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. At GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        Wrist_UART_UART_RX_CTRL_REG |= Wrist_UART_UART_RX_CTRL_SKIP_START;

    #if(Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(Wrist_UART_MOSI_SCL_RX_WAKE_PIN)
            (void) Wrist_UART_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
        #endif /* (Wrist_UART_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(Wrist_UART_UART_RX_WAKE_PIN)
            (void) Wrist_UART_rx_wake_ClearInterrupt();
        #endif /* (Wrist_UART_UART_RX_WAKE_PIN) */
    #endif /* (Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(Wrist_UART_UART_RX_WAKEUP_IRQ)
        Wrist_UART_RxWakeClearPendingInt();
        Wrist_UART_RxWakeEnableInt();
    #endif /* (Wrist_UART_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: Wrist_UART_UartRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Wrist_UART_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(Wrist_UART_UART_RX_WAKEUP_IRQ)
        Wrist_UART_RxWakeDisableInt();
    #endif /* (Wrist_UART_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (Wrist_UART_UART_WAKE_ENABLE_CONST) */


#if(Wrist_UART_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: Wrist_UART_UART_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
    *  event. This event is configured to trigger on a falling edge of the RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR(Wrist_UART_UART_WAKEUP_ISR)
    {
        /* Clear interrupt source: the event becomes multi triggered and is
        * only disabled by Wrist_UART_UartRestoreConfig() call.
        */
    #if(Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(Wrist_UART_MOSI_SCL_RX_WAKE_PIN)
            (void) Wrist_UART_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
        #endif /* (Wrist_UART_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(Wrist_UART_UART_RX_WAKE_PIN)
            (void) Wrist_UART_rx_wake_ClearInterrupt();
        #endif /* (Wrist_UART_UART_RX_WAKE_PIN) */
    #endif /* (Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
    }
#endif /* (Wrist_UART_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
