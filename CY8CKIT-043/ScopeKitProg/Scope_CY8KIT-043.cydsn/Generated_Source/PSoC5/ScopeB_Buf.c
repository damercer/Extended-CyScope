/*******************************************************************************
* File Name: ScopeB_Buf.c  
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

#include "ScopeB_Buf.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (CY_PSOC5A)
    static ScopeB_Buf_BACKUP_STRUCT  ScopeB_Buf_P5backup;
#endif /* (CY_ PSOC5A) */

uint8 ScopeB_Buf_initVar = 0u;


/*******************************************************************************   
* Function Name: ScopeB_Buf_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  ScopeB_Buf_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ScopeB_Buf_Init(void) 
{
    /* Set PGA mode */
    ScopeB_Buf_CR0_REG = ScopeB_Buf_MODE_PGA;      
    /* Set non-inverting PGA mode and reference mode */
    ScopeB_Buf_CR1_REG |= ScopeB_Buf_PGA_NINV;  
    /* Set default gain and ref mode */
    ScopeB_Buf_CR2_REG = ScopeB_Buf_VREF_MODE;
    /* Set gain and compensation */
    ScopeB_Buf_SetGain(ScopeB_Buf_DEFAULT_GAIN);
    /* Set power */
    ScopeB_Buf_SetPower(ScopeB_Buf_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: ScopeB_Buf_Enable
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
void ScopeB_Buf_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(ScopeB_Buf_P5backup.enableState == 1u)
        {
            ScopeB_Buf_CR1_REG = ScopeB_Buf_P5backup.scCR1Reg;
            ScopeB_Buf_CR2_REG = ScopeB_Buf_P5backup.scCR2Reg;
            ScopeB_Buf_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */   

    /* Enable power to the Amp in Active mode*/
    ScopeB_Buf_PM_ACT_CFG_REG |= ScopeB_Buf_ACT_PWR_EN;

    /* Enable power to the Amp in Alternative Active mode*/
    ScopeB_Buf_PM_STBY_CFG_REG |= ScopeB_Buf_STBY_PWR_EN;
    
    ScopeB_Buf_PUMP_CR1_REG |= ScopeB_Buf_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                ScopeB_Buf_BSTCLK_REG &= (uint8)(~ScopeB_Buf_BST_CLK_INDEX_MASK);
                ScopeB_Buf_BSTCLK_REG |= ScopeB_Buf_BST_CLK_EN | CyScBoostClk__INDEX;
                ScopeB_Buf_SC_MISC_REG |= ScopeB_Buf_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                ScopeB_Buf_BSTCLK_REG &= (uint8)(~ScopeB_Buf_BST_CLK_EN);
                ScopeB_Buf_SC_MISC_REG &= (uint8)(~ScopeB_Buf_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: ScopeB_Buf_Start
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
void ScopeB_Buf_Start(void) 
{

    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modification in stop() API */

    if(ScopeB_Buf_initVar == 0u)
    {
        ScopeB_Buf_Init();
        ScopeB_Buf_initVar = 1u;
    }

    ScopeB_Buf_Enable();
}


/*******************************************************************************
* Function Name: ScopeB_Buf_Stop
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
void ScopeB_Buf_Stop(void) 
{ 
    /* Disble power to the Amp in Active mode template */
    ScopeB_Buf_PM_ACT_CFG_REG &= (uint8)(~ScopeB_Buf_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    ScopeB_Buf_PM_STBY_CFG_REG &= (uint8)(~ScopeB_Buf_STBY_PWR_EN);

    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            ScopeB_Buf_BSTCLK_REG &= (uint8)(~ScopeB_Buf_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((ScopeB_Buf_PM_ACT_CFG_REG & ScopeB_Buf_PM_ACT_CFG_MASK) == 0u)
            {
                ScopeB_Buf_SC_MISC_REG &= (uint8)(~ScopeB_Buf_PUMP_FORCE);
                ScopeB_Buf_PUMP_CR1_REG &= (uint8)(~ScopeB_Buf_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /* This sets PGA in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        ScopeB_Buf_P5backup.scCR1Reg = ScopeB_Buf_CR1_REG;
        ScopeB_Buf_P5backup.scCR2Reg = ScopeB_Buf_CR2_REG;
        ScopeB_Buf_CR1_REG = 0x00u;
        ScopeB_Buf_CR2_REG = 0x00u;
        ScopeB_Buf_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: ScopeB_Buf_SetPower
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
void ScopeB_Buf_SetPower(uint8 power) 
{
    uint8 tmpCR;

    tmpCR = ScopeB_Buf_CR1_REG & (uint8)(~ScopeB_Buf_DRIVE_MASK);
    tmpCR |= (power & ScopeB_Buf_DRIVE_MASK);
    ScopeB_Buf_CR1_REG = tmpCR;  
}


/*******************************************************************************
* Function Name: ScopeB_Buf_SetGain
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
void ScopeB_Buf_SetGain(uint8 gain) 
{
    /* Constant array for gain settings */
    const uint8 ScopeB_Buf_GainArray[9] = { 
        (ScopeB_Buf_RVAL_0K   | ScopeB_Buf_R20_40B_40K | ScopeB_Buf_BIAS_LOW), /* G=1  */
        (ScopeB_Buf_RVAL_40K  | ScopeB_Buf_R20_40B_40K | ScopeB_Buf_BIAS_LOW), /* G=2  */
        (ScopeB_Buf_RVAL_120K | ScopeB_Buf_R20_40B_40K | ScopeB_Buf_BIAS_LOW), /* G=4  */
        (ScopeB_Buf_RVAL_280K | ScopeB_Buf_R20_40B_40K | ScopeB_Buf_BIAS_LOW), /* G=8  */
        (ScopeB_Buf_RVAL_600K | ScopeB_Buf_R20_40B_40K | ScopeB_Buf_BIAS_LOW), /* G=16 */
        (ScopeB_Buf_RVAL_460K | ScopeB_Buf_R20_40B_40K | ScopeB_Buf_BIAS_LOW), /* G=24, Sets Rin as 20k */
        (ScopeB_Buf_RVAL_620K | ScopeB_Buf_R20_40B_20K | ScopeB_Buf_BIAS_LOW), /* G=32 */
        (ScopeB_Buf_RVAL_470K | ScopeB_Buf_R20_40B_20K | ScopeB_Buf_BIAS_LOW), /* G=48, Sets Rin as 10k */
        (ScopeB_Buf_RVAL_490K | ScopeB_Buf_R20_40B_20K | ScopeB_Buf_BIAS_LOW)  /* G=50, Sets Rin as 10k */
    };
    
    /* Constant array for gain compenstion settings */
    const uint8 ScopeB_Buf_GainComp[9] = { 
        ( ScopeB_Buf_COMP_4P35PF  | (uint8)( ScopeB_Buf_REDC_00 >> 2 )), /* G=1  */
        ( ScopeB_Buf_COMP_4P35PF  | (uint8)( ScopeB_Buf_REDC_01 >> 2 )), /* G=2  */
        ( ScopeB_Buf_COMP_3P0PF   | (uint8)( ScopeB_Buf_REDC_01 >> 2 )), /* G=4  */
        ( ScopeB_Buf_COMP_3P0PF   | (uint8)( ScopeB_Buf_REDC_01 >> 2 )), /* G=8  */
        ( ScopeB_Buf_COMP_3P6PF   | (uint8)( ScopeB_Buf_REDC_01 >> 2 )), /* G=16 */
        ( ScopeB_Buf_COMP_3P6PF   | (uint8)( ScopeB_Buf_REDC_11 >> 2 )), /* G=24 */
        ( ScopeB_Buf_COMP_3P6PF   | (uint8)( ScopeB_Buf_REDC_11 >> 2 )), /* G=32 */
        ( ScopeB_Buf_COMP_3P6PF   | (uint8)( ScopeB_Buf_REDC_00 >> 2 )), /* G=48 */
        ( ScopeB_Buf_COMP_3P6PF   | (uint8)( ScopeB_Buf_REDC_00 >> 2 ))  /* G=50 */
    };
    
    /* Only set new gain if it is a valid gain */
    if( gain <= ScopeB_Buf_GAIN_MAX)
    {
        /* Clear resistors, redc, and bias */
        ScopeB_Buf_CR2_REG &= (uint8)(~(ScopeB_Buf_RVAL_MASK | ScopeB_Buf_R20_40B_MASK | 
                                ScopeB_Buf_REDC_MASK | ScopeB_Buf_BIAS_MASK ));

        /* Set gain value resistors, redc comp, and bias */
        ScopeB_Buf_CR2_REG |= (ScopeB_Buf_GainArray[gain] |
                                ((uint8)(ScopeB_Buf_GainComp[gain] << 2 ) & ScopeB_Buf_REDC_MASK));

        /* Clear sc_comp  */
        ScopeB_Buf_CR1_REG &= (uint8)(~ScopeB_Buf_COMP_MASK);
        /* Set sc_comp  */
        ScopeB_Buf_CR1_REG |= ( ScopeB_Buf_GainComp[gain] | ScopeB_Buf_COMP_MASK );
    }
}


/* [] END OF FILE */
