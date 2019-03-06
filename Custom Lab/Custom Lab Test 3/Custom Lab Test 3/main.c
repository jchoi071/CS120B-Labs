/*
 * Custom Lab Test 3.c
 *
 * Created: 3/5/2019 2:32:50 PM
 * Author : snesi
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "max7219.h"
#include "led_matrix.h"


int main(void)
{
    max7219_init();

    uint8_t ic = 0;

    //init ic
    ic = 0;
    max7219_shutdown(ic, 1); //power on
    max7219_test(ic, 0); //test mode off
    max7219_decode(ic, 0); //use led matrix
    max7219_intensity(ic, 15); //intensity
    max7219_scanlimit(ic, 7); //set number of digit to drive
	LED_ClearScreen();
	
	unsigned char i, j;
	
    while (1) 
    {
		for (j = 0; j < 8; ++j)
		{
			for (i = 0; i < 8; ++i)
			{
				LED_Pixel(i - 1, j, 0);
				LED_Pixel(i, j, 1);
				_delay_ms(17);
			}
			LED_Pixel(7, j, 0);
		}
    }
}

