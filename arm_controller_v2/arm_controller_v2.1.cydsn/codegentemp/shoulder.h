/*******************************************************************************
* File Name: shoulder.h  
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

#if !defined(CY_PINS_shoulder_H) /* Pins shoulder_H */
#define CY_PINS_shoulder_H

#include "cytypes.h"
#include "cyfitter.h"
#include "shoulder_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    shoulder_Write(uint8 value) ;
void    shoulder_SetDriveMode(uint8 mode) ;
uint8   shoulder_ReadDataReg(void) ;
uint8   shoulder_Read(void) ;
uint8   shoulder_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define shoulder_DRIVE_MODE_BITS        (3)
#define shoulder_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - shoulder_DRIVE_MODE_BITS))

#define shoulder_DM_ALG_HIZ         (0x00u)
#define shoulder_DM_DIG_HIZ         (0x01u)
#define shoulder_DM_RES_UP          (0x02u)
#define shoulder_DM_RES_DWN         (0x03u)
#define shoulder_DM_OD_LO           (0x04u)
#define shoulder_DM_OD_HI           (0x05u)
#define shoulder_DM_STRONG          (0x06u)
#define shoulder_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define shoulder_MASK               shoulder__MASK
#define shoulder_SHIFT              shoulder__SHIFT
#define shoulder_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define shoulder_PS                     (* (reg32 *) shoulder__PS)
/* Port Configuration */
#define shoulder_PC                     (* (reg32 *) shoulder__PC)
/* Data Register */
#define shoulder_DR                     (* (reg32 *) shoulder__DR)
/* Input Buffer Disable Override */
#define shoulder_INP_DIS                (* (reg32 *) shoulder__PC2)


#if defined(shoulder__INTSTAT)  /* Interrupt Registers */

    #define shoulder_INTSTAT                (* (reg32 *) shoulder__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define shoulder_DRIVE_MODE_SHIFT       (0x00u)
#define shoulder_DRIVE_MODE_MASK        (0x07u << shoulder_DRIVE_MODE_SHIFT)


#endif /* End Pins shoulder_H */


/* [] END OF FILE */
