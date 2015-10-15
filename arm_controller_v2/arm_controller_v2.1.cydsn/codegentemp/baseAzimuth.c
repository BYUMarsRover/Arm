/*******************************************************************************
* File Name: baseAzimuth.c  
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
#include "baseAzimuth.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        baseAzimuth_PC =   (baseAzimuth_PC & \
                                (uint32)(~(uint32)(baseAzimuth_DRIVE_MODE_IND_MASK << (baseAzimuth_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (baseAzimuth_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: baseAzimuth_Write
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
void baseAzimuth_Write(uint8 value) 
{
    uint8 drVal = (uint8)(baseAzimuth_DR & (uint8)(~baseAzimuth_MASK));
    drVal = (drVal | ((uint8)(value << baseAzimuth_SHIFT) & baseAzimuth_MASK));
    baseAzimuth_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: baseAzimuth_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  baseAzimuth_DM_STRONG     Strong Drive 
*  baseAzimuth_DM_OD_HI      Open Drain, Drives High 
*  baseAzimuth_DM_OD_LO      Open Drain, Drives Low 
*  baseAzimuth_DM_RES_UP     Resistive Pull Up 
*  baseAzimuth_DM_RES_DWN    Resistive Pull Down 
*  baseAzimuth_DM_RES_UPDWN  Resistive Pull Up/Down 
*  baseAzimuth_DM_DIG_HIZ    High Impedance Digital 
*  baseAzimuth_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void baseAzimuth_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(baseAzimuth__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: baseAzimuth_Read
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
*  Macro baseAzimuth_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 baseAzimuth_Read(void) 
{
    return (uint8)((baseAzimuth_PS & baseAzimuth_MASK) >> baseAzimuth_SHIFT);
}


/*******************************************************************************
* Function Name: baseAzimuth_ReadDataReg
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
uint8 baseAzimuth_ReadDataReg(void) 
{
    return (uint8)((baseAzimuth_DR & baseAzimuth_MASK) >> baseAzimuth_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(baseAzimuth_INTSTAT) 

    /*******************************************************************************
    * Function Name: baseAzimuth_ClearInterrupt
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
    uint8 baseAzimuth_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(baseAzimuth_INTSTAT & baseAzimuth_MASK);
		baseAzimuth_INTSTAT = maskedStatus;
        return maskedStatus >> baseAzimuth_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
