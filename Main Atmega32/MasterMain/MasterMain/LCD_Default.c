/******************
Default of sending a character or a command to the LCD devise 
PORTS used are D & C.....
******************/


void send_a_command (unsigned char command)
{
	PORTD = (PORTD & UPPER_NIBBLE) | (command & LOWER_NIBBLE);// Sending upper nibble 
	PORTD &= ~ (1<<RS);		// RS=0, command reg. 
	PORTD |= (1<<EN);		// Enable pulse 
	_delay_us(1);
	PORTD &= ~ (1<<EN);
	_delay_us(200);
	PORTD = (PORTD & UPPER_NIBBLE) | (command << 4);/* Sending lower nibble */
	PORTD |= (1<<EN);
	_delay_us(1);
	PORTD &= ~ (1<<EN);
	_delay_ms(20);
}

void send_a_character (unsigned char character)
{
	PORTD = (PORTD & UPPER_NIBBLE) | (character & LOWER_NIBBLE);// Sending upper nibble 
	PORTD |= (1<<RS);  // RS=1, data reg. 
	PORTD|= (1<<EN);
	_delay_us(1);
	PORTD &= ~ (1<<EN);
	_delay_us(200);
	PORTD = (PORTD & UPPER_NIBBLE) | (character << 4);  // Sending lower nibble 
	PORTD |= (1<<EN);
	_delay_us(1);
	PORTD &= ~ (1<<EN);
	_delay_ms(20);
}


/********************************************************************
//////Old Version (8 wires Data LCD) Functions : 
void send_a_command (unsigned char command)
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