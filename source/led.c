/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
 * @Credits : Referred Embedded_Systems_Fundamentals by Dean, chapter 2
​ ​*​ ​@date​ :April 28, 2023
 * @file name : led.c
 * @file_description: It consists of MKL25Z4.h a default header file of the KL25Z board and
 *                    stdio.h for printf usage. Along with I have included led.h.
 * This file includes LED Initialization, Blinking individual LEDs and turning off LEDs.
 *
 *
*************************************************************************************************************************
*/
/*Include files*/
#include <stdio.h>
#include <stdlib.h>
#include "clock_config.h"
#include "MKL25Z4.h"
#include "led.h"

#define RED_LED_PIN 18     //RED LED Port Pin number
#define GREEN_LED_PIN 19	//GREEN LED Port Pin number
#define BLUE_LED_PIN 1 		//BLUE LED Port Pin number
#define MASK(x) (1UL << (x))  // Masking bits

void led_OFF();
/*
 * @Function: Initializing the LED's by providing clock
 *           and configuring them as output pins.
 *
 * @Input parameters : None
 * @returns : None
 */
void led_init()
{
	//Enable clock to PORT B AND PORT D
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

	//select pin MUX mode to GPIO by setting the MUX field to PORTB_PCR18, PORTB_PCR_19 and PORTD_PCR_1 to 001
	//Make 3 pins GPIO
	PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(1);
	PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(1);
	PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(1);

	//Define appropriate port bits to be outputs. We will do this by setting bits 18 and 19 in Port
	//B’s PDDR register and bit 1 in Port D’s PDDR:
	PTB->PDDR |= MASK(RED_LED_PIN) | MASK(GREEN_LED_PIN);
	PTD->PDDR |= MASK(BLUE_LED_PIN);

	led_OFF();
}

/*
 * @Function
 * 	  This function turns BLUE LED ON
 *
 */
void led_BLUE_ON()
{

	PTD->PCOR |= MASK(BLUE_LED_PIN);
	PTB->PSOR |= MASK(RED_LED_PIN);
	PTB->PSOR |= MASK(GREEN_LED_PIN);

}
/*
 * @Function
 *     This function turns RED LED ON
 *
 */
void led_RED_ON()
{
	PTB->PCOR |= MASK(RED_LED_PIN);
	PTB->PSOR |= MASK(GREEN_LED_PIN);
	PTD->PSOR |= MASK(BLUE_LED_PIN);
}
/*
 * @Function
 * This function turns GREEN LED ON
 *
 */
void led_GREEN_ON()
{
	PTB->PSOR |= MASK(RED_LED_PIN);
	PTB->PCOR |= MASK(GREEN_LED_PIN);
	PTD->PSOR |= MASK(BLUE_LED_PIN);
}
/*
 * @Function
 *     This function turns OFF LED
 *
 */
void led_OFF()
{
	PTB->PSOR |= MASK(RED_LED_PIN);
	PTB->PSOR |= MASK(GREEN_LED_PIN);
	PTD->PSOR |= MASK(BLUE_LED_PIN);
}
