/*  Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu)
 *  Lab Section: 23
 *  Assignment: Custom Lab Project: Tetris
 *  File Description: Original code containing functions using Davide Gironi’s max7219.c and .h files to interface with the MAX7219 chip
 *  
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */

#include "max7219.h"

unsigned char screen[8];

// UCR-provided set bit function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b)
{
    return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

// UCR-provided get bit function
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