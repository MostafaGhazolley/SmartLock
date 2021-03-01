#ifndef _TIMER_H_
#define _TIMER_H_

#include "LCD_Messages.h"

#ifndef _MASTER_MCU_DEFINTIONS_
#include "Master.MCU.Definitions.h"
#endif /*CALLING FILE _MASTER_MCU_DEFINTIONS_*/
/************************ calling back global Variables *************************/
extern volatile unsigned char NUMBER_OF_TRIES; // Defined & initialized in Master.MCU.Definitions.h
extern volatile unsigned int TIMER0_INTERRUPT_FLAG;
extern volatile unsigned int TIMER0_INTERRUPT_SECONDS;
	
/****** FUNCTIONS ******/
/*
	Function Name        : Init_TIMER0
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize timer 0 in ATmega32, with enable interrupt
							Flag and pre-scaling Clock/64
*/	
void Init_TIMER0(void);

/*
	Function Name        : TIMER0_IN_SECONDS_WITH_LCD
	Function Returns     : void
	Function Arguments   : unsigned char
	Function Description : printing time (from timer0) in seconds (decreasing) 
							from (30 --> 0 Second) giving to the function,
							the position where to print on second line of LCD.
*/
void TIMER0_IN_SECONDS_WITH_LCD(unsigned char);

/*
	Function Name        : Close_TIMER0
	Function Returns     : void
	Function Arguments   : void
	Function Description : Terminate Timer0.
*/
void Close_TIMER0(void);

#include "Timer.c"
#endif /*_TIMER_H_*/

