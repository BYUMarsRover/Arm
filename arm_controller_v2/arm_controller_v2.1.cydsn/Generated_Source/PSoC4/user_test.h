/*******************************************************************************
* File Name: user_test.h  
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

#if !defined(CY_PINS_user_test_H) /* Pins user_test_H */
#define CY_PINS_user_test_H

#include "cytypes.h"
#include "cyfitter.h"
#include "user_test_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    user_test_Write(uint8 value) ;
void    user_test_SetDriveMode(uint8 mode) ;
uint8   user_test_ReadDataReg(void) ;
uint8   user_test_Read(void) ;
uint8   user_test_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define user_test_DRIVE_MODE_BITS        (3)
#define user_test_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - user_test_DRIVE_MODE_BITS))

#define user_test_DM_ALG_HIZ         (0x00u)
#define user_test_DM_DIG_HIZ         (0x01u)
#define user_test_DM_RES_UP          (0x02u)
#define user_test_DM_RES_DWN         (0x03u)
#define user_test_DM_OD_LO           (0x04u)
#define user_test_DM_OD_HI           (0x05u)
#define user_test_DM_STRONG          (0x06u)
#define user_test_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define user_test_MASK               user_test__MASK
#define user_test_SHIFT              user_test__SHIFT
#define user_test_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define user_test_PS                     (* (reg32 *) user_test__PS)
/* Port Configuration */
#define user_test_PC                     (* (reg32 *) user_test__PC)
/* Data Register */
#define user_test_DR                     (* (reg32 *) user_test__DR)
/* Input Buffer Disable Override */
#define user_test_INP_DIS                (* (reg32 *) user_test__PC2)


#if defined(user_test__INTSTAT)  /* Interrupt Registers */

    #define user_test_INTSTAT                (* (reg32 *) user_test__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define user_test_DRIVE_MODE_SHIFT       (0x00u)
#define user_test_DRIVE_MODE_MASK        (0x07u << user_test_DRIVE_MODE_SHIFT)


#endif /* End Pins user_test_H */


/* [] END OF FILE */
