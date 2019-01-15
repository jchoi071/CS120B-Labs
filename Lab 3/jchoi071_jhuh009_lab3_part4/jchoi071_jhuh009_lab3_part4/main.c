/*
 * jchoi071_jhuh009_lab3_part4.c
 *
 * Created: 1/15/2019 2:45:45 PM
 * Author : ucrcse
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
	unsigned char cntavail;
	unsigned char loop;

    while (1) 
    {
    }
}

