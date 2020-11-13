/******************

Default of sending a character or a command to the LCD devise 
PORTS used are D & C.....

******************/
#include <avr/delay.h>


void send_a_command (unsigned char command)
{
	/*
    //That code should be the first 4 pins.... but not working :(
	PORTB = (PORTB & 0xF0) | (command & 0x0F);// Sending upper nibble 
    PORTD&= ~(1<<RS);
    PORTD|= (1<<EN);
	_delay_us(10);
	PORTD&= ~(1<<EN);
	_delay_ms(90);
	PORTB = (PORTB & 0xF0) | (command >> 4);// Sending lower nibble 
	PORTD|= (1<<EN);
	_delay_us(10);
    PORTD&= ~(1<<RS);
	PORTB &=0xF0;
	_delay_ms(5);
	*/

	PORTD = (PORTD & 0x0F) | (command & 0xF0);// Sending upper nibble 
	PORTD &= ~ (1<<RS);		// RS=0, command reg. 
	PORTD |= (1<<EN);		// Enable pulse 
	_delay_us(1);
	PORTD &= ~ (1<<EN);
	_delay_us(200);
	PORTD = (PORTD & 0x0F) | (command << 4);/* Sending lower nibble */
	PORTD |= (1<<EN);
	_delay_us(1);
	PORTD &= ~ (1<<EN);
	_delay_ms(20);

}

void send_a_character (unsigned char character)
{
	/*
	//That code should be the first 4 pins.... but not working :(
    PORTB = (PORTB & 0xF0) | (character & 0x0F);// Sending upper nibble 
    PORTD|= (1<<RS);
    PORTD|= (1<<EN);
	_delay_us(10);
	PORTD&= ~(1<<EN);
	_delay_ms(90);
	PORTB = (PORTB & 0xF0) | (character >> 4);  //Sending lower nibble 
	PORTD|= (1<<EN);
	_delay_us(10);
    PORTD&= ~(1<<EN);
	PORTB &=0xF0;
	_delay_ms(5);
	*/
	
	PORTD = (PORTD & 0x0F) | (character & 0xF0);// Sending upper nibble 
	PORTD |= (1<<RS);  // RS=1, data reg. 
	PORTD|= (1<<EN);
	_delay_us(1);
	PORTD &= ~ (1<<EN);
	_delay_us(200);
	PORTD = (PORTD & 0x0F) | (character << 4);  // Sending lower nibble 
	PORTD |= (1<<EN);
	_delay_us(1);
	PORTD &= ~ (1<<EN);
	_delay_ms(20);
	
}


/********************************************************************
//////Sample hah!! use it if u want 8 wires communication...
//////magically short working version from the one in top ^^^^^
//////Old Version (8 wires Data LCD) Functions : void send_a_command (unsigned char command)
{
	PORTB=command;
	PORTD&= ~(1<<2);
	PORTD|= (1<<3);
	_delay_ms(100);
	PORTD&= ~(1<<3);
	PORTB =0;
}

void send_a_character (unsigned char character)
{
	PORTB=character;
	PORTD|= (1<<2);
	PORTD|= (1<<3);
	_delay_ms(100);
	PORTD&= ~(1<<3);
	PORTB =0;
}
*********************************************************************/