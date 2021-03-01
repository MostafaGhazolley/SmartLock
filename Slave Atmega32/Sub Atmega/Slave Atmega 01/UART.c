/***********************
ISR (USART_TXC_vect)
{
		
}

ISR (USART_RXC_vect)
{
	
}
#include <avr/interrupt.h>
***********************/

void UART_Init(void)
{
	DDRD  |= (1<<PD1);
	DDRD  &= (~(1<<PD0));
	UBRRL = 51;
	UBRRH = 0;
	//unsigned int BAUD_Rate=9600;								//			F_CPU
	//unsigned int UBRR_Value;									//UBRR=------------------ - 1					((F_CPU => the clock of the microcontroller..))			
	//UBRR_Value = (((F_CPU)/(16 * BAUD_Rate))-1);				//		16 * BAUD_Rate							and the BAUD_Rate is the data transferring bits per sec...
	UCSRB |= (1<<TXEN) | (1<<RXEN);			//Receive complete IE,Data reg. Empty IE, Transmit/Receive enable,Transmit complete IE
	UCSRC |= (1<<URSEL) |(1<<UCSZ0) | (1<<UCSZ1);			// 8bit-data and parity mode Even
		
		_delay_ms(250);
	/********
	if(UBRR_Value <=255)
	{
		UBRRL=UBRR_Value;
		//UBRRH=0;
	}
	else
	{
		UBRRL=UBRR_Value;
		UBRRH=(UBRR_Value>>8);
	}
	*****/

	
}

void UART_Send(unsigned char data)
{
	while( !(UCSRA & (1<<UDRE)) ) ; //wait until UDR is empty...
		UDR = data;					//putting data into UDR, send the data...
	
}

unsigned char UART_Rec(void)
{	
	while ( !(UCSRA & (1<<RXC)) );	// wait for the receive complete (RXC) flag...
	return UDR;						//Get and return received data from buffer...
}