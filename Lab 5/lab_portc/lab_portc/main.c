/*
 * lab_portc.c
 *
 * Created: 1/22/2019 6:00:08 PM
 * Author : Paul Choi
 */ 


#include <avr/io.h>

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; // Configure PORTA as input, initialize to 1s
    DDRC = 0xFF; PORTC = 0x00; // Configure PORTB as outputs, initialize to 0s
    unsigned char led = 0x00;
    unsigned char button = 0x00;
    while(1)
    {
        // if PA0 is 1, set PB1PB0=01, else =10
        // 1) Read inputs
        button = ~PINA & 0x01; // button is connected to A0
        // 2) Perform Computation
        if (button) { // True if button is pressed
            led = 0xFF;
            // (clear rightmost 2 bits, then set to 01)
        }
        else {
            led = 0x00;
            // (clear rightmost 2 bits, then set to 10)
        }
        // 3) Write output
        PORTC = led;
    }
}
