/*******************************************************************************
* File Name: UART_TEST_PM.c
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

#include "UART_TEST.h"
#include "UART_TEST_PVT.h"

#if(UART_TEST_SCB_MODE_I2C_INC)
    #include "UART_TEST_I2C_PVT.h"
#endif /* (UART_TEST_SCB_MODE_I2C_INC) */

#if(UART_TEST_SCB_MODE_EZI2C_INC)
    #include "UART_TEST_EZI2C_PVT.h"
#endif /* (UART_TEST_SCB_MODE_EZI2C_INC) */

#if(UART_TEST_SCB_MODE_SPI_INC || UART_TEST_SCB_MODE_UART_INC)
    #include "UART_TEST_SPI_UART_PVT.h"
#endif /* (UART_TEST_SCB_MODE_SPI_INC || UART_TEST_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(UART_TEST_SCB_MODE_UNCONFIG_CONST_CFG || \
   (UART_TEST_SCB_MODE_I2C_CONST_CFG   && (!UART_TEST_I2C_WAKE_ENABLE_CONST))   || \
   (UART_TEST_SCB_MODE_EZI2C_CONST_CFG && (!UART_TEST_EZI2C_WAKE_ENABLE_CONST)) || \
   (UART_TEST_SCB_MODE_SPI_CONST_CFG   && (!UART_TEST_SPI_WAKE_ENABLE_CONST))   || \
   (UART_TEST_SCB_MODE_UART_CONST_CFG  && (!UART_TEST_UART_WAKE_ENABLE_CONST)))

    UART_TEST_BACKUP_STRUCT UART_TEST_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: UART_TEST_Sleep
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
void UART_TEST_Sleep(void)
{
#if(UART_TEST_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_TEST_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_TEST_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_TEST_I2CSaveConfig();
        }
        else if(UART_TEST_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_TEST_EzI2CSaveConfig();
        }
    #if(!UART_TEST_CY_SCBIP_V1)
        else if(UART_TEST_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_TEST_SpiSaveConfig();
        }
        else if(UART_TEST_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_TEST_UartSaveConfig();
        }
    #endif /* (!UART_TEST_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        UART_TEST_backup.enableState = (uint8) UART_TEST_GET_CTRL_ENABLED;

        if(0u != UART_TEST_backup.enableState)
        {
            UART_TEST_Stop();
        }
    }

#else

    #if (UART_TEST_SCB_MODE_I2C_CONST_CFG && UART_TEST_I2C_WAKE_ENABLE_CONST)
        UART_TEST_I2CSaveConfig();

    #elif (UART_TEST_SCB_MODE_EZI2C_CONST_CFG && UART_TEST_EZI2C_WAKE_ENABLE_CONST)
        UART_TEST_EzI2CSaveConfig();

    #elif (UART_TEST_SCB_MODE_SPI_CONST_CFG && UART_TEST_SPI_WAKE_ENABLE_CONST)
        UART_TEST_SpiSaveConfig();

    #elif (UART_TEST_SCB_MODE_UART_CONST_CFG && UART_TEST_UART_WAKE_ENABLE_CONST)
        UART_TEST_UartSaveConfig();

    #else

        UART_TEST_backup.enableState = (uint8) UART_TEST_GET_CTRL_ENABLED;

        if(0u != UART_TEST_backup.enableState)
        {
            UART_TEST_Stop();
        }

    #endif /* defined (UART_TEST_SCB_MODE_I2C_CONST_CFG) && (UART_TEST_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_TEST_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_TEST_Wakeup
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
void UART_TEST_Wakeup(void)
{
#if(UART_TEST_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_TEST_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_TEST_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_TEST_I2CRestoreConfig();
        }
        else if(UART_TEST_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_TEST_EzI2CRestoreConfig();
        }
    #if(!UART_TEST_CY_SCBIP_V1)
        else if(UART_TEST_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_TEST_SpiRestoreConfig();
        }
        else if(UART_TEST_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_TEST_UartRestoreConfig();
        }
    #endif /* (!UART_TEST_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != UART_TEST_backup.enableState)
        {
            UART_TEST_Enable();
        }
    }

#else

    #if (UART_TEST_SCB_MODE_I2C_CONST_CFG  && UART_TEST_I2C_WAKE_ENABLE_CONST)
        UART_TEST_I2CRestoreConfig();

    #elif (UART_TEST_SCB_MODE_EZI2C_CONST_CFG && UART_TEST_EZI2C_WAKE_ENABLE_CONST)
        UART_TEST_EzI2CRestoreConfig();

    #elif (UART_TEST_SCB_MODE_SPI_CONST_CFG && UART_TEST_SPI_WAKE_ENABLE_CONST)
        UART_TEST_SpiRestoreConfig();

    #elif (UART_TEST_SCB_MODE_UART_CONST_CFG && UART_TEST_UART_WAKE_ENABLE_CONST)
        UART_TEST_UartRestoreConfig();

    #else

        if(0u != UART_TEST_backup.enableState)
        {
            UART_TEST_Enable();
        }

    #endif /* (UART_TEST_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_TEST_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
