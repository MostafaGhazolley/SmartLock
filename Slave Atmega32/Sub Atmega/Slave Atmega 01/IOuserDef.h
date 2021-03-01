/*
some definitions if IO ports... since it not all working in iom32.h
if #include <avr/io.h> works... no need that file...

Created by: MostafaGhazolley@outlook.com
*/
#ifndef _IOUSERDEF_H_
#define	_IOUSERDEF_H_

#include <avr/io.h>
#include <avr/delay.h>



#define F_CPU 8000000UL

#define PASSWORDS_SET			(unsigned char)0xEE

#define FIRST_ADDRESS			(unsigned char)0x00
#define ADMIN_ADDRESS			(unsigned char)0x02
#define HOST_ADDRESS			(unsigned char)0x09
#define AC_STAT_ADDRESS			(unsigned char)0x10
#define AC_TEMP_ADDRESS			(unsigned char)0x11

#define MAX_CHAR				(unsigned char)0xFF
/***MODE Variable Value names****/
#define	NONE					(unsigned char)0x00
#define ADMIN					(unsigned char)0x01
#define HOST					(unsigned char)0x02
//#define YES						(unsigned char)0x03
//#define NO						(unsigned char)0x04
#define TRUE_HOST				(unsigned char)0x05
#define TADMIN_SET_NewHostPass	(unsigned char)0x06
#define TRUE_ADMIN				(unsigned char)0x07
#define Right_PASSWORD			(unsigned char)0x08
#define Wrong_PASSWORD			(unsigned char)0x09

#define AC_STAT_ON				(unsigned char)0xB0
#define AC_STAT_OFF				(unsigned char)0xB1

#define BUSY					(unsigned char)0xCB
#define TRANSMISSION_COMPLETE	(unsigned char)0x0A

#define FAILURE					(unsigned char)0x55
#define PASS					(unsigned char)0xAA
#define EMPTY					(unsigned char)0x33



#ifndef __AVR_ATmega32__	//enable DDR/PIN,... registers on Atmega32.
#define __AVR_ATmega32__
#endif

#endif /*_IOUSERDEF_H_*/
/*
#include <avr/io.h>
#include <avr/iom32.h>
*/




