#ifndef _I2C_H_
#define _I2C_H_
#include <avr/io.h>

/********************************* DEFINITION *****************************/
#define F_CPU 8000000UL

#define EEPROM_Write_Addess		0xA0
#define EEPROM_Read_Addess		0xA1

/*********************************** FUNTIONS ************************************/
/*
	Function Name        : I2C_Init
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize I2C communication protocol on ATmega32
							with pre-defind clock rate (as its synchronous com.).
*/
void I2C_Init(void);

/*
	Function Name        : I2C_Start
	Function Returns     : void
	Function Arguments   : void
	Function Description : start the communication.
*/
void I2C_Start(void);

/*
	Function Name        : I2C_Stop
	Function Returns     : void
	Function Arguments   : void
	Function Description : Terminate the communication.
*/
void I2C_Stop(void);

/*
	Function Name        : I2C_Write
	Function Returns     : void
	Function Arguments   : unsigned char
	Function Description : Taking a byte to send.
*/
void I2C_Write(unsigned char data);

/*
	Function Name        : I2C_Read
	Function Returns     : unsigned char
	Function Arguments   : void
	Function Description : Receiving a byte.
*/
unsigned char I2C_Read(void);

/*
	Function Name        : I2C_GetStatus
	Function Returns     : unsigned char
	Function Arguments   : void
	Function Description : return the stats of the I2C com.
*/
unsigned char I2C_GetStatus(void);

/*
	Function Name        : I2C_Read_Nack
	Function Returns     : unsigned char
	Function Arguments   : void
	Function Description : Read N-ACK from the bus (I2C).
*/
unsigned char I2C_Read_Nack(void);

/*
	Function Name        : I2C_Read_Ack
	Function Returns     : unsigned char
	Function Arguments   : void
	Function Description : Read ACK from the bus (I2C).
*/
unsigned char I2C_Read_Ack(void);
#include "IOuserDef.h" // #include <avr/io.h> #include <avr/iom32.h>     <<-are inside...
#include "I2C.c"
#endif /*_I2C_H_*/