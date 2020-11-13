/***************************************************************************************************************
* LCD Messages file:
* Author: Mostafa Ghazolley
* Contact: MostafaGhazolley@outlook.com
* 
*---------------------------------------------------------------------------------------------------------------
* Function name LCD_GeneralMessage
* Arguments:L1 : -its number of spaces before start to print out on LCD
*				 -from 0 to 15 (16 digit of LCD)
*				 -99 indicates thats its empty. (no text will be printed out on LCD of line 1)
*			L2 : -its number of spaces before start to print out on LCD
*				 -from 0 to 15 (16 digit of LCD)
*				 -99 indicates thats its empty. (no text will be printed out on LCD of line 2)
*			a[] :String or array of characters thats its size define by the number of elements that will be sent
*				 and what is inside that string, will be print out in the first line of LCD.
*			b[] :String or array of characters thats its size define by the number of elements that will be sent
*				 and what is inside that string, will be print out in the second line of LCD.
* Return: Nothing (void).
* 		
*
*					 
***************************************************************************************************************/


void LCD_GeneralMessage(unsigned char L1,unsigned char L2,char a[],char b[]){
	//unsigned char a[16] = "Welcome!       ." ;//First row one LCD
	//unsigned char b[16] = "Motor Drive P.1M" ;//Second Row on LCD
	int i =0;
	//next two if condition clearing the garbage (if found any...)
	if(L1>16 && L1!=99)
	{
		L1=0;
	}
	else
	{
		//Nothing...
	}
	if(L2>15 && L2!=99)
	{
		L2=0;
	}
	else
	{
		//Nothing...
	}
	
	DDRD |=  0xF0;		//PortD will be the 4-Output data to LCD (last 4 pins)
	DDRD |= (1<<RS);
	DDRD |= (1<<EN); /* PC.0 -> Register Select , PC.1 -> E ((Set pin 0,1 as output pins))...*/
	_delay_ms(50);
	//send_a_command(0x01);   /* Sending all Clear Command */
	//send_a_command(0x0E);   /* Set Screen and cursor ON! */

	// First Line!...
	for (i=0;(L1!=99) && (*a!='\0') && (i<=15) && (*(a+i)!='\0');i++){
		for(L1;L1>0;L1--)
		{
			send_a_command(0x14); // shift right 1 X L1
		}
		send_a_character(a[i]);
		_delay_ms(50); //That delay to slow down the printing of characters...
	}
	send_a_command(0xC0); //go cursor to Second line...
	// Second Line
	for (i=0;(L2!=99) && (i<=15) && (*(b+i)!='\0');i++){
		for(L2;L2>0;L2--)
		{
			send_a_command(0x14); // shift right 1 X L1
		}
		send_a_character(b[i]);
		_delay_ms(50);	//That delay to slow down the printing of characters...
	}
	
}

void LCD_Init(void)
{
	 DDRD |=0xF0;		//PortD will be the 4-Output data to LCD (last 4 pins)
	 DDRD |= (1<<RS);
	 DDRD |= (1<<EN); /* PC.0 -> Register Select , PC.1 -> E ((Set pin 0,1 as output pins))...*/
	 _delay_ms(50);
	 
	send_a_command(0x02);				/* send for 4 bit initialization of LCD  */
	send_a_command(0x28);				/* 2 line, 5*7 matrix in 4-bit mode */
	send_a_command(0x0E);				/* Set Screen and cursor ON! */
	send_a_command(0x06);               /* Increment cursor (shift cursor to right)*/
	send_a_command(0x01);               /* Clear display screen*/


}

void LCD_Pass_Req01(void){
	unsigned char a[16] = "Enter the Pass.." ;//First row one LCD
	int i;
	DDRD |=0xF0;		//PortD will be the 4-Output data to LCD (last 4 pins)
	DDRD |= (1<<RS);
	DDRD |= (1<<EN); /* PC.0 -> Register Select , PC.1 -> E ((Set pin 0,1 as output pins))...*/
	_delay_ms(50);
	send_a_command(0x01);   /* Sending all Clear Command */
	send_a_command(0x0E);   /* Set Screen and cursor ON! */

	// First Line!...
	for (i=0; (i<=15) && (*(a+i)!='\0');i++)
	{
		send_a_character(a[i]);
		_delay_ms(50);	//That delay to slow down the printing of characters...
	}
	send_a_command(0xC0); //go cursor to Second line...
	
}



void LCD_Pass_Req02(unsigned char Key){
	if (Key !=0xFF && j!=6){ //0xFF is the default return if no key pressed...
		send_a_character(Key);
		_delay_ms(50);
		j++;
	}
}

/*******************************
* Functions has been replaced, with generic functions...
* 

void LCD_Start(void){
	unsigned char a[16] = "Welcome!       ." ;//First row one LCD
	unsigned char b[16] = "Motor Drive P.1M" ;//Second Row on LCD
	int i =0;
	DDRB =0xFF; // PortB will be the 8-Output data to LCD... 
	DDRD |= (1<<2);
	DDRD |= (1<<3); // PC.0 -> Register Select , PC.1 -> E ((Set pin 0,1 as output pins))...
	_delay_ms(50);
	send_a_command(0x01);   // Sending all Clear Command 
	send_a_command(0x38);   // 16*2 Line LCD 
	send_a_command(0x0E);   // Set Screen and cursor ON!

	// First Line!...
	for (i=0; (i<=15) && (*(a+i)!='\0');i++){
		send_a_character(a[i]);
	}
	send_a_command(0xC0); //go cursor to Second line...
	// Second Line
	for (i=0; (i<=15) && (*(b+i)!='\0');i++){
		send_a_character(b[i]);
	}
}


void Access_Granted(void)
{
	unsigned char a[16] = "Access Granted!!" ;//First row one LCD
	int i;
	DDRB =0xFF; // PortB will be the 8-Output data to LCD... 
	DDRD |= (1<<2);
	DDRD |= (1<<3); // PC.0 -> Register Select , PC.1 -> E ((Set pin 0,1 as output pins))...
	_delay_ms(100);
	send_a_command(0x01);   // Sending all Clear Command 
	send_a_command(0x38);   // 16*2 Line LCD 
	send_a_command(0x0E);   // Set Screen and cursor ON! 

	// First Line!...
	for (i=0; (i<=15) && (*(a+i)!='\0');i++)
	{
		send_a_character(a[i]);
	}
	send_a_command(0xC0); //go cursor to Second line...
}

void Try_Again(void)
{
	unsigned char a[16] = "Wrong Pass!!...." ;//First row one LCD
	int i;
	DDRB =0xFF; // PortB will be the 8-Output data to LCD... 
	DDRD |= (1<<2);
	DDRD |= (1<<3); // PC.0 -> Register Select , PC.1 -> E ((Set pin 0,1 as output pins))...
	_delay_ms(100);
	send_a_command(0x01);   // Sending all Clear Command 
	send_a_command(0x38);   // 16*2 Line LCD 
	send_a_command(0x0E);   // Set Screen and cursor ON! 

	// First Line!...
	for (i=0; (i<=15) && (*(a+i)!='\0');i++)
	{
		send_a_character(a[i]);
	}
	send_a_command(0xC0); //go cursor to Second line...
}


void Locked(void)
{
	unsigned char a[16] = "Locked!!........" ;//First row one LCD
	int i;
	DDRB =0xFF; // PortB will be the 8-Output data to LCD... 
	DDRD |= (1<<2);
	DDRD |= (1<<3); // PC.0 -> Register Select , PC.1 -> E ((Set pin 0,1 as output pins))...
	_delay_ms(100);
	send_a_command(0x01);   // Sending all Clear Command 
	send_a_command(0x38);   // 16*2 Line LCD 
	send_a_command(0x0E);   // Set Screen and cursor ON! 

	// First Line!...
	for (i=0; (i<=15) && (*(a+i)!='\0');i++)
	{
		send_a_character(a[i]);
	}
	send_a_command(0xC0); //go cursor to Second line...
}
********************************************************/