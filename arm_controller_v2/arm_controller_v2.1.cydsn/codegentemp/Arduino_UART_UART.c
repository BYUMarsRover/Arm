/*******************************************************************************
* File Name: Arduino_UART_UART.c
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

#include "Arduino_UART_PVT.h"
#include "Arduino_UART_SPI_UART_PVT.h"


#if(Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const Arduino_UART_UART_INIT_STRUCT Arduino_UART_configUart =
    {
        Arduino_UART_UART_SUB_MODE,
        Arduino_UART_UART_DIRECTION,
        Arduino_UART_UART_DATA_BITS_NUM,
        Arduino_UART_UART_PARITY_TYPE,
        Arduino_UART_UART_STOP_BITS_NUM,
        Arduino_UART_UART_OVS_FACTOR,
        Arduino_UART_UART_IRDA_LOW_POWER,
        Arduino_UART_UART_MEDIAN_FILTER_ENABLE,
        Arduino_UART_UART_RETRY_ON_NACK,
        Arduino_UART_UART_IRDA_POLARITY,
        Arduino_UART_UART_DROP_ON_PARITY_ERR,
        Arduino_UART_UART_DROP_ON_FRAME_ERR,
        Arduino_UART_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        Arduino_UART_UART_MP_MODE_ENABLE,
        Arduino_UART_UART_MP_ACCEPT_ADDRESS,
        Arduino_UART_UART_MP_RX_ADDRESS,
        Arduino_UART_UART_MP_RX_ADDRESS_MASK,
        (uint32) Arduino_UART_SCB_IRQ_INTERNAL,
        Arduino_UART_UART_INTR_RX_MASK,
        Arduino_UART_UART_RX_TRIGGER_LEVEL,
        Arduino_UART_UART_INTR_TX_MASK,
        Arduino_UART_UART_TX_TRIGGER_LEVEL,
        (uint8) Arduino_UART_UART_BYTE_MODE_ENABLE,
        (uint8) Arduino_UART_UART_CTS_ENABLE,
        (uint8) Arduino_UART_UART_CTS_POLARITY,
        (uint8) Arduino_UART_UART_RTS_POLARITY,
        (uint8) Arduino_UART_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: Arduino_UART_UartInit
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
    void Arduino_UART_UartInit(const Arduino_UART_UART_INIT_STRUCT *config)
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

        #if !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (Arduino_UART_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)         ? (Arduino_UART_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1) */

            /* Configure pins */
            Arduino_UART_SetPins(Arduino_UART_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            Arduino_UART_scbMode       = (uint8) Arduino_UART_SCB_MODE_UART;
            Arduino_UART_scbEnableWake = (uint8) config->enableWake;
            Arduino_UART_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            Arduino_UART_rxBuffer      =         config->rxBuffer;
            Arduino_UART_rxDataBits    = (uint8) config->dataBits;
            Arduino_UART_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            Arduino_UART_txBuffer      =         config->txBuffer;
            Arduino_UART_txDataBits    = (uint8) config->dataBits;
            Arduino_UART_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(Arduino_UART_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                Arduino_UART_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (Arduino_UART_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (Arduino_UART_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                Arduino_UART_CTRL_REG  = Arduino_UART_GET_CTRL_OVS(config->oversample);
            }

            Arduino_UART_CTRL_REG     |= Arduino_UART_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             Arduino_UART_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             Arduino_UART_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            Arduino_UART_UART_CTRL_REG = Arduino_UART_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            Arduino_UART_UART_RX_CTRL_REG = Arduino_UART_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        Arduino_UART_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        Arduino_UART_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        Arduino_UART_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        Arduino_UART_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(Arduino_UART_UART_PARITY_NONE != config->parity)
            {
               Arduino_UART_UART_RX_CTRL_REG |= Arduino_UART_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    Arduino_UART_UART_RX_CTRL_PARITY_ENABLED;
            }

            Arduino_UART_RX_CTRL_REG      = Arduino_UART_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                Arduino_UART_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                Arduino_UART_GET_UART_RX_CTRL_ENABLED(config->direction);

            Arduino_UART_RX_FIFO_CTRL_REG = Arduino_UART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            Arduino_UART_RX_MATCH_REG     = Arduino_UART_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                Arduino_UART_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            Arduino_UART_UART_TX_CTRL_REG = Arduino_UART_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                Arduino_UART_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(Arduino_UART_UART_PARITY_NONE != config->parity)
            {
               Arduino_UART_UART_TX_CTRL_REG |= Arduino_UART_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    Arduino_UART_UART_TX_CTRL_PARITY_ENABLED;
            }

            Arduino_UART_TX_CTRL_REG      = Arduino_UART_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                Arduino_UART_GET_UART_TX_CTRL_ENABLED(config->direction);

            Arduino_UART_TX_FIFO_CTRL_REG = Arduino_UART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1)
            Arduino_UART_UART_FLOW_CTRL_REG = Arduino_UART_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            Arduino_UART_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            Arduino_UART_GET_UART_FLOW_CTRL_RTS_POLARITY(config->rtsPolarity)   | \
                                            Arduino_UART_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (Arduino_UART_ISR_NUMBER);
            CyIntSetPriority(Arduino_UART_ISR_NUMBER, Arduino_UART_ISR_PRIORITY);
            (void) CyIntSetVector(Arduino_UART_ISR_NUMBER, &Arduino_UART_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(Arduino_UART_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (Arduino_UART_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(Arduino_UART_RX_WAKE_ISR_NUMBER, Arduino_UART_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(Arduino_UART_RX_WAKE_ISR_NUMBER, &Arduino_UART_UART_WAKEUP_ISR);
        #endif /* (Arduino_UART_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            Arduino_UART_INTR_I2C_EC_MASK_REG = Arduino_UART_NO_INTR_SOURCES;
            Arduino_UART_INTR_SPI_EC_MASK_REG = Arduino_UART_NO_INTR_SOURCES;
            Arduino_UART_INTR_SLAVE_MASK_REG  = Arduino_UART_NO_INTR_SOURCES;
            Arduino_UART_INTR_MASTER_MASK_REG = Arduino_UART_NO_INTR_SOURCES;
            Arduino_UART_INTR_RX_MASK_REG     = config->rxInterruptMask;
            Arduino_UART_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            Arduino_UART_rxBufferHead     = 0u;
            Arduino_UART_rxBufferTail     = 0u;
            Arduino_UART_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            Arduino_UART_txBufferHead = 0u;
            Arduino_UART_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: Arduino_UART_UartInit
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
    void Arduino_UART_UartInit(void)
    {
        /* Configure UART interface */
        Arduino_UART_CTRL_REG = Arduino_UART_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        Arduino_UART_UART_CTRL_REG = Arduino_UART_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        Arduino_UART_UART_RX_CTRL_REG = Arduino_UART_UART_DEFAULT_UART_RX_CTRL;
        Arduino_UART_RX_CTRL_REG      = Arduino_UART_UART_DEFAULT_RX_CTRL;
        Arduino_UART_RX_FIFO_CTRL_REG = Arduino_UART_UART_DEFAULT_RX_FIFO_CTRL;
        Arduino_UART_RX_MATCH_REG     = Arduino_UART_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        Arduino_UART_UART_TX_CTRL_REG = Arduino_UART_UART_DEFAULT_UART_TX_CTRL;
        Arduino_UART_TX_CTRL_REG      = Arduino_UART_UART_DEFAULT_TX_CTRL;
        Arduino_UART_TX_FIFO_CTRL_REG = Arduino_UART_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1)
        Arduino_UART_UART_FLOW_CTRL_REG = Arduino_UART_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(Arduino_UART_SCB_IRQ_INTERNAL)
        CyIntDisable    (Arduino_UART_ISR_NUMBER);
        CyIntSetPriority(Arduino_UART_ISR_NUMBER, Arduino_UART_ISR_PRIORITY);
        (void) CyIntSetVector(Arduino_UART_ISR_NUMBER, &Arduino_UART_SPI_UART_ISR);
    #endif /* (Arduino_UART_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(Arduino_UART_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (Arduino_UART_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(Arduino_UART_RX_WAKE_ISR_NUMBER, Arduino_UART_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(Arduino_UART_RX_WAKE_ISR_NUMBER, &Arduino_UART_UART_WAKEUP_ISR);
    #endif /* (Arduino_UART_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        Arduino_UART_INTR_I2C_EC_MASK_REG = Arduino_UART_UART_DEFAULT_INTR_I2C_EC_MASK;
        Arduino_UART_INTR_SPI_EC_MASK_REG = Arduino_UART_UART_DEFAULT_INTR_SPI_EC_MASK;
        Arduino_UART_INTR_SLAVE_MASK_REG  = Arduino_UART_UART_DEFAULT_INTR_SLAVE_MASK;
        Arduino_UART_INTR_MASTER_MASK_REG = Arduino_UART_UART_DEFAULT_INTR_MASTER_MASK;
        Arduino_UART_INTR_RX_MASK_REG     = Arduino_UART_UART_DEFAULT_INTR_RX_MASK;
        Arduino_UART_INTR_TX_MASK_REG     = Arduino_UART_UART_DEFAULT_INTR_TX_MASK;

    #if(Arduino_UART_INTERNAL_RX_SW_BUFFER_CONST)
        Arduino_UART_rxBufferHead     = 0u;
        Arduino_UART_rxBufferTail     = 0u;
        Arduino_UART_rxBufferOverflow = 0u;
    #endif /* (Arduino_UART_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(Arduino_UART_INTERNAL_TX_SW_BUFFER_CONST)
        Arduino_UART_txBufferHead = 0u;
        Arduino_UART_txBufferTail = 0u;
    #endif /* (Arduino_UART_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: Arduino_UART_UartSetRxAddress
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
void Arduino_UART_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = Arduino_UART_RX_MATCH_REG;

    matchReg &= ((uint32) ~Arduino_UART_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & Arduino_UART_RX_MATCH_ADDR_MASK)); /* Set address  */

    Arduino_UART_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: Arduino_UART_UartSetRxAddressMask
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
void Arduino_UART_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = Arduino_UART_RX_MATCH_REG;

    matchReg &= ((uint32) ~Arduino_UART_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << Arduino_UART_RX_MATCH_MASK_POS));

    Arduino_UART_RX_MATCH_REG = matchReg;
}


#if(Arduino_UART_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: Arduino_UART_UartGetChar
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
    uint32 Arduino_UART_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if(0u != Arduino_UART_SpiUartGetRxBufferSize())
        {
            rxData = Arduino_UART_SpiUartReadRxData();
        }

        if(Arduino_UART_CHECK_INTR_RX(Arduino_UART_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            Arduino_UART_ClearRxInterruptSource(Arduino_UART_INTR_RX_ERR);
        }

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: Arduino_UART_UartGetByte
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
    uint32 Arduino_UART_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;
        uint32 intSourceMask;

        intSourceMask = Arduino_UART_SpiUartDisableIntRx();

        if(0u != Arduino_UART_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            Arduino_UART_SpiUartEnableIntRx(intSourceMask);

            /* Get received byte */
            rxData = Arduino_UART_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the case
            * of empty. Otherwise the first received byte will be read.
            */
            rxData = Arduino_UART_RX_FIFO_RD_REG;

            /* Enables interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine
            * in case the byte was received and read by code above.
            */
            Arduino_UART_SpiUartEnableIntRx(intSourceMask);
        }

        /* Get and clear RX error mask */
        tmpStatus = (Arduino_UART_GetRxInterruptSource() & Arduino_UART_INTR_RX_ERR);
        Arduino_UART_ClearRxInterruptSource(Arduino_UART_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return(rxData);
    }


    #if !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: Arduino_UART_UartSetRtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of RTS output signal.
        *
        * Parameters:
        *  polarity: Active polarity of RTS output signal.
        *   Arduino_UART_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   Arduino_UART_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Arduino_UART_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                Arduino_UART_UART_FLOW_CTRL_REG |= (uint32)  Arduino_UART_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                Arduino_UART_UART_FLOW_CTRL_REG &= (uint32) ~Arduino_UART_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: Arduino_UART_UartSetRtsFifoLevel
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
        void Arduino_UART_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = Arduino_UART_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~Arduino_UART_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (Arduino_UART_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            Arduino_UART_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1) */

#endif /* (Arduino_UART_UART_RX_DIRECTION) */


#if(Arduino_UART_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: Arduino_UART_UartPutString
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
    void Arduino_UART_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            Arduino_UART_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: Arduino_UART_UartPutCRLF
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
    void Arduino_UART_UartPutCRLF(uint32 txDataByte)
    {
        Arduino_UART_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        Arduino_UART_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        Arduino_UART_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: Arduino_UARTSCB_UartEnableCts
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
        void Arduino_UART_UartEnableCts(void)
        {
            Arduino_UART_UART_FLOW_CTRL_REG |= (uint32)  Arduino_UART_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: Arduino_UART_UartDisableCts
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
        void Arduino_UART_UartDisableCts(void)
        {
            Arduino_UART_UART_FLOW_CTRL_REG &= (uint32) ~Arduino_UART_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: Arduino_UART_UartSetCtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of CTS input signal.
        *
        * Parameters:
        *  polarity: Active polarity of CTS output signal.
        *   Arduino_UART_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   Arduino_UART_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Arduino_UART_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                Arduino_UART_UART_FLOW_CTRL_REG |= (uint32)  Arduino_UART_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                Arduino_UART_UART_FLOW_CTRL_REG &= (uint32) ~Arduino_UART_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1) */

#endif /* (Arduino_UART_UART_TX_DIRECTION) */


#if(Arduino_UART_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: Arduino_UART_UartSaveConfig
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
    void Arduino_UART_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. At GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        Arduino_UART_UART_RX_CTRL_REG |= Arduino_UART_UART_RX_CTRL_SKIP_START;

    #if(Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(Arduino_UART_MOSI_SCL_RX_WAKE_PIN)
            (void) Arduino_UART_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
        #endif /* (Arduino_UART_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(Arduino_UART_UART_RX_WAKE_PIN)
            (void) Arduino_UART_rx_wake_ClearInterrupt();
        #endif /* (Arduino_UART_UART_RX_WAKE_PIN) */
    #endif /* (Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(Arduino_UART_UART_RX_WAKEUP_IRQ)
        Arduino_UART_RxWakeClearPendingInt();
        Arduino_UART_RxWakeEnableInt();
    #endif /* (Arduino_UART_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: Arduino_UART_UartRestoreConfig
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
    void Arduino_UART_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(Arduino_UART_UART_RX_WAKEUP_IRQ)
        Arduino_UART_RxWakeDisableInt();
    #endif /* (Arduino_UART_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (Arduino_UART_UART_WAKE_ENABLE_CONST) */


#if(Arduino_UART_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: Arduino_UART_UART_WAKEUP_ISR
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
    CY_ISR(Arduino_UART_UART_WAKEUP_ISR)
    {
        /* Clear interrupt source: the event becomes multi triggered and is
        * only disabled by Arduino_UART_UartRestoreConfig() call.
        */
    #if(Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(Arduino_UART_MOSI_SCL_RX_WAKE_PIN)
            (void) Arduino_UART_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
        #endif /* (Arduino_UART_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(Arduino_UART_UART_RX_WAKE_PIN)
            (void) Arduino_UART_rx_wake_ClearInterrupt();
        #endif /* (Arduino_UART_UART_RX_WAKE_PIN) */
    #endif /* (Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
    }
#endif /* (Arduino_UART_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
