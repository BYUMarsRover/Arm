/*******************************************************************************
* File Name: Arduino_UART_PM.c
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

#include "Arduino_UART.h"
#include "Arduino_UART_PVT.h"

#if(Arduino_UART_SCB_MODE_I2C_INC)
    #include "Arduino_UART_I2C_PVT.h"
#endif /* (Arduino_UART_SCB_MODE_I2C_INC) */

#if(Arduino_UART_SCB_MODE_EZI2C_INC)
    #include "Arduino_UART_EZI2C_PVT.h"
#endif /* (Arduino_UART_SCB_MODE_EZI2C_INC) */

#if(Arduino_UART_SCB_MODE_SPI_INC || Arduino_UART_SCB_MODE_UART_INC)
    #include "Arduino_UART_SPI_UART_PVT.h"
#endif /* (Arduino_UART_SCB_MODE_SPI_INC || Arduino_UART_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG || \
   (Arduino_UART_SCB_MODE_I2C_CONST_CFG   && (!Arduino_UART_I2C_WAKE_ENABLE_CONST))   || \
   (Arduino_UART_SCB_MODE_EZI2C_CONST_CFG && (!Arduino_UART_EZI2C_WAKE_ENABLE_CONST)) || \
   (Arduino_UART_SCB_MODE_SPI_CONST_CFG   && (!Arduino_UART_SPI_WAKE_ENABLE_CONST))   || \
   (Arduino_UART_SCB_MODE_UART_CONST_CFG  && (!Arduino_UART_UART_WAKE_ENABLE_CONST)))

    Arduino_UART_BACKUP_STRUCT Arduino_UART_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: Arduino_UART_Sleep
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
void Arduino_UART_Sleep(void)
{
#if(Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Arduino_UART_SCB_WAKE_ENABLE_CHECK)
    {
        if(Arduino_UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            Arduino_UART_I2CSaveConfig();
        }
        else if(Arduino_UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Arduino_UART_EzI2CSaveConfig();
        }
    #if(!Arduino_UART_CY_SCBIP_V1)
        else if(Arduino_UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            Arduino_UART_SpiSaveConfig();
        }
        else if(Arduino_UART_SCB_MODE_UART_RUNTM_CFG)
        {
            Arduino_UART_UartSaveConfig();
        }
    #endif /* (!Arduino_UART_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        Arduino_UART_backup.enableState = (uint8) Arduino_UART_GET_CTRL_ENABLED;

        if(0u != Arduino_UART_backup.enableState)
        {
            Arduino_UART_Stop();
        }
    }

#else

    #if (Arduino_UART_SCB_MODE_I2C_CONST_CFG && Arduino_UART_I2C_WAKE_ENABLE_CONST)
        Arduino_UART_I2CSaveConfig();

    #elif (Arduino_UART_SCB_MODE_EZI2C_CONST_CFG && Arduino_UART_EZI2C_WAKE_ENABLE_CONST)
        Arduino_UART_EzI2CSaveConfig();

    #elif (Arduino_UART_SCB_MODE_SPI_CONST_CFG && Arduino_UART_SPI_WAKE_ENABLE_CONST)
        Arduino_UART_SpiSaveConfig();

    #elif (Arduino_UART_SCB_MODE_UART_CONST_CFG && Arduino_UART_UART_WAKE_ENABLE_CONST)
        Arduino_UART_UartSaveConfig();

    #else

        Arduino_UART_backup.enableState = (uint8) Arduino_UART_GET_CTRL_ENABLED;

        if(0u != Arduino_UART_backup.enableState)
        {
            Arduino_UART_Stop();
        }

    #endif /* defined (Arduino_UART_SCB_MODE_I2C_CONST_CFG) && (Arduino_UART_I2C_WAKE_ENABLE_CONST) */

#endif /* (Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Arduino_UART_Wakeup
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
void Arduino_UART_Wakeup(void)
{
#if(Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Arduino_UART_SCB_WAKE_ENABLE_CHECK)
    {
        if(Arduino_UART_SCB_MODE_I2C_RUNTM_CFG)
        {
            Arduino_UART_I2CRestoreConfig();
        }
        else if(Arduino_UART_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Arduino_UART_EzI2CRestoreConfig();
        }
    #if(!Arduino_UART_CY_SCBIP_V1)
        else if(Arduino_UART_SCB_MODE_SPI_RUNTM_CFG)
        {
            Arduino_UART_SpiRestoreConfig();
        }
        else if(Arduino_UART_SCB_MODE_UART_RUNTM_CFG)
        {
            Arduino_UART_UartRestoreConfig();
        }
    #endif /* (!Arduino_UART_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != Arduino_UART_backup.enableState)
        {
            Arduino_UART_Enable();
        }
    }

#else

    #if (Arduino_UART_SCB_MODE_I2C_CONST_CFG  && Arduino_UART_I2C_WAKE_ENABLE_CONST)
        Arduino_UART_I2CRestoreConfig();

    #elif (Arduino_UART_SCB_MODE_EZI2C_CONST_CFG && Arduino_UART_EZI2C_WAKE_ENABLE_CONST)
        Arduino_UART_EzI2CRestoreConfig();

    #elif (Arduino_UART_SCB_MODE_SPI_CONST_CFG && Arduino_UART_SPI_WAKE_ENABLE_CONST)
        Arduino_UART_SpiRestoreConfig();

    #elif (Arduino_UART_SCB_MODE_UART_CONST_CFG && Arduino_UART_UART_WAKE_ENABLE_CONST)
        Arduino_UART_UartRestoreConfig();

    #else

        if(0u != Arduino_UART_backup.enableState)
        {
            Arduino_UART_Enable();
        }

    #endif /* (Arduino_UART_I2C_WAKE_ENABLE_CONST) */

#endif /* (Arduino_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
