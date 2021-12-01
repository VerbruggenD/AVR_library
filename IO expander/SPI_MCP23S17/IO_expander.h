/*
 * IO_expander.h
 * for MCP23017 and MCP23S17
 * 16-bit I/O-expander with I2C or SPI
 *
 * Created: 20/04/2019 17:58:05
 *  Author: Dieter Verbruggen
 */ 


#ifndef IO_EXPANDER_H_
#define IO_EXPANDER_H_

/*_____________________register_definitions_specific_for_bank_0__________________*/

#define IOCON 0x0A      // io-expander configuration register

// PORT A
#define IODIRA 0x00     // IO direction register: 0=OUT, 1=IN
#define IPOLA 0x02      // input polarity register: 0=non inverted, 1=inverted
#define GPINTENA 0x04   // interrupt-on-change pins
#define DEFVALA 0x06    // default value register --> for GPINTEN & INTCON
#define INTCONA 0x08    // interrupt-on-change control register
#define GPPUA 0x0C      // GPIO pull-up resistor register: 0=disabled, 1=enabled
#define INTFA 0x0E      // interrupt flag register
#define INTCAPA 0x10    // interrupt captured value for port register
#define GPIOA 0x12      // general purpose IO port register: 0=LOW, 1=HIGH
#define OLATA 0x14      // output latch register: 0=LOW, 1=HIGH

// PORT B
#define IODIRB 0x01		//
#define IPOLB 0x03		//
#define GPINTENB 0x05	//
#define DEFVALB 0x07	//
#define INCONB 0x09		//	same registers, only for expander-port B
#define GPPUB 0x0D		//
#define INTFB 0x0F		//
#define INTCAPB 0x11	//
#define GPIOB 0x13		//
#define OLATB 0x15		//

/*______________________________functions_used_______________________________*/

/*___________________________________SPI____________________________________*/

void IO_expander_setup_SPI(void);	// function to set: - use register bank 0
									//                  - use hardware address
									//                  - use INTpins together
									//                  - don't use sequential register operation
									//					- setups SPI as master

void IO_expander_send_SPI(char adr, char regist, char data);		// sends byte to the specified register and specified IO_expander

char IO_expander_receive_SPI(char adr, char regist);				// receives byte from specified register and specified IO_expander

void IO_expander_global_send_SPI(char regist, char data);			// sends 1 byte to a specific register of all connected SPI-expanders

void IO_expander_global_receive_SPI(char regist);					// receives data from all connected SPI-expanders in specific register
																	// uses char globalOutput[8] as variable

void IO_expander_global_SPI(void);									// bypasses hardware addresses of all connected SPI-expanders, and makes them 0

void IO_expander_NONglobal_SPI(void);							// re enables all the hardware addresses


/*___________________________________SPI_HIGH_LEVEL____________________________________________*/

void IO_pinAHigh(char adr, char pin);				// make 1 pin on portA high 

void IO_pinALow(char adr, char pin);				// make 1 pin on portA low H

void IO_pinBHigh(char adr, char pin);				// make 1 pin on portB high 

void IO_pinBLow(char adr, char pin);				// make 1 pin on portB low

void IO_portAWrite(char adr, char data);			// set all pins on port A 0=LOW 1=HIGH

void IO_portBWrite(char adr, char data);			// set all pins on port B 0=LOW 1=HIGH

char IO_portARead(char adr);						// read all pins on portA

char IO_portBRead(char adr);						// read all pins on portB

void IO_portASetup(char adr, char data);			// define IO portA

void IO_portBSetup(char adr, char data);			// define IO portB

void IO_portAPullup(char adr, char data);			// set pullups on portA

void IO_portBPullup(char adr, char data);			// set pullups on portB

#endif /* IO_EXPANDER_H_ */