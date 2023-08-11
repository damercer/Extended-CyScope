/*******************************************************************************
* File Name: VRef_Buf_PM.c
* Version 1.90
*
* Description:
*  This file provides the power management source code to the API for the 
*  OpAmp (Analog Buffer) component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "VRef_Buf.h"

static VRef_Buf_BACKUP_STRUCT  VRef_Buf_backup;


/*******************************************************************************  
* Function Name: VRef_Buf_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration registers.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
*******************************************************************************/
void VRef_Buf_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: VRef_Buf_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration registers.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void VRef_Buf_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: VRef_Buf_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  VRef_Buf_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void VRef_Buf_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((VRef_Buf_PM_ACT_CFG_REG & VRef_Buf_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        VRef_Buf_backup.enableState = 1u;
         /* Stops the component */
         VRef_Buf_Stop();
    }
    else
    {
        /* Component is disabled */
        VRef_Buf_backup.enableState = 0u;
    }
    /* Saves the configuration */
    VRef_Buf_SaveConfig();
}


/*******************************************************************************  
* Function Name: VRef_Buf_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  VRef_Buf_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void VRef_Buf_Wakeup(void) 
{
    /* Restore the user configuration */
    VRef_Buf_RestoreConfig();

    /* Enables the component operation */
    if(VRef_Buf_backup.enableState == 1u)
    {
        VRef_Buf_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
