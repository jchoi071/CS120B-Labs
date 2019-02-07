/*
 * test.c
 *
 * Created: 2/5/2019 2:44:23 PM
 * Author : snesi
 */ 

#include <avr/io.h>


int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		PORTB = 0xFF;
		PORTD = 0xFF;
    }
}

