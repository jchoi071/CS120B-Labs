/*  Partner(s) Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu), Ji Houn Huh (jhuh009@ucr.edu)
 *  Lab Section: 23
 *  Assignment: Lab # 4 Exercise # 5
 *  Exercise Description: #XYX Lock
 *  
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */

#include <avr/io.h>

enum DoorLock_States {Start, Init, KeyX, KeyY, KeyP, WaitP, WaitX, WaitY, DoorUnlock, DoorLock } DoorLock_State;
unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;
unsigned char tmpC = 0x00;
unsigned char record[4] = {0x04, 0x01, 0x02, 0x01};

void Tick_DoorLock()
{
    tmpA = PINA;

    switch (DoorLock_State)
    {
        case Start:
            DoorLock_State = Init;
            break;
        
        case Init:
            if ((tmpA & 0x07) == record[0])
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
	
		case KeyX:
			tmpC = PINC;
			
			if((tmpC & 0x07) == 0x02 || (tmpC & 0x07) == 0x06)
			{
				DoorLock_State = DoorUnlock;
			}
			else {
				DoorLock_State = WaitX;
			}
			
			
			break;

        case KeyY:
            DoorLock_State = WaitY;
            break;
        
        case KeyP:
            DoorLock_State = WaitP;
            break;
            
        case WaitP:
            if ((tmpA & 0x07) == record[1])
            {
                DoorLock_State = KeyX;
            }
            else if (((tmpA & 0x07) == record[0]) || !tmpA)
            {
                DoorLock_State = WaitP;
            }
            else if ((tmpA & 0x07) != record[1])
            {
                DoorLock_State = Init;
            }

            else if (tmpA == 0x80)
            {
                DoorLock_State = DoorLock;
            }
            else
            {
                DoorLock_State = WaitP;
            }
            break;
			
		case WaitX:
			if ((tmpA & 0x07) == record[2])
			{
				DoorLock_State = KeyY;
			}
			else if (((tmpA & 0x07) == record[1]) || !tmpA)
			{
				DoorLock_State = WaitX;
			}
			else if ((tmpA & 0x07) != record[2])
			{
				DoorLock_State = Init;
			}
            else if (tmpA == 0x80)
			{
				DoorLock_State = DoorLock;
			}
			else
			{
				DoorLock_State = WaitX;
			}
			break;
			
		case WaitY:
			if ((tmpA & 0x07) == record[1])
			{
				DoorLock_State = KeyX;
			}
			else if (((tmpA & 0x07) == record[2]) || !tmpA)
			{
				DoorLock_State = WaitY;
			}
			else if ((tmpA & 0x07) != record[1])
			{
				DoorLock_State = Init;
			}
            else if (tmpA == 0x80)
			{
				DoorLock_State = DoorLock;
			}
			else
			{
				DoorLock_State = WaitY;
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
			
        case KeyX:
			if(PORTC != 0x06)
			{
				PORTC = 0x01;
			}
			
			break;
		
        case KeyY:
            PORTC = 0x02;
            break;
        
        case WaitP:
            PORTC = 0x03;
            break;
			
		case WaitX:
            PORTC = 0x05;
            break;
			
		case WaitY:
            PORTC = 0x06;
			//PINC = 0x06;
            break;
            
        case DoorUnlock:
            tmpB = 0x01;
            PORTB = tmpB;
            PORTC = 0x07;
            break;
            
        case DoorLock:
            tmpB = 0x00;
            PORTB = tmpB;
            PORTC = 0x08;
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