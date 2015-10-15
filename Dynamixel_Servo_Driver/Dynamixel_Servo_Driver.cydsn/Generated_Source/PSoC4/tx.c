/*******************************************************************************
* File Name: tx.c  
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
#include "tx.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        tx_PC =   (tx_PC & \
                                (uint32)(~(uint32)(tx_DRIVE_MODE_IND_MASK << (tx_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (tx_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: tx_Write
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
void tx_Write(uint8 value) 
{
    uint8 drVal = (uint8)(tx_DR & (uint8)(~tx_MASK));
    drVal = (drVal | ((uint8)(value << tx_SHIFT) & tx_MASK));
    tx_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: tx_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  tx_DM_STRONG     Strong Drive 
*  tx_DM_OD_HI      Open Drain, Drives High 
*  tx_DM_OD_LO      Open Drain, Drives Low 
*  tx_DM_RES_UP     Resistive Pull Up 
*  tx_DM_RES_DWN    Resistive Pull Down 
*  tx_DM_RES_UPDWN  Resistive Pull Up/Down 
*  tx_DM_DIG_HIZ    High Impedance Digital 
*  tx_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void tx_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(tx__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: tx_Read
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
*  Macro tx_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 tx_Read(void) 
{
    return (uint8)((tx_PS & tx_MASK) >> tx_SHIFT);
}


/*******************************************************************************
* Function Name: tx_ReadDataReg
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
uint8 tx_ReadDataReg(void) 
{
    return (uint8)((tx_DR & tx_MASK) >> tx_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(tx_INTSTAT) 

    /*******************************************************************************
    * Function Name: tx_ClearInterrupt
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
    uint8 tx_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(tx_INTSTAT & tx_MASK);
		tx_INTSTAT = maskedStatus;
        return maskedStatus >> tx_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
