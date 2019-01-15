/*	Partner(s) Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu), Ji Houn Huh (jhuh009@ucr.edu)
 *	Lab Section: 23
 *	Assignment: Lab # 3 Exercise # 4
 *	Exercise Description: Map upper nibble of A to lower nibble of B, and lower nibble of A to upper nibble of C
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>


int main(void)
{
	//turns off JTAG register - use optimize by size
	MCUCR = 0x80;
	MCUCR = 0x80;

	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs
	
	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;

    while (1) 
    {
		tmpA = PINA;
		tmpB = (tmpA & 0xF0) >> 4;
		tmpC = (tmpA & 0x0F) << 4;
		
		PORTB = tmpB;
		PORTC = tmpC;
		
		tmpB = 0x00;
		tmpC = 0x00;
    }
}

