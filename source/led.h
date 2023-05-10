/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
 * @Credits : Referred Embedded_Systems_Fundamentals by Dean, chapter 2
​ ​*​ ​@date​ :April 28, 2023
 * @file name : led.h
 * @file_description:
 * 		This file includes LED Initialization, Blinking individual LEDs and turning off LEDs
 * 		function prototypes.
 *
*************************************************************************************************************************
*/
#ifndef LED_H_
#define LED_H_

/*
 * @Function: Initializing the LED's by providing clock
 *           and configuring them as output pins.
 *
 * @Input parameters : None
 * @returns : None
 */
void led_init();

/*
 * @Function
 * 	  This function turns BLUE LED ON
 *
 */
void led_BLUE_ON();

/*
 * @Function
 * This function turns GREEN LED ON
 *
 */
void led_GREEN_ON();

/*
 * @Function
 *     This function turns RED LED ON
 *
 */
void led_RED_ON();

/*
 * @Function
 *     This function turns OFF LED
 *
 */
void led_OFF();

#endif /* LED_H_ */
