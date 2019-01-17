/*
 * jchoi071_jhuh009_lab4_part2.c
 *
 * Created: 1/17/2019 3:01:57 PM
 * Author : ucrcse
 */ 

#include <avr/io.h>

enum IncDec_States { Start, Init, Wait, Inc, Dec, Reset } IncDec_State;

void TickFct_IncDec(unsigned char tmpA, unsigned char tmpC)
{
    switch (IncDec_State)
    {
        case Start:
            IncDec_State = Init;
            break;
        
        case Init:
            IncDec_State = Wait;
            break;
        
        case Wait:
            if ((tmpA & 0x01) && (!(tmpA & 0x02)))
            {
                IncDec_State = Inc;
            }
            else if ((!(tmpA & 0x01)) && (tmpA & 0x02))
            {
                IncDec_State = Dec;
            }
            else if (tmpA & 0x03)
            {
                IncDec_State = Reset;
            }
            else if (!(tmpA & 0x03))
            {
                IncDec_State = Wait;
            }
            else
            {
                IncDec_State = Wait;
            }
            break;
            
        case Inc:
            IncDec_State = Wait;
            break;
        
        case Dec:
            IncDec_State = Wait;
            break;
            
        case Reset:
            IncDec_State = Wait;
            break;
            
        default:
            IncDec_State = Wait;
            break;       
        
    }
    
    switch (IncDec_State)
    {
        case Start:
            break;
            
        case Init:
            tmpC = 7;
            break;
        
        case Wait:
            PORTC = tmpC;
            
        case Inc:
            if (tmpC + 1 <= 9)
            {
                ++tmpC;
            }
            break;
        
        case Dec:
            if (tmpC - 1 >= 0)
            {
                --tmpC;
            }
            break;
        
        case Reset:
            tmpC = 0;
            
        default:
            break;
    }
}


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
    DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs
        
    unsigned char tmpA = PINA;
    unsigned char tmpC = 0x00;
        
    IncDec_State = Start;
    while (1) 
    {
        TickFct_IncDec(tmpA, tmpC);
    }
}

