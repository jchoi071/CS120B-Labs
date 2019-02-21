/*
 * test.c
 *
 * Created: 2/12/2019 2:58:34 PM
 * Author : snesi
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    unsigned char tmpA = 0x00;
	unsigned char lights = 0x00;
	unsigned char speaker = 0x00;
	
    while (1) 
    {
		tmpA = ~PINA;
		
		if (tmpA & 0x01)
		{
			lights = 0x0F;
		}
		else
		{
			lights = 0x00;
		}
		
		if (tmpA & 0x02)
		{
			speaker = 0xF0;
		}
		else
		{
			speaker = 0x00;
		}
		PORTB = lights + speaker;
    }
}

