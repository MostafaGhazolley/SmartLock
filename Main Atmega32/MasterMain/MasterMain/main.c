/*
 * MasterMain.c
 *
 * 
 * Author : Mostafa Ghazolley
 * Contact: MostafaGhazolley@outlook.com
 */ 

#define F_CPU 8000000UL

volatile int j=0; 
volatile unsigned char Tries=1; // will use that var. to max. the tries to 3!! of the pass entry
volatile unsigned char PASS[6];
volatile unsigned char Key=0xFF;	// Default... no entry on Keypad

#include "IOuserDef.h" // #include <avr/io.h> #include <avr/iom32.h>     <<-are inside... 
#include "Keypad.h"
#include "LCD_Default.h"
#include "LCD_Messages.h"// LCD_Pass_Req01 LCD_Pass_Req02 LCD_Start Access_Granted Try_Again Locked
//#include "UART_Main.h"

///void PASS_CHECK_UART(void);
//#include <avr/delay.h>
#include <util/delay.h>

/*
 * Limit of pass set to 6 in loops in LCD_pass_Req02 & the while loop in the array that will take the 
 * keys pressed to save it... to use in another 
 * j-is global var, used to: 1-in the LCD_pass-Req02 to 
 */ 

int main(void)
{
   LCD_Init();
   LCD_GeneralMessage(0,0,"Welcome!       .","Motor Drive P.1M"); // LCD Start message
   //LCD_GeneralMessage(99,4,"","bye P.1M"); // testing function to LCD_GeneralMessage
   LCD_Pass_Req01();

	while(1)
    {
      while(j<6 && Tries<=3)// LOOP to enter pass and for 1st time till entered 6-i/p from 
      {
        Key=GetKeyPressed(); //Get the position of pressed key...
        PASS[j]=Key;
        LCD_Pass_Req02(Key);
        Key=0xFF; //Reset the Keypad entry
        _delay_ms(200);
      }
      //UART_Init();
	 ///PASS_CHECK_UART(); 

     }

    return 0;
}

/*V
void PASS_CHECK_UART(void)
{	
	unsigned char i=0;
	for (i=0;i<6;i++)
	{
		UART_Send(PASS[i]); // sending index of i of array of PASS 
		if(UART_Rec()==0)
		{
			j=0;	
			 ++Tries;		
			Try_Again(); // wrong pass.. message...
			_delay_ms(100);
			if(Tries<=3)
			 {
			LCD_Pass_Req01(); // if the number of pass... entry 2 times.. will allow you to try again!
			 }
			
			if((Tries>=4)&&(j<=8))
				{
				 Locked();
				 Tries++;
					j=10; // value to lock all the function... which will be out of range all fun. and block/end the system.
				 }
		
			break;
		}
	}
}

V*/


	 /****************
    if((RETURN_UART==2)&&(Tries<=3)&&(j<=8)) //Sending the 2 arrays as argument and if they are TRUE (matched) && the flag would go FROM 6 TO 8 (3 times)
     {
      Access_Granted(); //printing out that its matched 
       j=10; //j will be 9... skipping entering that loop again
       Tries=4;
     }
     else if ((RETURN_UART==0)&&(Tries<=3)&&(j<=8))
     {
       j=0;
       Try_Again();
       _delay_ms(100);
       if(Tries<3)
        {
          LCD_Pass_Req01();
        }
       ++Tries;
     }
     else if((Tries==4)&&(j<=8))
      {
        Locked();
        Tries++;
        j=10;
      }
	  **********************/