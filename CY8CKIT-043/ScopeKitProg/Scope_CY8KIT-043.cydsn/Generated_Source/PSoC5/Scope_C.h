/*******************************************************************************
* File Name: Scope_C.h  
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

#if !defined(CY_PINS_Scope_C_H) /* Pins Scope_C_H */
#define CY_PINS_Scope_C_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Scope_C_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Scope_C__PORT == 15 && ((Scope_C__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Scope_C_Write(uint8 value);
void    Scope_C_SetDriveMode(uint8 mode);
uint8   Scope_C_ReadDataReg(void);
uint8   Scope_C_Read(void);
void    Scope_C_SetInterruptMode(uint16 position, uint16 mode);
uint8   Scope_C_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Scope_C_SetDriveMode() function.
     *  @{
     */
        #define Scope_C_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Scope_C_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Scope_C_DM_RES_UP          PIN_DM_RES_UP
        #define Scope_C_DM_RES_DWN         PIN_DM_RES_DWN
        #define Scope_C_DM_OD_LO           PIN_DM_OD_LO
        #define Scope_C_DM_OD_HI           PIN_DM_OD_HI
        #define Scope_C_DM_STRONG          PIN_DM_STRONG
        #define Scope_C_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Scope_C_MASK               Scope_C__MASK
#define Scope_C_SHIFT              Scope_C__SHIFT
#define Scope_C_WIDTH              1u

/* Interrupt constants */
#if defined(Scope_C__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Scope_C_SetInterruptMode() function.
     *  @{
     */
        #define Scope_C_INTR_NONE      (uint16)(0x0000u)
        #define Scope_C_INTR_RISING    (uint16)(0x0001u)
        #define Scope_C_INTR_FALLING   (uint16)(0x0002u)
        #define Scope_C_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Scope_C_INTR_MASK      (0x01u) 
#endif /* (Scope_C__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Scope_C_PS                     (* (reg8 *) Scope_C__PS)
/* Data Register */
#define Scope_C_DR                     (* (reg8 *) Scope_C__DR)
/* Port Number */
#define Scope_C_PRT_NUM                (* (reg8 *) Scope_C__PRT) 
/* Connect to Analog Globals */                                                  
#define Scope_C_AG                     (* (reg8 *) Scope_C__AG)                       
/* Analog MUX bux enable */
#define Scope_C_AMUX                   (* (reg8 *) Scope_C__AMUX) 
/* Bidirectional Enable */                                                        
#define Scope_C_BIE                    (* (reg8 *) Scope_C__BIE)
/* Bit-mask for Aliased Register Access */
#define Scope_C_BIT_MASK               (* (reg8 *) Scope_C__BIT_MASK)
/* Bypass Enable */
#define Scope_C_BYP                    (* (reg8 *) Scope_C__BYP)
/* Port wide control signals */                                                   
#define Scope_C_CTL                    (* (reg8 *) Scope_C__CTL)
/* Drive Modes */
#define Scope_C_DM0                    (* (reg8 *) Scope_C__DM0) 
#define Scope_C_DM1                    (* (reg8 *) Scope_C__DM1)
#define Scope_C_DM2                    (* (reg8 *) Scope_C__DM2) 
/* Input Buffer Disable Override */
#define Scope_C_INP_DIS                (* (reg8 *) Scope_C__INP_DIS)
/* LCD Common or Segment Drive */
#define Scope_C_LCD_COM_SEG            (* (reg8 *) Scope_C__LCD_COM_SEG)
/* Enable Segment LCD */
#define Scope_C_LCD_EN                 (* (reg8 *) Scope_C__LCD_EN)
/* Slew Rate Control */
#define Scope_C_SLW                    (* (reg8 *) Scope_C__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Scope_C_PRTDSI__CAPS_SEL       (* (reg8 *) Scope_C__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Scope_C_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Scope_C__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Scope_C_PRTDSI__OE_SEL0        (* (reg8 *) Scope_C__PRTDSI__OE_SEL0) 
#define Scope_C_PRTDSI__OE_SEL1        (* (reg8 *) Scope_C__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Scope_C_PRTDSI__OUT_SEL0       (* (reg8 *) Scope_C__PRTDSI__OUT_SEL0) 
#define Scope_C_PRTDSI__OUT_SEL1       (* (reg8 *) Scope_C__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Scope_C_PRTDSI__SYNC_OUT       (* (reg8 *) Scope_C__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Scope_C__SIO_CFG)
    #define Scope_C_SIO_HYST_EN        (* (reg8 *) Scope_C__SIO_HYST_EN)
    #define Scope_C_SIO_REG_HIFREQ     (* (reg8 *) Scope_C__SIO_REG_HIFREQ)
    #define Scope_C_SIO_CFG            (* (reg8 *) Scope_C__SIO_CFG)
    #define Scope_C_SIO_DIFF           (* (reg8 *) Scope_C__SIO_DIFF)
#endif /* (Scope_C__SIO_CFG) */

/* Interrupt Registers */
#if defined(Scope_C__INTSTAT)
    #define Scope_C_INTSTAT            (* (reg8 *) Scope_C__INTSTAT)
    #define Scope_C_SNAP               (* (reg8 *) Scope_C__SNAP)
    
	#define Scope_C_0_INTTYPE_REG 		(* (reg8 *) Scope_C__0__INTTYPE)
#endif /* (Scope_C__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Scope_C_H */


/* [] END OF FILE */
