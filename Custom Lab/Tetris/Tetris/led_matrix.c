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


void LED_Pixel(unsigned char x, unsigned char y, unsigned char value, unsigned char intensity)
{
	if ((value == 0) || (value == 1))
	{
        max7219_intensity(0, intensity);
		screen[y] = SetBit(screen[y], 7 - x, value);
		max7219_digit(0, y, screen[y]);
	}
}

void LED_ClearScreen(unsigned char intensity)
{
    uint8_t i = 0;
    uint8_t j = 0;
    for(i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            LED_Pixel(i, j, 0, intensity);
        }
    }
}