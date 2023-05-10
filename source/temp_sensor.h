/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
​ ​*​ ​@date​ :April 28, 2023
 * @file name : temp_sensor.h
 * @file_description: This file includes temperature measurement function prototype which returns temperature in
 *                    deg C.
 * @Credits : Embedded_Systems_Fundamentals Book by Alexander Dean Chapter 6
 * 			  Kl25Z Reference manual.
 *
*************************************************************************************************************************
*/
#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

/*
 * @Function: To measure temperature using ADC and temperature sensor on the kl25z.
 *
 * @ input Parameter: None
 * @ returns : float temperature value after calibration in deg C.
 */
float Measure_Temperature(void);

#endif /* TEMP_SENSOR_H_ */
