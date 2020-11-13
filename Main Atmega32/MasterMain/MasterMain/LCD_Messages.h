#ifndef _LCD_MESSAGE_H_
#define _LCD_MESSAGE_H_
	
void LCD_GeneralMessage(unsigned char L1,unsigned char L2,char a[],char b[]);

void LCD_Pass_Req01(void);
void LCD_Pass_Req02(unsigned char Key);
void LCD_Start(void); // Start output welcome on LCD

void Access_Granted(void);
void Try_Again(void);
void Locked(void);

#include "LCD_Messages.c"
#endif /*_LCD_MESSAGE_H_*/