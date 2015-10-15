/*******************************************************************************
* File Name: effector_A.c  
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
#include "effector_A.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        effector_A_PC =   (effector_A_PC & \
                                (uint32)(~(uint32)(effector_A_DRIVE_MODE_IND_MASK << (effector_A_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (effector_A_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: effector_A_Write
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
void effector_A_Write(uint8 value) 
{
    uint8 drVal = (uint8)(effector_A_DR & (uint8)(~effector_A_MASK));
    drVal = (drVal | ((uint8)(value << effector_A_SHIFT) & effector_A_MASK));
    effector_A_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: effector_A_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  effector_A_DM_STRONG     Strong Drive 
*  effector_A_DM_OD_HI      Open Drain, Drives High 
*  effector_A_DM_OD_LO      Open Drain, Drives Low 
*  effector_A_DM_RES_UP     Resistive Pull Up 
*  effector_A_DM_RES_DWN    Resistive Pull Down 
*  effector_A_DM_RES_UPDWN  Resistive Pull Up/Down 
*  effector_A_DM_DIG_HIZ    High Impedance Digital 
*  effector_A_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void effector_A_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(effector_A__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: effector_A_Read
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
*  Macro effector_A_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 effector_A_Read(void) 
{
    return (uint8)((effector_A_PS & effector_A_MASK) >> effector_A_SHIFT);
}


/*******************************************************************************
* Function Name: effector_A_ReadDataReg
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
uint8 effector_A_ReadDataReg(void) 
{
    return (uint8)((effector_A_DR & effector_A_MASK) >> effector_A_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(effector_A_INTSTAT) 

    /*******************************************************************************
    * Function Name: effector_A_ClearInterrupt
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
    uint8 effector_A_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(effector_A_INTSTAT & effector_A_MASK);
		effector_A_INTSTAT = maskedStatus;
        return maskedStatus >> effector_A_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
