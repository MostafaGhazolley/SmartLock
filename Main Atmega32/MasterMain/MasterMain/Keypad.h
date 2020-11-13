#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#define KEYPAD A  //KEYPAD IS ATTACHED ON PORTA
#define KEYPAD_PORT PORT(KEYPAD)
#define KEYPAD_DDR   DDR(KEYPAD)
#define KEYPAD_PIN   PIN(KEYPAD)

unsigned char GetKeyPressed(void);


#include "Keypad.c"
#endif /*_KEYPAD_H_*/