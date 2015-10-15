/*******************************************************************************
* File Name: baseAzimuth.h  
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

#if !defined(CY_PINS_baseAzimuth_H) /* Pins baseAzimuth_H */
#define CY_PINS_baseAzimuth_H

#include "cytypes.h"
#include "cyfitter.h"
#include "baseAzimuth_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    baseAzimuth_Write(uint8 value) ;
void    baseAzimuth_SetDriveMode(uint8 mode) ;
uint8   baseAzimuth_ReadDataReg(void) ;
uint8   baseAzimuth_Read(void) ;
uint8   baseAzimuth_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define baseAzimuth_DRIVE_MODE_BITS        (3)
#define baseAzimuth_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - baseAzimuth_DRIVE_MODE_BITS))

#define baseAzimuth_DM_ALG_HIZ         (0x00u)
#define baseAzimuth_DM_DIG_HIZ         (0x01u)
#define baseAzimuth_DM_RES_UP          (0x02u)
#define baseAzimuth_DM_RES_DWN         (0x03u)
#define baseAzimuth_DM_OD_LO           (0x04u)
#define baseAzimuth_DM_OD_HI           (0x05u)
#define baseAzimuth_DM_STRONG          (0x06u)
#define baseAzimuth_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define baseAzimuth_MASK               baseAzimuth__MASK
#define baseAzimuth_SHIFT              baseAzimuth__SHIFT
#define baseAzimuth_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define baseAzimuth_PS                     (* (reg32 *) baseAzimuth__PS)
/* Port Configuration */
#define baseAzimuth_PC                     (* (reg32 *) baseAzimuth__PC)
/* Data Register */
#define baseAzimuth_DR                     (* (reg32 *) baseAzimuth__DR)
/* Input Buffer Disable Override */
#define baseAzimuth_INP_DIS                (* (reg32 *) baseAzimuth__PC2)


#if defined(baseAzimuth__INTSTAT)  /* Interrupt Registers */

    #define baseAzimuth_INTSTAT                (* (reg32 *) baseAzimuth__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define baseAzimuth_DRIVE_MODE_SHIFT       (0x00u)
#define baseAzimuth_DRIVE_MODE_MASK        (0x07u << baseAzimuth_DRIVE_MODE_SHIFT)


#endif /* End Pins baseAzimuth_H */


/* [] END OF FILE */
