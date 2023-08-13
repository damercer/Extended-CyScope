/*******************************************************************************
* File Name: WaveA_Out.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_WaveA_Out_H) /* Pins WaveA_Out_H */
#define CY_PINS_WaveA_Out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WaveA_Out_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 WaveA_Out__PORT == 15 && ((WaveA_Out__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    WaveA_Out_Write(uint8 value);
void    WaveA_Out_SetDriveMode(uint8 mode);
uint8   WaveA_Out_ReadDataReg(void);
uint8   WaveA_Out_Read(void);
void    WaveA_Out_SetInterruptMode(uint16 position, uint16 mode);
uint8   WaveA_Out_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the WaveA_Out_SetDriveMode() function.
     *  @{
     */
        #define WaveA_Out_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define WaveA_Out_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define WaveA_Out_DM_RES_UP          PIN_DM_RES_UP
        #define WaveA_Out_DM_RES_DWN         PIN_DM_RES_DWN
        #define WaveA_Out_DM_OD_LO           PIN_DM_OD_LO
        #define WaveA_Out_DM_OD_HI           PIN_DM_OD_HI
        #define WaveA_Out_DM_STRONG          PIN_DM_STRONG
        #define WaveA_Out_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define WaveA_Out_MASK               WaveA_Out__MASK
#define WaveA_Out_SHIFT              WaveA_Out__SHIFT
#define WaveA_Out_WIDTH              1u

/* Interrupt constants */
#if defined(WaveA_Out__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WaveA_Out_SetInterruptMode() function.
     *  @{
     */
        #define WaveA_Out_INTR_NONE      (uint16)(0x0000u)
        #define WaveA_Out_INTR_RISING    (uint16)(0x0001u)
        #define WaveA_Out_INTR_FALLING   (uint16)(0x0002u)
        #define WaveA_Out_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define WaveA_Out_INTR_MASK      (0x01u) 
#endif /* (WaveA_Out__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WaveA_Out_PS                     (* (reg8 *) WaveA_Out__PS)
/* Data Register */
#define WaveA_Out_DR                     (* (reg8 *) WaveA_Out__DR)
/* Port Number */
#define WaveA_Out_PRT_NUM                (* (reg8 *) WaveA_Out__PRT) 
/* Connect to Analog Globals */                                                  
#define WaveA_Out_AG                     (* (reg8 *) WaveA_Out__AG)                       
/* Analog MUX bux enable */
#define WaveA_Out_AMUX                   (* (reg8 *) WaveA_Out__AMUX) 
/* Bidirectional Enable */                                                        
#define WaveA_Out_BIE                    (* (reg8 *) WaveA_Out__BIE)
/* Bit-mask for Aliased Register Access */
#define WaveA_Out_BIT_MASK               (* (reg8 *) WaveA_Out__BIT_MASK)
/* Bypass Enable */
#define WaveA_Out_BYP                    (* (reg8 *) WaveA_Out__BYP)
/* Port wide control signals */                                                   
#define WaveA_Out_CTL                    (* (reg8 *) WaveA_Out__CTL)
/* Drive Modes */
#define WaveA_Out_DM0                    (* (reg8 *) WaveA_Out__DM0) 
#define WaveA_Out_DM1                    (* (reg8 *) WaveA_Out__DM1)
#define WaveA_Out_DM2                    (* (reg8 *) WaveA_Out__DM2) 
/* Input Buffer Disable Override */
#define WaveA_Out_INP_DIS                (* (reg8 *) WaveA_Out__INP_DIS)
/* LCD Common or Segment Drive */
#define WaveA_Out_LCD_COM_SEG            (* (reg8 *) WaveA_Out__LCD_COM_SEG)
/* Enable Segment LCD */
#define WaveA_Out_LCD_EN                 (* (reg8 *) WaveA_Out__LCD_EN)
/* Slew Rate Control */
#define WaveA_Out_SLW                    (* (reg8 *) WaveA_Out__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WaveA_Out_PRTDSI__CAPS_SEL       (* (reg8 *) WaveA_Out__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WaveA_Out_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WaveA_Out__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WaveA_Out_PRTDSI__OE_SEL0        (* (reg8 *) WaveA_Out__PRTDSI__OE_SEL0) 
#define WaveA_Out_PRTDSI__OE_SEL1        (* (reg8 *) WaveA_Out__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WaveA_Out_PRTDSI__OUT_SEL0       (* (reg8 *) WaveA_Out__PRTDSI__OUT_SEL0) 
#define WaveA_Out_PRTDSI__OUT_SEL1       (* (reg8 *) WaveA_Out__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WaveA_Out_PRTDSI__SYNC_OUT       (* (reg8 *) WaveA_Out__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(WaveA_Out__SIO_CFG)
    #define WaveA_Out_SIO_HYST_EN        (* (reg8 *) WaveA_Out__SIO_HYST_EN)
    #define WaveA_Out_SIO_REG_HIFREQ     (* (reg8 *) WaveA_Out__SIO_REG_HIFREQ)
    #define WaveA_Out_SIO_CFG            (* (reg8 *) WaveA_Out__SIO_CFG)
    #define WaveA_Out_SIO_DIFF           (* (reg8 *) WaveA_Out__SIO_DIFF)
#endif /* (WaveA_Out__SIO_CFG) */

/* Interrupt Registers */
#if defined(WaveA_Out__INTSTAT)
    #define WaveA_Out_INTSTAT            (* (reg8 *) WaveA_Out__INTSTAT)
    #define WaveA_Out_SNAP               (* (reg8 *) WaveA_Out__SNAP)
    
	#define WaveA_Out_0_INTTYPE_REG 		(* (reg8 *) WaveA_Out__0__INTTYPE)
#endif /* (WaveA_Out__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_WaveA_Out_H */


/* [] END OF FILE */
