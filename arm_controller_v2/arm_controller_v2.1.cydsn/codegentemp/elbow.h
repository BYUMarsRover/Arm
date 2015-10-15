/*******************************************************************************
* File Name: elbow.h  
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

#if !defined(CY_PINS_elbow_H) /* Pins elbow_H */
#define CY_PINS_elbow_H

#include "cytypes.h"
#include "cyfitter.h"
#include "elbow_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    elbow_Write(uint8 value) ;
void    elbow_SetDriveMode(uint8 mode) ;
uint8   elbow_ReadDataReg(void) ;
uint8   elbow_Read(void) ;
uint8   elbow_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define elbow_DRIVE_MODE_BITS        (3)
#define elbow_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - elbow_DRIVE_MODE_BITS))

#define elbow_DM_ALG_HIZ         (0x00u)
#define elbow_DM_DIG_HIZ         (0x01u)
#define elbow_DM_RES_UP          (0x02u)
#define elbow_DM_RES_DWN         (0x03u)
#define elbow_DM_OD_LO           (0x04u)
#define elbow_DM_OD_HI           (0x05u)
#define elbow_DM_STRONG          (0x06u)
#define elbow_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define elbow_MASK               elbow__MASK
#define elbow_SHIFT              elbow__SHIFT
#define elbow_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define elbow_PS                     (* (reg32 *) elbow__PS)
/* Port Configuration */
#define elbow_PC                     (* (reg32 *) elbow__PC)
/* Data Register */
#define elbow_DR                     (* (reg32 *) elbow__DR)
/* Input Buffer Disable Override */
#define elbow_INP_DIS                (* (reg32 *) elbow__PC2)


#if defined(elbow__INTSTAT)  /* Interrupt Registers */

    #define elbow_INTSTAT                (* (reg32 *) elbow__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define elbow_DRIVE_MODE_SHIFT       (0x00u)
#define elbow_DRIVE_MODE_MASK        (0x07u << elbow_DRIVE_MODE_SHIFT)


#endif /* End Pins elbow_H */


/* [] END OF FILE */
