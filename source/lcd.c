/*
*********************************************************************************************************************
​ *
​ ​*​ ​@author​ :​Vishwanath Bhavikatti
​ ​*​ ​@date​ :May 02, 2023
 * @file name : lcd.c
 * @file_description: This file initializes 16 X 4 LCD to write data and write integers using memory mapped approach,
 * @Credits : https://www.nxp.com/docs/en/application-note/AN3031.pdf
 * 	          https://learningmicro.wordpress.com/using-in-built-temperature-sensor-of-kl25z-mcu/
 * 	          also collaborated with Spandana in intializing LCD
 *
*************************************************************************************************************************
*/
#include "MKL25Z4.h"
#include <stdio.h>
#include "core_cm0plus.h"
#include "timer.h"
#include "lcd.h"

// Connected PORT C pins
#define DB7     (7) //PTC7 PIN
#define DB6     (0) //PTC0 PIN
#define DB5     (3) //PTC3 PIN
#define DB4     (4) //PTC4 PIN
#define RS      (10) //PTC10 PIN
#define RW      (6) //PTC6 PIN
#define EN      (5) //PTC5 PIN
 // LCD to GPIO pin configuration interface
#define LCD_DB7  ((uint32_t)1 << 7)  // PTC7
#define LCD_DB6  ((uint32_t)1 << 0)  // PTC0
#define LCD_DB5  ((uint32_t)1 << 3)  // PTC3
#define LCD_DB4  ((uint32_t)1 << 4)  // PTC4

#define LCD_E    ((uint32_t)1 << 5)  // PTC5
#define LCD_RW   ((uint32_t)1 << 6)  // PTC6
#define LCD_RS   ((uint32_t)1 << 10) // PTC10


#define DB7_BIT   (0x80)
#define DB6_BIT   (0x40)
#define DB5_BIT   (0x20)
#define DB4_BIT   (0x10)
#define FIRST_ROW_START_ADDR  (0x80)
#define SECOND_ROW_START_ADDR (0xC0)
#define MSB_NIBBLE  (0xF0)
#define SHIFT_FOUR  (4)
#define ONE_MSEC   (1)
#define TEN_MSEC   (10)
#define DOT_MODE   (0x28)
#define CLEAR_DISPLAY    (0x01)
#define DISPLAY_ON  (0x0C)
#define INITIAL_POS (0x02)
#define ROW_LENGTH  (16)

/*
 * @Function: Initialize the GPIO to interface the 16x2 LCD over it.
 * 			 GPIO port E is used for configuration
 *
 * @ input Parameter: None
 * @ returns : none.
 */
void lcd_init(void){
	//Enable clock to PORTC
	SIM->SCGC5 |= SIM_SCGC5_PORTC(1);

	//Enable and initialize all the GPIO pins
	PORTC->PCR[DB7] |= PORT_PCR_MUX(1);			//Configure PTC10
	PORTC->PCR[DB6] |= PORT_PCR_MUX(1);			//Configure PTC7
	PORTC->PCR[DB5] |= PORT_PCR_MUX(1);			//Configure PTC6
	PORTC->PCR[DB4] |= PORT_PCR_MUX(1);			//Configure PTC5
	PORTC->PCR[RS] |= PORT_PCR_MUX(1);			//Configure PTC4
	PORTC->PCR[RW] |= PORT_PCR_MUX(1);			//Configure PTC3
	PORTC->PCR[EN] |= PORT_PCR_MUX(1);			//Configure PTC0

	//Configure all the pins as output
	GPIOC->PDDR |= (LCD_DB7 | LCD_DB6 | LCD_DB5 |
				LCD_DB4 | LCD_E | LCD_RS | LCD_RW);
}


/*
 * @Function: write 4 bits on the LCD DDRAM.
 *
 * @ input Parameter: nibble		nibble to be written
 * @ returns : none.
 */
void write_nibble(uint8_t nibble){
	uint32_t gpio_cmd;

	//Get GPIOC Data Register
	gpio_cmd = GPIOC->PDOR;

	//Update the LCD data line DB7
	if(nibble & DB7_BIT){
		gpio_cmd |= LCD_DB7;
	}
	else{
		gpio_cmd &= ~LCD_DB7;
	}

	//Update the LCD data line DB6
	if(nibble & DB6_BIT){
		gpio_cmd |= LCD_DB6;
	}
	else{
		gpio_cmd &= ~LCD_DB6;
	}

	//Update the LCD data line DB5
	if(nibble & DB5_BIT){
		gpio_cmd |= LCD_DB5;
	}
	else{
		gpio_cmd &= ~LCD_DB5;
	}

	//Update the LCD data line DB4
	if(nibble & DB4_BIT){
		gpio_cmd |= LCD_DB4;
	}
	else{
		gpio_cmd &= ~LCD_DB4;
	}

	GPIOC->PDOR = gpio_cmd;					//Write - Update data on GPIO Port C
}

/*
 * @Function: sends the command to the device and device to memory
 *
 * @ input Parameter: cmd	command to be sent to the lCD
 * @ returns : none.
 */
void lcd_cmd(uint8_t cmd){
	GPIOC->PDOR &= ~LCD_RS;						//Select command register (RS=Low)
	GPIOC->PDOR &= ~LCD_RW;						//Select write operation (RW=Low)

	write_nibble(cmd & MSB_NIBBLE);					//Write upper nibble

	//Generate High to Low pulse on EN pin
	GPIOC->PDOR |= LCD_E;						//EN = High
	delay(ONE_MSEC);
	GPIOC->PDOR &= ~LCD_E;						//EN = Low
	delay(ONE_MSEC);

	write_nibble((cmd<<SHIFT_FOUR) & MSB_NIBBLE);				//Write lower nibble

	//Generate High to Low pulse on EN pin
	GPIOC->PDOR |= LCD_E;						//EN = High
	delay(ONE_MSEC);
	GPIOC->PDOR &= ~LCD_E;						//EN = Low
	delay(ONE_MSEC);
}

/*
 * @Function: Functions that sends command to the memory
 * 			 	to initialize the LCD and sets the position of cursor.
 *
 * @ input Parameter: none
 * @ returns : none.
 */
void start_lcd(void){
	lcd_cmd(INITIAL_POS);								//Moves the cursor to initial positions
	delay(TEN_MSEC);
	lcd_cmd(DOT_MODE);								//Enable 4-bit, 2 line, 5x7 dots mode for characters
	delay(TEN_MSEC);
	lcd_cmd(DISPLAY_ON);								//Display ON, Cursor OFF
	delay(TEN_MSEC);
	lcd_cmd(CLEAR_DISPLAY);								//Clear display
	delay(TEN_MSEC);
}

/**
 * @Function: 	 Clears the LCD and refreshes it
 * @input Parameters:   none
 * @returns:   none
 */
void clear_lcd(void){
	lcd_cmd(CLEAR_DISPLAY);	//Clear display
	delay(TEN_MSEC);
}

/**
 * @Function : Writes the string on the display,
 * 			 string is passed to display on LCD	.
 *
 * @ input Parameter:  pointer to the char pointer
 * @ returns:  count of Data to be displayed on LCD
 */
uint8_t lcd_string_write(char **str){
	uint8_t cnt = 0;							//Counting String length

	//Write the complete message
	while(**str && (cnt<ROW_LENGTH)){
		GPIOC->PDOR |= LCD_RS;					//Select data register for LCD
		GPIOC->PDOR &= ~LCD_RW;					//Select write mode

		write_nibble(**str & MSB_NIBBLE);				//Writing upper nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(ONE_MSEC);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(ONE_MSEC);

		write_nibble((**str << SHIFT_FOUR) & MSB_NIBBLE);		//Writing upper nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(ONE_MSEC);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(ONE_MSEC);

		(*str)++;								//Moving the pointer to next character
		cnt++;
		delay(TEN_MSEC);
	}
	return cnt;
}

/**
 * @Function: function writes string to be written on the LCD.
 *
 * @ input Parameter:    data	char pointer to be printed
 *                       line	cursor line
 * @ returns:   none
 */
void lcd_data_write(char *data, lcd_line line){
	uint8_t char_written;						//Actual no. of chars written on LCD
	char *temp = " ";							//Space to be filled for unused blocks on line

	//switch case which handles where the data is to be written
	switch(line){
	case LCD_LINE1:
		lcd_cmd(FIRST_ROW_START_ADDR);							//Move the cursor to the beginning of first line
		break;

	case LCD_LINE2:
		lcd_cmd(SECOND_ROW_START_ADDR);							//Move the cursor to the beginning of second line
		break;

	case SAME_LINE:								//Writes on the same line where the cursor currently is
		break;
	}

	//Write data string to LCD (it returns how many characters are written)
	char_written = lcd_string_write(&data);
	while(char_written < ROW_LENGTH){
		lcd_string_write(&temp);
		char_written++;
	}
}

/**
 * @Function: function which handles to write integer on
 * 			 the LCD. Converts the Integer to ASCII value.
 *
 * @ input parameters:   num	Integer to be displayed on screen.
 * 			             line	on which line the integer is to be printed
 * @ returns:   none
 */
void lcd_data_write_int(uint32_t num, lcd_line line){
	uint8_t byte[10] = {0};							//Handle 10 digit array
	uint8_t idx = 0;							//Index to preserve the state of byte array

	//switch case whre the lcd is to be initialized
	switch(line){
	case LCD_LINE1:
		lcd_cmd(FIRST_ROW_START_ADDR);							//Move the cursor to the beginning of first line
		break;

	case LCD_LINE2:
		lcd_cmd(SECOND_ROW_START_ADDR);							//Move the cursor to the beginning of second line
		break;

	case SAME_LINE:								//Writes on the same line where the cursor currently is
		break;
	}

	//Recovering each digit from the input
	while(num != 0){
		byte[idx] = num % 10;
		num = num / 10;
		idx++;
	}

	//Convert the decimal into ASCII and print on the LCD
	for(int i=(idx - 1); i>=0; i--){
		GPIOC->PDOR |= LCD_RS;					//Select data register
		GPIOC->PDOR &= ~LCD_RW;					//Select write mode

		write_nibble(('0'+byte[i]) & MSB_NIBBLE);		//Write upper nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(ONE_MSEC);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(ONE_MSEC);

		write_nibble((('0'+byte[i]) << SHIFT_FOUR) & MSB_NIBBLE);	//Write lower nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(ONE_MSEC);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(ONE_MSEC);

		delay(TEN_MSEC);
	}
	if(idx == 0){
		GPIOC->PDOR |= LCD_RS;					//Select data register
		GPIOC->PDOR &= ~LCD_RW;					//Select write mode

		write_nibble(('0'+byte[idx]) & MSB_NIBBLE);		//Write upper nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(ONE_MSEC);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(ONE_MSEC);

		write_nibble((('0'+byte[idx]) << SHIFT_FOUR) & MSB_NIBBLE);	//Write lower nibble
		GPIOC->PDOR |= LCD_E;					//EN = High
		delay(ONE_MSEC);
		GPIOC->PDOR &= ~LCD_E;					//EN = Low
		delay(ONE_MSEC);

		delay(TEN_MSEC);
	}
}
