/*******************************************************************************
* File Name: WaveA_DAC.h  
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

#if !defined(CY_WaveDAC8_WaveA_DAC_H) 
#define CY_WaveDAC8_WaveA_DAC_H

#include "cytypes.h"
#include "cyfitter.h"
#include <WaveA_DAC_Wave1_DMA_dma.h>
#include <WaveA_DAC_Wave2_DMA_dma.h>
#include <WaveA_DAC_VDAC8.h>


/***************************************
*  Initial Parameter Constants
***************************************/

#define WaveA_DAC_WAVE1_TYPE     (0u)     /* Waveform for wave1 */
#define WaveA_DAC_WAVE2_TYPE     (2u)     /* Waveform for wave2 */
#define WaveA_DAC_SINE_WAVE      (0u)
#define WaveA_DAC_SQUARE_WAVE    (1u)
#define WaveA_DAC_TRIANGLE_WAVE  (2u)
#define WaveA_DAC_SAWTOOTH_WAVE  (3u)
#define WaveA_DAC_ARB_DRAW_WAVE  (10u) /* Arbitrary (draw) */
#define WaveA_DAC_ARB_FILE_WAVE  (11u) /* Arbitrary (from file) */

#define WaveA_DAC_WAVE1_LENGTH   (256u)   /* Length for wave1 */
#define WaveA_DAC_WAVE2_LENGTH   (50u)   /* Length for wave2 */
	
#define WaveA_DAC_DEFAULT_RANGE    (1u) /* Default DAC range */
#define WaveA_DAC_DAC_RANGE_1V     (0u)
#define WaveA_DAC_DAC_RANGE_1V_BUF (16u)
#define WaveA_DAC_DAC_RANGE_4V     (1u)
#define WaveA_DAC_DAC_RANGE_4V_BUF (17u)
#define WaveA_DAC_VOLT_MODE        (0u)
#define WaveA_DAC_CURRENT_MODE     (1u)
#define WaveA_DAC_DAC_MODE         (((WaveA_DAC_DEFAULT_RANGE == WaveA_DAC_DAC_RANGE_1V) || \
									  (WaveA_DAC_DEFAULT_RANGE == WaveA_DAC_DAC_RANGE_4V) || \
							  		  (WaveA_DAC_DEFAULT_RANGE == WaveA_DAC_DAC_RANGE_1V_BUF) || \
									  (WaveA_DAC_DEFAULT_RANGE == WaveA_DAC_DAC_RANGE_4V_BUF)) ? \
									   WaveA_DAC_VOLT_MODE : WaveA_DAC_CURRENT_MODE)

#define WaveA_DAC_DACMODE WaveA_DAC_DAC_MODE /* legacy definition for backward compatibility */

#define WaveA_DAC_DIRECT_MODE (0u)
#define WaveA_DAC_BUFFER_MODE (1u)
#define WaveA_DAC_OUT_MODE    (((WaveA_DAC_DEFAULT_RANGE == WaveA_DAC_DAC_RANGE_1V_BUF) || \
								 (WaveA_DAC_DEFAULT_RANGE == WaveA_DAC_DAC_RANGE_4V_BUF)) ? \
								  WaveA_DAC_BUFFER_MODE : WaveA_DAC_DIRECT_MODE)

#if(WaveA_DAC_OUT_MODE == WaveA_DAC_BUFFER_MODE)
    #include <WaveA_DAC_BuffAmp.h>
#endif /* WaveA_DAC_OUT_MODE == WaveA_DAC_BUFFER_MODE */

#define WaveA_DAC_CLOCK_INT      (1u)
#define WaveA_DAC_CLOCK_EXT      (0u)
#define WaveA_DAC_CLOCK_SRC      (0u)

#if(WaveA_DAC_CLOCK_SRC == WaveA_DAC_CLOCK_INT)  
	#include <WaveA_DAC_DacClk.h>
	#if defined(WaveA_DAC_DacClk_PHASE)
		#define WaveA_DAC_CLK_PHASE_0nS (1u)
	#endif /* defined(WaveA_DAC_DacClk_PHASE) */
#endif /* WaveA_DAC_CLOCK_SRC == WaveA_DAC_CLOCK_INT */

#if (CY_PSOC3)
	#define WaveA_DAC_HI16FLASHPTR   (0xFFu)
#endif /* CY_PSOC3 */

#define WaveA_DAC_Wave1_DMA_BYTES_PER_BURST      (1u)
#define WaveA_DAC_Wave1_DMA_REQUEST_PER_BURST    (1u)
#define WaveA_DAC_Wave2_DMA_BYTES_PER_BURST      (1u)
#define WaveA_DAC_Wave2_DMA_REQUEST_PER_BURST    (1u)


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
	uint8   enableState;
}WaveA_DAC_BACKUP_STRUCT;


/***************************************
*        Function Prototypes 
***************************************/

void WaveA_DAC_Start(void)             ;
void WaveA_DAC_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)
                                        ;
void WaveA_DAC_Init(void)              ;
void WaveA_DAC_Enable(void)            ;
void WaveA_DAC_Stop(void)              ;

void WaveA_DAC_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;
void WaveA_DAC_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;

void WaveA_DAC_Sleep(void)             ;
void WaveA_DAC_Wakeup(void)            ;

#define WaveA_DAC_SetSpeed       WaveA_DAC_VDAC8_SetSpeed
#define WaveA_DAC_SetRange       WaveA_DAC_VDAC8_SetRange
#define WaveA_DAC_SetValue       WaveA_DAC_VDAC8_SetValue
#define WaveA_DAC_DacTrim        WaveA_DAC_VDAC8_DacTrim
#define WaveA_DAC_SaveConfig     WaveA_DAC_VDAC8_SaveConfig
#define WaveA_DAC_RestoreConfig  WaveA_DAC_VDAC8_RestoreConfig


/***************************************
*    Variable with external linkage 
***************************************/

extern uint8 WaveA_DAC_initVar;

extern const uint8 CYCODE WaveA_DAC_wave1[WaveA_DAC_WAVE1_LENGTH];
extern const uint8 CYCODE WaveA_DAC_wave2[WaveA_DAC_WAVE2_LENGTH];


/***************************************
*            API Constants
***************************************/

/* SetRange constants */
#if(WaveA_DAC_DAC_MODE == WaveA_DAC_VOLT_MODE)
    #define WaveA_DAC_RANGE_1V       (0x00u)
    #define WaveA_DAC_RANGE_4V       (0x04u)
#else /* current mode */
    #define WaveA_DAC_RANGE_32uA     (0x00u)
    #define WaveA_DAC_RANGE_255uA    (0x04u)
    #define WaveA_DAC_RANGE_2mA      (0x08u)
    #define WaveA_DAC_RANGE_2048uA   WaveA_DAC_RANGE_2mA
#endif /* WaveA_DAC_DAC_MODE == WaveA_DAC_VOLT_MODE */

/* Power setting for SetSpeed API */
#define WaveA_DAC_LOWSPEED       (0x00u)
#define WaveA_DAC_HIGHSPEED      (0x02u)


/***************************************
*              Registers        
***************************************/

#define WaveA_DAC_DAC8__D WaveA_DAC_VDAC8_viDAC8__D


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE */
#define WaveA_DAC_HS_MASK        (0x02u)
#define WaveA_DAC_HS_LOWPOWER    (0x00u)
#define WaveA_DAC_HS_HIGHSPEED   (0x02u)

/* Bit Field  DAC_MODE */
#define WaveA_DAC_MODE_MASK      (0x10u)
#define WaveA_DAC_MODE_V         (0x00u)
#define WaveA_DAC_MODE_I         (0x10u)

/* Bit Field  DAC_RANGE */
#define WaveA_DAC_RANGE_MASK     (0x0Cu)
#define WaveA_DAC_RANGE_0        (0x00u)
#define WaveA_DAC_RANGE_1        (0x04u)
#define WaveA_DAC_RANGE_2        (0x08u)
#define WaveA_DAC_RANGE_3        (0x0Cu)
#define WaveA_DAC_IDIR_MASK      (0x04u)

#define WaveA_DAC_DAC_RANGE      ((uint8)(1u << 2u) & WaveA_DAC_RANGE_MASK)
#define WaveA_DAC_DAC_POL        ((uint8)(1u >> 1u) & WaveA_DAC_IDIR_MASK)


#endif /* CY_WaveDAC8_WaveA_DAC_H  */

/* [] END OF FILE */
