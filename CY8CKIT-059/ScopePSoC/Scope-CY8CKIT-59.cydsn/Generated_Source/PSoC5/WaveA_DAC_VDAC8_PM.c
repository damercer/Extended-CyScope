/*******************************************************************************
* File Name: WaveA_DAC_VDAC8_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "WaveA_DAC_VDAC8.h"

static WaveA_DAC_VDAC8_backupStruct WaveA_DAC_VDAC8_backup;


/*******************************************************************************
* Function Name: WaveA_DAC_VDAC8_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void WaveA_DAC_VDAC8_SaveConfig(void) 
{
    if (!((WaveA_DAC_VDAC8_CR1 & WaveA_DAC_VDAC8_SRC_MASK) == WaveA_DAC_VDAC8_SRC_UDB))
    {
        WaveA_DAC_VDAC8_backup.data_value = WaveA_DAC_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: WaveA_DAC_VDAC8_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void WaveA_DAC_VDAC8_RestoreConfig(void) 
{
    if (!((WaveA_DAC_VDAC8_CR1 & WaveA_DAC_VDAC8_SRC_MASK) == WaveA_DAC_VDAC8_SRC_UDB))
    {
        if((WaveA_DAC_VDAC8_Strobe & WaveA_DAC_VDAC8_STRB_MASK) == WaveA_DAC_VDAC8_STRB_EN)
        {
            WaveA_DAC_VDAC8_Strobe &= (uint8)(~WaveA_DAC_VDAC8_STRB_MASK);
            WaveA_DAC_VDAC8_Data = WaveA_DAC_VDAC8_backup.data_value;
            WaveA_DAC_VDAC8_Strobe |= WaveA_DAC_VDAC8_STRB_EN;
        }
        else
        {
            WaveA_DAC_VDAC8_Data = WaveA_DAC_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: WaveA_DAC_VDAC8_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  WaveA_DAC_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void WaveA_DAC_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(WaveA_DAC_VDAC8_ACT_PWR_EN == (WaveA_DAC_VDAC8_PWRMGR & WaveA_DAC_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        WaveA_DAC_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        WaveA_DAC_VDAC8_backup.enableState = 0u;
    }
    
    WaveA_DAC_VDAC8_Stop();
    WaveA_DAC_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: WaveA_DAC_VDAC8_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  WaveA_DAC_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void WaveA_DAC_VDAC8_Wakeup(void) 
{
    WaveA_DAC_VDAC8_RestoreConfig();
    
    if(WaveA_DAC_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        WaveA_DAC_VDAC8_Enable();

        /* Restore the data register */
        WaveA_DAC_VDAC8_SetValue(WaveA_DAC_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
