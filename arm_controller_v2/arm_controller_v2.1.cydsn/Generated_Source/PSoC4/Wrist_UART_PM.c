/*******************************************************************************
* File Name: Wrist_UART_PM.c
* Version 2.0
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Wrist_UART.h"
#include "Wrist_UART_PVT.h"

#if(Wrist_UART_SCB_MODE_I2C_INC)
    #include "Wrist_UART_I2C_PVT.h"
#endif /* (Wrist_UART_SCB_MODE_I2C_INC) */

#if(Wrist_UART_SCB_MODE_EZI2C_INC)
    #include "Wrist_UART_EZI2C_PVT.h"
#endif /* (Wrist_UART_SCB_MODE_EZI2C_INC) */

#if(Wrist_UART_SCB_MODE_SPI_INC || Wrist_UART_SCB_MODE_UART_INC)
    #include "Wrist_UART_SPI_UART_PVT.h"
#endif /* (Wrist_UART_SCB_MODE_SPI_INC || Wrist_UART_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG || \
   (Wrist_UART_SCB_MODE_I2C_CONST_CFG   && (!Wrist_UART_I2C_WAKE_ENABLE_CONST))   || \
   (Wrist_UART_SCB_MODE_EZI2C_CONST_CFG && (!Wrist_UART_EZI2C_WAKE_ENABLE_CONST)) || \
   (Wrist_UART_SCB_MODE_SPI_CONST_CFG   && (!Wrist_UART_SPI_WAKE_ENABLE_CONST))   || \
   (Wrist_UART_SCB_MODE_UART_CONST_CFG  && (!Wrist_UART_UART_WAKE_ENABLE_CONST)))

    Wrist_UART_BACKUP_STRUCT Wrist_UART_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: Wrist_UART_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Wrist_UART_Sleep(void)
{
#if(Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Wrist_UART_SCB_WAKE_ENABLE_CHECK)
    {
        if(Wrist_UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            Wrist_UART_I2CSaveConfig();
        }
        else if(Wrist_UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Wrist_UART_EzI2CSaveConfig();
        }
    #if(!Wrist_UART_CY_SCBIP_V1)
        else if(Wrist_UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            Wrist_UART_SpiSaveConfig();
        }
        else if(Wrist_UART_SCB_MODE_UART_RUNTM_CFG)
        {
            Wrist_UART_UartSaveConfig();
        }
    #endif /* (!Wrist_UART_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        Wrist_UART_backup.enableState = (uint8) Wrist_UART_GET_CTRL_ENABLED;

        if(0u != Wrist_UART_backup.enableState)
        {
            Wrist_UART_Stop();
        }
    }

#else

    #if (Wrist_UART_SCB_MODE_I2C_CONST_CFG && Wrist_UART_I2C_WAKE_ENABLE_CONST)
        Wrist_UART_I2CSaveConfig();

    #elif (Wrist_UART_SCB_MODE_EZI2C_CONST_CFG && Wrist_UART_EZI2C_WAKE_ENABLE_CONST)
        Wrist_UART_EzI2CSaveConfig();

    #elif (Wrist_UART_SCB_MODE_SPI_CONST_CFG && Wrist_UART_SPI_WAKE_ENABLE_CONST)
        Wrist_UART_SpiSaveConfig();

    #elif (Wrist_UART_SCB_MODE_UART_CONST_CFG && Wrist_UART_UART_WAKE_ENABLE_CONST)
        Wrist_UART_UartSaveConfig();

    #else

        Wrist_UART_backup.enableState = (uint8) Wrist_UART_GET_CTRL_ENABLED;

        if(0u != Wrist_UART_backup.enableState)
        {
            Wrist_UART_Stop();
        }

    #endif /* defined (Wrist_UART_SCB_MODE_I2C_CONST_CFG) && (Wrist_UART_I2C_WAKE_ENABLE_CONST) */

#endif /* (Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Wrist_UART_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Wrist_UART_Wakeup(void)
{
#if(Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Wrist_UART_SCB_WAKE_ENABLE_CHECK)
    {
        if(Wrist_UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            Wrist_UART_I2CRestoreConfig();
        }
        else if(Wrist_UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Wrist_UART_EzI2CRestoreConfig();
        }
    #if(!Wrist_UART_CY_SCBIP_V1)
        else if(Wrist_UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            Wrist_UART_SpiRestoreConfig();
        }
        else if(Wrist_UART_SCB_MODE_UART_RUNTM_CFG)
        {
            Wrist_UART_UartRestoreConfig();
        }
    #endif /* (!Wrist_UART_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != Wrist_UART_backup.enableState)
        {
            Wrist_UART_Enable();
        }
    }

#else

    #if (Wrist_UART_SCB_MODE_I2C_CONST_CFG  && Wrist_UART_I2C_WAKE_ENABLE_CONST)
        Wrist_UART_I2CRestoreConfig();

    #elif (Wrist_UART_SCB_MODE_EZI2C_CONST_CFG && Wrist_UART_EZI2C_WAKE_ENABLE_CONST)
        Wrist_UART_EzI2CRestoreConfig();

    #elif (Wrist_UART_SCB_MODE_SPI_CONST_CFG && Wrist_UART_SPI_WAKE_ENABLE_CONST)
        Wrist_UART_SpiRestoreConfig();

    #elif (Wrist_UART_SCB_MODE_UART_CONST_CFG && Wrist_UART_UART_WAKE_ENABLE_CONST)
        Wrist_UART_UartRestoreConfig();

    #else

        if(0u != Wrist_UART_backup.enableState)
        {
            Wrist_UART_Enable();
        }

    #endif /* (Wrist_UART_I2C_WAKE_ENABLE_CONST) */

#endif /* (Wrist_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
