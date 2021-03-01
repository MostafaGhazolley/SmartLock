#ifndef _SPI_H_
#define _SPI_H_

/*********************** SPI PORTS DEFINITIONS ****************************/
/* Works on Atmega32 and could be easily optimized to any MCU */
extern volatile unsigned char SPI_INTERRUPT_FLAG;

#define _CONCAT(a,b) a##b
#define PORT(x) _CONCAT(PORT,x)
#define PIN(x) _CONCAT(PIN,x)
#define DDR(x) _CONCAT(DDR,x)

#define SPI B  //KEYPAD IS ATTACHED ON PORT B
#define SPI_PORT PORT(SPI)
#define SPI_DDR   DDR(SPI)
#define SPI_PIN   PIN(SPI)

#define SS 4 
#define MOSI 5
#define MISO 6
#define SCK 7

/******************************** FUNCTIONS ********************************/
/*
	Function Name        : SPI_MasterInit
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize Master SPI (MCU) Micro-Controller unit.
*/
void SPI_MasterInit(void);

/*
	Function Name        : SPI_SlaveInit
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize Slave SPI (MCU) Micro-Controller unit.
*/
void SPI_SlaveInit(void);

/*
	Function Name        : SPI_Transmitter
	Function Returns     : void
	Function Arguments   : unsigned char
	Function Description : Send and Receive data (FULL DUPLEX).
*/
unsigned char SPI_Transmitter(unsigned char DATA);


#include "IOuserDef.h" // #include <avr/io.h> #include <avr/iom32.h>     <<-are inside...
#include "SPI.c"
#endif /*_SPI_H_*/