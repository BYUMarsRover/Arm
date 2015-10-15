/*******************************************************************************
* File Name: Wrist_UART_SCBCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Wrist_UART_SCBCLK_H)
#define CY_CLOCK_Wrist_UART_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Wrist_UART_SCBCLK_StartEx(uint32 alignClkDiv);
#define Wrist_UART_SCBCLK_Start() \
    Wrist_UART_SCBCLK_StartEx(Wrist_UART_SCBCLK__PA_DIV_ID)

#else

void Wrist_UART_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Wrist_UART_SCBCLK_Stop(void);

void Wrist_UART_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Wrist_UART_SCBCLK_GetDividerRegister(void);
uint8  Wrist_UART_SCBCLK_GetFractionalDividerRegister(void);

#define Wrist_UART_SCBCLK_Enable()                         Wrist_UART_SCBCLK_Start()
#define Wrist_UART_SCBCLK_Disable()                        Wrist_UART_SCBCLK_Stop()
#define Wrist_UART_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    Wrist_UART_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define Wrist_UART_SCBCLK_SetDivider(clkDivider)           Wrist_UART_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define Wrist_UART_SCBCLK_SetDividerValue(clkDivider)      Wrist_UART_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Wrist_UART_SCBCLK_DIV_ID     Wrist_UART_SCBCLK__DIV_ID

#define Wrist_UART_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Wrist_UART_SCBCLK_CTRL_REG   (*(reg32 *)Wrist_UART_SCBCLK__CTRL_REGISTER)
#define Wrist_UART_SCBCLK_DIV_REG    (*(reg32 *)Wrist_UART_SCBCLK__DIV_REGISTER)

#define Wrist_UART_SCBCLK_CMD_DIV_SHIFT          (0u)
#define Wrist_UART_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define Wrist_UART_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define Wrist_UART_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define Wrist_UART_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Wrist_UART_SCBCLK_CMD_DISABLE_SHIFT))
#define Wrist_UART_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Wrist_UART_SCBCLK_CMD_ENABLE_SHIFT))

#define Wrist_UART_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define Wrist_UART_SCBCLK_DIV_FRAC_SHIFT (3u)
#define Wrist_UART_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define Wrist_UART_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define Wrist_UART_SCBCLK_DIV_REG        (*(reg32 *)Wrist_UART_SCBCLK__REGISTER)
#define Wrist_UART_SCBCLK_ENABLE_REG     Wrist_UART_SCBCLK_DIV_REG
#define Wrist_UART_SCBCLK_DIV_FRAC_MASK  Wrist_UART_SCBCLK__FRAC_MASK
#define Wrist_UART_SCBCLK_DIV_FRAC_SHIFT (16u)
#define Wrist_UART_SCBCLK_DIV_INT_MASK   Wrist_UART_SCBCLK__DIVIDER_MASK
#define Wrist_UART_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Wrist_UART_SCBCLK_H) */

/* [] END OF FILE */
