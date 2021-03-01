#ifndef _KEYPAD_H_
#define _KEYPAD_H_

/******************************** DEFINITIONS ************************************/
#define _CONCAT(a,b)	a##b
#define PORT(x)			_CONCAT(PORT,x)
#define PIN(x)			_CONCAT(PIN,x)
#define DDR(x)			_CONCAT(DDR,x)


#define DEFAULT_KEYPRESS 	(unsigned char)0xFF
#define ZERO_ASCII			(unsigned char)0x30
#define HASH_ASCII			(unsigned char)0x23
#define ASTERISK_ASCII		(unsigned char)0x2A
#define SWITCH_TO_ASCII 	(unsigned char)0x31
#define ALL_ROWS_HIGH 		(unsigned char)0x0F
#define ROW_COLUMN_HGIH 	(unsigned char)0x7F
#define FIRSTBIT		 	(unsigned char)0x01
#define FOURTHBIT			(unsigned char)0x10
#define NUMBER_ROWs			4
#define NUMBER_COLs			3
#define FOURTH_ROW			3
#define FIRST_COL			0	
#define SECOND_COL			1
#define THIRD_COL			2

#define KEYPAD A  //KEYPAD IS ATTACHED ON PORTA
#define KEYPAD_PORT		PORT(KEYPAD)
#define KEYPAD_DDR		DDR(KEYPAD)
#define KEYPAD_PIN		PIN(KEYPAD)

#define RESET_PRESSED_KEY		Key=DEFAULT_KEYPRESS; //Reset the Keypad entry
/*********************************** FUNCTIONS **********************************/
/*
	Function Name        : GetKeyPressed
	Function Returns     : unsigned char
	Function Arguments   : void
	Function Description : back the pressing key on keypad (4X3) in ASCII
*/
static unsigned char GetKeyPressed(void);


#include "Keypad.c"
#endif /*_KEYPAD_H_*/