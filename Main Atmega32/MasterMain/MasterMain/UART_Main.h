#ifndef _UART_Main_H_
#define _UART_Main_H_

void UART_Init(void);
void UART_Send(unsigned char);
unsigned char UART_Rec(void);

#include "UART_Main.c"

#endif /*_UART_Main_H_*/