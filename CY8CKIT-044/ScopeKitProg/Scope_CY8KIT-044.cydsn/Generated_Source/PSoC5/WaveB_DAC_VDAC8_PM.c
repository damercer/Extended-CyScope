/*******************************************************************************
* File Name: WaveB_DAC_VDAC8_PM.c  
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

#include "WaveB_DAC_VDAC8.h"

static WaveB_DAC_VDAC8_backupStruct WaveB_DAC_VDAC8_backup;


/*******************************************************************************
* Function Name: WaveB_DAC_VDAC8_SaveConfig
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
void WaveB_DAC_VDAC8_SaveConfig(void) 
{
    if (!((WaveB_DAC_VDAC8_CR1 & WaveB_DAC_VDAC8_SRC_MASK) == WaveB_DAC_VDAC8_SRC_UDB))
    {
        WaveB_DAC_VDAC8_backup.data_value = WaveB_DAC_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: WaveB_DAC_VDAC8_RestoreConfig
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
void WaveB_DAC_VDAC8_RestoreConfig(void) 
{
    if (!((WaveB_DAC_VDAC8_CR1 & WaveB_DAC_VDAC8_SRC_MASK) == WaveB_DAC_VDAC8_SRC_UDB))
    {
        if((WaveB_DAC_VDAC8_Strobe & WaveB_DAC_VDAC8_STRB_MASK) == WaveB_DAC_VDAC8_STRB_EN)
        {
            WaveB_DAC_VDAC8_Strobe &= (uint8)(~WaveB_DAC_VDAC8_STRB_MASK);
            WaveB_DAC_VDAC8_Data = WaveB_DAC_VDAC8_backup.data_value;
            WaveB_DAC_VDAC8_Strobe |= WaveB_DAC_VDAC8_STRB_EN;
        }
        else
        {
            WaveB_DAC_VDAC8_Data = WaveB_DAC_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: WaveB_DAC_VDAC8_Sleep
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
*  WaveB_DAC_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void WaveB_DAC_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(WaveB_DAC_VDAC8_ACT_PWR_EN == (WaveB_DAC_VDAC8_PWRMGR & WaveB_DAC_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        WaveB_DAC_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        WaveB_DAC_VDAC8_backup.enableState = 0u;
    }
    
    WaveB_DAC_VDAC8_Stop();
    WaveB_DAC_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: WaveB_DAC_VDAC8_Wakeup
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
*  WaveB_DAC_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void WaveB_DAC_VDAC8_Wakeup(void) 
{
    WaveB_DAC_VDAC8_RestoreConfig();
    
    if(WaveB_DAC_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        WaveB_DAC_VDAC8_Enable();

        /* Restore the data register */
        WaveB_DAC_VDAC8_SetValue(WaveB_DAC_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
