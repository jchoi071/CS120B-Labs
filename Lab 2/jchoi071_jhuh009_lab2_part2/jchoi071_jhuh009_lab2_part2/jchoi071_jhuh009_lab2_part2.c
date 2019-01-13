/*	Partner(s) Name & E-mail: Ji Houn Huh (jhuh009@ucr.edu), Ji Hoon Choi (jchoi071@ucr.edu)
 *	Lab Section: 23
 *	Assignment: Lab # 2 Exercise # 2
 *	Exercise Description: Parking Lot available
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
    DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs
    unsigned char tmpA = 0x00;
    unsigned char cntavail;
    unsigned char loop;

    while(1)
    {
        tmpA = PINA & 0x0F;

        for (loop = 0; loop < 4; ++loop)
        {
            if (tmpA & 0x01 == 0x01)
            {
                cntavail += 1;
            }

            tmpA = tmpA >> 1;
        }
        PORTC = cntavail;

        cntavail = 0;
    }

    return 0;
}
