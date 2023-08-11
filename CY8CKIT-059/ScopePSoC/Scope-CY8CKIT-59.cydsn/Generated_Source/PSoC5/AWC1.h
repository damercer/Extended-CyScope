/*******************************************************************************
* File Name: AWC1.h  
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

#if !defined(CY_PINS_AWC1_H) /* Pins AWC1_H */
#define CY_PINS_AWC1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "AWC1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 AWC1__PORT == 15 && ((AWC1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    AWC1_Write(uint8 value);
void    AWC1_SetDriveMode(uint8 mode);
uint8   AWC1_ReadDataReg(void);
uint8   AWC1_Read(void);
void    AWC1_SetInterruptMode(uint16 position, uint16 mode);
uint8   AWC1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the AWC1_SetDriveMode() function.
     *  @{
     */
        #define AWC1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define AWC1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define AWC1_DM_RES_UP          PIN_DM_RES_UP
        #define AWC1_DM_RES_DWN         PIN_DM_RES_DWN
        #define AWC1_DM_OD_LO           PIN_DM_OD_LO
        #define AWC1_DM_OD_HI           PIN_DM_OD_HI
        #define AWC1_DM_STRONG          PIN_DM_STRONG
        #define AWC1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define AWC1_MASK               AWC1__MASK
#define AWC1_SHIFT              AWC1__SHIFT
#define AWC1_WIDTH              1u

/* Interrupt constants */
#if defined(AWC1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AWC1_SetInterruptMode() function.
     *  @{
     */
        #define AWC1_INTR_NONE      (uint16)(0x0000u)
        #define AWC1_INTR_RISING    (uint16)(0x0001u)
        #define AWC1_INTR_FALLING   (uint16)(0x0002u)
        #define AWC1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define AWC1_INTR_MASK      (0x01u) 
#endif /* (AWC1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define AWC1_PS                     (* (reg8 *) AWC1__PS)
/* Data Register */
#define AWC1_DR                     (* (reg8 *) AWC1__DR)
/* Port Number */
#define AWC1_PRT_NUM                (* (reg8 *) AWC1__PRT) 
/* Connect to Analog Globals */                                                  
#define AWC1_AG                     (* (reg8 *) AWC1__AG)                       
/* Analog MUX bux enable */
#define AWC1_AMUX                   (* (reg8 *) AWC1__AMUX) 
/* Bidirectional Enable */                                                        
#define AWC1_BIE                    (* (reg8 *) AWC1__BIE)
/* Bit-mask for Aliased Register Access */
#define AWC1_BIT_MASK               (* (reg8 *) AWC1__BIT_MASK)
/* Bypass Enable */
#define AWC1_BYP                    (* (reg8 *) AWC1__BYP)
/* Port wide control signals */                                                   
#define AWC1_CTL                    (* (reg8 *) AWC1__CTL)
/* Drive Modes */
#define AWC1_DM0                    (* (reg8 *) AWC1__DM0) 
#define AWC1_DM1                    (* (reg8 *) AWC1__DM1)
#define AWC1_DM2                    (* (reg8 *) AWC1__DM2) 
/* Input Buffer Disable Override */
#define AWC1_INP_DIS                (* (reg8 *) AWC1__INP_DIS)
/* LCD Common or Segment Drive */
#define AWC1_LCD_COM_SEG            (* (reg8 *) AWC1__LCD_COM_SEG)
/* Enable Segment LCD */
#define AWC1_LCD_EN                 (* (reg8 *) AWC1__LCD_EN)
/* Slew Rate Control */
#define AWC1_SLW                    (* (reg8 *) AWC1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define AWC1_PRTDSI__CAPS_SEL       (* (reg8 *) AWC1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define AWC1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) AWC1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define AWC1_PRTDSI__OE_SEL0        (* (reg8 *) AWC1__PRTDSI__OE_SEL0) 
#define AWC1_PRTDSI__OE_SEL1        (* (reg8 *) AWC1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define AWC1_PRTDSI__OUT_SEL0       (* (reg8 *) AWC1__PRTDSI__OUT_SEL0) 
#define AWC1_PRTDSI__OUT_SEL1       (* (reg8 *) AWC1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define AWC1_PRTDSI__SYNC_OUT       (* (reg8 *) AWC1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(AWC1__SIO_CFG)
    #define AWC1_SIO_HYST_EN        (* (reg8 *) AWC1__SIO_HYST_EN)
    #define AWC1_SIO_REG_HIFREQ     (* (reg8 *) AWC1__SIO_REG_HIFREQ)
    #define AWC1_SIO_CFG            (* (reg8 *) AWC1__SIO_CFG)
    #define AWC1_SIO_DIFF           (* (reg8 *) AWC1__SIO_DIFF)
#endif /* (AWC1__SIO_CFG) */

/* Interrupt Registers */
#if defined(AWC1__INTSTAT)
    #define AWC1_INTSTAT            (* (reg8 *) AWC1__INTSTAT)
    #define AWC1_SNAP               (* (reg8 *) AWC1__SNAP)
    
	#define AWC1_0_INTTYPE_REG 		(* (reg8 *) AWC1__0__INTTYPE)
#endif /* (AWC1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_AWC1_H */


/* [] END OF FILE */
