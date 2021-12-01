/*
 * LCD_SPI_V2.h
 *
 * Created: 20/06/2019 13:25:07
 *  Author: Dieter
 */ 

#ifndef LCD_SPI_V2_0_H_
#define LCD_SPI_V2_0_H_

/*________________Instructions_______________________________*/
// ALL WITH REGISTER SELECT OFF, WRITE ONLY
#define LCD_CLEAR_DISPLAY 0x01				// clears data from DDRAM				t=2ms
#define LCD_RETURN_HOME 0x02				// returns to DDRAM position 0x00		t=2ms
#define LCD_ENTRY_MODE 0x04					// controls CURSOR_DIR & DISPLAY_SHIFT_ENBL
#define LCD_DISPLAY_ONOFF 0x08				// controls DISPLAY_ON & CURSOR_ON & CURSOR_BLINK
#define LCD_CURSORDISPLAY_SHIFT 0x10		// controls	DISPLAY_SHIFT & SHIFT-RIGHT
#define LCD_FUNCTION_SET 0x20				// controls DATA_LENGTH & NUMBER_LINES & FONT_TYPE
#define LCD_CGRAM_ADR 0x40					// character generation register, 8 customizable chars available, write to register by RS HIGH & bytes data
#define LCD_DDRAM_ADR 0x80					// display position register, write char to register by RS HIGH & byte data

/*_________________Data_for_instructions__________________________________*/
// entry mode set
#define CURSOR_DIR (1<<1)
#define DISPL_SHIFT_ENBL (1<<0)
// display on/off
#define DISPLAY_ON (1<<2)
#define CURSOR_ON (1<<1)
#define CURSOR_BLINK (1<<0)
// cursor or display shift
#define DISPLAY_SHIFT (1<<3)
#define SHIFT_RIGHT (1<<2)
// function set
#define DATA_LENGTH (1<<4)
#define NUMBER_LINES (1<<3)
#define FONT_TYPE (1<<2)

/*____________________LOW_LEVEL_FUNCTIONS______________________*/
// SETUP
void LCD_hardwareSetup(void);

void LCD_setup(void);

// *** CRITICAL *** to wait for some functions to complete
void smallWait(void);

// writing to LCD
void LCD_RSselect(void);

void LCD_RSdeselect(void);

char LCD_writeCharPtr(char* a);

char LCD_moveCursor(char line, char position);

void LCD_writeChar(char character);

void LCD_writeChars(char *character);

int getal[20];		// array used as buffer for conversion from number to ASCII-code
void LCD_writeNumber(int value);

// SETUP-functions
void LCD_returnHome(void);

void LCD_clear(void);

void LCD_set_EntryMode(char dir, char shift);

void LCD_on_off(char lcd, char cursor, char blink_cursor);

void LCD_set_Shift(char shift, char right);

void LCD_set_function(char dLength, char lines, char font);

/*___________________________________________________________HIGH_LEVEL_FUNCTIONS_______________________________________________________________________________*/
// write complete line + value, for monitoring values
void LCD_write_STR_VAL(char* str, char value, char line);

void LCD_writeLine(char* str, char line);

void LCD_write(char* str);

void LCD_update(char* str1, char* str2, char* str3, char* str4);

void LCD_selectLine(char line);

#endif /* LCD_SPI_V2_0_H_ */