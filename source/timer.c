/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
​ ​*​ ​@date​ :April 28, 2023
 * @file name : timer.c
 * @file_description: It consists of MKL25Z4.h a default header file of the KL25Z board.
 *                     Along with I have included core_cm0plus.h which includes systick prototypes,
 *                     whose function prototypes are being used in this file.
 * 					   This file includes SysTick Initialization for Timer Interrupt
 * @Credits : Embedded System Fundamentals with ARM cortex Microcontrollers Book by Alexander Dean chapter 7
 *
*************************************************************************************************************************
*/
#include "MKL25Z4.h"
#include <stdio.h>
#include "core_cm0plus.h"


#define EXTERNAL_CLK_FREQ 3000000L // Internal clock freq of 48MHz / 16
#define TIMER_DIV_FACTOR  1000  // for 1ms delay
typedef uint32_t ticktime_t;  // time since boot, in sixteenths of a second

ticktime_t timer_global; //System time variable
ticktime_t timer_local; // get timer local variable

/*
 * @Function
 *     This function initializes SysTick module
 * @credits: Alexander Dean Book
 * @Parametes: None
 * @Returns : None
 */


void Init_SysTick(void)
{
	// Using 3MHz External clock

	SysTick->LOAD = ((EXTERNAL_CLK_FREQ / TIMER_DIV_FACTOR ) - 1); //Loading value for 62.5 msec unit time
	NVIC_SetPriority(SysTick_IRQn, 0);//interrupt priority is set to 0
	SysTick -> VAL = 0;  // restarts counts when it touches zero
	SysTick -> CTRL = SysTick_CTRL_TICKINT_Msk |
					  SysTick_CTRL_ENABLE_Msk; ////enable interrupt and systick timer with alternative clock source


}
/*
 * @Function
 *     returns time since startup, in sixteenths of a second
 * @Parametes: None
 * @Returns : system time * unit time of systick
 */
ticktime_t now()
{
	return (timer_global) ;
}

/*
 * @Function
 *     resets timer to 0; doesn't affect now() values
 * @Parametes: None
 * @Returns : None
 */
void reset_timer()
{
	timer_local = 0;
}
/*
 * @Function
 *     returns ticks since the last call to reset_timer()
 * @Parametes: None
 * @Returns : latest time after reset_timer
 */

ticktime_t get_timer()
{
	return timer_local;
}


void delay(uint16_t delay)
{
	reset_timer();
	while(!(get_timer() >= delay))
	{
		__asm volatile ("nop");
	}
}
/*********************************************
 *@Function: This function initializes the interrupt in the  Systick timer
 *@input: None
 *@Returns:None
 *********************************************/
void SysTick_Handler()
{
	timer_global++;
	timer_local++;
}
