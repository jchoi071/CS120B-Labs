/*  Partner(s) Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu), Ji Houn Huh (jhuh009@ucr.edu)
 *  Lab Section: 23
 *  Assignment: Lab # 10 Exercise # 3
 *  Exercise Description: 3 sequential LEDs @ 300 ms + 1 blinking LED @ 1000 ms + PWM @ 4 ms, 50% duty cycle
 *  
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */

#include <avr/io.h>
#include "timer.h"

unsigned char tmpA = 0x00;

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

enum PWMStates { PWM_Start, PWM_Wait, PWM_On, PWM_Off } PWMState;
const unsigned char PULSE = 1;
unsigned char PWM_counter = 0;
unsigned char pwm;
void TickFct_PWM()
{
    tmpA = ~PINA;
    switch (PWMState)
    {
        case PWM_Start:
            PWMState = PWM_Wait;
            break;

        case PWM_Wait:
            if ((tmpA & 0x04) == 0x04)
            {
                PWMState = PWM_On;
            }
            else
            {
                PWMState = PWM_Wait;
            }
            break;

        case PWM_On:
            if (((tmpA & 0x04) == 0x04))
            {
                if (PWM_counter < PULSE)
                {
                    PWMState = PWM_On;
                }
                else
                {
                    PWMState = PWM_Off;
                }
            }
            else
            {
                PWMState = PWM_Wait;
            }
            break;

        case PWM_Off:
            if ((tmpA & 0x04) == 0x04)
            {
                if (PWM_counter < PULSE)
                {
                    PWMState = PWM_Off;
                }
                else
                {
                    PWMState = PWM_On;
                }
            }
            else
            {
                PWMState = PWM_Wait;
            }
            break;

        default:
            PWMState = PWM_Wait;
            break;
    }

    switch (PWMState)
    {
        case PWM_Start:
            break;

        case PWM_Wait:
            PWM_counter = 0;
            pwm = 0;
            break;

        case PWM_On:
            if (PWM_counter < PULSE)
            {
                ++PWM_counter;
                pwm = 0x10;
            }
            else
            {
                PWM_counter = 0;
            }
            break;

        case PWM_Off:
            if (PWM_counter < PULSE)
            {
                ++PWM_counter;
                pwm = 0x00;
            }
            else
            {
                PWM_counter = 0;
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
        PORTB = threeLEDs + blinkingLED + pwm;
        break;

        default:
        break;
    }
}

int main(void)
{
    unsigned long BL_elapsedTime = 0;
    unsigned long TL_elapsedTime = 0;
    unsigned long PWM_elapsedTime = 0;
    unsigned long CM_elapsedTime = 0;
    const unsigned long timerPeriod = 1;

    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    TimerSet(timerPeriod);
    TimerOn();
    ThreeLEDState = ThreeLEDs_Start;
    BlinkLEDState = BlinkLED_Start;
    PWMState = PWM_Start;
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

        if (PWM_elapsedTime >= 2)
        {
            TickFct_PWM();
            PWM_elapsedTime = 0;
        }

        if (CM_elapsedTime >= 1)
        {
            TickFct_CombineLEDs();
            CM_elapsedTime = 0;
        }

        while(!TimerFlag);
        TimerFlag = 0;
        BL_elapsedTime += timerPeriod;
        TL_elapsedTime += timerPeriod;
        PWM_elapsedTime += timerPeriod;
        CM_elapsedTime += timerPeriod;
    }
}
