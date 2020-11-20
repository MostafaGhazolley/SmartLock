

#ifndef _LCD_DEFAULT_H_
#define _LCD_DEFAULT_H_

#define RS PD0
#define EN PD1

/*
	Function Name        : send_a_command
	Function Returns     : void
	Function Arguments   : unsigned char command
	Function Description : Send Command line(byte) to LCD.
*/
void send_a_command (unsigned char command);

/*
	Function Name        : send_a_character
	Function Returns     : void
	Function Arguments   : unsigned char character
	Function Description : Send Data/Character line(byte) to LCD.
*/
void send_a_character(unsigned char character); 

#include "LCD_Default.c"

#endif /*_LCD_DEFAULT_H_*/