#ifndef _EXTEEPROM_H_
#define _EXTEEPROM_H_

/****************************** DEFINITION ******************************/
#define F_CPU 8000000UL

#define EEPROM_Write_Address	0xA0
#define EEPROM_Read_Address		0xA1

/******************************** FUNTIONS ******************************/
/*
	Function Name        : ExtEPROM_Write
	Function Returns     : unsigned char
	Function Arguments   : unsigned char addr
							unsigned char data
	Function Description : Write on External EEPROM via I2C giving the data and 
							address where the data will be written on the EEPROM.
*/
unsigned char ExtEPROM_Write(unsigned int addr,unsigned char data);

/*
	Function Name        : ExtEPROM_Read
	Function Returns     : unsigned char
	Function Arguments   : unsigned char addr
							unsigned char * data
	Function Description : Read from External EEPROM via I2C using an address where 
							the data will be written on and address where 
							the data will be read from the EEPROM.
*/
unsigned char ExtEPROM_Read(unsigned int addr,unsigned char *data);

#include <avr/io.h>
#include "ExtEEPROM.c"
#endif /*_EXTEEPROM_H_*/