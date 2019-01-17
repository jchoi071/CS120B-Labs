/*	Partner(s) Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu), Ji Houn Huh (jhuh009@ucr.edu)
 *	Lab Section: 23
 *	Assignment: Lab # 3 Exercise # 5
 *	Exercise Description: Passenger seat weight sensor
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b)
{
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}


int main(void)
{
    //turns off JTAG register - use optimize by size

    DDRD = 0x00; PORTD = 0xFF; // Configure port D's 8 pins as inputs
    DDRB = 0xFE; PORTB = 0x01; // Configure first pin of port B as input, and the other pins as outputs
	
    unsigned char tmpD = 0x00;
	unsigned char tmpB = 0x00;
	unsigned short weight = 0x0000;
	
	const unsigned char ULIMIT = 70;
	const unsigned char LLIMIT = 5;
	
    while (1) 
    {
		tmpD = PIND;
	    tmpB = PINB & 0x01;
		
		weight = 0;
		weight += tmpD;
		weight = weight << 1;
		weight += tmpB & 0x01;
		
		if (weight >= ULIMIT)
		{
			tmpB = SetBit(tmpB, 1, 1);
		}
		else if ((weight > LLIMIT) && (weight < ULIMIT))
		{
			tmpB = SetBit(tmpB, 2, 1);	
		}
		else
		{
			tmpB = tmpB & 0xFD;
		}
		
		tmpB = tmpB & 0x06;
		PORTB = tmpB;
		tmpB = 0x00;
    }
}

