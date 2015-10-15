/*******************************************************************************
* File Name: servo.c  
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
#include "servo.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        servo_PC =   (servo_PC & \
                                (uint32)(~(uint32)(servo_DRIVE_MODE_IND_MASK << (servo_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (servo_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: servo_Write
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
void servo_Write(uint8 value) 
{
    uint8 drVal = (uint8)(servo_DR & (uint8)(~servo_MASK));
    drVal = (drVal | ((uint8)(value << servo_SHIFT) & servo_MASK));
    servo_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: servo_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  servo_DM_STRONG     Strong Drive 
*  servo_DM_OD_HI      Open Drain, Drives High 
*  servo_DM_OD_LO      Open Drain, Drives Low 
*  servo_DM_RES_UP     Resistive Pull Up 
*  servo_DM_RES_DWN    Resistive Pull Down 
*  servo_DM_RES_UPDWN  Resistive Pull Up/Down 
*  servo_DM_DIG_HIZ    High Impedance Digital 
*  servo_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void servo_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(servo__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: servo_Read
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
*  Macro servo_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 servo_Read(void) 
{
    return (uint8)((servo_PS & servo_MASK) >> servo_SHIFT);
}


/*******************************************************************************
* Function Name: servo_ReadDataReg
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
uint8 servo_ReadDataReg(void) 
{
    return (uint8)((servo_DR & servo_MASK) >> servo_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(servo_INTSTAT) 

    /*******************************************************************************
    * Function Name: servo_ClearInterrupt
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
    uint8 servo_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(servo_INTSTAT & servo_MASK);
		servo_INTSTAT = maskedStatus;
        return maskedStatus >> servo_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
