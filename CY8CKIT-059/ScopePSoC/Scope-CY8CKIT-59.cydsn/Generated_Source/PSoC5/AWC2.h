/*******************************************************************************
* File Name: AWC2.h  
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

#if !defined(CY_PINS_AWC2_H) /* Pins AWC2_H */
#define CY_PINS_AWC2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "AWC2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 AWC2__PORT == 15 && ((AWC2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    AWC2_Write(uint8 value);
void    AWC2_SetDriveMode(uint8 mode);
uint8   AWC2_ReadDataReg(void);
uint8   AWC2_Read(void);
void    AWC2_SetInterruptMode(uint16 position, uint16 mode);
uint8   AWC2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the AWC2_SetDriveMode() function.
     *  @{
     */
        #define AWC2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define AWC2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define AWC2_DM_RES_UP          PIN_DM_RES_UP
        #define AWC2_DM_RES_DWN         PIN_DM_RES_DWN
        #define AWC2_DM_OD_LO           PIN_DM_OD_LO
        #define AWC2_DM_OD_HI           PIN_DM_OD_HI
        #define AWC2_DM_STRONG          PIN_DM_STRONG
        #define AWC2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define AWC2_MASK               AWC2__MASK
#define AWC2_SHIFT              AWC2__SHIFT
#define AWC2_WIDTH              1u

/* Interrupt constants */
#if defined(AWC2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AWC2_SetInterruptMode() function.
     *  @{
     */
        #define AWC2_INTR_NONE      (uint16)(0x0000u)
        #define AWC2_INTR_RISING    (uint16)(0x0001u)
        #define AWC2_INTR_FALLING   (uint16)(0x0002u)
        #define AWC2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define AWC2_INTR_MASK      (0x01u) 
#endif /* (AWC2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define AWC2_PS                     (* (reg8 *) AWC2__PS)
/* Data Register */
#define AWC2_DR                     (* (reg8 *) AWC2__DR)
/* Port Number */
#define AWC2_PRT_NUM                (* (reg8 *) AWC2__PRT) 
/* Connect to Analog Globals */                                                  
#define AWC2_AG                     (* (reg8 *) AWC2__AG)                       
/* Analog MUX bux enable */
#define AWC2_AMUX                   (* (reg8 *) AWC2__AMUX) 
/* Bidirectional Enable */                                                        
#define AWC2_BIE                    (* (reg8 *) AWC2__BIE)
/* Bit-mask for Aliased Register Access */
#define AWC2_BIT_MASK               (* (reg8 *) AWC2__BIT_MASK)
/* Bypass Enable */
#define AWC2_BYP                    (* (reg8 *) AWC2__BYP)
/* Port wide control signals */                                                   
#define AWC2_CTL                    (* (reg8 *) AWC2__CTL)
/* Drive Modes */
#define AWC2_DM0                    (* (reg8 *) AWC2__DM0) 
#define AWC2_DM1                    (* (reg8 *) AWC2__DM1)
#define AWC2_DM2                    (* (reg8 *) AWC2__DM2) 
/* Input Buffer Disable Override */
#define AWC2_INP_DIS                (* (reg8 *) AWC2__INP_DIS)
/* LCD Common or Segment Drive */
#define AWC2_LCD_COM_SEG            (* (reg8 *) AWC2__LCD_COM_SEG)
/* Enable Segment LCD */
#define AWC2_LCD_EN                 (* (reg8 *) AWC2__LCD_EN)
/* Slew Rate Control */
#define AWC2_SLW                    (* (reg8 *) AWC2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define AWC2_PRTDSI__CAPS_SEL       (* (reg8 *) AWC2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define AWC2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) AWC2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define AWC2_PRTDSI__OE_SEL0        (* (reg8 *) AWC2__PRTDSI__OE_SEL0) 
#define AWC2_PRTDSI__OE_SEL1        (* (reg8 *) AWC2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define AWC2_PRTDSI__OUT_SEL0       (* (reg8 *) AWC2__PRTDSI__OUT_SEL0) 
#define AWC2_PRTDSI__OUT_SEL1       (* (reg8 *) AWC2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define AWC2_PRTDSI__SYNC_OUT       (* (reg8 *) AWC2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(AWC2__SIO_CFG)
    #define AWC2_SIO_HYST_EN        (* (reg8 *) AWC2__SIO_HYST_EN)
    #define AWC2_SIO_REG_HIFREQ     (* (reg8 *) AWC2__SIO_REG_HIFREQ)
    #define AWC2_SIO_CFG            (* (reg8 *) AWC2__SIO_CFG)
    #define AWC2_SIO_DIFF           (* (reg8 *) AWC2__SIO_DIFF)
#endif /* (AWC2__SIO_CFG) */

/* Interrupt Registers */
#if defined(AWC2__INTSTAT)
    #define AWC2_INTSTAT            (* (reg8 *) AWC2__INTSTAT)
    #define AWC2_SNAP               (* (reg8 *) AWC2__SNAP)
    
	#define AWC2_0_INTTYPE_REG 		(* (reg8 *) AWC2__0__INTTYPE)
#endif /* (AWC2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_AWC2_H */


/* [] END OF FILE */
