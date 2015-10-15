/*******************************************************************************
* File Name: Arduino_UART_SPI_UART.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_Arduino_UART_H)
#define CY_SCB_SPI_UART_Arduino_UART_H

#include "Arduino_UART.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define Arduino_UART_SPI_MODE                   (0u)
#define Arduino_UART_SPI_SUB_MODE               (0u)
#define Arduino_UART_SPI_CLOCK_MODE             (0u)
#define Arduino_UART_SPI_OVS_FACTOR             (16u)
#define Arduino_UART_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define Arduino_UART_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define Arduino_UART_SPI_RX_DATA_BITS_NUM       (8u)
#define Arduino_UART_SPI_TX_DATA_BITS_NUM       (8u)
#define Arduino_UART_SPI_WAKE_ENABLE            (0u)
#define Arduino_UART_SPI_BITS_ORDER             (1u)
#define Arduino_UART_SPI_TRANSFER_SEPARATION    (1u)
#define Arduino_UART_SPI_NUMBER_OF_SS_LINES     (1u)
#define Arduino_UART_SPI_RX_BUFFER_SIZE         (8u)
#define Arduino_UART_SPI_TX_BUFFER_SIZE         (8u)

#define Arduino_UART_SPI_INTERRUPT_MODE         (0u)

#define Arduino_UART_SPI_INTR_RX_MASK           (0u)
#define Arduino_UART_SPI_INTR_TX_MASK           (0u)

#define Arduino_UART_SPI_RX_TRIGGER_LEVEL       (7u)
#define Arduino_UART_SPI_TX_TRIGGER_LEVEL       (0u)

#define Arduino_UART_SPI_BYTE_MODE_ENABLE       (0u)
#define Arduino_UART_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define Arduino_UART_SPI_SS0_POLARITY           (0u)
#define Arduino_UART_SPI_SS1_POLARITY           (0u)
#define Arduino_UART_SPI_SS2_POLARITY           (0u)
#define Arduino_UART_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define Arduino_UART_UART_SUB_MODE              (0u)
#define Arduino_UART_UART_DIRECTION             (3u)
#define Arduino_UART_UART_DATA_BITS_NUM         (8u)
#define Arduino_UART_UART_PARITY_TYPE           (2u)
#define Arduino_UART_UART_STOP_BITS_NUM         (2u)
#define Arduino_UART_UART_OVS_FACTOR            (12u)
#define Arduino_UART_UART_IRDA_LOW_POWER        (0u)
#define Arduino_UART_UART_MEDIAN_FILTER_ENABLE  (0u)
#define Arduino_UART_UART_RETRY_ON_NACK         (0u)
#define Arduino_UART_UART_IRDA_POLARITY         (0u)
#define Arduino_UART_UART_DROP_ON_FRAME_ERR     (0u)
#define Arduino_UART_UART_DROP_ON_PARITY_ERR    (0u)
#define Arduino_UART_UART_WAKE_ENABLE           (0u)
#define Arduino_UART_UART_RX_BUFFER_SIZE        (12u)
#define Arduino_UART_UART_TX_BUFFER_SIZE        (8u)
#define Arduino_UART_UART_MP_MODE_ENABLE        (0u)
#define Arduino_UART_UART_MP_ACCEPT_ADDRESS     (0u)
#define Arduino_UART_UART_MP_RX_ADDRESS         (2u)
#define Arduino_UART_UART_MP_RX_ADDRESS_MASK    (255u)

#define Arduino_UART_UART_INTERRUPT_MODE        (1u)

#define Arduino_UART_UART_INTR_RX_MASK          (4u)
#define Arduino_UART_UART_INTR_TX_MASK          (0u)

#define Arduino_UART_UART_RX_TRIGGER_LEVEL      (7u)
#define Arduino_UART_UART_TX_TRIGGER_LEVEL      (0u)

#define Arduino_UART_UART_BYTE_MODE_ENABLE      (0u)
#define Arduino_UART_UART_CTS_ENABLE            (0u)
#define Arduino_UART_UART_CTS_POLARITY          (0u)
#define Arduino_UART_UART_RTS_POLARITY          (0u)
#define Arduino_UART_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define Arduino_UART_SPI_SLAVE  (0u)
#define Arduino_UART_SPI_MASTER (1u)

/* UART direction enum */
#define Arduino_UART_UART_RX    (1u)
#define Arduino_UART_UART_TX    (2u)
#define Arduino_UART_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define Arduino_UART_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define Arduino_UART_RX_DIRECTION           (1u)
    #define Arduino_UART_TX_DIRECTION           (1u)
    #define Arduino_UART_UART_RX_DIRECTION      (1u)
    #define Arduino_UART_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define Arduino_UART_INTERNAL_RX_SW_BUFFER   (0u)
    #define Arduino_UART_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define Arduino_UART_RX_BUFFER_SIZE (Arduino_UART_rxBufferSize)
    #define Arduino_UART_TX_BUFFER_SIZE (Arduino_UART_txBufferSize)

    /* Return true if buffer is provided */
    #define Arduino_UART_CHECK_RX_SW_BUFFER (NULL != Arduino_UART_rxBuffer)
    #define Arduino_UART_CHECK_TX_SW_BUFFER (NULL != Arduino_UART_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define Arduino_UART_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define Arduino_UART_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define Arduino_UART_SPI_WAKE_ENABLE_CONST  (1u)
    #define Arduino_UART_CHECK_SPI_WAKE_ENABLE  (0u != Arduino_UART_scbEnableWake)
    #define Arduino_UART_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1)
        #define Arduino_UART_SPI_UART_FIFO_SIZE (Arduino_UART_FIFO_SIZE)
    #else
        #define Arduino_UART_SPI_UART_FIFO_SIZE (Arduino_UART_GET_FIFO_SIZE(Arduino_UART_CTRL_REG & \
                                                                                    Arduino_UART_CTRL_BYTE_MODE))
    #endif /* (Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (Arduino_UART_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define Arduino_UART_SPI_RX_DIRECTION (1u)
        #define Arduino_UART_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1)
            #define Arduino_UART_SPI_UART_FIFO_SIZE    (Arduino_UART_FIFO_SIZE)
        #else
            #define Arduino_UART_SPI_UART_FIFO_SIZE \
                                           Arduino_UART_GET_FIFO_SIZE(Arduino_UART_SPI_BYTE_MODE_ENABLE)

        #endif /* (Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define Arduino_UART_INTERNAL_SPI_RX_SW_BUFFER  (Arduino_UART_SPI_RX_BUFFER_SIZE > \
                                                                Arduino_UART_SPI_UART_FIFO_SIZE)
        #define Arduino_UART_INTERNAL_SPI_TX_SW_BUFFER  (Arduino_UART_SPI_TX_BUFFER_SIZE > \
                                                                Arduino_UART_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define Arduino_UART_INTERNAL_RX_SW_BUFFER  (Arduino_UART_INTERNAL_SPI_RX_SW_BUFFER)
        #define Arduino_UART_INTERNAL_TX_SW_BUFFER  (Arduino_UART_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define Arduino_UART_RX_BUFFER_SIZE         (Arduino_UART_SPI_RX_BUFFER_SIZE + 1u)
        #define Arduino_UART_TX_BUFFER_SIZE         (Arduino_UART_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define Arduino_UART_SPI_WAKE_ENABLE_CONST  (0u != Arduino_UART_SPI_WAKE_ENABLE)
        #define Arduino_UART_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define Arduino_UART_UART_RX_DIRECTION (0u != (Arduino_UART_UART_DIRECTION & Arduino_UART_UART_RX))
        #define Arduino_UART_UART_TX_DIRECTION (0u != (Arduino_UART_UART_DIRECTION & Arduino_UART_UART_TX))

        /* Get FIFO size */
        #if (Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1)
            #define Arduino_UART_SPI_UART_FIFO_SIZE    (Arduino_UART_FIFO_SIZE)
        #else
            #define Arduino_UART_SPI_UART_FIFO_SIZE \
                                           Arduino_UART_GET_FIFO_SIZE(Arduino_UART_UART_BYTE_MODE_ENABLE)
        #endif /* (Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define Arduino_UART_INTERNAL_UART_RX_SW_BUFFER  (Arduino_UART_UART_RX_BUFFER_SIZE > \
                                                                Arduino_UART_SPI_UART_FIFO_SIZE)
        #define Arduino_UART_INTERNAL_UART_TX_SW_BUFFER  (Arduino_UART_UART_TX_BUFFER_SIZE > \
                                                                    Arduino_UART_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define Arduino_UART_INTERNAL_RX_SW_BUFFER  (Arduino_UART_INTERNAL_UART_RX_SW_BUFFER)
        #define Arduino_UART_INTERNAL_TX_SW_BUFFER  (Arduino_UART_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define Arduino_UART_RX_BUFFER_SIZE         (Arduino_UART_UART_RX_BUFFER_SIZE + 1u)
        #define Arduino_UART_TX_BUFFER_SIZE         (Arduino_UART_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define Arduino_UART_SPI_WAKE_ENABLE_CONST  (0u)
        #define Arduino_UART_UART_WAKE_ENABLE_CONST (0u != Arduino_UART_UART_WAKE_ENABLE)

    #endif /* (Arduino_UART_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define Arduino_UART_SPI_MASTER_CONST   (Arduino_UART_SPI_MODE == Arduino_UART_SPI_MASTER)

    /* Direction */
    #define Arduino_UART_RX_DIRECTION ((Arduino_UART_SCB_MODE_SPI_CONST_CFG) ? \
                                            (Arduino_UART_SPI_RX_DIRECTION) : (Arduino_UART_UART_RX_DIRECTION))

    #define Arduino_UART_TX_DIRECTION ((Arduino_UART_SCB_MODE_SPI_CONST_CFG) ? \
                                            (Arduino_UART_SPI_TX_DIRECTION) : (Arduino_UART_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define Arduino_UART_CHECK_RX_SW_BUFFER (Arduino_UART_INTERNAL_RX_SW_BUFFER)
    #define Arduino_UART_CHECK_TX_SW_BUFFER (Arduino_UART_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define Arduino_UART_INTERNAL_RX_SW_BUFFER_CONST    (Arduino_UART_INTERNAL_RX_SW_BUFFER)
    #define Arduino_UART_INTERNAL_TX_SW_BUFFER_CONST    (Arduino_UART_INTERNAL_TX_SW_BUFFER)

    /* Wakeup for SPI */
    #define Arduino_UART_CHECK_SPI_WAKE_ENABLE  (Arduino_UART_SPI_WAKE_ENABLE_CONST)

#endif /* End (Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* Arduino_UART_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableFreeRunSclk;
    uint8 polaritySs;
} Arduino_UART_SPI_INIT_STRUCT;

/* Arduino_UART_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableCts;
    uint8 ctsPolarity;
    uint8 rtsRxFifoLevel;
    uint8 rtsPolarity;
} Arduino_UART_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    void Arduino_UART_SpiInit(const Arduino_UART_SPI_INIT_STRUCT *config);
#endif /* (Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(Arduino_UART_SCB_MODE_SPI_INC)
    #define Arduino_UART_SpiIsBusBusy() ((uint32) (0u != (Arduino_UART_SPI_STATUS_REG & \
                                                              Arduino_UART_SPI_STATUS_BUS_BUSY)))

    #if (Arduino_UART_SPI_MASTER_CONST)
        void Arduino_UART_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(Arduino_UART_SPI_MASTER_CONST) */

    #if !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1)
        void Arduino_UART_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1) */
#endif /* (Arduino_UART_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    void Arduino_UART_UartInit(const Arduino_UART_UART_INIT_STRUCT *config);
#endif /* (Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(Arduino_UART_SCB_MODE_UART_INC)
    void Arduino_UART_UartSetRxAddress(uint32 address);
    void Arduino_UART_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(Arduino_UART_UART_RX_DIRECTION)
        uint32 Arduino_UART_UartGetChar(void);
        uint32 Arduino_UART_UartGetByte(void);

        #if !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void Arduino_UART_UartSetRtsPolarity(uint32 polarity);
            void Arduino_UART_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1) */
    #endif /* (Arduino_UART_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(Arduino_UART_UART_TX_DIRECTION)
        #define Arduino_UART_UartPutChar(ch)    Arduino_UART_SpiUartWriteTxData((uint32)(ch))
        void Arduino_UART_UartPutString(const char8 string[]);
        void Arduino_UART_UartPutCRLF(uint32 txDataByte);

        #if !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void Arduino_UART_UartEnableCts(void);
            void Arduino_UART_UartDisableCts(void);
            void Arduino_UART_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(Arduino_UART_CY_SCBIP_V0 || Arduino_UART_CY_SCBIP_V1) */
    #endif /* (Arduino_UART_UART_TX_DIRECTION) */
#endif /* (Arduino_UART_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(Arduino_UART_RX_DIRECTION)
    uint32 Arduino_UART_SpiUartReadRxData(void);
    uint32 Arduino_UART_SpiUartGetRxBufferSize(void);
    void   Arduino_UART_SpiUartClearRxBuffer(void);
#endif /* (Arduino_UART_RX_DIRECTION) */

/* Common APIs TX direction */
#if(Arduino_UART_TX_DIRECTION)
    void   Arduino_UART_SpiUartWriteTxData(uint32 txData);
    void   Arduino_UART_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    void   Arduino_UART_SpiUartClearTxBuffer(void);
    uint32 Arduino_UART_SpiUartGetTxBufferSize(void);
#endif /* (Arduino_UART_TX_DIRECTION) */

CY_ISR_PROTO(Arduino_UART_SPI_UART_ISR);

#if(Arduino_UART_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(Arduino_UART_UART_WAKEUP_ISR);
#endif /* (Arduino_UART_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   Arduino_UART_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 Arduino_UART_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   Arduino_UART_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 Arduino_UART_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(Arduino_UART_INTERNAL_RX_SW_BUFFER_CONST)
        #define Arduino_UART_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    Arduino_UART_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define Arduino_UART_GetWordFromRxBuffer(idx) Arduino_UART_rxBufferInternal[(idx)]

    #endif /* (Arduino_UART_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(Arduino_UART_INTERNAL_TX_SW_BUFFER_CONST)
        #define Arduino_UART_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        Arduino_UART_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define Arduino_UART_GetWordFromTxBuffer(idx) Arduino_UART_txBufferInternal[(idx)]

    #endif /* (Arduino_UART_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (Arduino_UART_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define Arduino_UART_SPI_MODE_MOTOROLA      (0x00u)
#define Arduino_UART_SPI_MODE_TI_COINCIDES  (0x01u)
#define Arduino_UART_SPI_MODE_TI_PRECEDES   (0x11u)
#define Arduino_UART_SPI_MODE_NATIONAL      (0x02u)
#define Arduino_UART_SPI_MODE_MASK          (0x03u)
#define Arduino_UART_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define Arduino_UART_SPI_MODE_NS_MICROWIRE  (Arduino_UART_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define Arduino_UART_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define Arduino_UART_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define Arduino_UART_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define Arduino_UART_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define Arduino_UART_BITS_ORDER_LSB_FIRST   (0u)
#define Arduino_UART_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define Arduino_UART_SPI_TRANSFER_SEPARATED     (0u)
#define Arduino_UART_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define Arduino_UART_SPI_SLAVE_SELECT0    (Arduino_UART_SCB__SS0_POSISTION)
#define Arduino_UART_SPI_SLAVE_SELECT1    (Arduino_UART_SCB__SS1_POSISTION)
#define Arduino_UART_SPI_SLAVE_SELECT2    (Arduino_UART_SCB__SS2_POSISTION)
#define Arduino_UART_SPI_SLAVE_SELECT3    (Arduino_UART_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define Arduino_UART_SPI_SS_ACTIVE_LOW  (0u)
#define Arduino_UART_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define Arduino_UART_UART_MODE_STD          (0u)
#define Arduino_UART_UART_MODE_SMARTCARD    (1u)
#define Arduino_UART_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define Arduino_UART_UART_RX    (1u)
#define Arduino_UART_UART_TX    (2u)
#define Arduino_UART_UART_TX_RX (3u)

/* UART parity enum */
#define Arduino_UART_UART_PARITY_EVEN   (0u)
#define Arduino_UART_UART_PARITY_ODD    (1u)
#define Arduino_UART_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define Arduino_UART_UART_STOP_BITS_1   (2u)
#define Arduino_UART_UART_STOP_BITS_1_5 (3u)
#define Arduino_UART_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define Arduino_UART_UART_IRDA_LP_OVS16     (16u)
#define Arduino_UART_UART_IRDA_LP_OVS32     (32u)
#define Arduino_UART_UART_IRDA_LP_OVS48     (48u)
#define Arduino_UART_UART_IRDA_LP_OVS96     (96u)
#define Arduino_UART_UART_IRDA_LP_OVS192    (192u)
#define Arduino_UART_UART_IRDA_LP_OVS768    (768u)
#define Arduino_UART_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define Arduino_UART_UART_MP_MARK       (0x100u)
#define Arduino_UART_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define Arduino_UART_UART_CTS_ACTIVE_LOW    (0u)
#define Arduino_UART_UART_CTS_ACTIVE_HIGH   (1u)
#define Arduino_UART_UART_RTS_ACTIVE_LOW    (0u)
#define Arduino_UART_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define Arduino_UART_INTR_RX_ERR        (Arduino_UART_INTR_RX_OVERFLOW    | \
                                             Arduino_UART_INTR_RX_UNDERFLOW   | \
                                             Arduino_UART_INTR_RX_FRAME_ERROR | \
                                             Arduino_UART_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for Arduino_UART_UartGetByte() */
#define Arduino_UART_UART_RX_OVERFLOW       (Arduino_UART_INTR_RX_OVERFLOW << 8u)
#define Arduino_UART_UART_RX_UNDERFLOW      (Arduino_UART_INTR_RX_UNDERFLOW << 8u)
#define Arduino_UART_UART_RX_FRAME_ERROR    (Arduino_UART_INTR_RX_FRAME_ERROR << 8u)
#define Arduino_UART_UART_RX_PARITY_ERROR   (Arduino_UART_INTR_RX_PARITY_ERROR << 8u)
#define Arduino_UART_UART_RX_ERROR_MASK     (Arduino_UART_UART_RX_OVERFLOW    | \
                                                 Arduino_UART_UART_RX_UNDERFLOW   | \
                                                 Arduino_UART_UART_RX_FRAME_ERROR | \
                                                 Arduino_UART_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const Arduino_UART_SPI_INIT_STRUCT  Arduino_UART_configSpi;
    extern const Arduino_UART_UART_INIT_STRUCT Arduino_UART_configUart;
#endif /* (Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define Arduino_UART_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & Arduino_UART_INTR_SLAVE_SPI_BUS_ERROR)
#define Arduino_UART_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & Arduino_UART_INTR_MASTER_SPI_DONE)
#define Arduino_UART_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~Arduino_UART_INTR_SLAVE_SPI_BUS_ERROR)

#define Arduino_UART_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~Arduino_UART_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define Arduino_UART_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((Arduino_UART_UART_IRDA_LP_OVS16   == (oversample)) ? Arduino_UART_CTRL_OVS_IRDA_LP_OVS16 : \
         ((Arduino_UART_UART_IRDA_LP_OVS32   == (oversample)) ? Arduino_UART_CTRL_OVS_IRDA_LP_OVS32 : \
          ((Arduino_UART_UART_IRDA_LP_OVS48   == (oversample)) ? Arduino_UART_CTRL_OVS_IRDA_LP_OVS48 : \
           ((Arduino_UART_UART_IRDA_LP_OVS96   == (oversample)) ? Arduino_UART_CTRL_OVS_IRDA_LP_OVS96 : \
            ((Arduino_UART_UART_IRDA_LP_OVS192  == (oversample)) ? Arduino_UART_CTRL_OVS_IRDA_LP_OVS192 : \
             ((Arduino_UART_UART_IRDA_LP_OVS768  == (oversample)) ? Arduino_UART_CTRL_OVS_IRDA_LP_OVS768 : \
              ((Arduino_UART_UART_IRDA_LP_OVS1536 == (oversample)) ? Arduino_UART_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          Arduino_UART_CTRL_OVS_IRDA_LP_OVS16)))))))

#define Arduino_UART_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (Arduino_UART_UART_RX & (direction))) ? \
                                                                     (Arduino_UART_RX_CTRL_ENABLED) : (0u))

#define Arduino_UART_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (Arduino_UART_UART_TX & (direction))) ? \
                                                                     (Arduino_UART_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define Arduino_UART_CTRL_SPI      (Arduino_UART_CTRL_MODE_SPI)
#define Arduino_UART_SPI_RX_CTRL   (Arduino_UART_RX_CTRL_ENABLED)
#define Arduino_UART_SPI_TX_CTRL   (Arduino_UART_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define Arduino_UART_SPI_SS_POLARITY \
             (((uint32) Arduino_UART_SPI_SS0_POLARITY << Arduino_UART_SPI_SLAVE_SELECT0) | \
              ((uint32) Arduino_UART_SPI_SS1_POLARITY << Arduino_UART_SPI_SLAVE_SELECT1) | \
              ((uint32) Arduino_UART_SPI_SS2_POLARITY << Arduino_UART_SPI_SLAVE_SELECT2) | \
              ((uint32) Arduino_UART_SPI_SS3_POLARITY << Arduino_UART_SPI_SLAVE_SELECT3))

#if(Arduino_UART_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define Arduino_UART_SPI_DEFAULT_CTRL \
                    (Arduino_UART_GET_CTRL_OVS(Arduino_UART_SPI_OVS_FACTOR) | \
                     Arduino_UART_GET_CTRL_BYTE_MODE (Arduino_UART_SPI_BYTE_MODE_ENABLE) | \
                     Arduino_UART_GET_CTRL_EC_AM_MODE(Arduino_UART_SPI_WAKE_ENABLE)      | \
                     Arduino_UART_CTRL_SPI)

    #define Arduino_UART_SPI_DEFAULT_SPI_CTRL \
                    (Arduino_UART_GET_SPI_CTRL_CONTINUOUS    (Arduino_UART_SPI_TRANSFER_SEPARATION)       | \
                     Arduino_UART_GET_SPI_CTRL_SELECT_PRECEDE(Arduino_UART_SPI_SUB_MODE &                   \
                                                                  Arduino_UART_SPI_MODE_TI_PRECEDES_MASK)     | \
                     Arduino_UART_GET_SPI_CTRL_SCLK_MODE     (Arduino_UART_SPI_CLOCK_MODE)                | \
                     Arduino_UART_GET_SPI_CTRL_LATE_MISO_SAMPLE(Arduino_UART_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     Arduino_UART_GET_SPI_CTRL_SCLK_CONTINUOUS(Arduino_UART_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     Arduino_UART_GET_SPI_CTRL_SSEL_POLARITY (Arduino_UART_SPI_SS_POLARITY)               | \
                     Arduino_UART_GET_SPI_CTRL_SUB_MODE      (Arduino_UART_SPI_SUB_MODE)                  | \
                     Arduino_UART_GET_SPI_CTRL_MASTER_MODE   (Arduino_UART_SPI_MODE))

    /* RX direction */
    #define Arduino_UART_SPI_DEFAULT_RX_CTRL \
                    (Arduino_UART_GET_RX_CTRL_DATA_WIDTH(Arduino_UART_SPI_RX_DATA_BITS_NUM)     | \
                     Arduino_UART_GET_RX_CTRL_BIT_ORDER (Arduino_UART_SPI_BITS_ORDER)           | \
                     Arduino_UART_GET_RX_CTRL_MEDIAN    (Arduino_UART_SPI_MEDIAN_FILTER_ENABLE) | \
                     Arduino_UART_SPI_RX_CTRL)

    #define Arduino_UART_SPI_DEFAULT_RX_FIFO_CTRL \
                    Arduino_UART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(Arduino_UART_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define Arduino_UART_SPI_DEFAULT_TX_CTRL \
                    (Arduino_UART_GET_TX_CTRL_DATA_WIDTH(Arduino_UART_SPI_TX_DATA_BITS_NUM) | \
                     Arduino_UART_GET_TX_CTRL_BIT_ORDER (Arduino_UART_SPI_BITS_ORDER)       | \
                     Arduino_UART_SPI_TX_CTRL)

    #define Arduino_UART_SPI_DEFAULT_TX_FIFO_CTRL \
                    Arduino_UART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(Arduino_UART_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define Arduino_UART_SPI_DEFAULT_INTR_SPI_EC_MASK   (Arduino_UART_NO_INTR_SOURCES)

    #define Arduino_UART_SPI_DEFAULT_INTR_I2C_EC_MASK   (Arduino_UART_NO_INTR_SOURCES)
    #define Arduino_UART_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (Arduino_UART_SPI_INTR_RX_MASK & Arduino_UART_INTR_SLAVE_SPI_BUS_ERROR)

    #define Arduino_UART_SPI_DEFAULT_INTR_MASTER_MASK \
                    (Arduino_UART_SPI_INTR_TX_MASK & Arduino_UART_INTR_MASTER_SPI_DONE)

    #define Arduino_UART_SPI_DEFAULT_INTR_RX_MASK \
                    (Arduino_UART_SPI_INTR_RX_MASK & (uint32) ~Arduino_UART_INTR_SLAVE_SPI_BUS_ERROR)

    #define Arduino_UART_SPI_DEFAULT_INTR_TX_MASK \
                    (Arduino_UART_SPI_INTR_TX_MASK & (uint32) ~Arduino_UART_INTR_MASTER_SPI_DONE)

#endif /* (Arduino_UART_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define Arduino_UART_CTRL_UART      (Arduino_UART_CTRL_MODE_UART)
#define Arduino_UART_UART_RX_CTRL   (Arduino_UART_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define Arduino_UART_UART_TX_CTRL   (Arduino_UART_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(Arduino_UART_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(Arduino_UART_UART_MODE_IRDA == Arduino_UART_UART_SUB_MODE)

        #define Arduino_UART_DEFAULT_CTRL_OVS   ((0u != Arduino_UART_UART_IRDA_LOW_POWER) ?              \
                                (Arduino_UART_UART_GET_CTRL_OVS_IRDA_LP(Arduino_UART_UART_OVS_FACTOR)) : \
                                (Arduino_UART_CTRL_OVS_IRDA_OVS16))

    #else

        #define Arduino_UART_DEFAULT_CTRL_OVS   Arduino_UART_GET_CTRL_OVS(Arduino_UART_UART_OVS_FACTOR)

    #endif /* (Arduino_UART_UART_MODE_IRDA == Arduino_UART_UART_SUB_MODE) */

    #define Arduino_UART_UART_DEFAULT_CTRL \
                                (Arduino_UART_GET_CTRL_BYTE_MODE  (Arduino_UART_UART_BYTE_MODE_ENABLE)  | \
                                 Arduino_UART_GET_CTRL_ADDR_ACCEPT(Arduino_UART_UART_MP_ACCEPT_ADDRESS) | \
                                 Arduino_UART_DEFAULT_CTRL_OVS                                              | \
                                 Arduino_UART_CTRL_UART)

    #define Arduino_UART_UART_DEFAULT_UART_CTRL \
                                    (Arduino_UART_GET_UART_CTRL_MODE(Arduino_UART_UART_SUB_MODE))

    /* RX direction */
    #define Arduino_UART_UART_DEFAULT_RX_CTRL_PARITY \
                                ((Arduino_UART_UART_PARITY_NONE != Arduino_UART_UART_PARITY_TYPE) ?      \
                                  (Arduino_UART_GET_UART_RX_CTRL_PARITY(Arduino_UART_UART_PARITY_TYPE) | \
                                   Arduino_UART_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define Arduino_UART_UART_DEFAULT_UART_RX_CTRL \
                    (Arduino_UART_GET_UART_RX_CTRL_MODE(Arduino_UART_UART_STOP_BITS_NUM)                    | \
                     Arduino_UART_GET_UART_RX_CTRL_POLARITY(Arduino_UART_UART_IRDA_POLARITY)                | \
                     Arduino_UART_GET_UART_RX_CTRL_MP_MODE(Arduino_UART_UART_MP_MODE_ENABLE)                | \
                     Arduino_UART_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(Arduino_UART_UART_DROP_ON_PARITY_ERR) | \
                     Arduino_UART_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(Arduino_UART_UART_DROP_ON_FRAME_ERR)   | \
                     Arduino_UART_UART_DEFAULT_RX_CTRL_PARITY)

    #define Arduino_UART_UART_DEFAULT_RX_CTRL \
                                (Arduino_UART_GET_RX_CTRL_DATA_WIDTH(Arduino_UART_UART_DATA_BITS_NUM)        | \
                                 Arduino_UART_GET_RX_CTRL_MEDIAN    (Arduino_UART_UART_MEDIAN_FILTER_ENABLE) | \
                                 Arduino_UART_GET_UART_RX_CTRL_ENABLED(Arduino_UART_UART_DIRECTION))

    #define Arduino_UART_UART_DEFAULT_RX_FIFO_CTRL \
                                Arduino_UART_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(Arduino_UART_UART_RX_TRIGGER_LEVEL)

    #define Arduino_UART_UART_DEFAULT_RX_MATCH_REG  ((0u != Arduino_UART_UART_MP_MODE_ENABLE) ?          \
                                (Arduino_UART_GET_RX_MATCH_ADDR(Arduino_UART_UART_MP_RX_ADDRESS) | \
                                 Arduino_UART_GET_RX_MATCH_MASK(Arduino_UART_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define Arduino_UART_UART_DEFAULT_TX_CTRL_PARITY (Arduino_UART_UART_DEFAULT_RX_CTRL_PARITY)

    #define Arduino_UART_UART_DEFAULT_UART_TX_CTRL \
                                (Arduino_UART_GET_UART_TX_CTRL_MODE(Arduino_UART_UART_STOP_BITS_NUM)       | \
                                 Arduino_UART_GET_UART_TX_CTRL_RETRY_NACK(Arduino_UART_UART_RETRY_ON_NACK) | \
                                 Arduino_UART_UART_DEFAULT_TX_CTRL_PARITY)

    #define Arduino_UART_UART_DEFAULT_TX_CTRL \
                                (Arduino_UART_GET_TX_CTRL_DATA_WIDTH(Arduino_UART_UART_DATA_BITS_NUM) | \
                                 Arduino_UART_GET_UART_TX_CTRL_ENABLED(Arduino_UART_UART_DIRECTION))

    #define Arduino_UART_UART_DEFAULT_TX_FIFO_CTRL \
                                Arduino_UART_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(Arduino_UART_UART_TX_TRIGGER_LEVEL)

    #define Arduino_UART_UART_DEFAULT_FLOW_CTRL \
                        (Arduino_UART_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(Arduino_UART_UART_RTS_FIFO_LEVEL) | \
                         Arduino_UART_GET_UART_FLOW_CTRL_RTS_POLARITY (Arduino_UART_UART_RTS_POLARITY)   | \
                         Arduino_UART_GET_UART_FLOW_CTRL_CTS_POLARITY (Arduino_UART_UART_CTS_POLARITY)   | \
                         Arduino_UART_GET_UART_FLOW_CTRL_CTS_ENABLE   (Arduino_UART_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define Arduino_UART_UART_DEFAULT_INTR_I2C_EC_MASK  (Arduino_UART_NO_INTR_SOURCES)
    #define Arduino_UART_UART_DEFAULT_INTR_SPI_EC_MASK  (Arduino_UART_NO_INTR_SOURCES)
    #define Arduino_UART_UART_DEFAULT_INTR_SLAVE_MASK   (Arduino_UART_NO_INTR_SOURCES)
    #define Arduino_UART_UART_DEFAULT_INTR_MASTER_MASK  (Arduino_UART_NO_INTR_SOURCES)
    #define Arduino_UART_UART_DEFAULT_INTR_RX_MASK      (Arduino_UART_UART_INTR_RX_MASK)
    #define Arduino_UART_UART_DEFAULT_INTR_TX_MASK      (Arduino_UART_UART_INTR_TX_MASK)

#endif /* (Arduino_UART_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define Arduino_UART_SPIM_ACTIVE_SS0    (Arduino_UART_SPI_SLAVE_SELECT0)
#define Arduino_UART_SPIM_ACTIVE_SS1    (Arduino_UART_SPI_SLAVE_SELECT1)
#define Arduino_UART_SPIM_ACTIVE_SS2    (Arduino_UART_SPI_SLAVE_SELECT2)
#define Arduino_UART_SPIM_ACTIVE_SS3    (Arduino_UART_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_Arduino_UART_H */


/* [] END OF FILE */
