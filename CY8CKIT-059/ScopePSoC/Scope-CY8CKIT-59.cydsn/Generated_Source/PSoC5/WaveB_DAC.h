/*******************************************************************************
* File Name: WaveB_DAC.h  
* Version 2.10
*
* Description:
*  This file contains the function prototypes and constants used in
*  the 8-bit Waveform DAC (WaveDAC8) Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_WaveDAC8_WaveB_DAC_H) 
#define CY_WaveDAC8_WaveB_DAC_H

#include "cytypes.h"
#include "cyfitter.h"
#include <WaveB_DAC_Wave1_DMA_dma.h>
#include <WaveB_DAC_Wave2_DMA_dma.h>
#include <WaveB_DAC_VDAC8.h>


/***************************************
*  Initial Parameter Constants
***************************************/

#define WaveB_DAC_WAVE1_TYPE     (0u)     /* Waveform for wave1 */
#define WaveB_DAC_WAVE2_TYPE     (2u)     /* Waveform for wave2 */
#define WaveB_DAC_SINE_WAVE      (0u)
#define WaveB_DAC_SQUARE_WAVE    (1u)
#define WaveB_DAC_TRIANGLE_WAVE  (2u)
#define WaveB_DAC_SAWTOOTH_WAVE  (3u)
#define WaveB_DAC_ARB_DRAW_WAVE  (10u) /* Arbitrary (draw) */
#define WaveB_DAC_ARB_FILE_WAVE  (11u) /* Arbitrary (from file) */

#define WaveB_DAC_WAVE1_LENGTH   (256u)   /* Length for wave1 */
#define WaveB_DAC_WAVE2_LENGTH   (50u)   /* Length for wave2 */
	
#define WaveB_DAC_DEFAULT_RANGE    (1u) /* Default DAC range */
#define WaveB_DAC_DAC_RANGE_1V     (0u)
#define WaveB_DAC_DAC_RANGE_1V_BUF (16u)
#define WaveB_DAC_DAC_RANGE_4V     (1u)
#define WaveB_DAC_DAC_RANGE_4V_BUF (17u)
#define WaveB_DAC_VOLT_MODE        (0u)
#define WaveB_DAC_CURRENT_MODE     (1u)
#define WaveB_DAC_DAC_MODE         (((WaveB_DAC_DEFAULT_RANGE == WaveB_DAC_DAC_RANGE_1V) || \
									  (WaveB_DAC_DEFAULT_RANGE == WaveB_DAC_DAC_RANGE_4V) || \
							  		  (WaveB_DAC_DEFAULT_RANGE == WaveB_DAC_DAC_RANGE_1V_BUF) || \
									  (WaveB_DAC_DEFAULT_RANGE == WaveB_DAC_DAC_RANGE_4V_BUF)) ? \
									   WaveB_DAC_VOLT_MODE : WaveB_DAC_CURRENT_MODE)

#define WaveB_DAC_DACMODE WaveB_DAC_DAC_MODE /* legacy definition for backward compatibility */

#define WaveB_DAC_DIRECT_MODE (0u)
#define WaveB_DAC_BUFFER_MODE (1u)
#define WaveB_DAC_OUT_MODE    (((WaveB_DAC_DEFAULT_RANGE == WaveB_DAC_DAC_RANGE_1V_BUF) || \
								 (WaveB_DAC_DEFAULT_RANGE == WaveB_DAC_DAC_RANGE_4V_BUF)) ? \
								  WaveB_DAC_BUFFER_MODE : WaveB_DAC_DIRECT_MODE)

#if(WaveB_DAC_OUT_MODE == WaveB_DAC_BUFFER_MODE)
    #include <WaveB_DAC_BuffAmp.h>
#endif /* WaveB_DAC_OUT_MODE == WaveB_DAC_BUFFER_MODE */

#define WaveB_DAC_CLOCK_INT      (1u)
#define WaveB_DAC_CLOCK_EXT      (0u)
#define WaveB_DAC_CLOCK_SRC      (0u)

#if(WaveB_DAC_CLOCK_SRC == WaveB_DAC_CLOCK_INT)  
	#include <WaveB_DAC_DacClk.h>
	#if defined(WaveB_DAC_DacClk_PHASE)
		#define WaveB_DAC_CLK_PHASE_0nS (1u)
	#endif /* defined(WaveB_DAC_DacClk_PHASE) */
#endif /* WaveB_DAC_CLOCK_SRC == WaveB_DAC_CLOCK_INT */

#if (CY_PSOC3)
	#define WaveB_DAC_HI16FLASHPTR   (0xFFu)
#endif /* CY_PSOC3 */

#define WaveB_DAC_Wave1_DMA_BYTES_PER_BURST      (1u)
#define WaveB_DAC_Wave1_DMA_REQUEST_PER_BURST    (1u)
#define WaveB_DAC_Wave2_DMA_BYTES_PER_BURST      (1u)
#define WaveB_DAC_Wave2_DMA_REQUEST_PER_BURST    (1u)


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
	uint8   enableState;
}WaveB_DAC_BACKUP_STRUCT;


/***************************************
*        Function Prototypes 
***************************************/

void WaveB_DAC_Start(void)             ;
void WaveB_DAC_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)
                                        ;
void WaveB_DAC_Init(void)              ;
void WaveB_DAC_Enable(void)            ;
void WaveB_DAC_Stop(void)              ;

void WaveB_DAC_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;
void WaveB_DAC_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;

void WaveB_DAC_Sleep(void)             ;
void WaveB_DAC_Wakeup(void)            ;

#define WaveB_DAC_SetSpeed       WaveB_DAC_VDAC8_SetSpeed
#define WaveB_DAC_SetRange       WaveB_DAC_VDAC8_SetRange
#define WaveB_DAC_SetValue       WaveB_DAC_VDAC8_SetValue
#define WaveB_DAC_DacTrim        WaveB_DAC_VDAC8_DacTrim
#define WaveB_DAC_SaveConfig     WaveB_DAC_VDAC8_SaveConfig
#define WaveB_DAC_RestoreConfig  WaveB_DAC_VDAC8_RestoreConfig


/***************************************
*    Variable with external linkage 
***************************************/

extern uint8 WaveB_DAC_initVar;

extern const uint8 CYCODE WaveB_DAC_wave1[WaveB_DAC_WAVE1_LENGTH];
extern const uint8 CYCODE WaveB_DAC_wave2[WaveB_DAC_WAVE2_LENGTH];


/***************************************
*            API Constants
***************************************/

/* SetRange constants */
#if(WaveB_DAC_DAC_MODE == WaveB_DAC_VOLT_MODE)
    #define WaveB_DAC_RANGE_1V       (0x00u)
    #define WaveB_DAC_RANGE_4V       (0x04u)
#else /* current mode */
    #define WaveB_DAC_RANGE_32uA     (0x00u)
    #define WaveB_DAC_RANGE_255uA    (0x04u)
    #define WaveB_DAC_RANGE_2mA      (0x08u)
    #define WaveB_DAC_RANGE_2048uA   WaveB_DAC_RANGE_2mA
#endif /* WaveB_DAC_DAC_MODE == WaveB_DAC_VOLT_MODE */

/* Power setting for SetSpeed API */
#define WaveB_DAC_LOWSPEED       (0x00u)
#define WaveB_DAC_HIGHSPEED      (0x02u)


/***************************************
*              Registers        
***************************************/

#define WaveB_DAC_DAC8__D WaveB_DAC_VDAC8_viDAC8__D


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE */
#define WaveB_DAC_HS_MASK        (0x02u)
#define WaveB_DAC_HS_LOWPOWER    (0x00u)
#define WaveB_DAC_HS_HIGHSPEED   (0x02u)

/* Bit Field  DAC_MODE */
#define WaveB_DAC_MODE_MASK      (0x10u)
#define WaveB_DAC_MODE_V         (0x00u)
#define WaveB_DAC_MODE_I         (0x10u)

/* Bit Field  DAC_RANGE */
#define WaveB_DAC_RANGE_MASK     (0x0Cu)
#define WaveB_DAC_RANGE_0        (0x00u)
#define WaveB_DAC_RANGE_1        (0x04u)
#define WaveB_DAC_RANGE_2        (0x08u)
#define WaveB_DAC_RANGE_3        (0x0Cu)
#define WaveB_DAC_IDIR_MASK      (0x04u)

#define WaveB_DAC_DAC_RANGE      ((uint8)(1u << 2u) & WaveB_DAC_RANGE_MASK)
#define WaveB_DAC_DAC_POL        ((uint8)(1u >> 1u) & WaveB_DAC_IDIR_MASK)


#endif /* CY_WaveDAC8_WaveB_DAC_H  */

/* [] END OF FILE */
