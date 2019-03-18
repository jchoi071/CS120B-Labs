/*  Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu)
 *  Lab Section: 23
 *  Assignment: Custom Lab Project: Tetris
 *  File Description: Original header file for led_matrix.c
 *  
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */

#ifndef LED_MATRIX_H
#define LED_MATRIX_H

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b);
unsigned char GetBit(unsigned char x, unsigned char k);
void LED_ClearScreen(unsigned char intensity);
void LED_Pixel(unsigned char x, unsigned char y, unsigned char value, unsigned char intensity);

#endif