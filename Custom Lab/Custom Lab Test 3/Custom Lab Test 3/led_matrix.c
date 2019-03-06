/*
 * CFile1.c
 *
 * Created: 3/5/2019 2:34:02 PM
 *  Author: snesi
 */ 

#include "max7219.h"

unsigned char screen[8];

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b)
{
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k)
{
	return ((x & (0x01 << k)) != 0);
}

void LED_ClearScreen(void)
{
	uint8_t i = 0;
	for(i = 0; i < 8; i++)
	{
		max7219_digit(0, i, 0);
	}		
}

void LED_Pixel(unsigned char x, unsigned char y, unsigned char value)
{
	if ((value == 0) || (value == 1))
	{
		screen[7 - x] = SetBit(screen[7 - x], 7 - y, value);
		max7219_digit(0, 7 - x, screen[7 - x]);
	}
}