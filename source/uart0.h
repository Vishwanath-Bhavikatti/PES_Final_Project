/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
​ ​*​ ​@date​ :April 28, 2023
 * @file name : uart0.h
 * @file_description: This file has function prototypes for UART0_INIT
 * @Credits: Referred Dean's Book chapter 8 for uart initialisation and IRQ handler. Also referred Lecture notes.
*************************************************************************************************************************
*/

#ifndef UART0_H_
#define UART0_H_
#include <MKL25Z4.H>
#include <stdio.h>

/*
 * @Function
 *     This function initializes the UART0 for UART communication
 *     Clock configuration, mode bit setting, Parity setting and Enabling Interrupts are done here
 * @Parametes: Baud rate
 * @Returns : None
 */
void Init_UART0(uint32_t baud_rate);


#endif /* UART0_H_ */
