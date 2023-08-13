/*******************************************************************************
* File Name: WaveB_DAC_PM.c  
* Version 2.10
*
* Description:
*  This file provides the power manager source code to the API for 
*  the WaveDAC8 component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "WaveB_DAC.h"

static WaveB_DAC_BACKUP_STRUCT  WaveB_DAC_backup;


/*******************************************************************************
* Function Name: WaveB_DAC_Sleep
********************************************************************************
*
* Summary:
*  Stops the component and saves its configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  WaveB_DAC_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void WaveB_DAC_Sleep(void) 
{
	/* Save DAC8's enable state */

	WaveB_DAC_backup.enableState = (WaveB_DAC_VDAC8_ACT_PWR_EN == 
		(WaveB_DAC_VDAC8_PWRMGR_REG & WaveB_DAC_VDAC8_ACT_PWR_EN)) ? 1u : 0u ;
	
	WaveB_DAC_Stop();
	WaveB_DAC_SaveConfig();
}


/*******************************************************************************
* Function Name: WaveB_DAC_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component configuration. Should be called
*  just after awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  void
*
* Global variables:
*  WaveB_DAC_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void WaveB_DAC_Wakeup(void) 
{
	WaveB_DAC_RestoreConfig();

	if(WaveB_DAC_backup.enableState == 1u)
	{
		WaveB_DAC_Enable();
	}
}


/* [] END OF FILE */
