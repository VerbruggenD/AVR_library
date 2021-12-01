/*
 * IO_expander.c
 * for MCP23017 and MCP23S17
 * 16-bit I/O-expander with SPI
 *
 * Created: 20/04/2019 17:55:13
 *  Author: Dieter Verbruggen
 */ 

#include "SPI_Master.h"
#include "IO_expander.h"
char globalOutput[8];

/*___________________________________SPI_LOW_LEVEL__________________________________*/

void IO_expander_setup_SPI(void)
{
	SPI_Setup_Master();								// run SPI setup for master operations
	IO_expander_send_SPI(0,IOCON,0b01101000);
			// externally biased addresses are not activated after boot
			// sends control-register
			// data in register: bank 0, mirror 1, seqop 1, disslw 0, haen 1, odr 0, intpol 0, not used
}

void IO_expander_send_SPI(char adr, char regist, char data)
{
	char opcode = 64 + (adr<<1);	// R/W set to 0 equals write
	SPI_Select();					// lowers SS (active -low)
	SPI_Tranceive(opcode);          // sends opcode for particular device to write
	SPI_Tranceive(regist);          // sends register to use
	SPI_Tranceive(data);            // sends the data to the register
	SPI_Deselect();					// raises SS (active -low)
}

char IO_expander_receive_SPI(char adr, char regist)
{
	char opcode = 65 + (adr<<1);		// R/W set to 1 equals read
	SPI_Select();						// lowers SS (active -low)
	SPI_Tranceive(opcode);				// sends opcode for particular device to write
	SPI_Tranceive(regist);				// sends register to use
	char data = SPI_Tranceive(0xFF);    // sends the data to the register
	SPI_Deselect();						// raises SS (active -low)
	return data;						// returns data from buffer
}

void IO_expander_global_send_SPI(char regist, char data)
{
	IO_expander_global_SPI();							// disable hardware addresses
	IO_expander_send_SPI(0,regist,data);				// write to register with address 0
	IO_expander_NONglobal_SPI();						// re enables hardware addresses
}

void IO_expander_global_receive_SPI(char regist)
{
	for (int i = 0; i<= 7; i++)									// loop to access all possible addresses
	{
		globalOutput[i] = IO_expander_receive_SPI(i,regist);	// receives data and puts it in globalOutput array
	}
}

void IO_expander_global_SPI(void)
{
	for (int i=0; i<=7; i++)							// loop to access all possible addresses
	{
		IO_expander_send_SPI(i,IOCON,0b01100000);		// alters the control-register to disable hardware address
	}
}

void IO_expander_NONglobal_SPI(void)
{
	IO_expander_send_SPI(0,IOCON,0b01101000);			// re enables all hardware addresses
	// externally biased addresses are not activated after boot
	// sends control-register
	// data in register: bank 0, mirror 1, seqop 1, disslw 0, haen 1, odr 0, intpol 0, not used
}

/*___________________________________SPI_HIGH_LEVEL____________________________________________*/

void IO_pinAHigh(char adr, char pin)
{
	char data = IO_expander_receive_SPI(adr, GPIOA);
	data |= (1<<pin);
	IO_expander_send_SPI(adr, GPIOA, data);
}

void IO_pinALow(char adr, char pin)
{
	char data = IO_expander_receive_SPI(adr, GPIOA);
	data &= ~(1<<pin);
	IO_expander_send_SPI(adr, GPIOA, data);
}

void IO_pinBHigh(char adr, char pin)
{
	char data = IO_expander_receive_SPI(adr, GPIOB);
	data |= (1<<pin);
	IO_expander_send_SPI(adr, GPIOB, data);
}

void IO_pinBLow(char adr, char pin)
{
	char data = IO_expander_receive_SPI(adr, GPIOB);
	data &= ~(1<<pin);
	IO_expander_send_SPI(adr, GPIOB, data);
}

void IO_portAWrite(char adr, char data)
{
	IO_expander_send_SPI(adr, GPIOA, data);
}

void IO_portBWrite(char adr, char data)
{
	IO_expander_send_SPI(adr, GPIOB, data);
}

char IO_portARead(char adr)
{
	char data = IO_expander_receive_SPI(adr, GPIOA);
	return data;
}

char IO_portBRead(char adr)
{
	char data = IO_expander_receive_SPI(adr, GPIOB);
	return data;
}

void IO_portASetup(char adr, char data)
{
	IO_expander_send_SPI(adr, IODIRA, data);
}

void IO_portBSetup(char adr, char data)
{
	IO_expander_send_SPI(adr, IODIRB, data);
}

void IO_portAPullup(char adr, char data)
{
	IO_expander_send_SPI(adr, GPPUA, data);
}

void IO_portBPullup(char adr, char data)
{
	IO_expander_send_SPI(adr, GPPUB, data);
}