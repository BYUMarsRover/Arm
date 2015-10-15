/*******************************************************************************
* File Name: Arduino_UART_SPI_UART_INT.c
* Version 2.0
*
* Description:
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Arduino_UART_PVT.h"
#include "Arduino_UART_SPI_UART_PVT.h"


/*******************************************************************************
* Function Name: Arduino_UART_SPI_UART_ISR
********************************************************************************
*
* Summary:
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(Arduino_UART_SPI_UART_ISR)
{
#if(Arduino_UART_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
    uint32 dataRx;
#endif /* (Arduino_UART_INTERNAL_RX_SW_BUFFER_CONST) */

#if(Arduino_UART_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (Arduino_UART_INTERNAL_TX_SW_BUFFER_CONST) */

    if(NULL != Arduino_UART_customIntrHandler)
    {
        Arduino_UART_customIntrHandler();
    }

    #if(Arduino_UART_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        Arduino_UART_ClearSpiExtClkInterruptSource(Arduino_UART_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if(Arduino_UART_CHECK_RX_SW_BUFFER)
    {
        if(Arduino_UART_CHECK_INTR_RX_MASKED(Arduino_UART_INTR_RX_NOT_EMPTY))
        {
            while(0u != Arduino_UART_GET_RX_FIFO_ENTRIES)
            {
                /* Get data from RX FIFO */
                dataRx = Arduino_UART_RX_FIFO_RD_REG;

                /* Move local head index */
                locHead = (Arduino_UART_rxBufferHead + 1u);

                /* Adjust local head index */
                if(Arduino_UART_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if(locHead == Arduino_UART_rxBufferTail)
                {
                    /* Overflow: through away new data */
                    Arduino_UART_rxBufferOverflow = (uint8) Arduino_UART_INTR_RX_OVERFLOW;
                }
                else
                {
                    /* Store received data */
                    Arduino_UART_PutWordInRxBuffer(locHead, dataRx);

                    /* Move head index */
                    Arduino_UART_rxBufferHead = locHead;
                }
            }

            Arduino_UART_ClearRxInterruptSource(Arduino_UART_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if(Arduino_UART_CHECK_TX_SW_BUFFER)
    {
        if(Arduino_UART_CHECK_INTR_TX_MASKED(Arduino_UART_INTR_TX_NOT_FULL))
        {
            /* Put data into TX FIFO */
            while(Arduino_UART_SPI_UART_FIFO_SIZE != Arduino_UART_GET_TX_FIFO_ENTRIES)
            {
                /* Check for room in TX software buffer */
                if(Arduino_UART_txBufferHead != Arduino_UART_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (Arduino_UART_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if(Arduino_UART_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    Arduino_UART_TX_FIFO_WR_REG = Arduino_UART_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    Arduino_UART_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    Arduino_UART_DISABLE_INTR_TX(Arduino_UART_INTR_TX_NOT_FULL);
                    break;
                }
            }

            Arduino_UART_ClearTxInterruptSource(Arduino_UART_INTR_TX_NOT_FULL);
        }
    }
    #endif
}


/* [] END OF FILE */
