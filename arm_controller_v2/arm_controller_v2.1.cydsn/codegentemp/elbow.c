/*******************************************************************************
* File Name: elbow.c  
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
#include "elbow.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        elbow_PC =   (elbow_PC & \
                                (uint32)(~(uint32)(elbow_DRIVE_MODE_IND_MASK << (elbow_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (elbow_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: elbow_Write
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
void elbow_Write(uint8 value) 
{
    uint8 drVal = (uint8)(elbow_DR & (uint8)(~elbow_MASK));
    drVal = (drVal | ((uint8)(value << elbow_SHIFT) & elbow_MASK));
    elbow_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: elbow_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  elbow_DM_STRONG     Strong Drive 
*  elbow_DM_OD_HI      Open Drain, Drives High 
*  elbow_DM_OD_LO      Open Drain, Drives Low 
*  elbow_DM_RES_UP     Resistive Pull Up 
*  elbow_DM_RES_DWN    Resistive Pull Down 
*  elbow_DM_RES_UPDWN  Resistive Pull Up/Down 
*  elbow_DM_DIG_HIZ    High Impedance Digital 
*  elbow_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void elbow_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(elbow__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: elbow_Read
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
*  Macro elbow_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 elbow_Read(void) 
{
    return (uint8)((elbow_PS & elbow_MASK) >> elbow_SHIFT);
}


/*******************************************************************************
* Function Name: elbow_ReadDataReg
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
uint8 elbow_ReadDataReg(void) 
{
    return (uint8)((elbow_DR & elbow_MASK) >> elbow_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(elbow_INTSTAT) 

    /*******************************************************************************
    * Function Name: elbow_ClearInterrupt
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
    uint8 elbow_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(elbow_INTSTAT & elbow_MASK);
		elbow_INTSTAT = maskedStatus;
        return maskedStatus >> elbow_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
