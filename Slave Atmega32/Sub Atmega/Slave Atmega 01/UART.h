#ifndef _UART_H_
#define _UART_H_

/******************************** FUNCTIONS ********************************/
/*
	Function Name        : UART_Init
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize UART-Communication protocol on the MCU
							with fixed pre-defined baud-rate.
*/
void UART_Init(void);

/*
	Function Name        : UART_Send
	Function Returns     : void
	Function Arguments   : unsigned char
	Function Description : taking the sending byte as an argument and wait (while)
							till making sure that data sent away.
*/
void UART_Send(unsigned char);

/*
	Function Name        : UART_Rec
	Function Returns     : unsigned char
	Function Arguments   : void
	Function Description : Receiving byte and return it back to the caller
							and its polling, so the processor will stuck till
							data is received.
*/
unsigned char UART_Rec(void);


#include "UART.c"
#endif /*_UART_H_*/