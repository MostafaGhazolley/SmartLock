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

#include "IOuserDef.h" // #include <avr/io.h> #include <avr/iom32.h>     <<-are inside...	
#include <avr/interrupt.h> //ADC
#include "SPI.h"
//#include "LCD_Default.h"
//#include "LCD_Messages.h"
#include "I2C.h"
#include "ExtEEPROM.h"
#include "UART.h"

//volatile unsigned char Tries=1; // will use that var. to max. the tries to 3!! of the pass entry
volatile unsigned char REC_PASS[6]={0};	//Received password from the main save here...
volatile unsigned char SPI_INTERRUPT_FLAG=NONE;
volatile unsigned char SPI_REC_DATA=NONE;
volatile unsigned char SPI_SEND_DATA=NONE;

int main(void)
{
	unsigned char counter=0;
	unsigned char buffer=0;
	unsigned char ExtEEPROM_buffer=0;
	unsigned char PASSWORD=EMPTY;
	unsigned char Rec_MODE = EMPTY;
	unsigned char ADJUSTING_DATA_STAT=NONE;

	sei();
	UART_Init();
	SPI_SlaveInit();
	I2C_Init();
	/*************************** CHECK IF EEPROM New/CHANGED **********************/
	/*
	* put first address in EEPROM as a flag
	* if it changed to (0xEE) then the PASSWORD of host has changed before...
	* if not and the EEPROM is new (first time usage)
	* i will write the default Password of ADMIN & host and also, will change the flag to 0xEE
	* to stop repeating the write default password.
	*/
	unsigned char DELETE_IN_PRACTICAL_CODE =1;	
	ExtEPROM_Read(FIRST_ADDRESS,&ExtEEPROM_buffer);
	if ( ExtEEPROM_buffer != PASSWORDS_SET || DELETE_IN_PRACTICAL_CODE)
	//if ( ExtEEPROM_buffer != PASSWORDS_SET)
	{	
/*	in practical code, delete that if condition and write:
	if ( ExtEEPROM_buffer != PASSWORDS_SET)
	why? 
	in my testing and debugging the flag in EEPROM is written once, so i can't
	edit/test my changes in that if condition, as the flag is already written 
	once, so on that if condition is entered once, and thats okay (what we already
	want) in real life.
*/

/*******************Default ADMIN & HOST PASSWORD DATA IN EEPROM*****************/
		for(counter=0;counter<6;counter++)
		{
			ExtEPROM_Write((ADMIN_ADDRESS + counter) , (0x31+ counter) );
			_delay_ms(25);
			ExtEPROM_Write((HOST_ADDRESS  + counter ), (0x31+ counter) );
			_delay_ms(25);
		}
		
/************************ DEFAULT AC DATA (OFF/27°C) ******************/
		//ExtEPROM_Write( AC_STAT_ADDRESS , AC_STAT_OFF +0x30);
		ExtEPROM_Write(AC_STAT_ADDRESS, AC_STAT_OFF);
		_delay_ms(30);
		ExtEPROM_Write(AC_TEMP_ADDRESS, 27 );
		_delay_ms(30);	
		
/****************DEFAULT INDICATOR FLAG TO EEPROM INITIALIZATION*****************/
		ExtEPROM_Write(FIRST_ADDRESS, PASSWORDS_SET );
		_delay_ms(30);
	}
	else
	{
			//nothing..
	}
	
    while (1) 
    {
		
		DDRA=0xFF;
		//PORTA=0x00;
		PORTA=0b11111111;
		PASSWORD=NONE;	//resetting all used variables
		Rec_MODE=NONE;
		ADJUSTING_DATA_STAT=NONE;
		buffer=0;
		
/*********************** SPI-Receiving MODE and PASS *******************/
		Rec_MODE = SPI_Transmitter(TRANSMISSION_COMPLETE);	//first receiving message contains the mode
		for(counter=0;counter<6;counter++)
		{
			REC_PASS[counter]=SPI_Transmitter(TRANSMISSION_COMPLETE); //Receiving 6 digits from Master Controller
			_delay_ms(50);
		}

/****************************CHECKING PASSWORD MODE DEPENDING ******************/
		if(Rec_MODE == ADMIN && PASSWORD==NONE)
		{
			for(counter=0;counter<6;counter++)
			{	
				ExtEPROM_Read(ADMIN_ADDRESS+counter,&ExtEEPROM_buffer);
				if(REC_PASS[counter]!=ExtEEPROM_buffer)
				{
					PASSWORD=Wrong_PASSWORD;
					counter=6;	//get out of loop
				}
				else
				{
					PASSWORD=Right_PASSWORD;
				}
			}
			
			if(PASSWORD==Right_PASSWORD)
			{
				Rec_MODE=TRUE_ADMIN;
			}
			else
			{
				//nothing
			}//end of checking Admin user entering right password.
		}//End Admin checking all entries
		else if (Rec_MODE == HOST && PASSWORD == NONE)
		{
			for(counter=0;counter<6;counter++)
			{
				ExtEPROM_Read(HOST_ADDRESS+counter,&ExtEEPROM_buffer);
				if(REC_PASS[counter]!=ExtEEPROM_buffer)
				{
					PASSWORD=Wrong_PASSWORD;
					counter=6;	//get out of loop
				}
				else
				{
					PASSWORD=Right_PASSWORD;
				}
			}
			
			if(PASSWORD==Right_PASSWORD)
			{
				Rec_MODE=TRUE_HOST;
			}
			else
			{
				//nothing
			}//end of checking Admin user entering right password.
		}
		else
		{
			//nothing..
		}
		
/**************** SPI SEND BACK FEEDBACK IF PASSWORD MATCHES? ***********/
			buffer=SPI_Transmitter(PASSWORD); //if the password right go to the next step
			_delay_ms(50);
			Rec_MODE=SPI_Transmitter(TRANSMISSION_COMPLETE); //getting if we will change HOST pass on EEPROM
			_delay_ms(50);	
	
/****************** CHANGING HOST PASS ON EEPROM ********************/
		if(Rec_MODE==TADMIN_SET_NewHostPass)
		{
			for(counter=0;counter<6;counter++)
			{
				REC_PASS[counter]=SPI_Transmitter(TRANSMISSION_COMPLETE); //Receiving 6 digits from Master Controller
				_delay_ms(50);
			}
			for(counter=0;counter<6;counter++)
			{
				ExtEPROM_Write(HOST_ADDRESS+counter,REC_PASS[counter]);
				_delay_ms(35);
			}
			
		}
		else
		{
			//nothing..
		}
	
/************* DATA ADJUSTING FROM ADMIN OR HOST ***************/
		if(
		(Rec_MODE==TADMIN_SET_NewHostPass || Rec_MODE==TRUE_ADMIN 
		|| Rec_MODE==TRUE_HOST))
		{
			ExtEPROM_Read(AC_STAT_ADDRESS,&ExtEEPROM_buffer);
			UART_Send(ExtEEPROM_buffer);
			_delay_ms(250);
			ExtEPROM_Read(AC_TEMP_ADDRESS,&ExtEEPROM_buffer);
			UART_Send(ExtEEPROM_buffer);
			ADJUSTING_DATA_STAT=UART_Rec();
/************************** MAIN MCU ADJUSTING DATA ******************************/
			while(ADJUSTING_DATA_STAT==BUSY)
			{
				ADJUSTING_DATA_STAT=UART_Rec();
				if(ADJUSTING_DATA_STAT==BUSY)
				{
					ExtEEPROM_buffer=UART_Rec();
					ExtEPROM_Write(AC_STAT_ADDRESS,ExtEEPROM_buffer);
					_delay_ms(50);
					ExtEEPROM_buffer=UART_Rec();
					ExtEPROM_Write(AC_TEMP_ADDRESS,ExtEEPROM_buffer);
					_delay_ms(50);
				}
				else
				{
					//ADJUSTING_DATA_STAT==TRANSMISSION_COMPLETE;
				}
			}
			
		}
		else
		{
			//Nothing...
		}		
		
    }	//End of while 1
	
	return 0;
}

ISR(ADC_vect)
{
	
}