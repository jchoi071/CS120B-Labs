/*  Partner(s) Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu), Ji Houn Huh (jhuh009@ucr.edu)
 *  Lab Section: 23
 *  Assignment: Lab # 5 Exercise # 2
 *  Exercise Description: Increment and Decrement counter on hardware
 *  
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */

#include <avr/io.h>

enum IncDec_States { Start, Init, WaitRise, WaitFall, Inc, Dec, Reset } IncDec_State;

//unsigned char tmpA = 0x00;
unsigned char tmpC = 0x00;
unsigned char buttonA = 0x00;
unsigned char buttonB = 0x00;
unsigned char buttonC = 0x00;

void TickFct_IncDec()
{
	switch (IncDec_State)
	{
		case Start:
		IncDec_State = Init;
		break;
		
		case Init:
		//tmpA = PINA;
		
		IncDec_State = WaitRise;
		break;
		
		case WaitRise:
		
		buttonA = ~PINA & 0x01;
		buttonB = ~PINA & 0x02;
		//buttonC = ~PINA & 0x04;
		//if(buttonA)
		if ((buttonA) && (!(buttonB)))
		{
			IncDec_State = Inc;
			break;
		}
		//else if(buttonB)
		else if ((!(buttonA)) && (buttonB))
		{
			IncDec_State = Dec;
			break;
		}
		else if (buttonA && buttonB)
		{
			IncDec_State = Reset;
			break;
		}
		else
		{
			IncDec_State = WaitRise;
			break;
		}
		break;
		
		case WaitFall:
			buttonA = ~PINA & 0x01;
			buttonB = ~PINA & 0x02;
			//buttonC = ~PINA & 0x04;
			if (buttonA)
			{
				if(buttonB) IncDec_State = Reset;
				IncDec_State = WaitFall;
				break;
			}
			else if (buttonB)
			{
				if(buttonA) IncDec_State = Reset;
				IncDec_State = WaitFall;
				break;
			}
// 			else if (!buttonB)
// 			{
// 				IncDec_State = WaitRise;
// 				break;
// 			}
			else if ((buttonA) && (buttonB))
			{
				IncDec_State = Reset;
				break;
			}
// 			else if ((!(buttonA)) && !(buttonB))
// 			{
// 				IncDec_State = WaitRise;
// 				break;
// 			}
			else
			{
				IncDec_State = WaitRise;
				break;
			}
			break;

		case Inc:
		IncDec_State = WaitFall;
		break;
		
		case Dec:
		IncDec_State = WaitFall;
		break;
		
		case Reset:
		IncDec_State = WaitFall;
		break;
		
		default:
		IncDec_State = WaitRise;
		break;
		
	}
	
	switch (IncDec_State)
	{
		case Start:
			break;
		
		case Init:
			tmpC = 7;
			break;
		
		case WaitRise:
			PORTC = tmpC;
			break;

		case WaitFall:
		break;
		
		case Inc:
		if ((tmpC + 1) <= 9)
		{
			++tmpC;
		}
		break;
		
		case Dec:
		if ((tmpC - 1) >= 0)
		{
			tmpC = tmpC - 1;
		}
		break;
		
		case Reset:
		tmpC = 0;
		break;
		
		default:
		break;
	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs
	//unsigned char led = 0x00;
	IncDec_State = Start;
	while (1)
	{
// 		buttonA = ~PINA & 0x04;
// 		if (buttonA) { // True if button is pressed
// 			led = (led & 0xFC) | 0x01; // Sets B to bbbbbb01
// 			// (clear rightmost 2 bits, then set to 01)
// 		}
// 		else {
// 			led = (led & 0xFC) | 0x02;
// 		}
// 		PORTC = led;
 		TickFct_IncDec();
	}
}

