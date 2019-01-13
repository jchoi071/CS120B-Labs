/*
 * jchoi071_jhuh009_lab2_part4.c
 *
 * Created: 1/12/2019 5:36:54 PM
 * Author : Paul Choi
 */ 

#include <avr/io.h>

int main(void)
{
    MCUCR = 0x80;
    MCUCR = 0x80;

    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
    DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
    DDRC = 0x00; PORTC = 0xFF; // Configure port C's 8 pins as inputs
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
        tmpD = 0;
        
        totalWeight = tmpA + tmpB + tmpC;
        shiftWeight = (totalWeight / 10 * 4);   //divide by 10 then shift left twice
                                                //this allows the remaining 6 bits of PORTD to represent up to 
                                                //630 kg (multiply value of high 6 bits in D by 10)
                                                //drawback is the weight is approximate

        if (totalWeight > 140)
        {
            tmpD = ((tmpD & 0xFE) | 0x01);
        }
        else
        {
            tmpD = ((tmpD & 0xFE) | 0x00);
        }

        if ((tmpA - tmpC) > 80)
        {
            tmpD = (tmpD & 0xFD) | 0x02;
        }

        tmpD = tmpD + shiftWeight;
        PORTD = tmpD;
        tmpD = 0;
        totalWeight = 0;
    }
}

