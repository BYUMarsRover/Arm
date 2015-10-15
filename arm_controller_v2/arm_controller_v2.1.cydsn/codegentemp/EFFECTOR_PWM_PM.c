/*******************************************************************************
* File Name: EFFECTOR_PWM_PM.c
* Version 3.10
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "EFFECTOR_PWM.h"

static EFFECTOR_PWM_backupStruct EFFECTOR_PWM_backup;


/*******************************************************************************
* Function Name: EFFECTOR_PWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  EFFECTOR_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void EFFECTOR_PWM_SaveConfig(void) 
{

    #if(!EFFECTOR_PWM_UsingFixedFunction)
        #if(!EFFECTOR_PWM_PWMModeIsCenterAligned)
            EFFECTOR_PWM_backup.PWMPeriod = EFFECTOR_PWM_ReadPeriod();
        #endif /* (!EFFECTOR_PWM_PWMModeIsCenterAligned) */
        EFFECTOR_PWM_backup.PWMUdb = EFFECTOR_PWM_ReadCounter();
        #if (EFFECTOR_PWM_UseStatus)
            EFFECTOR_PWM_backup.InterruptMaskValue = EFFECTOR_PWM_STATUS_MASK;
        #endif /* (EFFECTOR_PWM_UseStatus) */

        #if(EFFECTOR_PWM_DeadBandMode == EFFECTOR_PWM__B_PWM__DBM_256_CLOCKS || \
            EFFECTOR_PWM_DeadBandMode == EFFECTOR_PWM__B_PWM__DBM_2_4_CLOCKS)
            EFFECTOR_PWM_backup.PWMdeadBandValue = EFFECTOR_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(EFFECTOR_PWM_KillModeMinTime)
             EFFECTOR_PWM_backup.PWMKillCounterPeriod = EFFECTOR_PWM_ReadKillTime();
        #endif /* (EFFECTOR_PWM_KillModeMinTime) */

        #if(EFFECTOR_PWM_UseControl)
            EFFECTOR_PWM_backup.PWMControlRegister = EFFECTOR_PWM_ReadControlRegister();
        #endif /* (EFFECTOR_PWM_UseControl) */
    #endif  /* (!EFFECTOR_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: EFFECTOR_PWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  EFFECTOR_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void EFFECTOR_PWM_RestoreConfig(void) 
{
        #if(!EFFECTOR_PWM_UsingFixedFunction)
            #if(!EFFECTOR_PWM_PWMModeIsCenterAligned)
                EFFECTOR_PWM_WritePeriod(EFFECTOR_PWM_backup.PWMPeriod);
            #endif /* (!EFFECTOR_PWM_PWMModeIsCenterAligned) */

            EFFECTOR_PWM_WriteCounter(EFFECTOR_PWM_backup.PWMUdb);

            #if (EFFECTOR_PWM_UseStatus)
                EFFECTOR_PWM_STATUS_MASK = EFFECTOR_PWM_backup.InterruptMaskValue;
            #endif /* (EFFECTOR_PWM_UseStatus) */

            #if(EFFECTOR_PWM_DeadBandMode == EFFECTOR_PWM__B_PWM__DBM_256_CLOCKS || \
                EFFECTOR_PWM_DeadBandMode == EFFECTOR_PWM__B_PWM__DBM_2_4_CLOCKS)
                EFFECTOR_PWM_WriteDeadTime(EFFECTOR_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(EFFECTOR_PWM_KillModeMinTime)
                EFFECTOR_PWM_WriteKillTime(EFFECTOR_PWM_backup.PWMKillCounterPeriod);
            #endif /* (EFFECTOR_PWM_KillModeMinTime) */

            #if(EFFECTOR_PWM_UseControl)
                EFFECTOR_PWM_WriteControlRegister(EFFECTOR_PWM_backup.PWMControlRegister);
            #endif /* (EFFECTOR_PWM_UseControl) */
        #endif  /* (!EFFECTOR_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: EFFECTOR_PWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  EFFECTOR_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void EFFECTOR_PWM_Sleep(void) 
{
    #if(EFFECTOR_PWM_UseControl)
        if(EFFECTOR_PWM_CTRL_ENABLE == (EFFECTOR_PWM_CONTROL & EFFECTOR_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            EFFECTOR_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            EFFECTOR_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (EFFECTOR_PWM_UseControl) */

    /* Stop component */
    EFFECTOR_PWM_Stop();

    /* Save registers configuration */
    EFFECTOR_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: EFFECTOR_PWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  EFFECTOR_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void EFFECTOR_PWM_Wakeup(void) 
{
     /* Restore registers values */
    EFFECTOR_PWM_RestoreConfig();

    if(EFFECTOR_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        EFFECTOR_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
