/*******************************************************************************
* File Name: ScopeC_Buf.c  
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

#include "ScopeC_Buf.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (CY_PSOC5A)
    static ScopeC_Buf_BACKUP_STRUCT  ScopeC_Buf_P5backup;
#endif /* (CY_ PSOC5A) */

uint8 ScopeC_Buf_initVar = 0u;


/*******************************************************************************   
* Function Name: ScopeC_Buf_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  ScopeC_Buf_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ScopeC_Buf_Init(void) 
{
    /* Set PGA mode */
    ScopeC_Buf_CR0_REG = ScopeC_Buf_MODE_PGA;      
    /* Set non-inverting PGA mode and reference mode */
    ScopeC_Buf_CR1_REG |= ScopeC_Buf_PGA_NINV;  
    /* Set default gain and ref mode */
    ScopeC_Buf_CR2_REG = ScopeC_Buf_VREF_MODE;
    /* Set gain and compensation */
    ScopeC_Buf_SetGain(ScopeC_Buf_DEFAULT_GAIN);
    /* Set power */
    ScopeC_Buf_SetPower(ScopeC_Buf_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: ScopeC_Buf_Enable
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
void ScopeC_Buf_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(ScopeC_Buf_P5backup.enableState == 1u)
        {
            ScopeC_Buf_CR1_REG = ScopeC_Buf_P5backup.scCR1Reg;
            ScopeC_Buf_CR2_REG = ScopeC_Buf_P5backup.scCR2Reg;
            ScopeC_Buf_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */   

    /* Enable power to the Amp in Active mode*/
    ScopeC_Buf_PM_ACT_CFG_REG |= ScopeC_Buf_ACT_PWR_EN;

    /* Enable power to the Amp in Alternative Active mode*/
    ScopeC_Buf_PM_STBY_CFG_REG |= ScopeC_Buf_STBY_PWR_EN;
    
    ScopeC_Buf_PUMP_CR1_REG |= ScopeC_Buf_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                ScopeC_Buf_BSTCLK_REG &= (uint8)(~ScopeC_Buf_BST_CLK_INDEX_MASK);
                ScopeC_Buf_BSTCLK_REG |= ScopeC_Buf_BST_CLK_EN | CyScBoostClk__INDEX;
                ScopeC_Buf_SC_MISC_REG |= ScopeC_Buf_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                ScopeC_Buf_BSTCLK_REG &= (uint8)(~ScopeC_Buf_BST_CLK_EN);
                ScopeC_Buf_SC_MISC_REG &= (uint8)(~ScopeC_Buf_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: ScopeC_Buf_Start
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
void ScopeC_Buf_Start(void) 
{

    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modification in stop() API */

    if(ScopeC_Buf_initVar == 0u)
    {
        ScopeC_Buf_Init();
        ScopeC_Buf_initVar = 1u;
    }

    ScopeC_Buf_Enable();
}


/*******************************************************************************
* Function Name: ScopeC_Buf_Stop
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
void ScopeC_Buf_Stop(void) 
{ 
    /* Disble power to the Amp in Active mode template */
    ScopeC_Buf_PM_ACT_CFG_REG &= (uint8)(~ScopeC_Buf_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    ScopeC_Buf_PM_STBY_CFG_REG &= (uint8)(~ScopeC_Buf_STBY_PWR_EN);

    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            ScopeC_Buf_BSTCLK_REG &= (uint8)(~ScopeC_Buf_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((ScopeC_Buf_PM_ACT_CFG_REG & ScopeC_Buf_PM_ACT_CFG_MASK) == 0u)
            {
                ScopeC_Buf_SC_MISC_REG &= (uint8)(~ScopeC_Buf_PUMP_FORCE);
                ScopeC_Buf_PUMP_CR1_REG &= (uint8)(~ScopeC_Buf_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /* This sets PGA in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        ScopeC_Buf_P5backup.scCR1Reg = ScopeC_Buf_CR1_REG;
        ScopeC_Buf_P5backup.scCR2Reg = ScopeC_Buf_CR2_REG;
        ScopeC_Buf_CR1_REG = 0x00u;
        ScopeC_Buf_CR2_REG = 0x00u;
        ScopeC_Buf_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: ScopeC_Buf_SetPower
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
void ScopeC_Buf_SetPower(uint8 power) 
{
    uint8 tmpCR;

    tmpCR = ScopeC_Buf_CR1_REG & (uint8)(~ScopeC_Buf_DRIVE_MASK);
    tmpCR |= (power & ScopeC_Buf_DRIVE_MASK);
    ScopeC_Buf_CR1_REG = tmpCR;  
}


/*******************************************************************************
* Function Name: ScopeC_Buf_SetGain
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
void ScopeC_Buf_SetGain(uint8 gain) 
{
    /* Constant array for gain settings */
    const uint8 ScopeC_Buf_GainArray[9] = { 
        (ScopeC_Buf_RVAL_0K   | ScopeC_Buf_R20_40B_40K | ScopeC_Buf_BIAS_LOW), /* G=1  */
        (ScopeC_Buf_RVAL_40K  | ScopeC_Buf_R20_40B_40K | ScopeC_Buf_BIAS_LOW), /* G=2  */
        (ScopeC_Buf_RVAL_120K | ScopeC_Buf_R20_40B_40K | ScopeC_Buf_BIAS_LOW), /* G=4  */
        (ScopeC_Buf_RVAL_280K | ScopeC_Buf_R20_40B_40K | ScopeC_Buf_BIAS_LOW), /* G=8  */
        (ScopeC_Buf_RVAL_600K | ScopeC_Buf_R20_40B_40K | ScopeC_Buf_BIAS_LOW), /* G=16 */
        (ScopeC_Buf_RVAL_460K | ScopeC_Buf_R20_40B_40K | ScopeC_Buf_BIAS_LOW), /* G=24, Sets Rin as 20k */
        (ScopeC_Buf_RVAL_620K | ScopeC_Buf_R20_40B_20K | ScopeC_Buf_BIAS_LOW), /* G=32 */
        (ScopeC_Buf_RVAL_470K | ScopeC_Buf_R20_40B_20K | ScopeC_Buf_BIAS_LOW), /* G=48, Sets Rin as 10k */
        (ScopeC_Buf_RVAL_490K | ScopeC_Buf_R20_40B_20K | ScopeC_Buf_BIAS_LOW)  /* G=50, Sets Rin as 10k */
    };
    
    /* Constant array for gain compenstion settings */
    const uint8 ScopeC_Buf_GainComp[9] = { 
        ( ScopeC_Buf_COMP_4P35PF  | (uint8)( ScopeC_Buf_REDC_00 >> 2 )), /* G=1  */
        ( ScopeC_Buf_COMP_4P35PF  | (uint8)( ScopeC_Buf_REDC_01 >> 2 )), /* G=2  */
        ( ScopeC_Buf_COMP_3P0PF   | (uint8)( ScopeC_Buf_REDC_01 >> 2 )), /* G=4  */
        ( ScopeC_Buf_COMP_3P0PF   | (uint8)( ScopeC_Buf_REDC_01 >> 2 )), /* G=8  */
        ( ScopeC_Buf_COMP_3P6PF   | (uint8)( ScopeC_Buf_REDC_01 >> 2 )), /* G=16 */
        ( ScopeC_Buf_COMP_3P6PF   | (uint8)( ScopeC_Buf_REDC_11 >> 2 )), /* G=24 */
        ( ScopeC_Buf_COMP_3P6PF   | (uint8)( ScopeC_Buf_REDC_11 >> 2 )), /* G=32 */
        ( ScopeC_Buf_COMP_3P6PF   | (uint8)( ScopeC_Buf_REDC_00 >> 2 )), /* G=48 */
        ( ScopeC_Buf_COMP_3P6PF   | (uint8)( ScopeC_Buf_REDC_00 >> 2 ))  /* G=50 */
    };
    
    /* Only set new gain if it is a valid gain */
    if( gain <= ScopeC_Buf_GAIN_MAX)
    {
        /* Clear resistors, redc, and bias */
        ScopeC_Buf_CR2_REG &= (uint8)(~(ScopeC_Buf_RVAL_MASK | ScopeC_Buf_R20_40B_MASK | 
                                ScopeC_Buf_REDC_MASK | ScopeC_Buf_BIAS_MASK ));

        /* Set gain value resistors, redc comp, and bias */
        ScopeC_Buf_CR2_REG |= (ScopeC_Buf_GainArray[gain] |
                                ((uint8)(ScopeC_Buf_GainComp[gain] << 2 ) & ScopeC_Buf_REDC_MASK));

        /* Clear sc_comp  */
        ScopeC_Buf_CR1_REG &= (uint8)(~ScopeC_Buf_COMP_MASK);
        /* Set sc_comp  */
        ScopeC_Buf_CR1_REG |= ( ScopeC_Buf_GainComp[gain] | ScopeC_Buf_COMP_MASK );
    }
}


/* [] END OF FILE */
