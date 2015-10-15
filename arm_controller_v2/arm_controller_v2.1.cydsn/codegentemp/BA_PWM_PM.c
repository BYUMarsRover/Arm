/*******************************************************************************
* File Name: BA_PWM_PM.c
* Version 2.0
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BA_PWM.h"

static BA_PWM_BACKUP_STRUCT BA_PWM_backup;


/*******************************************************************************
* Function Name: BA_PWM_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BA_PWM_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: BA_PWM_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BA_PWM_Sleep(void)
{
    if(0u != (BA_PWM_BLOCK_CONTROL_REG & BA_PWM_MASK))
    {
        BA_PWM_backup.enableState = 1u;
    }
    else
    {
        BA_PWM_backup.enableState = 0u;
    }

    BA_PWM_Stop();
    BA_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: BA_PWM_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BA_PWM_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: BA_PWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BA_PWM_Wakeup(void)
{
    BA_PWM_RestoreConfig();

    if(0u != BA_PWM_backup.enableState)
    {
        BA_PWM_Enable();
    }
}


/* [] END OF FILE */
