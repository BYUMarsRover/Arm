/*******************************************************************************
* File Name: ELBW_PWM_PM.c
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

#include "ELBW_PWM.h"

static ELBW_PWM_BACKUP_STRUCT ELBW_PWM_backup;


/*******************************************************************************
* Function Name: ELBW_PWM_SaveConfig
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
void ELBW_PWM_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: ELBW_PWM_Sleep
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
void ELBW_PWM_Sleep(void)
{
    if(0u != (ELBW_PWM_BLOCK_CONTROL_REG & ELBW_PWM_MASK))
    {
        ELBW_PWM_backup.enableState = 1u;
    }
    else
    {
        ELBW_PWM_backup.enableState = 0u;
    }

    ELBW_PWM_Stop();
    ELBW_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: ELBW_PWM_RestoreConfig
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
void ELBW_PWM_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: ELBW_PWM_Wakeup
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
void ELBW_PWM_Wakeup(void)
{
    ELBW_PWM_RestoreConfig();

    if(0u != ELBW_PWM_backup.enableState)
    {
        ELBW_PWM_Enable();
    }
}


/* [] END OF FILE */
