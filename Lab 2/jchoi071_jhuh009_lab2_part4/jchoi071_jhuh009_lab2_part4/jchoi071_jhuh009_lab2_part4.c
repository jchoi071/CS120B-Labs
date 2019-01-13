/*	Partner(s) Name & E-mail: Ji Houn Huh (jhuh009@ucr.edu), Ji Hoon Choi (jchoi071@ucr.edu)
 *	Lab Section:  023
 *	Assignment: Lab #2  Exercise # 4
 *	Exercise Description: Fat Kids on a rollercoaster
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
    DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
    DDRC = 0x00; //PORTC = 0xFF; // Configure port C's 8 pins as inputs
    DDRD = 0xFF; PORTD = 0x00; // Configure port D's 8 pins as outputs, initialize to 0s

    unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
    unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
    unsigned char tmpC = 0x00; // Temporary variable to hold the value of C
    unsigned char tmpD = 0x00; // Temporary variable to hold the value of D

    unsigned short totalWeight;
    unsigned char shiftWeight;

    while (1) 
    {
        tmpA = PINA;
        tmpB = PINB;
        tmpC = PINC;
        
        totalWeight = tmpA + tmpB + tmpC;
        shiftWeight = totalWeight * 4;

        if (totalWeight > 140)
        {
            tmpD = (tmpD & 0xFE) | 0x01;
        }
        else
        {
            tmpD = (tmpD & 0xFE) | 0x00;
        }

        if ((tmpA - tmpC) > 80)
        {
            tmpD = (tmpD & 0xFC) | 0x02;
        }

        tmpD = tmpD + shiftWeight;
        PORTD = tmpD;
        tmpD = 0;
    }
}

