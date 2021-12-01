/*
 * arduino expander test.c
 *
 * Created: 11/05/2019 12:11:53
 * Author : Dieter
 */ 

#include <avr/io.h>
#include "IO_expander.h"
#include "SPI_328.h"

#define adr 0x01

void delay(void)
{
	for (long i=0; i<=160000; i++)
	{
	}
}


//int main(void)
//{
	//IO_expander_setup_SPI();
	//IO_portASetup(adr, 0);		// outputs
//
    //
    //while (1) 
    //{
		//IO_pinAHigh(adr, 0);
		//delay();
		//IO_pinAHigh(adr, 1);
		//delay();
		//IO_pinALow(adr, 1);
		//delay();
		//IO_pinALow(adr, 0);
		//delay();
    //}
//}

int main(void)
{
	IO_expander_setup_SPI();
	IO_portASetup(adr, 0);		// outputs
	IO_portBSetup(adr, 0xff);
	IO_portBPullup(adr, 0xff);
	
	while (1)
	{
		if (IO_portBRead(adr)!=0xff)
		{
			IO_pinAHigh(adr, 0);
			IO_pinALow(adr, 1);
		}
		else
		{
			IO_pinALow(adr, 0);
			IO_pinAHigh(adr, 1);
		}
	}
}
