/*******************************************************************************
* File Name: Exy_Trig_out.h  
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

#if !defined(CY_PINS_Exy_Trig_out_H) /* Pins Exy_Trig_out_H */
#define CY_PINS_Exy_Trig_out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Exy_Trig_out_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Exy_Trig_out__PORT == 15 && ((Exy_Trig_out__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Exy_Trig_out_Write(uint8 value);
void    Exy_Trig_out_SetDriveMode(uint8 mode);
uint8   Exy_Trig_out_ReadDataReg(void);
uint8   Exy_Trig_out_Read(void);
void    Exy_Trig_out_SetInterruptMode(uint16 position, uint16 mode);
uint8   Exy_Trig_out_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Exy_Trig_out_SetDriveMode() function.
     *  @{
     */
        #define Exy_Trig_out_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Exy_Trig_out_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Exy_Trig_out_DM_RES_UP          PIN_DM_RES_UP
        #define Exy_Trig_out_DM_RES_DWN         PIN_DM_RES_DWN
        #define Exy_Trig_out_DM_OD_LO           PIN_DM_OD_LO
        #define Exy_Trig_out_DM_OD_HI           PIN_DM_OD_HI
        #define Exy_Trig_out_DM_STRONG          PIN_DM_STRONG
        #define Exy_Trig_out_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Exy_Trig_out_MASK               Exy_Trig_out__MASK
#define Exy_Trig_out_SHIFT              Exy_Trig_out__SHIFT
#define Exy_Trig_out_WIDTH              1u

/* Interrupt constants */
#if defined(Exy_Trig_out__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Exy_Trig_out_SetInterruptMode() function.
     *  @{
     */
        #define Exy_Trig_out_INTR_NONE      (uint16)(0x0000u)
        #define Exy_Trig_out_INTR_RISING    (uint16)(0x0001u)
        #define Exy_Trig_out_INTR_FALLING   (uint16)(0x0002u)
        #define Exy_Trig_out_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Exy_Trig_out_INTR_MASK      (0x01u) 
#endif /* (Exy_Trig_out__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Exy_Trig_out_PS                     (* (reg8 *) Exy_Trig_out__PS)
/* Data Register */
#define Exy_Trig_out_DR                     (* (reg8 *) Exy_Trig_out__DR)
/* Port Number */
#define Exy_Trig_out_PRT_NUM                (* (reg8 *) Exy_Trig_out__PRT) 
/* Connect to Analog Globals */                                                  
#define Exy_Trig_out_AG                     (* (reg8 *) Exy_Trig_out__AG)                       
/* Analog MUX bux enable */
#define Exy_Trig_out_AMUX                   (* (reg8 *) Exy_Trig_out__AMUX) 
/* Bidirectional Enable */                                                        
#define Exy_Trig_out_BIE                    (* (reg8 *) Exy_Trig_out__BIE)
/* Bit-mask for Aliased Register Access */
#define Exy_Trig_out_BIT_MASK               (* (reg8 *) Exy_Trig_out__BIT_MASK)
/* Bypass Enable */
#define Exy_Trig_out_BYP                    (* (reg8 *) Exy_Trig_out__BYP)
/* Port wide control signals */                                                   
#define Exy_Trig_out_CTL                    (* (reg8 *) Exy_Trig_out__CTL)
/* Drive Modes */
#define Exy_Trig_out_DM0                    (* (reg8 *) Exy_Trig_out__DM0) 
#define Exy_Trig_out_DM1                    (* (reg8 *) Exy_Trig_out__DM1)
#define Exy_Trig_out_DM2                    (* (reg8 *) Exy_Trig_out__DM2) 
/* Input Buffer Disable Override */
#define Exy_Trig_out_INP_DIS                (* (reg8 *) Exy_Trig_out__INP_DIS)
/* LCD Common or Segment Drive */
#define Exy_Trig_out_LCD_COM_SEG            (* (reg8 *) Exy_Trig_out__LCD_COM_SEG)
/* Enable Segment LCD */
#define Exy_Trig_out_LCD_EN                 (* (reg8 *) Exy_Trig_out__LCD_EN)
/* Slew Rate Control */
#define Exy_Trig_out_SLW                    (* (reg8 *) Exy_Trig_out__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Exy_Trig_out_PRTDSI__CAPS_SEL       (* (reg8 *) Exy_Trig_out__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Exy_Trig_out_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Exy_Trig_out__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Exy_Trig_out_PRTDSI__OE_SEL0        (* (reg8 *) Exy_Trig_out__PRTDSI__OE_SEL0) 
#define Exy_Trig_out_PRTDSI__OE_SEL1        (* (reg8 *) Exy_Trig_out__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Exy_Trig_out_PRTDSI__OUT_SEL0       (* (reg8 *) Exy_Trig_out__PRTDSI__OUT_SEL0) 
#define Exy_Trig_out_PRTDSI__OUT_SEL1       (* (reg8 *) Exy_Trig_out__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Exy_Trig_out_PRTDSI__SYNC_OUT       (* (reg8 *) Exy_Trig_out__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Exy_Trig_out__SIO_CFG)
    #define Exy_Trig_out_SIO_HYST_EN        (* (reg8 *) Exy_Trig_out__SIO_HYST_EN)
    #define Exy_Trig_out_SIO_REG_HIFREQ     (* (reg8 *) Exy_Trig_out__SIO_REG_HIFREQ)
    #define Exy_Trig_out_SIO_CFG            (* (reg8 *) Exy_Trig_out__SIO_CFG)
    #define Exy_Trig_out_SIO_DIFF           (* (reg8 *) Exy_Trig_out__SIO_DIFF)
#endif /* (Exy_Trig_out__SIO_CFG) */

/* Interrupt Registers */
#if defined(Exy_Trig_out__INTSTAT)
    #define Exy_Trig_out_INTSTAT            (* (reg8 *) Exy_Trig_out__INTSTAT)
    #define Exy_Trig_out_SNAP               (* (reg8 *) Exy_Trig_out__SNAP)
    
	#define Exy_Trig_out_0_INTTYPE_REG 		(* (reg8 *) Exy_Trig_out__0__INTTYPE)
#endif /* (Exy_Trig_out__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Exy_Trig_out_H */


/* [] END OF FILE */
