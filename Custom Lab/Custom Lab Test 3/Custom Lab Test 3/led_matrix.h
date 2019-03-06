/*
 * led_matrix.h
 *
 * Created: 3/5/2019 2:34:22 PM
 *  Author: snesi
 */ 

#ifndef LED_MATRIX_H
#define LED_MATRIX_H

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b);
unsigned char GetBit(unsigned char x, unsigned char k);
void LED_ClearScreen(void);
void LED_Pixel(unsigned char x, unsigned char y, unsigned char value);

#endif