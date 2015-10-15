/*******************************************************************************
* File Name: effector_A.h  
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

#if !defined(CY_PINS_effector_A_H) /* Pins effector_A_H */
#define CY_PINS_effector_A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "effector_A_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    effector_A_Write(uint8 value) ;
void    effector_A_SetDriveMode(uint8 mode) ;
uint8   effector_A_ReadDataReg(void) ;
uint8   effector_A_Read(void) ;
uint8   effector_A_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define effector_A_DRIVE_MODE_BITS        (3)
#define effector_A_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - effector_A_DRIVE_MODE_BITS))

#define effector_A_DM_ALG_HIZ         (0x00u)
#define effector_A_DM_DIG_HIZ         (0x01u)
#define effector_A_DM_RES_UP          (0x02u)
#define effector_A_DM_RES_DWN         (0x03u)
#define effector_A_DM_OD_LO           (0x04u)
#define effector_A_DM_OD_HI           (0x05u)
#define effector_A_DM_STRONG          (0x06u)
#define effector_A_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define effector_A_MASK               effector_A__MASK
#define effector_A_SHIFT              effector_A__SHIFT
#define effector_A_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define effector_A_PS                     (* (reg32 *) effector_A__PS)
/* Port Configuration */
#define effector_A_PC                     (* (reg32 *) effector_A__PC)
/* Data Register */
#define effector_A_DR                     (* (reg32 *) effector_A__DR)
/* Input Buffer Disable Override */
#define effector_A_INP_DIS                (* (reg32 *) effector_A__PC2)


#if defined(effector_A__INTSTAT)  /* Interrupt Registers */

    #define effector_A_INTSTAT                (* (reg32 *) effector_A__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define effector_A_DRIVE_MODE_SHIFT       (0x00u)
#define effector_A_DRIVE_MODE_MASK        (0x07u << effector_A_DRIVE_MODE_SHIFT)


#endif /* End Pins effector_A_H */


/* [] END OF FILE */
