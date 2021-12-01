/*
 * LCD_SPI_V2.c
 *
 * Created: 20/06/2019 13:26:42
 *  Author: Dieter
 */ 
#include <avr/io.h>
#include <ctype.h>
#include "SPI_328.h"			// SPI as MASTER for ATMEGA328P
#include "LCD_SPI_V2_0.h"
#include "string.h"

/*____________________LOW_LEVEL_FUNCTIONS______________________*/		// without SPI_(de)select in the functions, EXCEPTION: LCD_setup
																		// RS(de)select before every function according to the char write / change settings & write addresses
// SETUP
void LCD_hardwareSetup(void)
{
	DDRB |= (1<<1);			// register select as output
	LCD_RSdeselect();
}

void LCD_setup(void)
{
	LCD_hardwareSetup();
	SPI_Setup_Master();			// setups software and hardware for SPI_MASTER operation
	SPI_Select();				// slave select, function from SPI_328.h
	SPI_Tranceive(LCD_FUNCTION_SET | DATA_LENGTH | NUMBER_LINES);	// function set, 8-bit / number of lines is 2 / font type 5x8
	SPI_Tranceive(LCD_DISPLAY_ONOFF | DISPLAY_ON );					// display ON/OFF, display on / cursor and blinking off
	SPI_Tranceive(LCD_CLEAR_DISPLAY);								// clear display
	SPI_Tranceive(LCD_ENTRY_MODE | CURSOR_DIR);						// entry mode, cursor direction / shift disabled
	LCD_clear();
	LCD_returnHome();
	SPI_Deselect();
}
// *** CRITICAL *** to wait for some functions to complete
void smallWait(void)				// wait loop for LCD communication
{									// !! turn optimalisation off !!
	for (long i = 0; i<1000; i++)
	{								// dumb wait loop
	}								// *** CRITICAL ***	used with lcd_clear & return_home
}

// writing to LCD
void LCD_RSselect(void)		// register select, for writing to DDRAM & CGRAM addresses selected
{
	PORTB |= (1<<1);		// active-high
}

void LCD_RSdeselect(void)	// register deselect, for writing to control registers
{
	PORTB &= ~(1<<1);		// active-high
}

char LCD_writeCharPtr(char* a)		// writing char with pointer
{
	LCD_RSselect();
	SPDR = *a;							// writes to the buffer
	while((SPSR & (1<<SPIF))==0);		// waits for transmission-complete	!! cant write to the buffer when transmitting !!
	return SPDR;						// reads out the buffer
}

char LCD_moveCursor(char line, char position)		// write correct address to DDRAM for the line and selected char-place
{
	if (position>19)					// to prevent overwriting other chars on the display
	{
		return 0;						// !!! possibility to implement error code !!!
	}
	char DDRAM = 0;					// local var to chose position of char (includes line position after conversion)
	switch (line)				// switch case for the line selection
	{
		case 1:
		DDRAM = 0 + position;		// line 1 starts at address 0
		break;
		
		case 2:
		DDRAM = 64 + position;		// line 2 starts at address 64
		break;
		
		case 3:
		DDRAM = 20 + position;		// line 3 starts at address 20
		break;
		
		case 4:
		DDRAM = 84 + position;		// line 4 starts at address 84
		break;
	}
	LCD_RSdeselect();
	SPI_Tranceive(LCD_DDRAM_ADR | DDRAM);		// adding the position address to the DDRAM conditioning
	return 1;		// !!! possibility to implement error code !!!
}

void LCD_writeChar(char character)			// function to write a single char (in the form of the ASCII-code) 
{
	LCD_RSselect();				// register select
	SPI_Tranceive(character);
}

void LCD_writeChars(char *character)		// function to write a string/array to the LCD, with length limitation to prevent overriding
{
	char amount = strLength(character);		// function from string.h to calculate string length
	if (amount>20)			// limiting the size to row-length
	{
		amount = 20;
	}
	LCD_RSselect();						// to write chars
	for (int i=1; i<=amount; i++)
	{
		SPI_Tranceive(*character);		// writing the string with pointers
		character++;
		smallWait();	// *** CRITICAL *** , but can be a smaller wait for faster LCD-updating
	}
}

int getal[20];		// array used as buffer for conversion from number to ASCII-code
void LCD_writeNumber(int value)							// *** improvements possible ***: generation of a variable length local array to fill and use write chars-function
{
	int i = 0;
	do		// at least run once, bc if value is 0
	{
		getal[i] = value%10;
		value/=10;
		i++;
	}while(value != 0);		// do-while condition
	
	while(i>0)	// to reverse print the array so numbers will be normally visible
	{
		i--;
		LCD_writeChar(48+getal[i]);		// to write the ASCII-characters of numbers
		smallWait();
	}
}

// HIGH-SETUP-functions
void LCD_returnHome(void)		// returns to DDRAM position 00 (line 1 char 0)
{
	LCD_RSdeselect();
	SPI_Tranceive(LCD_RETURN_HOME);
	smallWait();				// *** CRITICAL ***
}

void LCD_clear(void)			// clears DDRAM & CGRAM
{
	LCD_RSdeselect();
	SPI_Tranceive(LCD_CLEAR_DISPLAY);
	smallWait();				// *** CRITICAL ***
}

void LCD_set_EntryMode(char dir, char shift)			// function to set entry-mode register
{
	LCD_RSdeselect();
	char data = LCD_ENTRY_MODE | (dir<<1) | (shift<<0);
	SPI_Tranceive(data);
}

void LCD_on_off(char lcd, char cursor, char blink_cursor)	// function to set lcd on/off register
{
	LCD_RSdeselect();
	char data = LCD_DISPLAY_ONOFF | (lcd<<2) | (cursor<<1) | (blink_cursor<<0);
	SPI_Tranceive(data);
}

void LCD_set_Shift(char shift, char right)		// function to set shift-control register
{
	LCD_RSdeselect();
	char data = LCD_CURSORDISPLAY_SHIFT | (shift<<3) | (right<<2);
	SPI_Tranceive(data);
}

void LCD_set_function(char dLength, char lines, char font)		// function to set set function register
{
	LCD_RSdeselect();
	char data = LCD_FUNCTION_SET | (dLength<<4) | (lines<<3) | (font<<2);
	SPI_Tranceive(data);
}

/*___________________________________________________________HIGH_LEVEL_FUNCTIONS_______________________________________________________________________________*/

// write complete line + value, for monitoring values
void LCD_write_STR_VAL(char* str, char value, char line)		// writes a full line with str & value combined, starts at beginning of selected line
{
	SPI_Select();
	LCD_moveCursor(line,0);
	LCD_writeChars(str);
	LCD_writeNumber(value);
	SPI_Deselect();
}

void LCD_writeLine(char* str, char line)			// writes a line (str) starting from position 0
{
	SPI_Select();
	LCD_moveCursor(line,0);
	LCD_writeChars(str);
	SPI_Deselect();
}

void LCD_write(char* str)		// writes char to the position that was set previously
{
	SPI_Select();
	LCD_writeChars(str);
	SPI_Deselect();
}

void LCD_update(char* str1, char* str2, char* str3, char* str4)
{
	SPI_Select();
	LCD_clear();
	LCD_moveCursor(1,0);
	LCD_writeChars(str1);
	LCD_moveCursor(2,0);
	LCD_writeChars(str2);
	LCD_moveCursor(3,0);
	LCD_writeChars(str3);
	LCD_moveCursor(4,0);
	LCD_writeChars(str4);
	SPI_Deselect();
}

void LCD_selectLine(char line)
{
	SPI_Select();
	LCD_moveCursor(line, 0);
	SPI_Deselect();
}