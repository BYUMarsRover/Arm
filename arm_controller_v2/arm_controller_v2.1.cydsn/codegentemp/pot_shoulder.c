/*******************************************************************************
* File Name: pot_shoulder.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "pot_shoulder.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        pot_shoulder_PC =   (pot_shoulder_PC & \
                                (uint32)(~(uint32)(pot_shoulder_DRIVE_MODE_IND_MASK << (pot_shoulder_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (pot_shoulder_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: pot_shoulder_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void pot_shoulder_Write(uint8 value) 
{
    uint8 drVal = (uint8)(pot_shoulder_DR & (uint8)(~pot_shoulder_MASK));
    drVal = (drVal | ((uint8)(value << pot_shoulder_SHIFT) & pot_shoulder_MASK));
    pot_shoulder_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: pot_shoulder_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  pot_shoulder_DM_STRONG     Strong Drive 
*  pot_shoulder_DM_OD_HI      Open Drain, Drives High 
*  pot_shoulder_DM_OD_LO      Open Drain, Drives Low 
*  pot_shoulder_DM_RES_UP     Resistive Pull Up 
*  pot_shoulder_DM_RES_DWN    Resistive Pull Down 
*  pot_shoulder_DM_RES_UPDWN  Resistive Pull Up/Down 
*  pot_shoulder_DM_DIG_HIZ    High Impedance Digital 
*  pot_shoulder_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void pot_shoulder_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(pot_shoulder__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: pot_shoulder_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro pot_shoulder_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 pot_shoulder_Read(void) 
{
    return (uint8)((pot_shoulder_PS & pot_shoulder_MASK) >> pot_shoulder_SHIFT);
}


/*******************************************************************************
* Function Name: pot_shoulder_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 pot_shoulder_ReadDataReg(void) 
{
    return (uint8)((pot_shoulder_DR & pot_shoulder_MASK) >> pot_shoulder_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(pot_shoulder_INTSTAT) 

    /*******************************************************************************
    * Function Name: pot_shoulder_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 pot_shoulder_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(pot_shoulder_INTSTAT & pot_shoulder_MASK);
		pot_shoulder_INTSTAT = maskedStatus;
        return maskedStatus >> pot_shoulder_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
