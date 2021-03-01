void Init_TIMER0(void)
{
	TIMSK=(1<<TOIE0);  	/* Enable Timer0 overflow interrupts */
	TCCR0=(1<<CS00)|(1<<CS01);			//Start Timer0 & clock/64 PreScale.
}

void Close_TIMER0(void)
{
	TCCR0=0x00;
}

void TIMER0_IN_SECONDS_WITH_LCD(unsigned char position)
{
	TCNT0=0x70;			//in order to get 250 cycle (0x06 to 0x255"max") + 1
	unsigned char counter=0;
	TIMER0_INTERRUPT_FLAG=0;
	Init_TIMER0();
	send_a_command(cmd_CURSOROFF); //go cursor to Second line...
	while(TIMER0_INTERRUPT_SECONDS>0)
	{
		send_a_command(cmd_SECONDLINE); //go cursor to Second line...
		for(counter=0;counter<position;counter++)
		{	//shifting the output on screen to the right
			send_a_command(cmd_RIGHTSHIFT); // shift right 1 X L1
		}
		send_a_character(((TIMER0_INTERRUPT_SECONDS%100)/10)+0x30);	//showing higher value digit
		send_a_character((TIMER0_INTERRUPT_SECONDS%10)+0x30);		//showing the lower value digit
	}//end of showing seconds on screen loop
	Close_TIMER0();		//turn off timer
}


/*
unsigned char TIMER0_IN_SECONDS(unsigned char Sec)
{
	if(TIMER0_INTERRUPT_FLAG>=500)
	{
		Sec--;
		TIMER0_INTERRUPT_FLAG=0;	
	}
	else
	{
		//nothing...
	}
	return(Sec);
}
*/
