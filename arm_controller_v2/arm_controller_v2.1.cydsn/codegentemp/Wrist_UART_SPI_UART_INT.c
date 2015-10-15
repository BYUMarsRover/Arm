/*******************************************************************************
* File Name: Wrist_UART_SPI_UART_INT.c
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

#include "Wrist_UART_PVT.h"
#include "Wrist_UART_SPI_UART_PVT.h"


/*******************************************************************************
* Function Name: Wrist_UART_SPI_UART_ISR
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
CY_ISR(Wrist_UART_SPI_UART_ISR)
{
#if(Wrist_UART_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
    uint32 dataRx;
#endif /* (Wrist_UART_INTERNAL_RX_SW_BUFFER_CONST) */

#if(Wrist_UART_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (Wrist_UART_INTERNAL_TX_SW_BUFFER_CONST) */

    if(NULL != Wrist_UART_customIntrHandler)
    {
        Wrist_UART_customIntrHandler();
    }

    #if(Wrist_UART_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        Wrist_UART_ClearSpiExtClkInterruptSource(Wrist_UART_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if(Wrist_UART_CHECK_RX_SW_BUFFER)
    {
        if(Wrist_UART_CHECK_INTR_RX_MASKED(Wrist_UART_INTR_RX_NOT_EMPTY))
        {
            while(0u != Wrist_UART_GET_RX_FIFO_ENTRIES)
            {
                /* Get data from RX FIFO */
                dataRx = Wrist_UART_RX_FIFO_RD_REG;

                /* Move local head index */
                locHead = (Wrist_UART_rxBufferHead + 1u);

                /* Adjust local head index */
                if(Wrist_UART_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if(locHead == Wrist_UART_rxBufferTail)
                {
                    /* Overflow: through away new data */
                    Wrist_UART_rxBufferOverflow = (uint8) Wrist_UART_INTR_RX_OVERFLOW;
                }
                else
                {
                    /* Store received data */
                    Wrist_UART_PutWordInRxBuffer(locHead, dataRx);

                    /* Move head index */
                    Wrist_UART_rxBufferHead = locHead;
                }
            }

            Wrist_UART_ClearRxInterruptSource(Wrist_UART_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if(Wrist_UART_CHECK_TX_SW_BUFFER)
    {
        if(Wrist_UART_CHECK_INTR_TX_MASKED(Wrist_UART_INTR_TX_NOT_FULL))
        {
            /* Put data into TX FIFO */
            while(Wrist_UART_SPI_UART_FIFO_SIZE != Wrist_UART_GET_TX_FIFO_ENTRIES)
            {
                /* Check for room in TX software buffer */
                if(Wrist_UART_txBufferHead != Wrist_UART_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (Wrist_UART_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if(Wrist_UART_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    Wrist_UART_TX_FIFO_WR_REG = Wrist_UART_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    Wrist_UART_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    Wrist_UART_DISABLE_INTR_TX(Wrist_UART_INTR_TX_NOT_FULL);
                    break;
                }
            }

            Wrist_UART_ClearTxInterruptSource(Wrist_UART_INTR_TX_NOT_FULL);
        }
    }
    #endif
}


/* [] END OF FILE */
