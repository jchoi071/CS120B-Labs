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
	uint8_t j = 0;
	//do test loop for every ic
	for(;;) {
		for(ic=0; ic<MAX7219_ICNUMBER; ic++) {
			for(i=0; i<8; i++) {
				for(j=0; j<8; j++) {
					max7219_digit(ic, i, (1<<j));
					_delay_ms(50);
				}
				max7219_digit(ic, i, 0);
			}
		}
	}
}
