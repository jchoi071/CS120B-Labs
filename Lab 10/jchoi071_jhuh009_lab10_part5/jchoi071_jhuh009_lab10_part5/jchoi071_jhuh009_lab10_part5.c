/*  Partner(s) Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu), Ji Houn Huh (jhuh009@ucr.edu)
 *  Lab Section: 23
 *  Assignment: Lab # 10 Exercise # 5
 *  Exercise Description: Binary increment/decrement w/ synchSMs
 *  
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */

#include <avr/io.h>
#include "timer.h"

unsigned char tmpA = 0x00;
unsigned char num = 0x00;
unsigned char counter = 0;
unsigned char waitTick = 0;
unsigned char speedCounter = 1;
const unsigned char WAITSPEED = 3;

enum InputStates { Input_Start, Input_Wait, Input_IncDec } InputState;
void TickFct_Input()
{
    tmpA = ~PINA;
    switch (InputState)
    {
        case Input_Start:
            InputState = Input_Wait;
            break;
        
        case Input_Wait:
            if (((tmpA & 0x03) == 0x01) || ((tmpA & 0x03) == 0x02))
            {
                InputState = Input_IncDec;
            }
            else if ((tmpA & 0x03) == 0x03)
            {
                InputState = Input_Wait;
            }
            break;

        case Input_IncDec:
            if (((tmpA & 0x03) == 0x01) || ((tmpA & 0x03) == 0x02))
            {
                InputState = Input_IncDec;
            }
            else
            {
                InputState = Input_Wait;
            }
            break;

        default:
            InputState = Input_Wait;
            break;
    }

    switch (InputState)
    {
        case Input_Start:
            break;

        case Input_Wait:
            waitTick = 1;
            counter = 10;   //1000 ms synchSM tick from 100ms timer tick
            speedCounter = 1;
            if ((tmpA & 0x03) == 0x03)
            {
                num = 0x00;
            }
            break;

        case Input_IncDec:
            if ((tmpA & 0x03) == 0x01)
            {
                if ((num < 9) && waitTick == 1)
                {
                    ++num;
                }
            }
            else if ((tmpA & 0x03) == 0x02)
            {
                if ((num > 0) && waitTick == 1)
                {
                    --num;
                }
            }
            if (waitTick < counter)
            {
                ++waitTick;
            }
            else if ((waitTick >= counter ) && (speedCounter < 3))
            {
                waitTick = 1;
                ++speedCounter;
            }
            else if (speedCounter >= 3)
            {
                speedCounter = 1;
                counter = 4;    //400 ms synchSM tick from 100 ms timer tick
            }
            break;

        default:
            break;
    }
}

enum LightStates { Light_Start, Light_Update } LightState;
void TickFct_Lights()
{
    switch (LightState)
    {
        case Light_Start:
            LightState = Light_Update;
            break;

        case Light_Update:
            LightState = Light_Update;
            break;

        default:
            LightState = Light_Update;
            break;
    }

    switch (LightState)
    {
        case Light_Start:
            break;

        case Light_Update:
            PORTB = num;
            break;

        default:
            break;
    }
}



int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    TimerSet(100);
    TimerOn();
    InputState = Input_Start;
    LightState = Light_Start;

    while (1)
    {
        TickFct_Input();
        TickFct_Lights();
        while(!TimerFlag);
        TimerFlag = 0;
    }
}

