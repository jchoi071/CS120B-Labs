/*  Partner(s) Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu), Ji Houn Huh (jhuh009@ucr.edu)
 *  Lab Section: 23
 *  Assignment: Lab # 10 Exercise # 2
 *  Exercise Description: 3 sequential LEDs @ 300 ms + 1 blinking LED @ 1000 ms
 *  
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */

#include <avr/io.h>
#include "timer.h"

enum ThreeLEDStates { ThreeLEDs_Start, ThreeLEDs_S0, ThreeLEDs_S1, ThreeLEDs_S2 } ThreeLEDState;
unsigned char threeLEDs = 0x00;
unsigned char blinkingLED = 0x00;
unsigned char blinkCount = 0x01;

void TickFct_ThreeLEDs()
{
	switch(ThreeLEDState)
    {
		case ThreeLEDs_Start: ThreeLEDState = ThreeLEDs_S0; break;
		case ThreeLEDs_S0: 
			ThreeLEDState = ThreeLEDs_S1; break;
		case ThreeLEDs_S1: 
			ThreeLEDState = ThreeLEDs_S2; break;
		case ThreeLEDs_S2: 
			ThreeLEDState = ThreeLEDs_S0; break;
		default: 
			ThreeLEDState = ThreeLEDs_Start; break;
	}

	switch(ThreeLEDState)
    {
		case ThreeLEDs_Start: 
			break;
				
		case ThreeLEDs_S0:
			threeLEDs = 0x01; 
			break;
		case ThreeLEDs_S1:
			threeLEDs = 0x02; 
			break;
		case ThreeLEDs_S2: 
			threeLEDs = 0x04; 
			break;
		default: break;
	}
}
enum BlinkLEDStates {BlinkLED_Start, BlinkLED_Blink} BlinkLEDState;
void TickFct_BlinkLed()
{
	switch(BlinkLEDState)
    {
		case BlinkLED_Start:
			BlinkLEDState = BlinkLED_Blink;
			break;
		
		case BlinkLED_Blink:
            BlinkLEDState = BlinkLED_Blink;
			break;

		default:
			BlinkLEDState = BlinkLED_Start;
			break;
	}
	switch(BlinkLEDState)
    {
		case BlinkLED_Start:
			break;

		case BlinkLED_Blink:
			if(blinkCount == 0x01)
            {
				blinkingLED = 0x08;
				blinkCount = 0x00;
			}
			else
            {
                blinkingLED = 0x00;
				blinkCount = 0x01;
			}
			break;

		default:
			break;
	}
}

enum CombineStates { CombineLED_Start, CombineLED_Combine } CombineState;
void TickFct_CombineLEDs()
{
    switch (CombineState)
    {
        case CombineLED_Start:
            CombineState = CombineLED_Combine;
            break;

        case CombineLED_Combine:
            CombineState = CombineLED_Combine;
            break;

        default:
            CombineState = CombineLED_Combine;
            break;
    }

    switch (CombineState)
    {
        case CombineLED_Start:
            break;

        case CombineLED_Combine:
            PORTB = threeLEDs + blinkingLED;
            break;

        default:
            break;
    }
}

int main(void)
{
	unsigned long BL_elapsedTime = 0;
	unsigned long TL_elapsedTime = 0;
    unsigned long CM_elapsedTime = 0;
	const unsigned long timerPeriod = 75;

	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(timerPeriod);
	TimerOn();
	ThreeLEDState = ThreeLEDs_Start;
	BlinkLEDState = BlinkLED_Start;
    CombineState = CombineLED_Start;

	while (1)
	{
        if (TL_elapsedTime >= 300)
        {
            TickFct_ThreeLEDs();
            TL_elapsedTime = 0;
        }

		if (BL_elapsedTime >= 1000)
        {
			TickFct_BlinkLed();
			BL_elapsedTime = 0;
		}

        if (CM_elapsedTime >= 75)
        {
            TickFct_CombineLEDs();
            CM_elapsedTime = 0;
        }

		while(!TimerFlag);
		TimerFlag = 0;
		BL_elapsedTime += timerPeriod;
		TL_elapsedTime += timerPeriod;
        CM_elapsedTime += timerPeriod;
	}
}

