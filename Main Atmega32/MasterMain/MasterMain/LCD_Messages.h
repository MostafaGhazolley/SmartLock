#ifndef _LCD_MESSAGE_H_
#define _LCD_MESSAGE_H_

/****** DEFINITIONS ******/
#define DEFAULT_KEYPRESSED 	(unsigned char)0xFF
#define LOWER_NIBBLE		(unsigned char)0xF0
#define	cmd_FOURWIRES 		(unsigned char)0x02
#define cmd_TWOLINES		(unsigned char)0x28
#define cmd_CURSORON		(unsigned char)0x0E
#define cmd_CURSOROFF		(unsigned char)0x0C
#define	cmd_INCREMENTRIGHT	(unsigned char)0x06
#define	cmd_CLEARSIPLAY		(unsigned char)0x01
#define	cmd_GOHOME			(unsigned char)0x02
#define	cmd_SECONDLINE		(unsigned char)0xC0
#define	cmd_RIGHTSHIFT		(unsigned char)0x14
/***************************** MAIN FILE DEFINITIONS ***************************/
#define ADMIN				(unsigned char)0x01
#define HOST				(unsigned char)0x02
	
/*********************************** FUNCTIONS **********************************/
/*
	Function Name        : LCD_GeneralMessage
	Function Returns     : void
	Function Arguments   : L1 : -its number of spaces before start to print out on LCD
								from 0 to 15 (16 digit of LCD)
								99 indicates thats its empty. (no text will be printed out on LCD of line 1)
						   L2 : -its number of spaces before start to print out on LCD
								from 0 to 15 (16 digit of LCD)
								99 indicates thats its empty. (no text will be printed out on LCD of line 2)
						   a[] :String or array of characters thats its size define by the number of elements that will be sent
								and what is inside that string, will be print out in the first line of LCD.
						   b[] :String or array of characters thats its size define by the number of elements that will be sent
	Function Description : write 2x16 LCD both lines, which the first two arguments takes a number
						   where it should start from (number of white spaces before the string)
						   from 0 to 16... and 99 represent nothing.
						   the last two argument are the strings that will be print out on LCD.
*/	
void LCD_GeneralMessage(unsigned char L1,unsigned char L2,char a[],char b[]);

/*
	Function Name        : LCD_Selector
	Function Returns     : void
	Function Arguments   : unsigned char
	Function Description : used to change on LCD location of the selected (X)
							stats and clearing also the old selection.
*/	
void LCD_Selector(unsigned char selector);

//void LCD_String(unsigned char Line,unsigned char Spaces,unsigned char STRING[]);


/*
	Function Name        : LCD_Pass_Req
	Function Returns     : void
	Function Arguments   : unsigned char
	Function Description : writing the entered password out and save the entered 
		`					number in the global Array PASS with limit of
							six-index.
*/
void LCD_Pass_Req(unsigned char);

/*
	Function Name        : LCD_TEMP_PRINT
	Function Returns     : void
	Function Arguments   : unsigned char
	Function Description : printing out the temperature that giving as an argument
							to this function (in ASCII).
*/
void LCD_TEMP_PRINT(unsigned char);

#include "Master.MCU.Definitions.h"
#include "LCD_Messages.c"
#endif /*_LCD_MESSAGE_H_*/



/****** not using anymore ******/

/*
	Function Name        : LCD_Start
	Function Returns     : void
	Function Arguments   : void
	Function Description : .
*/
//void LCD_Start(void); // Start output welcome on LCD

/*
	Function Name        : Access_Granted
	Function Returns     : void
	Function Arguments   : void
	Function Description : .
*/
//void Access_Granted(void);

/*
	Function Name        : Try_Again
	Function Returns     : void
	Function Arguments   : void
	Function Description : .
*/
//void Try_Again(void);

/*
	Function Name        : LCD_Pass_Req01
	Function Returns     : void
	Function Arguments   : void
	Function Description : .
*/
/*
	Function Name        : LCD_Pass_Req01
	Function Returns     : void
	Function Arguments   : void
	Function Description : .

void LCD_Pass_Req01(void);

//void Locked(void);
*/