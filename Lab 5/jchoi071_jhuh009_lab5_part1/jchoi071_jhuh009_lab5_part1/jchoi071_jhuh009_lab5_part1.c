/*  Partner(s) Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu), Ji Houn Huh (jhuh009@ucr.edu)
 *  Lab Section: 23
 *  Assignment: Lab # 5 Exercise # 1
 *  Exercise Description: Car fuel level sensor on hardware
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
    /* Replace with your application code */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    unsigned char button = 0x00;
    unsigned short value = 0x00;
    unsigned char tmpA = 0x00;
    unsigned char tmpB = 0x00;

    while (1) 
    {
        tmpA = PINA;
        button = ~tmpA & 0x0F;
        value = 0x00;
        
        if(GetBit(button, 0)) {
            value += 0x01;
        }
        if(GetBit(button, 1)) {
            value += 0x02;
        }
        if(GetBit(button, 2)) {
            value += 0x04;
        }
        if(GetBit(button, 3)) {
            value += 0x08;
        }
        if(value < 3 && value > 0 ) {
            tmpB = SetBit(tmpB, 5, 1);
        }
        else if(value < 4 && value > 0) {
            tmpB = SetBit(tmpB, 5, 1);
            tmpB = SetBit(tmpB, 4, 1);
        }
        else if(value < 6 && value > 0) {
            tmpB = SetBit(tmpB, 5, 1);
            tmpB = SetBit(tmpB, 4, 1);
            tmpB = SetBit(tmpB, 3, 1);
        }
        else if(value < 9 && value > 0) {
            tmpB = SetBit(tmpB, 5, 1);
            tmpB = SetBit(tmpB, 4, 1);
            tmpB = SetBit(tmpB, 3, 1);
            tmpB = SetBit(tmpB, 2, 1);
        }
        else if(value < 12 && value > 0) {
            tmpB = SetBit(tmpB, 5, 1);
            tmpB = SetBit(tmpB, 4, 1);
            tmpB = SetBit(tmpB, 3, 1);
            tmpB = SetBit(tmpB, 2, 1);
            tmpB = SetBit(tmpB, 1, 1);
        }
        else if(value <= 15 && value > 0) {
            tmpB = SetBit(tmpB, 5, 1);
            tmpB = SetBit(tmpB, 4, 1);
            tmpB = SetBit(tmpB, 3, 1);
            tmpB = SetBit(tmpB, 2, 1);
            tmpB = SetBit(tmpB, 1, 1);
            tmpB = SetBit(tmpB, 0, 1);
        }
        if(value < 5) {
            tmpB = SetBit(tmpB, 6, 1);
        }
        value = 0x00;
        
        PORTB = tmpB;
        tmpB = 0x00;
    }
}

