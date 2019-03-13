#ifndef __io_h__
#define __io_h__

void LCD_init();
void LCD_ClearScreen(void);
void LCD_ClearScreenTop(void);
void LCD_ClearScreenBottom(void);
void LCD_WriteCommand (unsigned char Command);
void LCD_Cursor (unsigned char column);
void LCD_DisplayString(unsigned char column ,const unsigned char *string);
void LCD_DisplayStringTop(unsigned char column ,const unsigned char *string);
void LCD_DisplayStringBottom(unsigned char column ,const unsigned char *string);
void delay_ms(int miliSec);
#endif

