/*******************************************************************************
* File Name: WaveB_Buf.c
* Version 1.90
*
* Description:
*  This file provides the source code to the API for OpAmp (Analog Buffer) 
*  Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "WaveB_Buf.h"

uint8 WaveB_Buf_initVar = 0u;


/*******************************************************************************   
* Function Name: WaveB_Buf_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  WaveB_Buf_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void WaveB_Buf_Init(void) 
{
    WaveB_Buf_SetPower(WaveB_Buf_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: WaveB_Buf_Enable
********************************************************************************
*
* Summary:
*  Enables the OpAmp block operation
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void WaveB_Buf_Enable(void) 
{
    /* Enable negative charge pumps in ANIF */
    WaveB_Buf_PUMP_CR1_REG  |= (WaveB_Buf_PUMP_CR1_CLKSEL | WaveB_Buf_PUMP_CR1_FORCE);

    /* Enable power to buffer in active mode */
    WaveB_Buf_PM_ACT_CFG_REG |= WaveB_Buf_ACT_PWR_EN;

    /* Enable power to buffer in alternative active mode */
    WaveB_Buf_PM_STBY_CFG_REG |= WaveB_Buf_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name:   WaveB_Buf_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Analog Buffer with the default values and 
*  sets the power to the given level. A power level of 0, is same as 
*  executing the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  WaveB_Buf_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
*******************************************************************************/
void WaveB_Buf_Start(void) 
{
    if(WaveB_Buf_initVar == 0u)
    {
        WaveB_Buf_initVar = 1u;
        WaveB_Buf_Init();
    }

    WaveB_Buf_Enable();
}


/*******************************************************************************
* Function Name: WaveB_Buf_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void WaveB_Buf_Stop(void) 
{
    /* Disable power to buffer in active mode template */
    WaveB_Buf_PM_ACT_CFG_REG &= (uint8)(~WaveB_Buf_ACT_PWR_EN);

    /* Disable power to buffer in alternative active mode template */
    WaveB_Buf_PM_STBY_CFG_REG &= (uint8)(~WaveB_Buf_STBY_PWR_EN);
    
    /* Disable negative charge pumps for ANIF only if all ABuf is turned OFF */
    if(WaveB_Buf_PM_ACT_CFG_REG == 0u)
    {
        WaveB_Buf_PUMP_CR1_REG &= (uint8)(~(WaveB_Buf_PUMP_CR1_CLKSEL | WaveB_Buf_PUMP_CR1_FORCE));
    }
}


/*******************************************************************************
* Function Name: WaveB_Buf_SetPower
********************************************************************************
*
* Summary:
*  Sets power level of Analog buffer.
*
* Parameters: 
*  power: PSoC3: Sets power level between low (1) and high power (3).
*         PSoC5: Sets power level High (0)
*
* Return:
*  void
*
**********************************************************************************/
void WaveB_Buf_SetPower(uint8 power) 
{
    #if (CY_PSOC3 || CY_PSOC5LP)
        WaveB_Buf_CR_REG &= (uint8)(~WaveB_Buf_PWR_MASK);
        WaveB_Buf_CR_REG |= power & WaveB_Buf_PWR_MASK;      /* Set device power */
    #else
        CYASSERT(WaveB_Buf_HIGHPOWER == power);
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/* [] END OF FILE */
