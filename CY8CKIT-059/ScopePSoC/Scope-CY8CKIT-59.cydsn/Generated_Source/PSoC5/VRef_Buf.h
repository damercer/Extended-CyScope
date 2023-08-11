/*******************************************************************************
* File Name: VRef_Buf.h  
* Version 1.90
*
* Description:
*  This file contains the function prototypes and constants used in
*  the OpAmp (Analog Buffer) Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_OPAMP_VRef_Buf_H) 
#define CY_OPAMP_VRef_Buf_H 

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component OpAmp_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
    uint8   enableState;
}   VRef_Buf_BACKUP_STRUCT;

/* Variable describes initial state of the component */
extern uint8 VRef_Buf_initVar;


/**************************************
*        Function Prototypes 
**************************************/

void VRef_Buf_Start(void)               ;
void VRef_Buf_Stop(void)                ;
void VRef_Buf_SetPower(uint8 power)     ;
void VRef_Buf_Sleep(void)               ;
void VRef_Buf_Wakeup(void)              ;
void VRef_Buf_SaveConfig(void)          ;
void VRef_Buf_RestoreConfig(void)       ;
void VRef_Buf_Init(void)                ;
void VRef_Buf_Enable(void)              ;


/**************************************
*           API Constants
**************************************/

/* Power constants for SetPower() function */
#define VRef_Buf_LPOCPOWER              (0x00u)
#define VRef_Buf_LOWPOWER               (0x01u)
#define VRef_Buf_MEDPOWER               (0x02u)
#define VRef_Buf_HIGHPOWER              (0x03u)


/**************************************
*           Parameter Defaults        
**************************************/
#define VRef_Buf_DEFAULT_POWER          (3u)
#define VRef_Buf_DEFAULT_MODE           (1u)


/**************************************
*             Registers
**************************************/

#define VRef_Buf_CR_REG                 (* (reg8 *) VRef_Buf_ABuf__CR)
#define VRef_Buf_CR_PTR                 (  (reg8 *) VRef_Buf_ABuf__CR)

#define VRef_Buf_MX_REG                 (* (reg8 *) VRef_Buf_ABuf__MX)
#define VRef_Buf_MX_PTR                 (  (reg8 *) VRef_Buf_ABuf__MX)

#define VRef_Buf_SW_REG                 (* (reg8 *) VRef_Buf_ABuf__SW)
#define VRef_Buf_SW_PTR                 (  (reg8 *) VRef_Buf_ABuf__SW)

/* Active mode power manager register */
#define VRef_Buf_PM_ACT_CFG_REG         (* (reg8 *) VRef_Buf_ABuf__PM_ACT_CFG)
#define VRef_Buf_PM_ACT_CFG_PTR         (  (reg8 *) VRef_Buf_ABuf__PM_ACT_CFG)

/* Alternative mode power manager register */
#define VRef_Buf_PM_STBY_CFG_REG        (* (reg8 *) VRef_Buf_ABuf__PM_STBY_CFG)
#define VRef_Buf_PM_STBY_CFG_PTR        (  (reg8 *) VRef_Buf_ABuf__PM_STBY_CFG)

/* ANIF.PUMP.CR1 Pump Configuration Register 1 */
#define VRef_Buf_PUMP_CR1_REG           (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)
#define VRef_Buf_PUMP_CR1_PTR           (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)

/* Trim register defines */
#define VRef_Buf_TR0_REG                (* (reg8 *) VRef_Buf_ABuf__TR0)
#define VRef_Buf_TR0_PTR                (  (reg8 *) VRef_Buf_ABuf__TR0)

#define VRef_Buf_TR1_REG                (* (reg8 *) VRef_Buf_ABuf__TR1)
#define VRef_Buf_TR1_PTR                (  (reg8 *) VRef_Buf_ABuf__TR1)


/**************************************
*       Register Constants
**************************************/

/* CX Analog Buffer Input Selection Register */

/* Power mode defines */

/* PM_ACT_CFG (Active Power Mode CFG Register) mask */ 
#define VRef_Buf_ACT_PWR_EN             VRef_Buf_ABuf__PM_ACT_MSK 
/* PM_STBY_CFG (Alternative Active Power Mode CFG Register) mask */ 
#define VRef_Buf_STBY_PWR_EN            VRef_Buf_ABuf__PM_STBY_MSK 
/* Power mask */
#define VRef_Buf_PWR_MASK               (0x03u)

/* MX Analog Buffer Input Selection Register */

/* Bit Field  MX_VN */
#define VRef_Buf_MX_VN_MASK             (0x30u)
#define VRef_Buf_MX_VN_NC               (0x00u)
#define VRef_Buf_MX_VN_AG4              (0x10u)
#define VRef_Buf_MX_VN_AG6              (0x20u)

/* Bit Field  MX_VP */
#define VRef_Buf_MX_VP_MASK             (0x0Fu)
#define VRef_Buf_MX_VP_NC               (0x00u)
#define VRef_Buf_MX_VP_VREF             (0x09u)
#define VRef_Buf_MX_VP_AG4              (0x01u)
#define VRef_Buf_MX_VP_AG5              (0x02u)
#define VRef_Buf_MX_VP_AG6              (0x03u)
#define VRef_Buf_MX_VP_AG7              (0x04u)
#define VRef_Buf_MX_VP_ABUS0            (0x05u)
#define VRef_Buf_MX_VP_ABUS1            (0x06u)
#define VRef_Buf_MX_VP_ABUS2            (0x07u)
#define VRef_Buf_MX_VP_ABUS3            (0x08u)

/* SW Analog Buffer Routing Switch Reg */

/* Bit Field  SW */
#define VRef_Buf_SW_MASK                (0x07u) 
#define VRef_Buf_SW_SWINP               (0x04u)  /* Enable positive input */
#define VRef_Buf_SW_SWINN               (0x02u)  /* Enable negative input */

/* Pump configuration register masks */
#define VRef_Buf_PUMP_CR1_CLKSEL        (0x40u)
#define VRef_Buf_PUMP_CR1_FORCE         (0x20u)
#define VRef_Buf_PUMP_CR1_AUTO          (0x10u)

#endif /* CY_OPAMP_VRef_Buf_H */


/* [] END OF FILE */
