/*******************************************************************************
* File Name: TriggerLevelPGA.c  
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the PGA 
*  User Module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "TriggerLevelPGA.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (CY_PSOC5A)
    static TriggerLevelPGA_BACKUP_STRUCT  TriggerLevelPGA_P5backup;
#endif /* (CY_ PSOC5A) */

uint8 TriggerLevelPGA_initVar = 0u;


/*******************************************************************************   
* Function Name: TriggerLevelPGA_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  TriggerLevelPGA_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TriggerLevelPGA_Init(void) 
{
    /* Set PGA mode */
    TriggerLevelPGA_CR0_REG = TriggerLevelPGA_MODE_PGA;      
    /* Set non-inverting PGA mode and reference mode */
    TriggerLevelPGA_CR1_REG |= TriggerLevelPGA_PGA_NINV;  
    /* Set default gain and ref mode */
    TriggerLevelPGA_CR2_REG = TriggerLevelPGA_VREF_MODE;
    /* Set gain and compensation */
    TriggerLevelPGA_SetGain(TriggerLevelPGA_DEFAULT_GAIN);
    /* Set power */
    TriggerLevelPGA_SetPower(TriggerLevelPGA_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: TriggerLevelPGA_Enable
********************************************************************************
*
* Summary:
*  Enables the PGA block operation.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TriggerLevelPGA_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(TriggerLevelPGA_P5backup.enableState == 1u)
        {
            TriggerLevelPGA_CR1_REG = TriggerLevelPGA_P5backup.scCR1Reg;
            TriggerLevelPGA_CR2_REG = TriggerLevelPGA_P5backup.scCR2Reg;
            TriggerLevelPGA_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */   

    /* Enable power to the Amp in Active mode*/
    TriggerLevelPGA_PM_ACT_CFG_REG |= TriggerLevelPGA_ACT_PWR_EN;

    /* Enable power to the Amp in Alternative Active mode*/
    TriggerLevelPGA_PM_STBY_CFG_REG |= TriggerLevelPGA_STBY_PWR_EN;
    
    TriggerLevelPGA_PUMP_CR1_REG |= TriggerLevelPGA_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                TriggerLevelPGA_BSTCLK_REG &= (uint8)(~TriggerLevelPGA_BST_CLK_INDEX_MASK);
                TriggerLevelPGA_BSTCLK_REG |= TriggerLevelPGA_BST_CLK_EN | CyScBoostClk__INDEX;
                TriggerLevelPGA_SC_MISC_REG |= TriggerLevelPGA_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                TriggerLevelPGA_BSTCLK_REG &= (uint8)(~TriggerLevelPGA_BST_CLK_EN);
                TriggerLevelPGA_SC_MISC_REG &= (uint8)(~TriggerLevelPGA_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: TriggerLevelPGA_Start
********************************************************************************
*
* Summary:
*  The start function initializes the PGA with the default values and sets
*  the power to the given level. A power level of 0, is same as executing
*  the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TriggerLevelPGA_Start(void) 
{

    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modification in stop() API */

    if(TriggerLevelPGA_initVar == 0u)
    {
        TriggerLevelPGA_Init();
        TriggerLevelPGA_initVar = 1u;
    }

    TriggerLevelPGA_Enable();
}


/*******************************************************************************
* Function Name: TriggerLevelPGA_Stop
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
void TriggerLevelPGA_Stop(void) 
{ 
    /* Disble power to the Amp in Active mode template */
    TriggerLevelPGA_PM_ACT_CFG_REG &= (uint8)(~TriggerLevelPGA_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    TriggerLevelPGA_PM_STBY_CFG_REG &= (uint8)(~TriggerLevelPGA_STBY_PWR_EN);

    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            TriggerLevelPGA_BSTCLK_REG &= (uint8)(~TriggerLevelPGA_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((TriggerLevelPGA_PM_ACT_CFG_REG & TriggerLevelPGA_PM_ACT_CFG_MASK) == 0u)
            {
                TriggerLevelPGA_SC_MISC_REG &= (uint8)(~TriggerLevelPGA_PUMP_FORCE);
                TriggerLevelPGA_PUMP_CR1_REG &= (uint8)(~TriggerLevelPGA_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /* This sets PGA in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        TriggerLevelPGA_P5backup.scCR1Reg = TriggerLevelPGA_CR1_REG;
        TriggerLevelPGA_P5backup.scCR2Reg = TriggerLevelPGA_CR2_REG;
        TriggerLevelPGA_CR1_REG = 0x00u;
        TriggerLevelPGA_CR2_REG = 0x00u;
        TriggerLevelPGA_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: TriggerLevelPGA_SetPower
********************************************************************************
*
* Summary:
*  Set the power of the PGA.
*
* Parameters:
*  power: Sets power level between (0) and (3) high power
*
* Return:
*  void
*
*******************************************************************************/
void TriggerLevelPGA_SetPower(uint8 power) 
{
    uint8 tmpCR;

    tmpCR = TriggerLevelPGA_CR1_REG & (uint8)(~TriggerLevelPGA_DRIVE_MASK);
    tmpCR |= (power & TriggerLevelPGA_DRIVE_MASK);
    TriggerLevelPGA_CR1_REG = tmpCR;  
}


/*******************************************************************************
* Function Name: TriggerLevelPGA_SetGain
********************************************************************************
*
* Summary:
*  This function sets values of the input and feedback resistors to set a 
*  specific gain of the amplifier.
*
* Parameters:
*  gain: Gain value of PGA (See header file for gain values.)
*
* Return:
*  void 
*
*******************************************************************************/
void TriggerLevelPGA_SetGain(uint8 gain) 
{
    /* Constant array for gain settings */
    const uint8 TriggerLevelPGA_GainArray[9] = { 
        (TriggerLevelPGA_RVAL_0K   | TriggerLevelPGA_R20_40B_40K | TriggerLevelPGA_BIAS_LOW), /* G=1  */
        (TriggerLevelPGA_RVAL_40K  | TriggerLevelPGA_R20_40B_40K | TriggerLevelPGA_BIAS_LOW), /* G=2  */
        (TriggerLevelPGA_RVAL_120K | TriggerLevelPGA_R20_40B_40K | TriggerLevelPGA_BIAS_LOW), /* G=4  */
        (TriggerLevelPGA_RVAL_280K | TriggerLevelPGA_R20_40B_40K | TriggerLevelPGA_BIAS_LOW), /* G=8  */
        (TriggerLevelPGA_RVAL_600K | TriggerLevelPGA_R20_40B_40K | TriggerLevelPGA_BIAS_LOW), /* G=16 */
        (TriggerLevelPGA_RVAL_460K | TriggerLevelPGA_R20_40B_40K | TriggerLevelPGA_BIAS_LOW), /* G=24, Sets Rin as 20k */
        (TriggerLevelPGA_RVAL_620K | TriggerLevelPGA_R20_40B_20K | TriggerLevelPGA_BIAS_LOW), /* G=32 */
        (TriggerLevelPGA_RVAL_470K | TriggerLevelPGA_R20_40B_20K | TriggerLevelPGA_BIAS_LOW), /* G=48, Sets Rin as 10k */
        (TriggerLevelPGA_RVAL_490K | TriggerLevelPGA_R20_40B_20K | TriggerLevelPGA_BIAS_LOW)  /* G=50, Sets Rin as 10k */
    };
    
    /* Constant array for gain compenstion settings */
    const uint8 TriggerLevelPGA_GainComp[9] = { 
        ( TriggerLevelPGA_COMP_4P35PF  | (uint8)( TriggerLevelPGA_REDC_00 >> 2 )), /* G=1  */
        ( TriggerLevelPGA_COMP_4P35PF  | (uint8)( TriggerLevelPGA_REDC_01 >> 2 )), /* G=2  */
        ( TriggerLevelPGA_COMP_3P0PF   | (uint8)( TriggerLevelPGA_REDC_01 >> 2 )), /* G=4  */
        ( TriggerLevelPGA_COMP_3P0PF   | (uint8)( TriggerLevelPGA_REDC_01 >> 2 )), /* G=8  */
        ( TriggerLevelPGA_COMP_3P6PF   | (uint8)( TriggerLevelPGA_REDC_01 >> 2 )), /* G=16 */
        ( TriggerLevelPGA_COMP_3P6PF   | (uint8)( TriggerLevelPGA_REDC_11 >> 2 )), /* G=24 */
        ( TriggerLevelPGA_COMP_3P6PF   | (uint8)( TriggerLevelPGA_REDC_11 >> 2 )), /* G=32 */
        ( TriggerLevelPGA_COMP_3P6PF   | (uint8)( TriggerLevelPGA_REDC_00 >> 2 )), /* G=48 */
        ( TriggerLevelPGA_COMP_3P6PF   | (uint8)( TriggerLevelPGA_REDC_00 >> 2 ))  /* G=50 */
    };
    
    /* Only set new gain if it is a valid gain */
    if( gain <= TriggerLevelPGA_GAIN_MAX)
    {
        /* Clear resistors, redc, and bias */
        TriggerLevelPGA_CR2_REG &= (uint8)(~(TriggerLevelPGA_RVAL_MASK | TriggerLevelPGA_R20_40B_MASK | 
                                TriggerLevelPGA_REDC_MASK | TriggerLevelPGA_BIAS_MASK ));

        /* Set gain value resistors, redc comp, and bias */
        TriggerLevelPGA_CR2_REG |= (TriggerLevelPGA_GainArray[gain] |
                                ((uint8)(TriggerLevelPGA_GainComp[gain] << 2 ) & TriggerLevelPGA_REDC_MASK));

        /* Clear sc_comp  */
        TriggerLevelPGA_CR1_REG &= (uint8)(~TriggerLevelPGA_COMP_MASK);
        /* Set sc_comp  */
        TriggerLevelPGA_CR1_REG |= ( TriggerLevelPGA_GainComp[gain] | TriggerLevelPGA_COMP_MASK );
    }
}


/* [] END OF FILE */
