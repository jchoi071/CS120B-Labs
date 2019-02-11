/*  Partner(s) Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu), Ji Houn Huh (jhuh009@ucr.edu)
 *  Lab Section: 23
 *  Assignment: Lab # 9 Exercise # 3
 *  Exercise Description: PWM play music
 *  
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */

#include <avr/io.h>
#include "timer.h"

// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(double frequency) {
    static double current_frequency; // Keeps track of the currently set frequency
    // Will only update the registers when the frequency changes, otherwise allows
    // music to play uninterrupted.
    if (frequency != current_frequency) {
        if (!frequency) { TCCR0B &= 0x08; } //stops timer/counter
        else { TCCR0B |= 0x03; } // resumes/continues timer/counter
        
        // prevents OCR3A from overflowing, using prescaler 64
        // 0.954 is smallest frequency that will not result in overflow
        if (frequency < 0.954) { OCR0A = 0xFFFF; }
        
        // prevents OCR0A from underflowing, using prescaler 64                 // 31250 is largest frequency that will not result in underflow
        else if (frequency > 31250) { OCR0A = 0x0000; }
        
        // set OCR3A based on desired frequency
        else { OCR0A = (short)(8000000 / (128 * frequency)) - 1; }

        TCNT0 = 0; // resets counter
        current_frequency = frequency; // Updates the current frequency
    }
}

void PWM_on() {
    TCCR0A = (1 << COM0A0) | (1 << WGM00);
    // COM3A0: Toggle PB3 on compare match between counter and OCR0A
    TCCR0B = (1 << WGM02) | (1 << CS01) | (1 << CS00);
    // WGM02: When counter (TCNT0) matches OCR0A, reset counter
    // CS01 & CS30: Set a prescaler of 64
    set_PWM(0);
}

void PWM_off() {
    TCCR0A = 0x00;
    TCCR0B = 0x00;
}

enum Music_States { Start, Init, Wait, Play, Hold, End } Music_State;
unsigned char tmpA = 0x00;
unsigned char noteCounter = 0;
unsigned char holdCounter = 1;
const unsigned char SIZE = 18;
const double NOTES[18] = { 440.00, 523.25, 587.33, 440.00, 392.00, 0.00, 392.00, 0.00, 554.37, 440.00, 523.25, 587.33, 440.00, 392.00, 0.00, 392.00, 0.00, 329.63 };
const unsigned char HOLD[18] = { 1, 1, 1, 4, 1, 1, 1, 1, 5, 1, 1, 1, 4, 1, 1, 1, 1, 5 };

void TickFct_Music()
{
    tmpA = ~PINA;
    switch (Music_State)
    {
        case Start:
            Music_State = Init;
            break;

        case Init:
            Music_State = Wait;

        case Wait:
            if ((tmpA & 0x01) == 0x01)
            {
                Music_State = Play;
            }
            else
            {
                Music_State = Wait;
            }
            break;

         case Play:
            if (noteCounter < SIZE)
            {
                Music_State = Play;
            }
            else
            {
                Music_State = End;
            }
            break;

        case End:
            if ((tmpA & 0x01) == 0x01)
            {
                Music_State = End;
            }
            else
            {
                Music_State = Init;
            }
            break;

        default:
            Music_State = Wait;
            break;
    }

    switch (Music_State)
    {
        case Start:
            break;

        case Init:
            PWM_on();
            noteCounter = 0;
            break;

        case Wait:
            break;

        case Play:
            if (holdCounter == 1)
            {
                set_PWM(NOTES[noteCounter]);
            }
            if (holdCounter < HOLD[noteCounter])
            {

                ++holdCounter;
            }
            else
            {
                holdCounter = 1;
                ++noteCounter;
            }
            break;

        case End:
            PWM_off();
            break;

        default:
            break;
    }
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0x08; PORTB = 0x00;
    TimerSet(200);
    TimerOn();
    PWM_on();
    while (1) 
    {
        TickFct_Music();
        while (!TimerFlag);
        TimerFlag = 0;
    }
}

