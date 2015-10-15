/*******************************************************************************
* File Name: tx.h  
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

#if !defined(CY_PINS_tx_H) /* Pins tx_H */
#define CY_PINS_tx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "tx_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    tx_Write(uint8 value) ;
void    tx_SetDriveMode(uint8 mode) ;
uint8   tx_ReadDataReg(void) ;
uint8   tx_Read(void) ;
uint8   tx_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define tx_DRIVE_MODE_BITS        (3)
#define tx_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - tx_DRIVE_MODE_BITS))

#define tx_DM_ALG_HIZ         (0x00u)
#define tx_DM_DIG_HIZ         (0x01u)
#define tx_DM_RES_UP          (0x02u)
#define tx_DM_RES_DWN         (0x03u)
#define tx_DM_OD_LO           (0x04u)
#define tx_DM_OD_HI           (0x05u)
#define tx_DM_STRONG          (0x06u)
#define tx_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define tx_MASK               tx__MASK
#define tx_SHIFT              tx__SHIFT
#define tx_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define tx_PS                     (* (reg32 *) tx__PS)
/* Port Configuration */
#define tx_PC                     (* (reg32 *) tx__PC)
/* Data Register */
#define tx_DR                     (* (reg32 *) tx__DR)
/* Input Buffer Disable Override */
#define tx_INP_DIS                (* (reg32 *) tx__PC2)


#if defined(tx__INTSTAT)  /* Interrupt Registers */

    #define tx_INTSTAT                (* (reg32 *) tx__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define tx_DRIVE_MODE_SHIFT       (0x00u)
#define tx_DRIVE_MODE_MASK        (0x07u << tx_DRIVE_MODE_SHIFT)


#endif /* End Pins tx_H */


/* [] END OF FILE */
