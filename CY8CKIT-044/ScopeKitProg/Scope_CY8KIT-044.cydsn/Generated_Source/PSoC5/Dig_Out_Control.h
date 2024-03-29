/*******************************************************************************
* File Name: Dig_Out_Control.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_Dig_Out_Control_H) /* CY_CONTROL_REG_Dig_Out_Control_H */
#define CY_CONTROL_REG_Dig_Out_Control_H

#include "cyfitter.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} Dig_Out_Control_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    Dig_Out_Control_Write(uint8 control) ;
uint8   Dig_Out_Control_Read(void) ;

void Dig_Out_Control_SaveConfig(void) ;
void Dig_Out_Control_RestoreConfig(void) ;
void Dig_Out_Control_Sleep(void) ; 
void Dig_Out_Control_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define Dig_Out_Control_Control        (* (reg8 *) Dig_Out_Control_Sync_ctrl_reg__CONTROL_REG )
#define Dig_Out_Control_Control_PTR    (  (reg8 *) Dig_Out_Control_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_Dig_Out_Control_H */


/* [] END OF FILE */
