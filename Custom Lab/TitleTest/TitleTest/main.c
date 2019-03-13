#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "io.c"
#include "timer.h"

enum DisplayStates { Start, Display } DisplayState;
const char TOP_MSG[] = "ÿÿÿÿÿTETRISÿÿÿÿÿ";
const char BOTTOM_MSG[] = "*Instructions*        *Press any button*        *Use the potentiometer to select where to place your tetromino*        *Use button 1 to rotate your tetromino*       *Use button 2 to drop your tetromino*        *Make complete rows to clear them and earn points*";
//const char BOTTOM_MSG[] = "Woomy!"; //Test message, shorter than buffer
char buffer[] = "                ";
unsigned short pos = 0;
const unsigned char BUFFER_SIZE = 16;
unsigned short msg_size = strlen(BOTTOM_MSG);


void TickFct_DisplayMsg()
{
    unsigned char counter = 0;
    switch (DisplayState)
    {
        case Start:
        DisplayState = Display;
        break;
        
        case Display:
        DisplayState = Display;
        break;
        
        default:
        DisplayState = Display;
        break;
    }
    
    switch (DisplayState)
    {
        case Start:
        break;
        
        case Display:
        if ((!strcmp(buffer, "                ")) && (pos != 0))
        {
            pos = 0;
        }
        if (pos == 0)
        {
            buffer[BUFFER_SIZE - 1] = BOTTOM_MSG[0];
        }
        else if ((pos > 0) && (pos < msg_size))
        {
            for (counter = 1; counter < BUFFER_SIZE; ++counter)
            {
                buffer[counter - 1] = buffer[counter];
            }
            buffer[BUFFER_SIZE - 1] = BOTTOM_MSG[pos];
        }
        else
        {
            for (counter = 1; counter < BUFFER_SIZE; ++counter)
            {
                buffer[counter - 1] = buffer[counter];
            }
            buffer[BUFFER_SIZE - 1] = 0x20;
        }
        ++pos;
        LCD_DisplayStringBottom(1, buffer);
        break;
    }
}

int main(void)
{
    DDRC = 0xFF; PORTC = 0x00; // LCD data lines
    DDRD = 0xFF; PORTD = 0x00; // LCD control lines
    TimerSet(100);
    TimerOn();
    DisplayState = Start;
    // Initializes the LCD display
    LCD_init();
    LCD_DisplayStringTop(1, TOP_MSG);
    while(1)
    {
        TickFct_DisplayMsg();
        while (!TimerFlag);
        TimerFlag = 0;
    }
}


