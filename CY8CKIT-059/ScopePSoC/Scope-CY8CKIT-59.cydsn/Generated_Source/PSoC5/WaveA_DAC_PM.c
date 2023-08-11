/*******************************************************************************
* File Name: WaveA_DAC_PM.c  
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

#include "WaveA_DAC.h"

static WaveA_DAC_BACKUP_STRUCT  WaveA_DAC_backup;


/*******************************************************************************
* Function Name: WaveA_DAC_Sleep
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
*  WaveA_DAC_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void WaveA_DAC_Sleep(void) 
{
	/* Save DAC8's enable state */

	WaveA_DAC_backup.enableState = (WaveA_DAC_VDAC8_ACT_PWR_EN == 
		(WaveA_DAC_VDAC8_PWRMGR_REG & WaveA_DAC_VDAC8_ACT_PWR_EN)) ? 1u : 0u ;
	
	WaveA_DAC_Stop();
	WaveA_DAC_SaveConfig();
}


/*******************************************************************************
* Function Name: WaveA_DAC_Wakeup
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
*  WaveA_DAC_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void WaveA_DAC_Wakeup(void) 
{
	WaveA_DAC_RestoreConfig();

	if(WaveA_DAC_backup.enableState == 1u)
	{
		WaveA_DAC_Enable();
	}
}


/* [] END OF FILE */
