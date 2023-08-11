/*******************************************************************************
* File Name: ScopeA_Buf_PM.c  
* Version 2.0
*
* Description:
*  This file provides the power manager source code to the API for PGA 
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

#include "ScopeA_Buf.h"

static ScopeA_Buf_BACKUP_STRUCT  ScopeA_Buf_backup;


/*******************************************************************************
* Function Name: ScopeA_Buf_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user register configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ScopeA_Buf_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: ScopeA_Buf_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ScopeA_Buf_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: ScopeA_Buf_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ScopeA_Buf_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ScopeA_Buf_Sleep(void) 
{
    /* Save PGA enable state */
    if((ScopeA_Buf_PM_ACT_CFG_REG & ScopeA_Buf_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        ScopeA_Buf_backup.enableState = 1u;
        /* Stop the configuration */
        ScopeA_Buf_Stop();
    }
    else
    {
        /* Component is disabled */
        ScopeA_Buf_backup.enableState = 0u;
    }
    /* Save the configuration */
    ScopeA_Buf_SaveConfig();
}


/*******************************************************************************
* Function Name: ScopeA_Buf_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  void
*
* Global variables:
*  ScopeA_Buf_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
* 
*******************************************************************************/
void ScopeA_Buf_Wakeup(void) 
{
    /* Restore the configurations */
    ScopeA_Buf_RestoreConfig();
     /* Enables the component operation */
    if(ScopeA_Buf_backup.enableState == 1u)
    {
        ScopeA_Buf_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
