/*  Partner(s) Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu), Ji Houn Huh (jhuh009@ucr.edu)
 *  Lab Section: 23
 *  Assignment: Lab # 4 Exercise # 1
 *  Exercise Description: Buttons and LEDs SM
 *  
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */

#include <avr/io.h>
enum States{Start, Init, PBOne} state;
unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;

void tick()
{
    tmpA = PINA;

    switch(state) {
        case Start:
            state = Init;
            break;
        
        case Init:
            if(!(tmpA & 0x01)) {
                state = Init;
            }
            else if(tmpA & 0x01) {
                 state = PBOne;
            }
            break;
        
        case PBOne:
            if(!(tmpA & 0x01)) {
                state = PBOne;
            }
            else if(tmpA & 0x01) {
                 state = Init;
            }
            break;
        default:
            state = Start;
            break;
    }
    
    switch(state) {
        case Init:
            tmpB = 0x01;
            PORTB = tmpB;
            break;
        
        case PBOne:
            tmpB = 0x02;
            PORTB = tmpB;
            break;
            
        default:
            break;  
    }   
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    state = Start;
    
    while(1) {
        tick();
    }
}

