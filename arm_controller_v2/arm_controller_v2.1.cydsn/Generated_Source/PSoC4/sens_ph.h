/*******************************************************************************
* File Name: sens_ph.h  
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

#if !defined(CY_PINS_sens_ph_H) /* Pins sens_ph_H */
#define CY_PINS_sens_ph_H

#include "cytypes.h"
#include "cyfitter.h"
#include "sens_ph_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    sens_ph_Write(uint8 value) ;
void    sens_ph_SetDriveMode(uint8 mode) ;
uint8   sens_ph_ReadDataReg(void) ;
uint8   sens_ph_Read(void) ;
uint8   sens_ph_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define sens_ph_DRIVE_MODE_BITS        (3)
#define sens_ph_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - sens_ph_DRIVE_MODE_BITS))

#define sens_ph_DM_ALG_HIZ         (0x00u)
#define sens_ph_DM_DIG_HIZ         (0x01u)
#define sens_ph_DM_RES_UP          (0x02u)
#define sens_ph_DM_RES_DWN         (0x03u)
#define sens_ph_DM_OD_LO           (0x04u)
#define sens_ph_DM_OD_HI           (0x05u)
#define sens_ph_DM_STRONG          (0x06u)
#define sens_ph_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define sens_ph_MASK               sens_ph__MASK
#define sens_ph_SHIFT              sens_ph__SHIFT
#define sens_ph_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sens_ph_PS                     (* (reg32 *) sens_ph__PS)
/* Port Configuration */
#define sens_ph_PC                     (* (reg32 *) sens_ph__PC)
/* Data Register */
#define sens_ph_DR                     (* (reg32 *) sens_ph__DR)
/* Input Buffer Disable Override */
#define sens_ph_INP_DIS                (* (reg32 *) sens_ph__PC2)


#if defined(sens_ph__INTSTAT)  /* Interrupt Registers */

    #define sens_ph_INTSTAT                (* (reg32 *) sens_ph__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define sens_ph_DRIVE_MODE_SHIFT       (0x00u)
#define sens_ph_DRIVE_MODE_MASK        (0x07u << sens_ph_DRIVE_MODE_SHIFT)


#endif /* End Pins sens_ph_H */


/* [] END OF FILE */
