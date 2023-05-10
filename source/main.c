/*
 *********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
​ ​*​ ​@date​ :April 28, 2023
 * @file name : main.c
 * @file_description: This main file includes all the necessary supported header files and
 * 					  Implemented function headers. It calls all initialization functions for
 * 					  ADC(Temp sensor), UART0, Systick and LEDs to read temperature and display on UART
 * 					  with LED indications.
 * 					  It calls an infinite while loop to continuously print temperature on UART
 *
 *************************************************************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
/* TODO: insert other include files here. */
#include "uart0.h"
#include "llfifo.h"
#include "temp_sensor.h"
#include "timer.h"
#include "adc.h"
#include "led.h"
#include "lcd.h"
#include "stdbool.h"
/* TODO: insert other definitions and declarations here. */

#define ONE_SECOND        (1000) //one second delay
#define TWO_SECOND        (2000) //2 seconds delay
#define MUL_FACTOR        (1.8)  // Mul factor for fahrenheit conversion
#define ADD_FACTOR        (32)   // Add factor for fahrenheit conversion
#define BAUD_RATE         (38400) //UART Baud Rate
#define UPPER_TEMP_LIMIT  (25) //Upper threshold temp
#define LOWER_TEMP_LIMIT  (18) //Lower Threshold temp

/*
 * @brief   Application entry point.
 */
int main(void)
{
	float temp_deg_c=0;
	float temp_deg_f=0;

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

	//Initializations
	Init_UART0(BAUD_RATE);
	Init_SysTick();
	Init_ADC();
	led_init();


	lcd_init();				//initialize LCD

	printf("******************** TEMPERATURE MONITORING SYSTEM ***********************\n\r");
	delay(ONE_SECOND);
	/*****************Initialize LCD*****************/
	start_lcd();
	lcd_data_write("WELCOME TO", LCD_LINE1);
	lcd_data_write("   PES PROJECT", LCD_LINE2);
	delay(TWO_SECOND);
	clear_lcd();




	reset_timer();		//Resetting timer before entering while loop.
	while(1)
	{
		if (get_timer() > ONE_SECOND ) //Check for 2 second.
		{
			temp_deg_c = Measure_Temperature();//get the temp in deg Celsius
			temp_deg_f = (temp_deg_c * MUL_FACTOR) +  ADD_FACTOR;// converting to fahrenheit
			if(temp_deg_c > UPPER_TEMP_LIMIT)
			{
				led_RED_ON(); //Temp greater that upper threshold
			}
			else if(temp_deg_c < LOWER_TEMP_LIMIT)
			{
				led_BLUE_ON(); //Temp lower that lower threshold
			}
			else
				led_GREEN_ON();// Normal range

			printf("The current temperature in Celsius %0.2f deg C and in Fahrenheit %0.2f deg F \n\r", temp_deg_c,temp_deg_f);
			uint32_t temp_C= (uint32_t)temp_deg_c;
			uint32_t temp_F= (uint32_t)temp_deg_f;
			lcd_data_write("Deg C:", LCD_LINE1);
			lcd_data_write_int(temp_C, SAME_LINE);
			lcd_data_write("Deg F:", LCD_LINE2);
			lcd_data_write_int(temp_F, SAME_LINE);
			delay(TWO_SECOND);
			clear_lcd();
			reset_timer();

		}
	}
	return 0 ;
}
