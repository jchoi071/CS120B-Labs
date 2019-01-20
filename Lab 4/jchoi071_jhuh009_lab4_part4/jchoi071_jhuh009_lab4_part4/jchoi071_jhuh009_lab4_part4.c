/*  Partner(s) Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu), Ji Houn Huh (jhuh009@ucr.edu)
 *  Lab Section: 23
 *  Assignment: Lab # 4 Exercise # 3
 *  Exercise Description: XY# Lock
 *  
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */

#include <avr/io.h>

enum DoorLock_States {Start, Init, KeyY, KeyP, Wait, DoorUnlock, DoorLock } DoorLock_State;
unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;

void Tick_DoorLock()
{
    tmpA = PINA;

    switch (DoorLock_State)
    {
        case Start:
            DoorLock_State = Init;
            break;
        
        case Init:
            if ((tmpA & 0x07) == 0x04)
            {
                DoorLock_State = KeyP;
            }
            else if (tmpA & 0x80)
            {
                DoorLock_State = DoorLock;
            }
            else
            {
                DoorLock_State = Init;
            }
            break;

        case KeyY:
            if (!tmpB)
            {
                DoorLock_State = DoorUnlock;
            }
            else
            {
                DoorLock_State = DoorLock;
            }
            break;
        
        case KeyP:
            DoorLock_State = Wait;
            break;
            
        case Wait:
            if ((tmpA & 0x07) == 0x02)
            {
                DoorLock_State = KeyY;
            }
            else if (((tmpA & 0x07) == 0x04) || !tmpA)
            {
                DoorLock_State = Wait;
            }
            else if ((tmpA & 0x07) != 0x02)
            {
                DoorLock_State = Init;
            }

            else if (tmpA == 0x80)
            {
                DoorLock_State = DoorLock;
            }
            else
            {
                DoorLock_State = Wait;
            }
            break;
            
        case DoorLock:
            if (!tmpA)
            {
                DoorLock_State = Init;
            }
            else {
                DoorLock_State = DoorLock;
            }
            break;
        
        case DoorUnlock:
            if (tmpA & 0x87)
            {
                DoorLock_State = Init;
            }
            else
            {
                DoorLock_State = DoorUnlock;
            }
            break;
        
        default:
            break;
    }
    switch (DoorLock_State) 
    {
        case Start:
            PORTB = 0x00;
            PORTC = 0x00;
            break;
        
        case Init:
            break;
            
        case KeyP:
            PORTC = 0x04;
            break;
        
        case KeyY:
            PORTC = 0x02;
            break;
        
        case Wait:
            PORTC = 0x03;
            break;
            
        case DoorUnlock:
            tmpB = 0x01;
            PORTB = tmpB;
            PORTC = 0x05;
            break;
            
        case DoorLock:
            tmpB = 0x00;
            PORTB = tmpB;
            PORTC = 0x06;
            break;
            
    }
    
}
int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DoorLock_State = Start;
    while (1)
    {
        Tick_DoorLock();
    }
}