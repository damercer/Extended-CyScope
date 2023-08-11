/*******************************************************************************
* File Name: ScopeC_Buf_PM.c  
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

#include "ScopeC_Buf.h"

static ScopeC_Buf_BACKUP_STRUCT  ScopeC_Buf_backup;


/*******************************************************************************
* Function Name: ScopeC_Buf_SaveConfig
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
void ScopeC_Buf_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: ScopeC_Buf_RestoreConfig
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
void ScopeC_Buf_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: ScopeC_Buf_Sleep
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
*  ScopeC_Buf_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ScopeC_Buf_Sleep(void) 
{
    /* Save PGA enable state */
    if((ScopeC_Buf_PM_ACT_CFG_REG & ScopeC_Buf_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        ScopeC_Buf_backup.enableState = 1u;
        /* Stop the configuration */
        ScopeC_Buf_Stop();
    }
    else
    {
        /* Component is disabled */
        ScopeC_Buf_backup.enableState = 0u;
    }
    /* Save the configuration */
    ScopeC_Buf_SaveConfig();
}


/*******************************************************************************
* Function Name: ScopeC_Buf_Wakeup
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
*  ScopeC_Buf_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
* 
*******************************************************************************/
void ScopeC_Buf_Wakeup(void) 
{
    /* Restore the configurations */
    ScopeC_Buf_RestoreConfig();
     /* Enables the component operation */
    if(ScopeC_Buf_backup.enableState == 1u)
    {
        ScopeC_Buf_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
