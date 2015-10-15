/*******************************************************************************
* File Name: stop_shdr_up.h  
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

#if !defined(CY_PINS_stop_shdr_up_H) /* Pins stop_shdr_up_H */
#define CY_PINS_stop_shdr_up_H

#include "cytypes.h"
#include "cyfitter.h"
#include "stop_shdr_up_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    stop_shdr_up_Write(uint8 value) ;
void    stop_shdr_up_SetDriveMode(uint8 mode) ;
uint8   stop_shdr_up_ReadDataReg(void) ;
uint8   stop_shdr_up_Read(void) ;
uint8   stop_shdr_up_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define stop_shdr_up_DRIVE_MODE_BITS        (3)
#define stop_shdr_up_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - stop_shdr_up_DRIVE_MODE_BITS))

#define stop_shdr_up_DM_ALG_HIZ         (0x00u)
#define stop_shdr_up_DM_DIG_HIZ         (0x01u)
#define stop_shdr_up_DM_RES_UP          (0x02u)
#define stop_shdr_up_DM_RES_DWN         (0x03u)
#define stop_shdr_up_DM_OD_LO           (0x04u)
#define stop_shdr_up_DM_OD_HI           (0x05u)
#define stop_shdr_up_DM_STRONG          (0x06u)
#define stop_shdr_up_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define stop_shdr_up_MASK               stop_shdr_up__MASK
#define stop_shdr_up_SHIFT              stop_shdr_up__SHIFT
#define stop_shdr_up_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define stop_shdr_up_PS                     (* (reg32 *) stop_shdr_up__PS)
/* Port Configuration */
#define stop_shdr_up_PC                     (* (reg32 *) stop_shdr_up__PC)
/* Data Register */
#define stop_shdr_up_DR                     (* (reg32 *) stop_shdr_up__DR)
/* Input Buffer Disable Override */
#define stop_shdr_up_INP_DIS                (* (reg32 *) stop_shdr_up__PC2)


#if defined(stop_shdr_up__INTSTAT)  /* Interrupt Registers */

    #define stop_shdr_up_INTSTAT                (* (reg32 *) stop_shdr_up__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define stop_shdr_up_DRIVE_MODE_SHIFT       (0x00u)
#define stop_shdr_up_DRIVE_MODE_MASK        (0x07u << stop_shdr_up_DRIVE_MODE_SHIFT)


#endif /* End Pins stop_shdr_up_H */


/* [] END OF FILE */
