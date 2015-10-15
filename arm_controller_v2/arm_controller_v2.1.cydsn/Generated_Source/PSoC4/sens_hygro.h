/*******************************************************************************
* File Name: sens_hygro.h  
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

#if !defined(CY_PINS_sens_hygro_H) /* Pins sens_hygro_H */
#define CY_PINS_sens_hygro_H

#include "cytypes.h"
#include "cyfitter.h"
#include "sens_hygro_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    sens_hygro_Write(uint8 value) ;
void    sens_hygro_SetDriveMode(uint8 mode) ;
uint8   sens_hygro_ReadDataReg(void) ;
uint8   sens_hygro_Read(void) ;
uint8   sens_hygro_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define sens_hygro_DRIVE_MODE_BITS        (3)
#define sens_hygro_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - sens_hygro_DRIVE_MODE_BITS))

#define sens_hygro_DM_ALG_HIZ         (0x00u)
#define sens_hygro_DM_DIG_HIZ         (0x01u)
#define sens_hygro_DM_RES_UP          (0x02u)
#define sens_hygro_DM_RES_DWN         (0x03u)
#define sens_hygro_DM_OD_LO           (0x04u)
#define sens_hygro_DM_OD_HI           (0x05u)
#define sens_hygro_DM_STRONG          (0x06u)
#define sens_hygro_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define sens_hygro_MASK               sens_hygro__MASK
#define sens_hygro_SHIFT              sens_hygro__SHIFT
#define sens_hygro_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sens_hygro_PS                     (* (reg32 *) sens_hygro__PS)
/* Port Configuration */
#define sens_hygro_PC                     (* (reg32 *) sens_hygro__PC)
/* Data Register */
#define sens_hygro_DR                     (* (reg32 *) sens_hygro__DR)
/* Input Buffer Disable Override */
#define sens_hygro_INP_DIS                (* (reg32 *) sens_hygro__PC2)


#if defined(sens_hygro__INTSTAT)  /* Interrupt Registers */

    #define sens_hygro_INTSTAT                (* (reg32 *) sens_hygro__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define sens_hygro_DRIVE_MODE_SHIFT       (0x00u)
#define sens_hygro_DRIVE_MODE_MASK        (0x07u << sens_hygro_DRIVE_MODE_SHIFT)


#endif /* End Pins sens_hygro_H */


/* [] END OF FILE */
