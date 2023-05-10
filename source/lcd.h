/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
​ ​*​ ​@date​ :May 02, 2023
 * @file name : lcd.h
 * @file_description: This file initializes 16 X 4 LCD to write data and write integers using memory mapped approach,
 * @Credits : https://www.nxp.com/docs/en/application-note/AN3031.pdf
 * 	          https://learningmicro.wordpress.com/using-in-built-temperature-sensor-of-kl25z-mcu/
 *	          also collaborated with Spandana in intializing LCD
*************************************************************************************************************************
*/
#ifndef LCD_H_
#define LCD_H_

#include "MKL25Z4.h"
#include "timer.h"


//lcd_line denotes the line number on the LCD.
typedef enum{
	LCD_LINE1,
	LCD_LINE2,
	SAME_LINE
}lcd_line;

/*
 * @Function: Initialize the GPIO to interface the 16x2 LCD over it.
 * 			 GPIO port E is used for configuration
 *
 * @ input Parameter: None
 * @ returns : none.
 */
void lcd_init(void);

/*
 * @Function: write 4 bits on the LCD DDRAM.
 *
 * @ input Parameter: nibble		nibble to be written
 * @ returns : none.
 */
void write_nibble(uint8_t nibble);

/*
 * @Function: sends the command to the device and device to memory
 *
 * @ input Parameter: cmd	command to be sent to the lCD
 * @ returns : none.
 */
void lcd_cmd(uint8_t cmd);

/*
 * @Function: Functions that sends command to the memory
 * 			 	to initialize the LCD and sets the position of cursor.
 *
 * @ input Parameter: none
 * @ returns : none.
 */
void start_lcd(void);

/**
 * @Function: 	 Clears the LCD and refreshes it
 * @input Parameters:   none
 * @returns:   none
 */
void clear_lcd(void);

/**
 * @Function : Writes the string on the display,
 * 			 string is passed to display on LCD	.
 *
 * @ input Parameter:  pointer to the char pointer
 * @ returns:  count of Data to be displayed on LCD
 */
uint8_t lcd_string_write(char **str);

/**
 * @Function: function writes string to be written on the LCD.
 *
 * @ input Parameter:    data	char pointer to be printed
 *                       line	cursor line
 * @ returns:   none
 */
void lcd_data_write(char *data, lcd_line line);

/**
 * @Function: function which handles to write integer on
 * 			 the LCD. Converts the Integer to ASCII value.
 *
 * @ input parameters:   num	Integer to be displayed on screen.
 * 			             line	on which line the integer is to be printed
 * @ returns:   none
 */
void lcd_data_write_int(uint32_t num, lcd_line line);

#endif /* LCD_H_ */
