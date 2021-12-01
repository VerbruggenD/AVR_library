/*
 * LCD_SPI_V2.c
 *
 * Created: 20/06/2019 13:22:56
 * Author : Dieter
 */ 

#include <avr/io.h>
#include "SPI_328.h"
#include "LCD_SPI_V2_0.h"
#include "string.h"

void wait(void)
{
	for (long i = 0; i<=200000; i++)
	{
	}
}

//int main(void)
//{
	//LCD_setup();
	//int i = 0;
	//SPI_Select();
	//LCD_clear();
	//LCD_moveCursor(1,3);
	//LCD_RSselect();
	//LCD_writeChars("Hello World!!!");
	////LCD_RSdeselect();
	//SPI_Deselect();
    ///* Replace with your application code */
    //while (1) 
    //{
		//LCD_RSdeselect();
		//SPI_Select();
		//LCD_moveCursor(2,9);
		////LCD_clear();
		////LCD_RSselect();
		//LCD_writeNumber(i);
		////LCD_RSdeselect();
		//SPI_Deselect();
		//wait();
		//i++;
    //}
//}

//int main(void)
//{
	//LCD_setup();
	//LCD_update("Hello", "is it me", "youre", "looking for");
	//while(1)
	//{
		//
	//}
//}

//int main(void)
//{
	//LCD_setup();
	//LCD_clear();
	//LCD_writeLine("Hello",1);
	//LCD_writeLine("is it me",2);
	//LCD_writeLine("youre",3);
	//LCD_writeLine("looking for",4);
	//while(1)
	//{
//
	//}
//}

int main(void)
{
	LCD_setup();
	LCD_clear();
	LCD_write_STR_VAL("De waarde is: ", 123,1);
	LCD_write("°C");
	LCD_selectLine(3);
	LCD_write("adzuobdhzigyzyçg");
	while(1)
	{

	}
}