/*
 * MasterMain.c
 * 
 * 
 * Author : Mostafa Ghazolley
 * Contact: MostafaGhazolley@outlook.com
 */ 


#include "Master.MCU.Definitions.h"
#include "IOuserDef.h" // #include <avr/io.h> #include <avr/iom32.h>     <<-are inside... 
#include "Keypad.h"
#include "LCD_Default.h"
#include "LCD_Messages.h"
#include "SPI.h" 
#include "Timer.h"
#include "UART.h"
//#include <avr/interrupt.h>


/*
 * Limit of pass set to 6 in loops in LCD_pass_Req02 & the while loop in the array that will take the 
 * keys pressed to save it... to use in another 
 * Entry_Pass-is global var, used to: 1-in the LCD_pass-Req02 to 
 */ 

int main(void)
{
	unsigned char counter=0;
	volatile unsigned char buffer='y';
	unsigned char NUMBER_OF_TRIES=1;	//use to max 3 entries the go to BLOCK function for specific time

	LCD_Init();
	SPI_MasterInit();
	UART_Init();
	
	sei();

	while(1)
    {	
		
/************************** 30 SEC DELAY --> ENTERING 3-TIMES PASSWORD WRONG ******************/
		if(NUMBER_OF_TRIES>=4)
		{
			LCD_Init();
			LCD_GeneralMessage(0,99,"ACCESS DENIED ","");
			LCD_Init();
			LCD_GeneralMessage(0,0,"ENTERING WRONG","PASS MANY TIMES");
			LCD_Init();
			LCD_GeneralMessage(0,10," <BLOCKED  FOR> ","Seconds");
			TIMER0_INTERRUPT_SECONDS=30;	//Setting Number of seconds
			TIMER0_IN_SECONDS_WITH_LCD(5); //arguments "position" on LCD
			NUMBER_OF_TRIES=1;
		}
		
/************************************ MODE SELECTOR ****************************************/
		else if(NUMBER_OF_TRIES<=3) //First Time Entry...
		{//first time only, will ask from user to enter mode!
			MODE=ADMIN; //First and default selection option 
			LCD_Init();
			LCD_GeneralMessage(0,0,"SELECT <->  MODE","ADMIN[X] HOST[ ]"); // LCD Start message
			RESET_PRESSED_KEY
			while(Key != '0') //and mode has been selected (press zero)
			{	
				RESET_PRESSED_KEY
				Key=GetKeyPressed(); //Get the position of pressed key...
				if(Key == '#' && MODE!=HOST)
				{
					LCD_Selector(HOST);
					MODE=HOST;
				}
				else if (Key =='*' && MODE != ADMIN)
				{
					LCD_Selector(ADMIN);
					MODE=ADMIN;
				}
				else
				{
					//nothing...
				}
				_delay_ms(50);
			}
		}
		else
		{
			//nothing..
		}
		
/*********************************** ADMIN ENTERING PASS *************************************/
		if(MODE==ADMIN)
		{
			buffer=SPI_Transmitter( MODE );
			LCD_Init();
			LCD_GeneralMessage(0,0,"Enter ADMIN pass",""); 
			while(Entry_Pass<6)// LOOP to enter pass and for 1st time till entered 6-i/p from
			{
				Key=DEFAULT_KEYPRESS; //Reset the Keypad entry
				Key=GetKeyPressed(); //Get the position of pressed key...
				PASS[Entry_Pass]=Key;
				LCD_Pass_Req(Key); //
				_delay_ms(150);
			}
			Entry_Pass=0;
		}
		
/************************************ HOST ENTERING PASS *************************************/
		else if (MODE==HOST)
		{
			buffer=SPI_Transmitter( MODE );
			LCD_Init();
			LCD_GeneralMessage(0,0,"Enter HOST pass","");
			while(Entry_Pass<6)// LOOP to enter pass and for 1st time till entered 6-i/p from
			{
				RESET_PRESSED_KEY
				Key=GetKeyPressed(); //Get the position of pressed key...
				PASS[Entry_Pass]=Key;
				LCD_Pass_Req(Key); //
				_delay_ms(150);
			}
			Entry_Pass=0;

		}
		else
		{
			//nothing..
		}
		
/************************ SPI CHECK ADMIN ENTERING PASSWORD FROM SLAVE ************************/
		for(counter=0;counter<6;counter++)
		{		// Sending 6 digits of password to slave
			buffer=SPI_Transmitter( PASS[counter] );
			_delay_ms(100);
		}
			
/************************************ SPI - PASSWORD MATCHES? **********************************/
		buffer=NONE;
		buffer=SPI_Transmitter(TRANSMISSION_COMPLETE);
		_delay_ms(50);	//Halt the system for the given time in (ms)
		if(buffer==Right_PASSWORD && MODE == ADMIN)
		{
			MODE=TRUE_ADMIN;
			LCD_Init();
			LCD_GeneralMessage(0,99,"TRUE ADMIN","");	
		}
		else if(buffer==Right_PASSWORD && MODE == HOST)
		{
			MODE=TRUE_HOST;
			LCD_Init();
			LCD_GeneralMessage(0,99,"TRUE HOST","");
		}
		else if(buffer==Wrong_PASSWORD && (MODE == HOST || MODE == ADMIN))
		{
			MODE=FALSE_PASSWORD_MODE;
		}
		else 
		{	
			//Nothing!
		}
		
/***************************** SET HOST PASSWORD? (WHILE TRUE ADMIN MODE ONLY!) *****************/
	//MODE=SPI_Transmitter(TRANSMISSION_COMPLETE);
	//_delay_ms(50);
		if(MODE == TRUE_ADMIN)
		{	//condition to SET Host pass while ADMIN-Mode only!
			LCD_Init();
			LCD_GeneralMessage(0,0,"SET HOST PASS?","YES[ ] <-> NO[X]"); // LCD Start message	
		}
		RESET_PRESSED_KEY
		while(Key!='0' && (MODE == TRUE_ADMIN || MODE == TADMIN_SET_NewHostPass))
		{
			Key=GetKeyPressed(); //Get the position of pressed key...
			if(Key == '#' && MODE!=TRUE_ADMIN)
			{
				LCD_Selector(NO);
				MODE=TRUE_ADMIN;
			}
			else if (Key =='*' && MODE != TADMIN_SET_NewHostPass)
			{
				LCD_Selector(YES);
				MODE=TADMIN_SET_NewHostPass;
			}
			else
			{
				//nothing
			}
			_delay_ms(100);	//Halt the system for the given time in (ms)
		}
		buffer=SPI_Transmitter(MODE); //Sending if again mode (if we wanna change the Host address)

/********************************* SETTING NEW-HOST PASSWORD ********************************/
		if(MODE==TADMIN_SET_NewHostPass)
		{
			LCD_Init();
			LCD_GeneralMessage(0,0,"Set New HOST pas","");
			while(Entry_Pass<6)// LOOP to enter pass and for 1st time till entered 6-i/p from
			{
				Key=GetKeyPressed(); //Get the position of pressed key...
				PASS[Entry_Pass]=Key;
				LCD_Pass_Req(Key); //
				_delay_ms(150);	
			}
			Entry_Pass=0;
			for(counter=0;counter<6;counter++)
			{		// Sending 6 digits of password to slave
				buffer=SPI_Transmitter( PASS[counter] );
				_delay_ms(100);	//Halt the system for the given time in (ms)
			}
		}
		else
		{
			//nothing
		}
	

/********************* ADJUSTING DATA IN True_HOST or TRUE_ADMIN MODES *************************/
		if(MODE==TRUE_ADMIN || MODE==TADMIN_SET_NewHostPass)
		{
			UART_Init();
			AC_STAT=UART_Rec();
			_delay_ms(35);
			AC_DATA_VALUE=UART_Rec();
		
			LCD_Init();
			LCD_GeneralMessage(0,0,"AC.ADMIN     / ","Change.Temp   °C");
			if(AC_STAT== AC_STAT_OFF) // printing out the stat of motor
			{
				LCD_Selector(AC_STAT_OFF);
				AC_STAT=AC_STAT_OFF;
			}
			else if (AC_STAT==AC_STAT_ON)
			{
				LCD_Selector(AC_STAT_ON);
				AC_STAT==AC_STAT_ON;
			}
			else
			{
				//Nothing...
			}
			LCD_TEMP_PRINT(AC_DATA_VALUE);
			RESET_PRESSED_KEY
			UART_Send(BUSY);
			while(Key != '0') //and mode has been selected (press zero)
			{
				UART_Send(BUSY);
				Key=GetKeyPressed(); //Get the position of pressed key...
				if(Key == '*' && AC_STAT== AC_STAT_OFF)
				{
					LCD_Selector(AC_STAT_ON);
					AC_STAT=AC_STAT_ON;
				}
				else if (Key =='#' && AC_STAT==AC_STAT_ON)
				{
					LCD_Selector(AC_STAT_OFF);
					AC_STAT=AC_STAT_OFF;
				}
				else if (Key =='7' && AC_DATA_VALUE>18)
				{
					AC_DATA_VALUE--;
					LCD_TEMP_PRINT(AC_DATA_VALUE);
				}
				else if (Key =='9' && AC_DATA_VALUE<38)
				{
					AC_DATA_VALUE++;
					LCD_TEMP_PRINT(AC_DATA_VALUE);
				}
				else
				{
					//nothing...
				}
				_delay_ms(5);
				UART_Send(AC_STAT);
				UART_Send(AC_DATA_VALUE);
			}
		//sending back last changing values
			
		}
		else if(MODE == TRUE_HOST)
		{
			//sending back last changing values
			UART_Init();
			AC_STAT=UART_Rec();
			_delay_ms(35);
			AC_DATA_VALUE=UART_Rec();
		
			LCD_Init();
			LCD_GeneralMessage(0,0,"AC.ADMIN     / ","Change.Temp   °C");
			if(AC_STAT== AC_STAT_OFF) // printing out the stat of motor
			{
				LCD_Selector(AC_STAT_OFF);
				AC_STAT=AC_STAT_OFF;
			}
			else if (AC_STAT==AC_STAT_ON)
			{
				LCD_Selector(AC_STAT_ON);
				AC_STAT==AC_STAT_ON;
			}
			else
			{
				//Nothing
			}
			LCD_TEMP_PRINT(AC_DATA_VALUE);
			RESET_PRESSED_KEY
			UART_Send(BUSY);
			while(Key != '0') //and mode has been selected (press zero)
			{
				UART_Send(BUSY);
				Key=GetKeyPressed(); //Get the position of pressed key...
				if(Key == '*' && AC_STAT== AC_STAT_OFF)
				{
					LCD_Selector(AC_STAT_ON);
					AC_STAT=AC_STAT_ON;
				}
				else if (Key =='#' && AC_STAT==AC_STAT_ON)
				{
					LCD_Selector(AC_STAT_OFF);
					AC_STAT=AC_STAT_OFF;
				}
				else
				{
					//nothing...
				}
				_delay_ms(5);
				//sending back last changing values
				UART_Send(AC_STAT);
				UART_Send(AC_DATA_VALUE);
			}
		}
/**********************ACCESS Denied Message**************/
		if(MODE==FALSE_PASSWORD_MODE)
		{//will reach to that condition means that the MODE hasn't changed to TRUE_XXXX
			LCD_Init();
			LCD_GeneralMessage(0,4,"  Wrong password","Try Again");
			NUMBER_OF_TRIES++;	//Max 3 wrong tries!...
		}
		else
		{
			NUMBER_OF_TRIES=1;	/*if MODE== True HOSt/ True Admin or even True admin setting new 
							host password that means he entered right password...
							so the number of tries will reset to 1
							and he come to that part of code, when he finished his operation
							or time out.*/
		}

	}//  end of while 1

    return 0;
}


ISR(TIMER0_OVF_vect)
{
	if(TIMER0_INTERRUPT_FLAG>=0 && TIMER0_INTERRUPT_FLAG<=500)
	{
		++TIMER0_INTERRUPT_FLAG;
	}
	else if(TIMER0_INTERRUPT_FLAG>=500 && TIMER0_INTERRUPT_SECONDS>=0)
	{
		TIMER0_INTERRUPT_SECONDS--;
		TIMER0_INTERRUPT_FLAG=0;
	}
	else
	{
		//nothing...
	}
	// Decrement the timer flag, each second
	
	TCNT0=0x70; //Reseting timer0 counter register.
	//to get overflow every 250 clock! ((255-6)+1).
}