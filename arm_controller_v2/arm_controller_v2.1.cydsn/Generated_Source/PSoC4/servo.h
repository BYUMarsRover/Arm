/*******************************************************************************
* File Name: servo.h  
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

#if !defined(CY_PINS_servo_H) /* Pins servo_H */
#define CY_PINS_servo_H

#include "cytypes.h"
#include "cyfitter.h"
#include "servo_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    servo_Write(uint8 value) ;
void    servo_SetDriveMode(uint8 mode) ;
uint8   servo_ReadDataReg(void) ;
uint8   servo_Read(void) ;
uint8   servo_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define servo_DRIVE_MODE_BITS        (3)
#define servo_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - servo_DRIVE_MODE_BITS))

#define servo_DM_ALG_HIZ         (0x00u)
#define servo_DM_DIG_HIZ         (0x01u)
#define servo_DM_RES_UP          (0x02u)
#define servo_DM_RES_DWN         (0x03u)
#define servo_DM_OD_LO           (0x04u)
#define servo_DM_OD_HI           (0x05u)
#define servo_DM_STRONG          (0x06u)
#define servo_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define servo_MASK               servo__MASK
#define servo_SHIFT              servo__SHIFT
#define servo_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define servo_PS                     (* (reg32 *) servo__PS)
/* Port Configuration */
#define servo_PC                     (* (reg32 *) servo__PC)
/* Data Register */
#define servo_DR                     (* (reg32 *) servo__DR)
/* Input Buffer Disable Override */
#define servo_INP_DIS                (* (reg32 *) servo__PC2)


#if defined(servo__INTSTAT)  /* Interrupt Registers */

    #define servo_INTSTAT                (* (reg32 *) servo__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define servo_DRIVE_MODE_SHIFT       (0x00u)
#define servo_DRIVE_MODE_MASK        (0x07u << servo_DRIVE_MODE_SHIFT)


#endif /* End Pins servo_H */


/* [] END OF FILE */
