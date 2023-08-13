/*******************************************************************************
* File Name: WaveA_DAC_VDAC8.c  
* Version 1.90
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "WaveA_DAC_VDAC8.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 WaveA_DAC_VDAC8_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 WaveA_DAC_VDAC8_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static WaveA_DAC_VDAC8_backupStruct WaveA_DAC_VDAC8_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: WaveA_DAC_VDAC8_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void WaveA_DAC_VDAC8_Init(void) 
{
    WaveA_DAC_VDAC8_CR0 = (WaveA_DAC_VDAC8_MODE_V );

    /* Set default data source */
    #if(WaveA_DAC_VDAC8_DEFAULT_DATA_SRC != 0 )
        WaveA_DAC_VDAC8_CR1 = (WaveA_DAC_VDAC8_DEFAULT_CNTL | WaveA_DAC_VDAC8_DACBUS_ENABLE) ;
    #else
        WaveA_DAC_VDAC8_CR1 = (WaveA_DAC_VDAC8_DEFAULT_CNTL | WaveA_DAC_VDAC8_DACBUS_DISABLE) ;
    #endif /* (WaveA_DAC_VDAC8_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(WaveA_DAC_VDAC8_DEFAULT_STRB != 0)
        WaveA_DAC_VDAC8_Strobe |= WaveA_DAC_VDAC8_STRB_EN ;
    #endif/* (WaveA_DAC_VDAC8_DEFAULT_STRB != 0) */

    /* Set default range */
    WaveA_DAC_VDAC8_SetRange(WaveA_DAC_VDAC8_DEFAULT_RANGE); 

    /* Set default speed */
    WaveA_DAC_VDAC8_SetSpeed(WaveA_DAC_VDAC8_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: WaveA_DAC_VDAC8_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void WaveA_DAC_VDAC8_Enable(void) 
{
    WaveA_DAC_VDAC8_PWRMGR |= WaveA_DAC_VDAC8_ACT_PWR_EN;
    WaveA_DAC_VDAC8_STBY_PWRMGR |= WaveA_DAC_VDAC8_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(WaveA_DAC_VDAC8_restoreVal == 1u) 
        {
             WaveA_DAC_VDAC8_CR0 = WaveA_DAC_VDAC8_backup.data_value;
             WaveA_DAC_VDAC8_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: WaveA_DAC_VDAC8_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  WaveA_DAC_VDAC8_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void WaveA_DAC_VDAC8_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(WaveA_DAC_VDAC8_initVar == 0u)
    { 
        WaveA_DAC_VDAC8_Init();
        WaveA_DAC_VDAC8_initVar = 1u;
    }

    /* Enable power to DAC */
    WaveA_DAC_VDAC8_Enable();

    /* Set default value */
    WaveA_DAC_VDAC8_SetValue(WaveA_DAC_VDAC8_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: WaveA_DAC_VDAC8_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void WaveA_DAC_VDAC8_Stop(void) 
{
    /* Disble power to DAC */
    WaveA_DAC_VDAC8_PWRMGR &= (uint8)(~WaveA_DAC_VDAC8_ACT_PWR_EN);
    WaveA_DAC_VDAC8_STBY_PWRMGR &= (uint8)(~WaveA_DAC_VDAC8_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        WaveA_DAC_VDAC8_backup.data_value = WaveA_DAC_VDAC8_CR0;
        WaveA_DAC_VDAC8_CR0 = WaveA_DAC_VDAC8_CUR_MODE_OUT_OFF;
        WaveA_DAC_VDAC8_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: WaveA_DAC_VDAC8_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void WaveA_DAC_VDAC8_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    WaveA_DAC_VDAC8_CR0 &= (uint8)(~WaveA_DAC_VDAC8_HS_MASK);
    WaveA_DAC_VDAC8_CR0 |=  (speed & WaveA_DAC_VDAC8_HS_MASK);
}


/*******************************************************************************
* Function Name: WaveA_DAC_VDAC8_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void WaveA_DAC_VDAC8_SetRange(uint8 range) 
{
    WaveA_DAC_VDAC8_CR0 &= (uint8)(~WaveA_DAC_VDAC8_RANGE_MASK);      /* Clear existing mode */
    WaveA_DAC_VDAC8_CR0 |= (range & WaveA_DAC_VDAC8_RANGE_MASK);      /*  Set Range  */
    WaveA_DAC_VDAC8_DacTrim();
}


/*******************************************************************************
* Function Name: WaveA_DAC_VDAC8_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void WaveA_DAC_VDAC8_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 WaveA_DAC_VDAC8_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    WaveA_DAC_VDAC8_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        WaveA_DAC_VDAC8_Data = value;
        CyExitCriticalSection(WaveA_DAC_VDAC8_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: WaveA_DAC_VDAC8_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void WaveA_DAC_VDAC8_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((WaveA_DAC_VDAC8_CR0 & WaveA_DAC_VDAC8_RANGE_MASK) >> 2) + WaveA_DAC_VDAC8_TRIM_M7_1V_RNG_OFFSET;
    WaveA_DAC_VDAC8_TR = CY_GET_XTND_REG8((uint8 *)(WaveA_DAC_VDAC8_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
