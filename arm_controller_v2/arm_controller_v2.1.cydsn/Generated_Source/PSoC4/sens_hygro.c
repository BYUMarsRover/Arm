/*******************************************************************************
* File Name: sens_hygro.c  
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
#include "sens_hygro.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        sens_hygro_PC =   (sens_hygro_PC & \
                                (uint32)(~(uint32)(sens_hygro_DRIVE_MODE_IND_MASK << (sens_hygro_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (sens_hygro_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: sens_hygro_Write
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
void sens_hygro_Write(uint8 value) 
{
    uint8 drVal = (uint8)(sens_hygro_DR & (uint8)(~sens_hygro_MASK));
    drVal = (drVal | ((uint8)(value << sens_hygro_SHIFT) & sens_hygro_MASK));
    sens_hygro_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: sens_hygro_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  sens_hygro_DM_STRONG     Strong Drive 
*  sens_hygro_DM_OD_HI      Open Drain, Drives High 
*  sens_hygro_DM_OD_LO      Open Drain, Drives Low 
*  sens_hygro_DM_RES_UP     Resistive Pull Up 
*  sens_hygro_DM_RES_DWN    Resistive Pull Down 
*  sens_hygro_DM_RES_UPDWN  Resistive Pull Up/Down 
*  sens_hygro_DM_DIG_HIZ    High Impedance Digital 
*  sens_hygro_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void sens_hygro_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(sens_hygro__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: sens_hygro_Read
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
*  Macro sens_hygro_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 sens_hygro_Read(void) 
{
    return (uint8)((sens_hygro_PS & sens_hygro_MASK) >> sens_hygro_SHIFT);
}


/*******************************************************************************
* Function Name: sens_hygro_ReadDataReg
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
uint8 sens_hygro_ReadDataReg(void) 
{
    return (uint8)((sens_hygro_DR & sens_hygro_MASK) >> sens_hygro_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(sens_hygro_INTSTAT) 

    /*******************************************************************************
    * Function Name: sens_hygro_ClearInterrupt
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
    uint8 sens_hygro_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(sens_hygro_INTSTAT & sens_hygro_MASK);
		sens_hygro_INTSTAT = maskedStatus;
        return maskedStatus >> sens_hygro_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
