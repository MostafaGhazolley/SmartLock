#ifndef _MASTER_MCU_DEFINTIONS_
#define _MASTER_MCU_DEFINTIONS_

/********************************** DIFINITIONS ****************************************/
#define F_CPU 8000000UL

//MODE names and different stats with giving/receiving feedback stat
#define	NONE					(unsigned char)0x00
#define ADMIN					(unsigned char)0x01
#define HOST					(unsigned char)0x02
#define YES						(unsigned char)0x03
#define NO						(unsigned char)0x04
#define TRUE_HOST				(unsigned char)0x05
#define TADMIN_SET_NewHostPass	(unsigned char)0x06
#define TRUE_ADMIN				(unsigned char)0x07
#define Right_PASSWORD			(unsigned char)0x08
#define Wrong_PASSWORD			(unsigned char)0x09
#define FALSE_PASSWORD_MODE		(unsigned char)0x1A

// ON/OFF switcher
#define ON						(unsigned char)0xA0
#define OFF						(unsigned char)0xA1

//AC Stats
#define AC_STAT_ON				(unsigned char)0xB0
#define AC_STAT_OFF				(unsigned char)0xB1


//Transmission stat
#define BUSY					(unsigned char)0xCB
#define TRANSMISSION_COMPLETE	(unsigned char)0x0A

//Keypad needs
#define DEFAULT_KEYPRESS		(unsigned char)0xFF
#define RESET_PRESSED_KEY		Key=DEFAULT_KEYPRESS; //Reset the Keypad entry
#define Turn_ASCII				(unsigned char)0x30
/************************************* GLOBAL VARIABLES **************************************/
volatile int Entry_Pass=0;
volatile unsigned char SPI_INTERRUPT_FLAG=NONE;
//volatile unsigned char SPI_REC_DATA=NONE;
//volatile unsigned char SPI_SEND_DATA=NONE;

volatile unsigned char Tries=1; // will use that var. to max. the tries to 3!! of the pass entry
volatile unsigned char PASS[6];

volatile unsigned char ON_OFF_Switcher=0;
volatile unsigned char ADC_DATA_VALUE=0;

//AC Variables
volatile unsigned char AC_STAT=AC_STAT_OFF;
volatile unsigned char AC_DATA_VALUE=27;

volatile unsigned char Key=DEFAULT_KEYPRESS;	// Default... no entry on Keypad
unsigned char MODE=NONE;

volatile unsigned int TIMER0_INTERRUPT_FLAG=0;
volatile unsigned int TIMER0_INTERRUPT_SECONDS=0;

/****************************** Important Include libraries *******************************/
#include <avr/interrupt.h>

#endif /*_MASTER_MCU_DEFINTIONS_*/