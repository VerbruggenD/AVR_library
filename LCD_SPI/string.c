/*
 * string.c
 *
 * Created: 20/06/2019 11:02:54
 *  Author: Dieter
 */ 
#include "string.h"

char strCompare1(char *str1, char *str2)
{
	while(*str1!=0 && *str2!=0)
	{
		if (*str1 != *str2)
		{
			return 0;
		} 
		str1++;
		str2++;
	}
	if (*str1!=0 && *str2!=0)
	{
		return 0;
	}
	return 1;
}

char* strCompare2(char* str1, char* str2)		// str1 is previous, str2 is new (so compared to the first)
{
	while(*str1!=0 && *str2!=0)
	{
		if (*str1 != *str2)
		{
			return 0;
		}
		str1++;
		str2++;
	}
	return str2;
}

char strLength(char *str)
{
	char a = 0;
	while(*str!=0)
	{
		str++;
		a++;
	}
	return a;
}