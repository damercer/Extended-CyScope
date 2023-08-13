/*******************************************************************************
* File Name: ScopeA_Buf.c  
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

#include "ScopeA_Buf.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (CY_PSOC5A)
    static ScopeA_Buf_BACKUP_STRUCT  ScopeA_Buf_P5backup;
#endif /* (CY_ PSOC5A) */

uint8 ScopeA_Buf_initVar = 0u;


/*******************************************************************************   
* Function Name: ScopeA_Buf_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  ScopeA_Buf_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ScopeA_Buf_Init(void) 
{
    /* Set PGA mode */
    ScopeA_Buf_CR0_REG = ScopeA_Buf_MODE_PGA;      
    /* Set non-inverting PGA mode and reference mode */
    ScopeA_Buf_CR1_REG |= ScopeA_Buf_PGA_NINV;  
    /* Set default gain and ref mode */
    ScopeA_Buf_CR2_REG = ScopeA_Buf_VREF_MODE;
    /* Set gain and compensation */
    ScopeA_Buf_SetGain(ScopeA_Buf_DEFAULT_GAIN);
    /* Set power */
    ScopeA_Buf_SetPower(ScopeA_Buf_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: ScopeA_Buf_Enable
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
void ScopeA_Buf_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(ScopeA_Buf_P5backup.enableState == 1u)
        {
            ScopeA_Buf_CR1_REG = ScopeA_Buf_P5backup.scCR1Reg;
            ScopeA_Buf_CR2_REG = ScopeA_Buf_P5backup.scCR2Reg;
            ScopeA_Buf_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */   

    /* Enable power to the Amp in Active mode*/
    ScopeA_Buf_PM_ACT_CFG_REG |= ScopeA_Buf_ACT_PWR_EN;

    /* Enable power to the Amp in Alternative Active mode*/
    ScopeA_Buf_PM_STBY_CFG_REG |= ScopeA_Buf_STBY_PWR_EN;
    
    ScopeA_Buf_PUMP_CR1_REG |= ScopeA_Buf_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                ScopeA_Buf_BSTCLK_REG &= (uint8)(~ScopeA_Buf_BST_CLK_INDEX_MASK);
                ScopeA_Buf_BSTCLK_REG |= ScopeA_Buf_BST_CLK_EN | CyScBoostClk__INDEX;
                ScopeA_Buf_SC_MISC_REG |= ScopeA_Buf_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                ScopeA_Buf_BSTCLK_REG &= (uint8)(~ScopeA_Buf_BST_CLK_EN);
                ScopeA_Buf_SC_MISC_REG &= (uint8)(~ScopeA_Buf_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: ScopeA_Buf_Start
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
void ScopeA_Buf_Start(void) 
{

    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modification in stop() API */

    if(ScopeA_Buf_initVar == 0u)
    {
        ScopeA_Buf_Init();
        ScopeA_Buf_initVar = 1u;
    }

    ScopeA_Buf_Enable();
}


/*******************************************************************************
* Function Name: ScopeA_Buf_Stop
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
void ScopeA_Buf_Stop(void) 
{ 
    /* Disble power to the Amp in Active mode template */
    ScopeA_Buf_PM_ACT_CFG_REG &= (uint8)(~ScopeA_Buf_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    ScopeA_Buf_PM_STBY_CFG_REG &= (uint8)(~ScopeA_Buf_STBY_PWR_EN);

    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            ScopeA_Buf_BSTCLK_REG &= (uint8)(~ScopeA_Buf_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((ScopeA_Buf_PM_ACT_CFG_REG & ScopeA_Buf_PM_ACT_CFG_MASK) == 0u)
            {
                ScopeA_Buf_SC_MISC_REG &= (uint8)(~ScopeA_Buf_PUMP_FORCE);
                ScopeA_Buf_PUMP_CR1_REG &= (uint8)(~ScopeA_Buf_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /* This sets PGA in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        ScopeA_Buf_P5backup.scCR1Reg = ScopeA_Buf_CR1_REG;
        ScopeA_Buf_P5backup.scCR2Reg = ScopeA_Buf_CR2_REG;
        ScopeA_Buf_CR1_REG = 0x00u;
        ScopeA_Buf_CR2_REG = 0x00u;
        ScopeA_Buf_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: ScopeA_Buf_SetPower
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
void ScopeA_Buf_SetPower(uint8 power) 
{
    uint8 tmpCR;

    tmpCR = ScopeA_Buf_CR1_REG & (uint8)(~ScopeA_Buf_DRIVE_MASK);
    tmpCR |= (power & ScopeA_Buf_DRIVE_MASK);
    ScopeA_Buf_CR1_REG = tmpCR;  
}


/*******************************************************************************
* Function Name: ScopeA_Buf_SetGain
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
void ScopeA_Buf_SetGain(uint8 gain) 
{
    /* Constant array for gain settings */
    const uint8 ScopeA_Buf_GainArray[9] = { 
        (ScopeA_Buf_RVAL_0K   | ScopeA_Buf_R20_40B_40K | ScopeA_Buf_BIAS_LOW), /* G=1  */
        (ScopeA_Buf_RVAL_40K  | ScopeA_Buf_R20_40B_40K | ScopeA_Buf_BIAS_LOW), /* G=2  */
        (ScopeA_Buf_RVAL_120K | ScopeA_Buf_R20_40B_40K | ScopeA_Buf_BIAS_LOW), /* G=4  */
        (ScopeA_Buf_RVAL_280K | ScopeA_Buf_R20_40B_40K | ScopeA_Buf_BIAS_LOW), /* G=8  */
        (ScopeA_Buf_RVAL_600K | ScopeA_Buf_R20_40B_40K | ScopeA_Buf_BIAS_LOW), /* G=16 */
        (ScopeA_Buf_RVAL_460K | ScopeA_Buf_R20_40B_40K | ScopeA_Buf_BIAS_LOW), /* G=24, Sets Rin as 20k */
        (ScopeA_Buf_RVAL_620K | ScopeA_Buf_R20_40B_20K | ScopeA_Buf_BIAS_LOW), /* G=32 */
        (ScopeA_Buf_RVAL_470K | ScopeA_Buf_R20_40B_20K | ScopeA_Buf_BIAS_LOW), /* G=48, Sets Rin as 10k */
        (ScopeA_Buf_RVAL_490K | ScopeA_Buf_R20_40B_20K | ScopeA_Buf_BIAS_LOW)  /* G=50, Sets Rin as 10k */
    };
    
    /* Constant array for gain compenstion settings */
    const uint8 ScopeA_Buf_GainComp[9] = { 
        ( ScopeA_Buf_COMP_4P35PF  | (uint8)( ScopeA_Buf_REDC_00 >> 2 )), /* G=1  */
        ( ScopeA_Buf_COMP_4P35PF  | (uint8)( ScopeA_Buf_REDC_01 >> 2 )), /* G=2  */
        ( ScopeA_Buf_COMP_3P0PF   | (uint8)( ScopeA_Buf_REDC_01 >> 2 )), /* G=4  */
        ( ScopeA_Buf_COMP_3P0PF   | (uint8)( ScopeA_Buf_REDC_01 >> 2 )), /* G=8  */
        ( ScopeA_Buf_COMP_3P6PF   | (uint8)( ScopeA_Buf_REDC_01 >> 2 )), /* G=16 */
        ( ScopeA_Buf_COMP_3P6PF   | (uint8)( ScopeA_Buf_REDC_11 >> 2 )), /* G=24 */
        ( ScopeA_Buf_COMP_3P6PF   | (uint8)( ScopeA_Buf_REDC_11 >> 2 )), /* G=32 */
        ( ScopeA_Buf_COMP_3P6PF   | (uint8)( ScopeA_Buf_REDC_00 >> 2 )), /* G=48 */
        ( ScopeA_Buf_COMP_3P6PF   | (uint8)( ScopeA_Buf_REDC_00 >> 2 ))  /* G=50 */
    };
    
    /* Only set new gain if it is a valid gain */
    if( gain <= ScopeA_Buf_GAIN_MAX)
    {
        /* Clear resistors, redc, and bias */
        ScopeA_Buf_CR2_REG &= (uint8)(~(ScopeA_Buf_RVAL_MASK | ScopeA_Buf_R20_40B_MASK | 
                                ScopeA_Buf_REDC_MASK | ScopeA_Buf_BIAS_MASK ));

        /* Set gain value resistors, redc comp, and bias */
        ScopeA_Buf_CR2_REG |= (ScopeA_Buf_GainArray[gain] |
                                ((uint8)(ScopeA_Buf_GainComp[gain] << 2 ) & ScopeA_Buf_REDC_MASK));

        /* Clear sc_comp  */
        ScopeA_Buf_CR1_REG &= (uint8)(~ScopeA_Buf_COMP_MASK);
        /* Set sc_comp  */
        ScopeA_Buf_CR1_REG |= ( ScopeA_Buf_GainComp[gain] | ScopeA_Buf_COMP_MASK );
    }
}


/* [] END OF FILE */
