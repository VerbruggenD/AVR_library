/*
 * SPI.h
 *
 * Created: 20/04/2019 18:00:41
 *  Author: Dieter Verbruggen
 */ 


#ifndef SPI_H_
#define SPI_H_

/*___________________________________SPI_______________________________datasheet_Page_132-139___*/

void SPI_Setup_Master(void);	// sets up the ATM as SPI master

void SPI_Select(void);		// selects the slave that is spoken to

void SPI_Deselect(void);	// deselects the slave that is spoken to

void SPI_Sleep(void);			// temporarily disables SPI communication 
// still no implementation

void SPI_Wake(void);			// re enables SPI communication after sleep
// still no implementation

char SPI_Tranceive(char data);	// actual transmitting and receiving of bytes
								// sends data and returns data		==>		to only send data, send your data, ignore return
								//											to only receive data, send 0xff, read the return data

#endif /* SPI_H_ */