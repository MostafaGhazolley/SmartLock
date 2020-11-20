#ifndef _KEYPAD_H_
#define _KEYPAD_H_

//#ifndef _CONCAT(a,b)
#define _CONCAT(a,b) a##b
#define PORT(x) _CONCAT(PORT,x)
#define PIN(x) _CONCAT(PIN,x)
#define DDR(x) _CONCAT(DDR,x)
//#endif

#define DEFAULT_KEYPRESS (unsigned char)0xFF
#define ZERO_ASCII	(unsigned char)0x30
#define HASH_ASCII	(unsigned char)0x2A
#define ASTERISK_ASCII	(unsigned char)0x23
#define SWITCH_TO_ASCII (unsigned char)0x31
#define ALL_ROWS_HIGH (unsigned char)0x0F
#define ROW_COLUMN_HGIH (unsigned char)0x7F

#define KEYPAD A  //KEYPAD IS ATTACHED ON PORTA
#define KEYPAD_PORT PORT(KEYPAD)
#define KEYPAD_DDR   DDR(KEYPAD)
#define KEYPAD_PIN   PIN(KEYPAD)

unsigned char GetKeyPressed(void);


#include "Keypad.c"
#endif /*_KEYPAD_H_*/