/*
 * SPI_328.c
 *
 * Created: 11/05/2019 12:18:59
 *  Author: Dieter
 */ 

#include <avr/io.h>
#include "SPI_328.h"

/*___________________________________SPI_______________________________datasheet_Page_132-139___*/

void SPI_Setup_Master(void)
{
	DDRB |= 0b00101100;					// make the master pins as output
	//PORTB |= (1<<0);
	SPI_Deselect();									// makes sure that the SS high is
	SPCR = (1<<SPE)|(1<<MSTR)|(3<<SPR0);
	// enable	master		3th speed option
}

void SPI_Select(void)
{
	PORTB &= ~(1<<2);					// sets slave select low (SS is active-low)
}

void SPI_Deselect(void)
{
	PORTB |= (1<<2);					// sets slave select high (SS is active-low)
}

void SPI_Sleep(void)					// this code should temporary disable the SPI communication
{
	// still no implementation
}

void SPI_Wake(void)						// this code should re enable the SPI communication after sleep
{
	// still no implementation
}

char SPI_Tranceive(char data)			// sends data to and returns data from the SPI buffer
{
	SPDR = data;						// writes to the buffer
	while((SPSR & (1<<SPIF))==0);		// waits for transmission-complete	!! cant write to the buffer when transmitting !!
	return SPDR;						// reads out the buffer
}