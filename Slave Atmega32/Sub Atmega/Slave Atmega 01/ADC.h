#ifndef _ADC_H_
#define _ADC_H_



/********************************* DEFINITION *****************************/
#define F_CPU 8000000UL

/*********************************** FUNTIONS ************************************/
/*
	Function Name        : I2C_Init
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize I2C communication protocol on ATmega32
							with pre-defind clock rate (as its synchronous com.).
*/
void I2C_Init(void);

/*
	Function Name        : I2C_Start
	Function Returns     : void
	Function Arguments   : void
	Function Description : start the communication.
*/
void I2C_Start(void);


#include "IOuserDef.h" // #include <avr/io.h> #include <avr/iom32.h>     <<-are inside...
#include "ADC.c"
#endif /*_ADC_H_*/