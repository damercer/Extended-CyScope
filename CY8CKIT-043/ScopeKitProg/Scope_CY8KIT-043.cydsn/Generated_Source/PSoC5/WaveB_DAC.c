/*******************************************************************************
* File Name: WaveB_DAC.c
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

#include "WaveB_DAC.h"

uint8  WaveB_DAC_initVar = 0u;

const uint8 CYCODE WaveB_DAC_wave1[WaveB_DAC_WAVE1_LENGTH] = { 128u,129u,131u,132u,134u,135u,137u,138u,140u,141u,143u,144u,146u,147u,149u,150u,152u,153u,155u,156u,158u,159u,161u,162u,164u,165u,167u,168u,170u,171u,172u,174u,175u,177u,178u,180u,181u,182u,184u,185u,186u,188u,189u,190u,192u,193u,194u,196u,197u,198u,199u,201u,202u,203u,204u,206u,207u,208u,209u,210u,211u,213u,214u,215u,216u,217u,218u,219u,220u,221u,222u,223u,224u,225u,226u,227u,228u,229u,230u,231u,231u,232u,233u,234u,235u,235u,236u,237u,238u,238u,239u,240u,240u,241u,242u,242u,243u,244u,244u,245u,245u,246u,246u,247u,247u,248u,248u,248u,249u,249u,249u,250u,250u,250u,251u,251u,251u,251u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,251u,251u,251u,251u,250u,250u,250u,249u,249u,249u,248u,248u,248u,247u,247u,246u,246u,245u,245u,244u,244u,243u,242u,242u,241u,240u,240u,239u,238u,238u,237u,236u,235u,235u,234u,233u,232u,231u,231u,230u,229u,228u,227u,226u,225u,224u,223u,222u,221u,220u,219u,218u,217u,216u,215u,214u,213u,211u,210u,209u,208u,207u,206u,204u,203u,202u,201u,199u,198u,197u,196u,194u,193u,192u,190u,189u,188u,186u,185u,184u,182u,181u,180u,178u,177u,175u,174u,172u,171u,170u,168u,167u,165u,164u,162u,161u,159u,158u,156u,155u,153u,152u,150u,149u,147u,146u,144u,143u,141u,140u,138u,137u,135u,134u,132u,131u,129u,128u,126u,124u,123u,121u,120u,118u,117u,115u,114u,112u,111u,109u,108u,106u,105u,103u,102u,100u,99u,97u,96u,94u,93u,91u,90u,88u,87u,85u,84u,83u,81u,80u,78u,77u,75u,74u,73u,71u,70u,69u,67u,66u,65u,63u,62u,61u,59u,58u,57u,56u,54u,53u,52u,51u,49u,48u,47u,46u,45u,44u,42u,41u,40u,39u,38u,37u,36u,35u,34u,33u,32u,31u,30u,29u,28u,27u,26u,25u,24u,24u,23u,22u,21u,20u,20u,19u,18u,17u,17u,16u,15u,15u,14u,13u,13u,12u,11u,11u,10u,10u,9u,9u,8u,8u,7u,7u,7u,6u,6u,6u,5u,5u,5u,4u,4u,4u,4u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,4u,4u,4u,4u,5u,5u,5u,6u,6u,6u,7u,7u,7u,8u,8u,9u,9u,10u,10u,11u,11u,12u,13u,13u,14u,15u,15u,16u,17u,17u,18u,19u,20u,20u,21u,22u,23u,24u,24u,25u,26u,27u,28u,29u,30u,31u,32u,33u,34u,35u,36u,37u,38u,39u,40u,41u,42u,44u,45u,46u,47u,48u,49u,51u,52u,53u,54u,56u,57u,58u,59u,61u,62u,63u,65u,66u,67u,69u,70u,71u,73u,74u,75u,77u,78u,80u,81u,83u,84u,85u,87u,88u,90u,91u,93u,94u,96u,97u,99u,100u,102u,103u,105u,106u,108u,109u,111u,112u,114u,115u,117u,118u,120u,121u,123u,124u,126u };
const uint8 CYCODE WaveB_DAC_wave2[WaveB_DAC_WAVE2_LENGTH] = { 128u,132u,138u,143u,148u,152u,158u,162u,168u,172u,178u,182u,188u,192u,198u,202u,208u,213u,218u,222u,228u,232u,238u,242u,248u,252u,248u,242u,238u,232u,228u,222u,218u,212u,208u,202u,198u,192u,188u,182u,178u,173u,168u,162u,158u,152u,148u,143u,138u,132u,128u,122u,118u,112u,107u,102u,97u,93u,88u,83u,78u,73u,68u,62u,57u,52u,47u,42u,37u,33u,28u,23u,18u,13u,8u,3u,8u,13u,18u,23u,28u,33u,37u,42u,47u,52u,57u,62u,68u,73u,78u,83u,88u,93u,97u,102u,107u,112u,118u,122u };

static uint8  WaveB_DAC_Wave1Chan;
static uint8  WaveB_DAC_Wave2Chan;
static uint8  WaveB_DAC_Wave1TD;
static uint8  WaveB_DAC_Wave2TD;


/*******************************************************************************
* Function Name: WaveB_DAC_Init
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
void WaveB_DAC_Init(void) 
{
	WaveB_DAC_VDAC8_Init();
	WaveB_DAC_VDAC8_SetSpeed(WaveB_DAC_HIGHSPEED);
	WaveB_DAC_VDAC8_SetRange(WaveB_DAC_DAC_RANGE);

	#if(WaveB_DAC_DAC_MODE == WaveB_DAC_CURRENT_MODE)
		WaveB_DAC_IDAC8_SetPolarity(WaveB_DAC_DAC_POL);
	#endif /* WaveB_DAC_DAC_MODE == WaveB_DAC_CURRENT_MODE */

	#if(WaveB_DAC_OUT_MODE == WaveB_DAC_BUFFER_MODE)
	   WaveB_DAC_BuffAmp_Init();
	#endif /* WaveB_DAC_OUT_MODE == WaveB_DAC_BUFFER_MODE */

	/* Get the TD Number for the DMA channel 1 and 2   */
	WaveB_DAC_Wave1TD = CyDmaTdAllocate();
	WaveB_DAC_Wave2TD = CyDmaTdAllocate();
	
	/* Initialize waveform pointers  */
	WaveB_DAC_Wave1Setup(WaveB_DAC_wave1, WaveB_DAC_WAVE1_LENGTH) ;
	WaveB_DAC_Wave2Setup(WaveB_DAC_wave2, WaveB_DAC_WAVE2_LENGTH) ;
	
	/* Initialize the internal clock if one present  */
	#if defined(WaveB_DAC_DacClk_PHASE)
	   WaveB_DAC_DacClk_SetPhase(WaveB_DAC_CLK_PHASE_0nS);
	#endif /* defined(WaveB_DAC_DacClk_PHASE) */
}


/*******************************************************************************
* Function Name: WaveB_DAC_Enable
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
void WaveB_DAC_Enable(void) 
{
	WaveB_DAC_VDAC8_Enable();

	#if(WaveB_DAC_OUT_MODE == WaveB_DAC_BUFFER_MODE)
	   WaveB_DAC_BuffAmp_Enable();
	#endif /* WaveB_DAC_OUT_MODE == WaveB_DAC_BUFFER_MODE */

	/* 
	* Enable the channel. It is configured to remember the TD value so that
	* it can be restored from the place where it has been stopped.
	*/
	(void)CyDmaChEnable(WaveB_DAC_Wave1Chan, 1u);
	(void)CyDmaChEnable(WaveB_DAC_Wave2Chan, 1u);
	
	/* set the initial value */
	WaveB_DAC_SetValue(0u);
	
	#if(WaveB_DAC_CLOCK_SRC == WaveB_DAC_CLOCK_INT)  	
	   WaveB_DAC_DacClk_Start();
	#endif /* WaveB_DAC_CLOCK_SRC == WaveB_DAC_CLOCK_INT */
}


/*******************************************************************************
* Function Name: WaveB_DAC_Start
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
void WaveB_DAC_Start(void) 
{
	/* If not Initialized then initialize all required hardware and software */
	if(WaveB_DAC_initVar == 0u)
	{
		WaveB_DAC_Init();
		WaveB_DAC_initVar = 1u;
	}
	
	WaveB_DAC_Enable();
}


/*******************************************************************************
* Function Name: WaveB_DAC_StartEx
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
void WaveB_DAC_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)

{
	WaveB_DAC_Wave1Setup(wavePtr1, sampleSize1);
	WaveB_DAC_Wave2Setup(wavePtr2, sampleSize2);
	WaveB_DAC_Start();
}


/*******************************************************************************
* Function Name: WaveB_DAC_Stop
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
void WaveB_DAC_Stop(void) 
{
	/* Turn off internal clock, if one present */
	#if(WaveB_DAC_CLOCK_SRC == WaveB_DAC_CLOCK_INT)  	
	   WaveB_DAC_DacClk_Stop();
	#endif /* WaveB_DAC_CLOCK_SRC == WaveB_DAC_CLOCK_INT */
	
	/* Disble DMA channels */
	(void)CyDmaChDisable(WaveB_DAC_Wave1Chan);
	(void)CyDmaChDisable(WaveB_DAC_Wave2Chan);

	/* Disable power to DAC */
	WaveB_DAC_VDAC8_Stop();
}


/*******************************************************************************
* Function Name: WaveB_DAC_Wave1Setup
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
void WaveB_DAC_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)

{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (WaveB_DAC_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
		
		WaveB_DAC_Wave1Chan = WaveB_DAC_Wave1_DMA_DmaInitialize(
		WaveB_DAC_Wave1_DMA_BYTES_PER_BURST, WaveB_DAC_Wave1_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		WaveB_DAC_Wave1Chan = WaveB_DAC_Wave1_DMA_DmaInitialize(
		WaveB_DAC_Wave1_DMA_BYTES_PER_BURST, WaveB_DAC_Wave1_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(WaveB_DAC_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
    * Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(WaveB_DAC_Wave1TD, sampleSize, WaveB_DAC_Wave1TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)WaveB_DAC_Wave1_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(WaveB_DAC_Wave1TD, LO16((uint32)wavePtr), LO16(WaveB_DAC_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(WaveB_DAC_Wave1Chan, WaveB_DAC_Wave1TD);
}


/*******************************************************************************
* Function Name: WaveB_DAC_Wave2Setup
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
void WaveB_DAC_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
 
{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (WaveB_DAC_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
			
		WaveB_DAC_Wave2Chan = WaveB_DAC_Wave2_DMA_DmaInitialize(
		WaveB_DAC_Wave2_DMA_BYTES_PER_BURST, WaveB_DAC_Wave2_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		WaveB_DAC_Wave2Chan = WaveB_DAC_Wave2_DMA_DmaInitialize(
		WaveB_DAC_Wave2_DMA_BYTES_PER_BURST, WaveB_DAC_Wave2_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(WaveB_DAC_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
	* Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(WaveB_DAC_Wave2TD, sampleSize, WaveB_DAC_Wave2TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)WaveB_DAC_Wave2_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(WaveB_DAC_Wave2TD, LO16((uint32)wavePtr), LO16(WaveB_DAC_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(WaveB_DAC_Wave2Chan, WaveB_DAC_Wave2TD);
}


/* [] END OF FILE */
