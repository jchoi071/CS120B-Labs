#include <avr/io.h>
#include "io.c"

int main(void)
{
	DDRD = 0xFF; PORTD = 0x00; // LCD data lines
	DDRA = 0xFF; PORTA = 0x00; // LCD control lines
	
	// Initializes the LCD display
	LCD_init();
	LCD_DisplayString(1, "Woomy!");
	
	while(1) {continue;}
}
