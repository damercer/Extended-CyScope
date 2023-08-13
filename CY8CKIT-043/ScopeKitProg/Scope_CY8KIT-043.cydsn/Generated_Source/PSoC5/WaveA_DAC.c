/*******************************************************************************
* File Name: WaveA_DAC.c
* Version 2.10
*
* Description:
*  This file provides the source code for the 8-bit Waveform DAC 
*  (WaveDAC8) Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "WaveA_DAC.h"

uint8  WaveA_DAC_initVar = 0u;

const uint8 CYCODE WaveA_DAC_wave1[WaveA_DAC_WAVE1_LENGTH] = { 128u,128u,128u,129u,129u,129u,130u,130u,131u,131u,131u,132u,132u,132u,133u,133u,134u,134u,134u,135u,135u,135u,136u,136u,137u,137u,137u,138u,138u,138u,139u,139u,139u,140u,140u,141u,141u,141u,142u,142u,142u,143u,143u,143u,144u,144u,144u,145u,145u,145u,145u,146u,146u,146u,147u,147u,147u,148u,148u,148u,148u,149u,149u,149u,150u,150u,150u,150u,151u,151u,151u,151u,152u,152u,152u,152u,153u,153u,153u,153u,153u,154u,154u,154u,154u,154u,155u,155u,155u,155u,155u,156u,156u,156u,156u,156u,156u,157u,157u,157u,157u,157u,157u,157u,157u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,159u,159u,159u,159u,159u,159u,159u,159u,159u,159u,159u,159u,159u,159u,159u,159u,159u,159u,159u,159u,159u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,157u,157u,157u,157u,157u,157u,157u,157u,156u,156u,156u,156u,156u,156u,155u,155u,155u,155u,155u,154u,154u,154u,154u,154u,153u,153u,153u,153u,153u,152u,152u,152u,152u,151u,151u,151u,151u,150u,150u,150u,150u,149u,149u,149u,148u,148u,148u,148u,147u,147u,147u,146u,146u,146u,145u,145u,145u,145u,144u,144u,144u,143u,143u,143u,142u,142u,142u,141u,141u,141u,140u,140u,139u,139u,139u,138u,138u,138u,137u,137u,137u,136u,136u,135u,135u,135u,134u,134u,134u,133u,133u,132u,132u,132u,131u,131u,131u,130u,130u,129u,129u,129u,128u,128u,128u,127u,127u,126u,126u,126u,125u,125u,124u,124u,124u,123u,123u,123u,122u,122u,121u,121u,121u,120u,120u,120u,119u,119u,118u,118u,118u,117u,117u,117u,116u,116u,116u,115u,115u,114u,114u,114u,113u,113u,113u,112u,112u,112u,111u,111u,111u,110u,110u,110u,110u,109u,109u,109u,108u,108u,108u,107u,107u,107u,107u,106u,106u,106u,105u,105u,105u,105u,104u,104u,104u,104u,103u,103u,103u,103u,102u,102u,102u,102u,102u,101u,101u,101u,101u,101u,100u,100u,100u,100u,100u,99u,99u,99u,99u,99u,99u,98u,98u,98u,98u,98u,98u,98u,98u,97u,97u,97u,97u,97u,97u,97u,97u,97u,97u,97u,97u,97u,96u,96u,96u,96u,96u,96u,96u,96u,96u,96u,96u,96u,96u,96u,96u,96u,96u,96u,96u,96u,96u,97u,97u,97u,97u,97u,97u,97u,97u,97u,97u,97u,97u,97u,98u,98u,98u,98u,98u,98u,98u,98u,99u,99u,99u,99u,99u,99u,100u,100u,100u,100u,100u,101u,101u,101u,101u,101u,102u,102u,102u,102u,102u,103u,103u,103u,103u,104u,104u,104u,104u,105u,105u,105u,105u,106u,106u,106u,107u,107u,107u,107u,108u,108u,108u,109u,109u,109u,110u,110u,110u,110u,111u,111u,111u,112u,112u,112u,113u,113u,113u,114u,114u,114u,115u,115u,116u,116u,116u,117u,117u,117u,118u,118u,118u,119u,119u,120u,120u,120u,121u,121u,121u,122u,122u,123u,123u,123u,124u,124u,124u,125u,125u,126u,126u,126u,127u,127u };
const uint8 CYCODE WaveA_DAC_wave2[WaveA_DAC_WAVE2_LENGTH] = {  32,35,37,40,42,45,47,50,52,55,58,60,63,63,60,58,55,52,50,47,45,42,40,37,35,32,29,27,24,22,19,17,14,12,9,6,4,1,1,4,6,9,12,14,17,19,22,24,27,29 };

static uint8  WaveA_DAC_Wave1Chan;
static uint8  WaveA_DAC_Wave2Chan;
static uint8  WaveA_DAC_Wave1TD;
static uint8  WaveA_DAC_Wave2TD;


/*******************************************************************************
* Function Name: WaveA_DAC_Init
********************************************************************************
*
* Summary:
*  Initializes component with parameters set in the customizer.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void WaveA_DAC_Init(void) 
{
	WaveA_DAC_VDAC8_Init();
	WaveA_DAC_VDAC8_SetSpeed(WaveA_DAC_HIGHSPEED);
	WaveA_DAC_VDAC8_SetRange(WaveA_DAC_DAC_RANGE);

	#if(WaveA_DAC_DAC_MODE == WaveA_DAC_CURRENT_MODE)
		WaveA_DAC_IDAC8_SetPolarity(WaveA_DAC_DAC_POL);
	#endif /* WaveA_DAC_DAC_MODE == WaveA_DAC_CURRENT_MODE */

	#if(WaveA_DAC_OUT_MODE == WaveA_DAC_BUFFER_MODE)
	   WaveA_DAC_BuffAmp_Init();
	#endif /* WaveA_DAC_OUT_MODE == WaveA_DAC_BUFFER_MODE */

	/* Get the TD Number for the DMA channel 1 and 2   */
	WaveA_DAC_Wave1TD = CyDmaTdAllocate();
	WaveA_DAC_Wave2TD = CyDmaTdAllocate();
	
	/* Initialize waveform pointers  */
	WaveA_DAC_Wave1Setup(WaveA_DAC_wave1, WaveA_DAC_WAVE1_LENGTH) ;
	WaveA_DAC_Wave2Setup(WaveA_DAC_wave2, WaveA_DAC_WAVE2_LENGTH) ;
	
	/* Initialize the internal clock if one present  */
	#if defined(WaveA_DAC_DacClk_PHASE)
	   WaveA_DAC_DacClk_SetPhase(WaveA_DAC_CLK_PHASE_0nS);
	#endif /* defined(WaveA_DAC_DacClk_PHASE) */
}


/*******************************************************************************
* Function Name: WaveA_DAC_Enable
********************************************************************************
*  
* Summary: 
*  Enables the DAC block and DMA operation.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void WaveA_DAC_Enable(void) 
{
	WaveA_DAC_VDAC8_Enable();

	#if(WaveA_DAC_OUT_MODE == WaveA_DAC_BUFFER_MODE)
	   WaveA_DAC_BuffAmp_Enable();
	#endif /* WaveA_DAC_OUT_MODE == WaveA_DAC_BUFFER_MODE */

	/* 
	* Enable the channel. It is configured to remember the TD value so that
	* it can be restored from the place where it has been stopped.
	*/
	(void)CyDmaChEnable(WaveA_DAC_Wave1Chan, 1u);
	(void)CyDmaChEnable(WaveA_DAC_Wave2Chan, 1u);
	
	/* set the initial value */
	WaveA_DAC_SetValue(0u);
	
	#if(WaveA_DAC_CLOCK_SRC == WaveA_DAC_CLOCK_INT)  	
	   WaveA_DAC_DacClk_Start();
	#endif /* WaveA_DAC_CLOCK_SRC == WaveA_DAC_CLOCK_INT */
}


/*******************************************************************************
* Function Name: WaveA_DAC_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as 
*  executing the stop function.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void WaveA_DAC_Start(void) 
{
	/* If not Initialized then initialize all required hardware and software */
	if(WaveA_DAC_initVar == 0u)
	{
		WaveA_DAC_Init();
		WaveA_DAC_initVar = 1u;
	}
	
	WaveA_DAC_Enable();
}


/*******************************************************************************
* Function Name: WaveA_DAC_StartEx
********************************************************************************
*
* Summary:
*  The StartEx function sets pointers and sizes for both waveforms
*  and then starts the component.
*
* Parameters:  
*   uint8 * wavePtr1:     Pointer to the waveform 1 array.
*   uint16  sampleSize1:  The amount of samples in the waveform 1.
*   uint8 * wavePtr2:     Pointer to the waveform 2 array.
*   uint16  sampleSize2:  The amount of samples in the waveform 2.
*
* Return: 
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void WaveA_DAC_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)

{
	WaveA_DAC_Wave1Setup(wavePtr1, sampleSize1);
	WaveA_DAC_Wave2Setup(wavePtr2, sampleSize2);
	WaveA_DAC_Start();
}


/*******************************************************************************
* Function Name: WaveA_DAC_Stop
********************************************************************************
*
* Summary:
*  Stops the clock (if internal), disables the DMA channels
*  and powers down the DAC.
*
* Parameters:  
*  None  
*
* Return: 
*  None
*
*******************************************************************************/
void WaveA_DAC_Stop(void) 
{
	/* Turn off internal clock, if one present */
	#if(WaveA_DAC_CLOCK_SRC == WaveA_DAC_CLOCK_INT)  	
	   WaveA_DAC_DacClk_Stop();
	#endif /* WaveA_DAC_CLOCK_SRC == WaveA_DAC_CLOCK_INT */
	
	/* Disble DMA channels */
	(void)CyDmaChDisable(WaveA_DAC_Wave1Chan);
	(void)CyDmaChDisable(WaveA_DAC_Wave2Chan);

	/* Disable power to DAC */
	WaveA_DAC_VDAC8_Stop();
}


/*******************************************************************************
* Function Name: WaveA_DAC_Wave1Setup
********************************************************************************
*
* Summary:
*  Sets pointer and size for waveform 1.                                    
*
* Parameters:  
*  uint8 * WavePtr:     Pointer to the waveform array.
*  uint16  SampleSize:  The amount of samples in the waveform.
*
* Return: 
*  None 
*
*******************************************************************************/
void WaveA_DAC_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)

{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (WaveA_DAC_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
		
		WaveA_DAC_Wave1Chan = WaveA_DAC_Wave1_DMA_DmaInitialize(
		WaveA_DAC_Wave1_DMA_BYTES_PER_BURST, WaveA_DAC_Wave1_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		WaveA_DAC_Wave1Chan = WaveA_DAC_Wave1_DMA_DmaInitialize(
		WaveA_DAC_Wave1_DMA_BYTES_PER_BURST, WaveA_DAC_Wave1_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(WaveA_DAC_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
    * Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(WaveA_DAC_Wave1TD, sampleSize, WaveA_DAC_Wave1TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)WaveA_DAC_Wave1_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(WaveA_DAC_Wave1TD, LO16((uint32)wavePtr), LO16(WaveA_DAC_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(WaveA_DAC_Wave1Chan, WaveA_DAC_Wave1TD);
}


/*******************************************************************************
* Function Name: WaveA_DAC_Wave2Setup
********************************************************************************
*
* Summary:
*  Sets pointer and size for waveform 2.                                    
*
* Parameters:  
*  uint8 * WavePtr:     Pointer to the waveform array.
*  uint16  SampleSize:  The amount of samples in the waveform.
*
* Return: 
*  None
*
*******************************************************************************/
void WaveA_DAC_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
 
{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (WaveA_DAC_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
			
		WaveA_DAC_Wave2Chan = WaveA_DAC_Wave2_DMA_DmaInitialize(
		WaveA_DAC_Wave2_DMA_BYTES_PER_BURST, WaveA_DAC_Wave2_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		WaveA_DAC_Wave2Chan = WaveA_DAC_Wave2_DMA_DmaInitialize(
		WaveA_DAC_Wave2_DMA_BYTES_PER_BURST, WaveA_DAC_Wave2_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(WaveA_DAC_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
	* Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(WaveA_DAC_Wave2TD, sampleSize, WaveA_DAC_Wave2TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)WaveA_DAC_Wave2_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(WaveA_DAC_Wave2TD, LO16((uint32)wavePtr), LO16(WaveA_DAC_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(WaveA_DAC_Wave2Chan, WaveA_DAC_Wave2TD);
}


/* [] END OF FILE */
