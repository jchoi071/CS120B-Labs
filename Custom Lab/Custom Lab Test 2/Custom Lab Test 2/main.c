//max7219 output example

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "max7219.h"

int main(void) {
	max7219_init();

	uint8_t ic = 0;

	//init ic
	for(ic=0; ic<MAX7219_ICNUMBER; ic++) {
		max7219_shutdown(ic, 1); //power on
		max7219_test(ic, 0); //test mode off
		max7219_decode(ic, 0); //use led matrix
		max7219_intensity(ic, 15); //intensity
		max7219_scanlimit(ic, 7); //set number of digit to drive
	}
	uint8_t i = 0;
	for(i=0; i<8; i++)
	{
		max7219_digit(0, i, 0);
		//_delay_ms(50);
	}

	//do test loop for every ic
	while(1)
	{
		max7219_digit(0, 0, 0xFF);
		max7219_digit(0, 1, 0xFF);
		max7219_digit(0, 2, 0xFF);
		max7219_digit(0, 3, 0xFF);
		max7219_digit(0, 4, 0xFF);
		max7219_digit(0, 5, 0xFF);
		max7219_digit(0, 6, 0xFF);
		max7219_digit(0, 7, 0xFF);
		
	}
}
