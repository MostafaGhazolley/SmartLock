

#ifndef _LCD_DEFAULT_H_
#define _LCD_DEFAULT_H_

#define RS PD0
#define EN PD1

void send_a_command (unsigned char command);  // LCD Commands..
void send_a_character(unsigned char character);  //LCD outPut a charcter...

#include "LCD_Default.c"

#endif /*_LCD_DEFAULT_H_*/