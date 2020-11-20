/*************************************************************************************************
 * Slave Atmega 01.c
 *
 *
 *
 * Author : Mostafa Ghazolley
 * Contact: MostafaGhazolley@outlook.com
 ************************************************************************************************/

#define F_CPU 8000000UL

volatile int j=0;
volatile unsigned char Tries=1; // will use that var. to max. the tries to 3!! of the pass entry
volatile unsigned char REC_PASS[6]={0};	//Received password from the main save here...

#include "IOuserDef.h" // #include <avr/io.h> #include <avr/iom32.h>     <<-are inside...
#include "SPI.h"
#include "LCD_Default.h"
#include "LCD_Messages.h"



int main(void)
{
	unsigned char counter=0;
	SPI_SlaveInit();
    while (1) 
    {
/****************************LCD TESTING OUTPUT*********************************/
		LCD_Init();
/***************************** SPI COMMUNICATION ************************************/
		SPI_SlaveInit();
		for(counter=0;counter<6;counter++)
		{	
			REC_PASS[counter]=SPI_Transmitter('y'); //Receiving 6 digits from Master Controller
			_delay_ms(5);
		
		}
/****************testing print out what in pass array*************************/
			LCD_Init();
			LCD_GeneralMessage(0,0,"PASS RECEIVE IS:","");
		for(counter=0;counter<6;counter++)
		{
			LCD_Pass_Req02(REC_PASS[counter]);
		}

		
    }
}

