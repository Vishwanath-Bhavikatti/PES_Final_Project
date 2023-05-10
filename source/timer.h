/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
 * @Credits : Embedded System Fundamentals with ARM cortex Microcontrollers Book by Alexander Dean chapter 7
​ ​*​ ​@date​ :April 28, 2023
 * @file name : timer.h
 * @file_description: It defines function prototypes for Init_SysTick, now(), reset_timer()
 * 					  and get_timer().
 *
*************************************************************************************************************************
*/
#ifndef TIMER_H_
#define TIMER_H_

#include "MKL25Z4.h"

typedef uint32_t ticktime_t;  // time since boot, in 1msec
ticktime_t now();

/*
 * @Function
 *     This function initializes SysTick module
 * @credits: Alexander Dean Book
 * @Parametes: None
 * @Returns : None
 */
void Init_SysTick(void);

/*
 * @Function
 *     resets timer to 0; doesn't affect now() values
 * @Parametes: None
 * @Returns : None
 */
void reset_timer();

/*
 * @Function
 *     returns ticks since the last call to reset_timer()
 * @Parametes: None
 * @Returns : latest time after reset_timer
 */
ticktime_t get_timer();

void delay(uint16_t delay);
#endif /* TIMER_H_ */
