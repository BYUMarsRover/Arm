/*******************************************************************************
* File Name: SHLDR_PWM_PM.c
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

#include "SHLDR_PWM.h"

static SHLDR_PWM_BACKUP_STRUCT SHLDR_PWM_backup;


/*******************************************************************************
* Function Name: SHLDR_PWM_SaveConfig
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
void SHLDR_PWM_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: SHLDR_PWM_Sleep
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
void SHLDR_PWM_Sleep(void)
{
    if(0u != (SHLDR_PWM_BLOCK_CONTROL_REG & SHLDR_PWM_MASK))
    {
        SHLDR_PWM_backup.enableState = 1u;
    }
    else
    {
        SHLDR_PWM_backup.enableState = 0u;
    }

    SHLDR_PWM_Stop();
    SHLDR_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: SHLDR_PWM_RestoreConfig
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
void SHLDR_PWM_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: SHLDR_PWM_Wakeup
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
void SHLDR_PWM_Wakeup(void)
{
    SHLDR_PWM_RestoreConfig();

    if(0u != SHLDR_PWM_backup.enableState)
    {
        SHLDR_PWM_Enable();
    }
}


/* [] END OF FILE */
