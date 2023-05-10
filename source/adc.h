/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
​ ​*​ ​@date​ :April 28, 2023
 * @file name : adc.h
 * @file_description: This file includes the ADC initialization function prototypes.
 * @Credits : Embedded_Systems_Fundamentals Book by Alexander Dean Chapter 6
 * 			  Kl25Z Reference manual.
 *
*************************************************************************************************************************
*/
#ifndef ADC_H_
#define ADC_H_

/*Including files*/
#include <MKL25Z4.H>

/*
 * @Function
 *     This function Initializes ADC using Bare metal approach
 *
 * @Parametes: None
 * @Returns : None
 */
void Init_ADC(void);

#endif /* ADC_H_ */
