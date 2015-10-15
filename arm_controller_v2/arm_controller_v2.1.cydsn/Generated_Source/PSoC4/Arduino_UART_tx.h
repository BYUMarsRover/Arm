/*******************************************************************************
* File Name: Arduino_UART_tx.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Arduino_UART_tx_H) /* Pins Arduino_UART_tx_H */
#define CY_PINS_Arduino_UART_tx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Arduino_UART_tx_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Arduino_UART_tx_Write(uint8 value) ;
void    Arduino_UART_tx_SetDriveMode(uint8 mode) ;
uint8   Arduino_UART_tx_ReadDataReg(void) ;
uint8   Arduino_UART_tx_Read(void) ;
uint8   Arduino_UART_tx_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Arduino_UART_tx_DRIVE_MODE_BITS        (3)
#define Arduino_UART_tx_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Arduino_UART_tx_DRIVE_MODE_BITS))

#define Arduino_UART_tx_DM_ALG_HIZ         (0x00u)
#define Arduino_UART_tx_DM_DIG_HIZ         (0x01u)
#define Arduino_UART_tx_DM_RES_UP          (0x02u)
#define Arduino_UART_tx_DM_RES_DWN         (0x03u)
#define Arduino_UART_tx_DM_OD_LO           (0x04u)
#define Arduino_UART_tx_DM_OD_HI           (0x05u)
#define Arduino_UART_tx_DM_STRONG          (0x06u)
#define Arduino_UART_tx_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Arduino_UART_tx_MASK               Arduino_UART_tx__MASK
#define Arduino_UART_tx_SHIFT              Arduino_UART_tx__SHIFT
#define Arduino_UART_tx_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Arduino_UART_tx_PS                     (* (reg32 *) Arduino_UART_tx__PS)
/* Port Configuration */
#define Arduino_UART_tx_PC                     (* (reg32 *) Arduino_UART_tx__PC)
/* Data Register */
#define Arduino_UART_tx_DR                     (* (reg32 *) Arduino_UART_tx__DR)
/* Input Buffer Disable Override */
#define Arduino_UART_tx_INP_DIS                (* (reg32 *) Arduino_UART_tx__PC2)


#if defined(Arduino_UART_tx__INTSTAT)  /* Interrupt Registers */

    #define Arduino_UART_tx_INTSTAT                (* (reg32 *) Arduino_UART_tx__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Arduino_UART_tx_DRIVE_MODE_SHIFT       (0x00u)
#define Arduino_UART_tx_DRIVE_MODE_MASK        (0x07u << Arduino_UART_tx_DRIVE_MODE_SHIFT)


#endif /* End Pins Arduino_UART_tx_H */


/* [] END OF FILE */
