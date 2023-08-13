/*******************************************************************************
* File Name: AuxDAC_Buf.c
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

#include "AuxDAC_Buf.h"

uint8 AuxDAC_Buf_initVar = 0u;


/*******************************************************************************   
* Function Name: AuxDAC_Buf_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  AuxDAC_Buf_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AuxDAC_Buf_Init(void) 
{
    AuxDAC_Buf_SetPower(AuxDAC_Buf_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: AuxDAC_Buf_Enable
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
void AuxDAC_Buf_Enable(void) 
{
    /* Enable negative charge pumps in ANIF */
    AuxDAC_Buf_PUMP_CR1_REG  |= (AuxDAC_Buf_PUMP_CR1_CLKSEL | AuxDAC_Buf_PUMP_CR1_FORCE);

    /* Enable power to buffer in active mode */
    AuxDAC_Buf_PM_ACT_CFG_REG |= AuxDAC_Buf_ACT_PWR_EN;

    /* Enable power to buffer in alternative active mode */
    AuxDAC_Buf_PM_STBY_CFG_REG |= AuxDAC_Buf_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name:   AuxDAC_Buf_Start
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
*  AuxDAC_Buf_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
*******************************************************************************/
void AuxDAC_Buf_Start(void) 
{
    if(AuxDAC_Buf_initVar == 0u)
    {
        AuxDAC_Buf_initVar = 1u;
        AuxDAC_Buf_Init();
    }

    AuxDAC_Buf_Enable();
}


/*******************************************************************************
* Function Name: AuxDAC_Buf_Stop
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
void AuxDAC_Buf_Stop(void) 
{
    /* Disable power to buffer in active mode template */
    AuxDAC_Buf_PM_ACT_CFG_REG &= (uint8)(~AuxDAC_Buf_ACT_PWR_EN);

    /* Disable power to buffer in alternative active mode template */
    AuxDAC_Buf_PM_STBY_CFG_REG &= (uint8)(~AuxDAC_Buf_STBY_PWR_EN);
    
    /* Disable negative charge pumps for ANIF only if all ABuf is turned OFF */
    if(AuxDAC_Buf_PM_ACT_CFG_REG == 0u)
    {
        AuxDAC_Buf_PUMP_CR1_REG &= (uint8)(~(AuxDAC_Buf_PUMP_CR1_CLKSEL | AuxDAC_Buf_PUMP_CR1_FORCE));
    }
}


/*******************************************************************************
* Function Name: AuxDAC_Buf_SetPower
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
void AuxDAC_Buf_SetPower(uint8 power) 
{
    #if (CY_PSOC3 || CY_PSOC5LP)
        AuxDAC_Buf_CR_REG &= (uint8)(~AuxDAC_Buf_PWR_MASK);
        AuxDAC_Buf_CR_REG |= power & AuxDAC_Buf_PWR_MASK;      /* Set device power */
    #else
        CYASSERT(AuxDAC_Buf_HIGHPOWER == power);
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/* [] END OF FILE */
