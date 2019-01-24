/*
 * jchoi071_jhuh009_lab5_part3.c
 *
 * Created: 1/24/2019 2:26:00 PM
 * Author : snesi
 */ 

#include <avr/io.h>

enum Lights_States {Start, Init, Off_Rise, Off_Fall, Wait, Light_Rise, Light_Fall} lights_state;
unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;
unsigned char dir = 0x00;
signed char count = 0x00;

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b)
{
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

void TickFct_Lights()
{
	tmpA = ~PINA & 0x01;
	
	switch (lights_state)
	{
		case Start:
			lights_state = Init;
			break;
			
		case Init:
			lights_state = Wait;
			break;
		
		case Off_Rise:
			lights_state = Off_Fall;
			break;
		
		case Off_Fall:
			if (tmpA)
			{
				lights_state = Off_Fall;
			}
			else
			{
				lights_state = Wait;
			}
			break;
			
		case Wait:
			if (tmpA)
			{
				if (!dir)
				{
					if (count < 6)
					{
						lights_state = Light_Rise;
					}
					else if (count >= 6)
					{
						lights_state = Off_Rise;
					}
					else
					{
						lights_state = Off_Rise;
					}
				}
				else
				{
					if (count >= 0)
					{
						lights_state = Light_Rise;
					}
					else if (count < 0)
					{
						lights_state = Off_Rise;
					}
					else
					{
						lights_state = Off_Rise;
					}
				}
			}
			else if (!tmpA)
			{
				lights_state = Wait;
			}
			else
			{
				lights_state = Wait;
			}
		break;
			
		case Light_Rise:
			lights_state = Light_Fall;
			break;
			
		case Light_Fall:
			if (tmpA)
			{
				lights_state = Light_Fall;
			}
			else if (!tmpA)
			{
				lights_state = Wait;
			}
			else
			{
				lights_state = Wait;
			}
			break;
			
		default:
			lights_state = Wait;
			break;
	}
	
	switch (lights_state)
	{
		case Start:
			break;
			
		case Init:
			break;
		
		case Off_Rise:
			tmpB = 0x00;
			if (dir)
			{
				dir = 0;
				count = 0;
			}
			else
			{
				dir = 1;
				count = 5;
			}
			PORTB = tmpB;
			break;
		
		case Off_Fall:
			break;	
			
		case Wait:
			break;
			
		case Light_Rise:
			tmpB = SetBit(tmpB, count, 1);
			
			if (dir)
			{
				--count;
			}
			else
			{
				++count;
			}
			
			PORTB = tmpB;
			break;
			
		case Light_Fall:
			break;
	}
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
	
	lights_state = Start;
	
    while (1) 
    {
		TickFct_Lights();
    }
}

