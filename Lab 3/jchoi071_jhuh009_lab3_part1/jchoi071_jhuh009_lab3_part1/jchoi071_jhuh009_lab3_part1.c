/*  Partner(s) Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu), Ji Houn Huh (jhuh009@ucr.edu)
 *  Lab Section: 23
 *  Assignment: Lab # 3 Exercise # 1
 *  Exercise Description: Count 1s on A
 *  
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */


#include <avr/io.h>
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
    return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
    return ((x & (0x01 << k)) != 0);
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; //Configure port A's 8 pins as inputs, initialize to 1s
    DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs, initialize to 1s
    DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
    
    unsigned char tmpA = 0x00;
    unsigned char tmpB = 0x00;
    unsigned char tmpC = 0x00;
    
    unsigned short counter = 0x00;
    unsigned char place = 0x00;
    
    while(1) 
    {
        tmpA = PINA;
        tmpB = PINB;
        
        for(counter = 0; counter < 8; counter++)
        {
            if(GetBit(tmpA, counter))
            {
                place++;
            }
            if(GetBit(tmpB,counter))
            {
                place++;
            }
              
        }
        tmpC = place;
        PORTC = tmpC;
        place = 0;
    }
}    
