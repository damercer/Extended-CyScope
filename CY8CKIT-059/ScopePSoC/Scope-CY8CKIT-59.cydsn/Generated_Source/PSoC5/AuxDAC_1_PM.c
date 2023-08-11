/*******************************************************************************
* File Name: AuxDAC_1_PM.c  
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

#include "AuxDAC_1.h"

static AuxDAC_1_backupStruct AuxDAC_1_backup;


/*******************************************************************************
* Function Name: AuxDAC_1_SaveConfig
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
void AuxDAC_1_SaveConfig(void) 
{
    if (!((AuxDAC_1_CR1 & AuxDAC_1_SRC_MASK) == AuxDAC_1_SRC_UDB))
    {
        AuxDAC_1_backup.data_value = AuxDAC_1_Data;
    }
}


/*******************************************************************************
* Function Name: AuxDAC_1_RestoreConfig
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
void AuxDAC_1_RestoreConfig(void) 
{
    if (!((AuxDAC_1_CR1 & AuxDAC_1_SRC_MASK) == AuxDAC_1_SRC_UDB))
    {
        if((AuxDAC_1_Strobe & AuxDAC_1_STRB_MASK) == AuxDAC_1_STRB_EN)
        {
            AuxDAC_1_Strobe &= (uint8)(~AuxDAC_1_STRB_MASK);
            AuxDAC_1_Data = AuxDAC_1_backup.data_value;
            AuxDAC_1_Strobe |= AuxDAC_1_STRB_EN;
        }
        else
        {
            AuxDAC_1_Data = AuxDAC_1_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: AuxDAC_1_Sleep
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
*  AuxDAC_1_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void AuxDAC_1_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(AuxDAC_1_ACT_PWR_EN == (AuxDAC_1_PWRMGR & AuxDAC_1_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        AuxDAC_1_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        AuxDAC_1_backup.enableState = 0u;
    }
    
    AuxDAC_1_Stop();
    AuxDAC_1_SaveConfig();
}


/*******************************************************************************
* Function Name: AuxDAC_1_Wakeup
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
*  AuxDAC_1_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void AuxDAC_1_Wakeup(void) 
{
    AuxDAC_1_RestoreConfig();
    
    if(AuxDAC_1_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        AuxDAC_1_Enable();

        /* Restore the data register */
        AuxDAC_1_SetValue(AuxDAC_1_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
