/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
​ ​*​ ​@date​ :April 28, 2023
 * @file name : adc.c
 * @file_description: This file includes ADC initialization,
 * @Credits : Embedded_Systems_Fundamentals Book by Alexander Dean Chapter 6
 * 			  Kl25Z Reference manual
 *
*************************************************************************************************************************
*/
/*Include files*/
#include <stdio.h>
#include <stdlib.h>
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "adc.h"

#define MODE_10BIT         (2) //single ended 10 bit mode
#define CLK_DIV_RATIO_8    (3) //Clock divide by 8
/*
 * @Function
 *     This function Initializes ADC using Bare metal approach
 *
 * @Parametes: None
 * @Returns : None
 */
void Init_ADC(void)
{
	//Provide clock to ADC.
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

	//ADLPC - Low-Power Configuration : Disabled(normal Power config)
	//ADIV - Clock Divide Select :The divide ratio is 8 and the clock rate is (input clock)/8.
	//ADLSMP - Sample time configuration :Short sample time
	//MODE - single-ended 10-bit conversion
	//ADICLK - Input Clock Select :Bus clock
	ADC0->CFG1 = ADC_CFG1_ADLPC_MASK | ADC_CFG1_ADLSMP_MASK | ADC_CFG1_MODE(MODE_10BIT) | ADC_CFG1_ADIV(CLK_DIV_RATIO_8) | ADC_CFG1_ADICLK(0);

	// Software trigger, compare function disabled, DMA disabled, voltage references VREFH and VREFL
	ADC0->SC2 = ADC_SC2_REFSEL(0);
}
