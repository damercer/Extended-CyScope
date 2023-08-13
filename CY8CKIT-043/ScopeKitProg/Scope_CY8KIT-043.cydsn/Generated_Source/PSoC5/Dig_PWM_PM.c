/*******************************************************************************
* File Name: Dig_PWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Dig_PWM.h"

static Dig_PWM_backupStruct Dig_PWM_backup;


/*******************************************************************************
* Function Name: Dig_PWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Dig_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Dig_PWM_SaveConfig(void) 
{

    #if(!Dig_PWM_UsingFixedFunction)
        #if(!Dig_PWM_PWMModeIsCenterAligned)
            Dig_PWM_backup.PWMPeriod = Dig_PWM_ReadPeriod();
        #endif /* (!Dig_PWM_PWMModeIsCenterAligned) */
        Dig_PWM_backup.PWMUdb = Dig_PWM_ReadCounter();
        #if (Dig_PWM_UseStatus)
            Dig_PWM_backup.InterruptMaskValue = Dig_PWM_STATUS_MASK;
        #endif /* (Dig_PWM_UseStatus) */

        #if(Dig_PWM_DeadBandMode == Dig_PWM__B_PWM__DBM_256_CLOCKS || \
            Dig_PWM_DeadBandMode == Dig_PWM__B_PWM__DBM_2_4_CLOCKS)
            Dig_PWM_backup.PWMdeadBandValue = Dig_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Dig_PWM_KillModeMinTime)
             Dig_PWM_backup.PWMKillCounterPeriod = Dig_PWM_ReadKillTime();
        #endif /* (Dig_PWM_KillModeMinTime) */

        #if(Dig_PWM_UseControl)
            Dig_PWM_backup.PWMControlRegister = Dig_PWM_ReadControlRegister();
        #endif /* (Dig_PWM_UseControl) */
    #endif  /* (!Dig_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Dig_PWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Dig_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Dig_PWM_RestoreConfig(void) 
{
        #if(!Dig_PWM_UsingFixedFunction)
            #if(!Dig_PWM_PWMModeIsCenterAligned)
                Dig_PWM_WritePeriod(Dig_PWM_backup.PWMPeriod);
            #endif /* (!Dig_PWM_PWMModeIsCenterAligned) */

            Dig_PWM_WriteCounter(Dig_PWM_backup.PWMUdb);

            #if (Dig_PWM_UseStatus)
                Dig_PWM_STATUS_MASK = Dig_PWM_backup.InterruptMaskValue;
            #endif /* (Dig_PWM_UseStatus) */

            #if(Dig_PWM_DeadBandMode == Dig_PWM__B_PWM__DBM_256_CLOCKS || \
                Dig_PWM_DeadBandMode == Dig_PWM__B_PWM__DBM_2_4_CLOCKS)
                Dig_PWM_WriteDeadTime(Dig_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Dig_PWM_KillModeMinTime)
                Dig_PWM_WriteKillTime(Dig_PWM_backup.PWMKillCounterPeriod);
            #endif /* (Dig_PWM_KillModeMinTime) */

            #if(Dig_PWM_UseControl)
                Dig_PWM_WriteControlRegister(Dig_PWM_backup.PWMControlRegister);
            #endif /* (Dig_PWM_UseControl) */
        #endif  /* (!Dig_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Dig_PWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Dig_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Dig_PWM_Sleep(void) 
{
    #if(Dig_PWM_UseControl)
        if(Dig_PWM_CTRL_ENABLE == (Dig_PWM_CONTROL & Dig_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            Dig_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Dig_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (Dig_PWM_UseControl) */

    /* Stop component */
    Dig_PWM_Stop();

    /* Save registers configuration */
    Dig_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: Dig_PWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Dig_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Dig_PWM_Wakeup(void) 
{
     /* Restore registers values */
    Dig_PWM_RestoreConfig();

    if(Dig_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Dig_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
