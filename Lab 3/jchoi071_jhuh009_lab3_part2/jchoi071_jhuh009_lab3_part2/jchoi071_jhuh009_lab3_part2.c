/*  Partner(s) Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu), Ji Houn Huh (jhuh009@ucr.edu)
 *  Lab Section: 23
 *  Assignment: Lab # 3 Exercise # 2
 *  Exercise Description: Car fuel level sensor
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
    //DDRC = 0xFF; PORTC = 0x00;
    
    unsigned short value = 0x00;
    while (1) 
    {
        DDRC = 0xFF; PORTC = 0x00;
        unsigned char tmpA = 0x00;
        value = 0x00;
        
        if(GetBit(PINA,0)) {
            value += 0x01;
        }
        if(GetBit(PINA,1)) {
            value += 0x02;
        }
        if(GetBit(PINA,2)) {
            value += 0x04;
        }
        if(GetBit(PINA,3)) {
            value += 0x08;
        }
        if(value < 3 && value > 0 ) {
            tmpA = SetBit(tmpA, 5, 1);
        }
        else if(value < 4 && value > 0) {
            tmpA = SetBit(tmpA, 5, 1);
            tmpA = SetBit(tmpA, 4, 1);
        }
        else if(value < 6 && value > 0) {
            tmpA = SetBit(tmpA, 5, 1);
            tmpA = SetBit(tmpA, 4, 1);
            tmpA = SetBit(tmpA, 3, 1);
        }
        else if(value < 9 && value > 0) {
            tmpA = SetBit(tmpA, 5, 1);
            tmpA = SetBit(tmpA, 4, 1);
            tmpA = SetBit(tmpA, 3, 1);
            tmpA = SetBit(tmpA, 2, 1);
        }
        else if(value < 12 && value > 0) {
            tmpA = SetBit(tmpA, 5, 1);
            tmpA = SetBit(tmpA, 4, 1);
            tmpA = SetBit(tmpA, 3, 1);
            tmpA = SetBit(tmpA, 2, 1);
            tmpA = SetBit(tmpA, 1, 1);
        }
        else if(value < 15 && value > 0) {
            tmpA = SetBit(tmpA, 5, 1);
            tmpA = SetBit(tmpA, 4, 1);
            tmpA = SetBit(tmpA, 3, 1);
            tmpA = SetBit(tmpA, 2, 1);
            tmpA = SetBit(tmpA, 1, 1);
            tmpA = SetBit(tmpA, 0, 1);
        }
        if(value < 5) {
            tmpA = SetBit(tmpA, 6, 1);
        }
        value = 0x00;
        
        PORTC = tmpA;
    }
}

