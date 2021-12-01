/*
 * IO_Expander_V2.0.c
 *
 * Created: 9/05/2019 9:11:18
 * Author : r0711421
 */ 

#include <avr/io.h>
#include "IO_expander.h"

#define clk 8000000

#define adr 1

#define RV 0
#define RO 1
#define RL 2
#define RR 3
#define LV 4
#define LO 5
#define LL 6
#define LR 7

int klok = 0;

void wait(int millis)
{
	long delay = (millis*clk)/1000;
	 long j;
	for (j = delay; j>=0; j--)
	{
	}
}

void dommeWacht(void)
{
	for (long i = 0; i<= 40000; i++)
	{
	}
}

void showCount(void)
{
	IO_portAWrite(adr, 0xff);
	wait(5000);
	IO_portAWrite(adr, 0x00);
}

int main(void)
{
	IO_expander_setup_SPI();
	IO_portASetup(adr, 0x00);			// Out
	IO_portBSetup(adr, 0xff);			// In
	IO_portBPullup(adr, 0xff);			// pullup high
	
    while (1) 
    {
		for (int i = 0; i<=7; i++)
		{
			IO_portAWrite(adr, (1<<i));
			//wait(1000);
			dommeWacht();
			if (!(IO_portBRead(adr) & (1<<0)))
			{
				showCount();
			}
		}
		for (int i = 6; i>=0; i--)
		{
			IO_portAWrite(adr, (1<<i));
			//wait(1000);
			dommeWacht();
			if (!(IO_portBRead(adr) & (1<<0)))
			{
				showCount();
					}
		}
    }
}

