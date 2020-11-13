/*
some definitions if IO ports... since it not all working in iom32.h
if #include <avr/io.h> works... no need that file...

Created by: MostafaGhazolley@outlook.com
*/
#include <avr/io.h>
#ifndef __AVR_ATmega32__	//enable DDR/PIN,... registers on Atmega32.
#define __AVR_ATmega32__
#endif

/*
#include <avr/io.h>
#include <avr/iom32.h>
*/

#define _CONCAT(a,b) a##b
#define PORT(x) _CONCAT(PORT,x)
#define PIN(x) _CONCAT(PIN,x)
#define DDR(x) _CONCAT(DDR,x)

