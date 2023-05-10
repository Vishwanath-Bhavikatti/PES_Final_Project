/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
​ ​*​ ​@date​ :April 28, 2023
 * @file name : temp_sensor.c
 * @file_description: This file includes temperature measurement function which selects an ADC channel
 *                    for starting conversion and waits for the conversion completion and reads the
 *                    temperature and calculates the readable temperature.
 * @Credits : Embedded_Systems_Fundamentals Book by Alexander Dean Chapter 6
 * 			  Kl25Z Reference manual.
 * 			  https://learningmicro.wordpress.com/using-in-built-temperature-sensor-of-kl25z-mcu/
 *
*************************************************************************************************************************
*/
/*Include files*/

#include <stdio.h>
#include <stdlib.h>
#include "clock_config.h"
#include "MKL25Z4.h"
#include "temp_sensor.h"
#include "adc.h"

/*Defining macros*/
#define TEMP_CHNL          (0x1A) //Channel 26 for Temperature sensor
#define V_TEMP_25          (0.7012) //sensor produces this voltage at 25 deg c
#define HOT_SLOPE          (0.001646) //if temp > V_temp_25 deg C use this hot slope for calibration
#define COLD_SLOPE         (0.001749) //if temp < V_temp_25 deg C use this cold slope for calibration
#define MULTIPLIER         (0.0029296875) //multiplier calibration value
#define REF_TEMP           (25) // Reference temperature as room temperature of 25 deg C
#define CAL_OFFSET         (18) //Calibration offset

/*
 * @Function: To measure temperature using ADC and temperature sensor on the kl25z.
 *
 * @ input Parameter: None
 * @ returns : float temperature value after calibration in deg C.
 */
float Measure_Temperature(void)
{
	float vtemp, temp;

	ADC0->SC1[0] = TEMP_CHNL; // start conversion on channel 26

	// Wait for conversion to finish
	while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));

	// Read result, convert to floating-point
	vtemp = (float) ADC0->R[0];
	vtemp = vtemp * MULTIPLIER;
	if (vtemp >= V_TEMP_25)
	{
		temp = REF_TEMP -  ((vtemp - V_TEMP_25)/HOT_SLOPE) + CAL_OFFSET; // temperature calculation using cold slope value.
	}
	else
	{
		temp = REF_TEMP -  ((vtemp - V_TEMP_25)/COLD_SLOPE) + CAL_OFFSET; // temperature calculation using hot slope value.
	}
	return temp;
}
