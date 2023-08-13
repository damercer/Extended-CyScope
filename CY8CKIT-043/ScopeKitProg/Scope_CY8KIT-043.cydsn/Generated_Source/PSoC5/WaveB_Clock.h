/*******************************************************************************
* File Name: WaveB_Clock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_WaveB_Clock_H)
#define CY_CLOCK_WaveB_Clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void WaveB_Clock_Start(void) ;
void WaveB_Clock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void WaveB_Clock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void WaveB_Clock_StandbyPower(uint8 state) ;
void WaveB_Clock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 WaveB_Clock_GetDividerRegister(void) ;
void WaveB_Clock_SetModeRegister(uint8 modeBitMask) ;
void WaveB_Clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 WaveB_Clock_GetModeRegister(void) ;
void WaveB_Clock_SetSourceRegister(uint8 clkSource) ;
uint8 WaveB_Clock_GetSourceRegister(void) ;
#if defined(WaveB_Clock__CFG3)
void WaveB_Clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 WaveB_Clock_GetPhaseRegister(void) ;
#endif /* defined(WaveB_Clock__CFG3) */

#define WaveB_Clock_Enable()                       WaveB_Clock_Start()
#define WaveB_Clock_Disable()                      WaveB_Clock_Stop()
#define WaveB_Clock_SetDivider(clkDivider)         WaveB_Clock_SetDividerRegister(clkDivider, 1u)
#define WaveB_Clock_SetDividerValue(clkDivider)    WaveB_Clock_SetDividerRegister((clkDivider) - 1u, 1u)
#define WaveB_Clock_SetMode(clkMode)               WaveB_Clock_SetModeRegister(clkMode)
#define WaveB_Clock_SetSource(clkSource)           WaveB_Clock_SetSourceRegister(clkSource)
#if defined(WaveB_Clock__CFG3)
#define WaveB_Clock_SetPhase(clkPhase)             WaveB_Clock_SetPhaseRegister(clkPhase)
#define WaveB_Clock_SetPhaseValue(clkPhase)        WaveB_Clock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(WaveB_Clock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define WaveB_Clock_CLKEN              (* (reg8 *) WaveB_Clock__PM_ACT_CFG)
#define WaveB_Clock_CLKEN_PTR          ((reg8 *) WaveB_Clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define WaveB_Clock_CLKSTBY            (* (reg8 *) WaveB_Clock__PM_STBY_CFG)
#define WaveB_Clock_CLKSTBY_PTR        ((reg8 *) WaveB_Clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define WaveB_Clock_DIV_LSB            (* (reg8 *) WaveB_Clock__CFG0)
#define WaveB_Clock_DIV_LSB_PTR        ((reg8 *) WaveB_Clock__CFG0)
#define WaveB_Clock_DIV_PTR            ((reg16 *) WaveB_Clock__CFG0)

/* Clock MSB divider configuration register. */
#define WaveB_Clock_DIV_MSB            (* (reg8 *) WaveB_Clock__CFG1)
#define WaveB_Clock_DIV_MSB_PTR        ((reg8 *) WaveB_Clock__CFG1)

/* Mode and source configuration register */
#define WaveB_Clock_MOD_SRC            (* (reg8 *) WaveB_Clock__CFG2)
#define WaveB_Clock_MOD_SRC_PTR        ((reg8 *) WaveB_Clock__CFG2)

#if defined(WaveB_Clock__CFG3)
/* Analog clock phase configuration register */
#define WaveB_Clock_PHASE              (* (reg8 *) WaveB_Clock__CFG3)
#define WaveB_Clock_PHASE_PTR          ((reg8 *) WaveB_Clock__CFG3)
#endif /* defined(WaveB_Clock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define WaveB_Clock_CLKEN_MASK         WaveB_Clock__PM_ACT_MSK
#define WaveB_Clock_CLKSTBY_MASK       WaveB_Clock__PM_STBY_MSK

/* CFG2 field masks */
#define WaveB_Clock_SRC_SEL_MSK        WaveB_Clock__CFG2_SRC_SEL_MASK
#define WaveB_Clock_MODE_MASK          (~(WaveB_Clock_SRC_SEL_MSK))

#if defined(WaveB_Clock__CFG3)
/* CFG3 phase mask */
#define WaveB_Clock_PHASE_MASK         WaveB_Clock__CFG3_PHASE_DLY_MASK
#endif /* defined(WaveB_Clock__CFG3) */

#endif /* CY_CLOCK_WaveB_Clock_H */


/* [] END OF FILE */
