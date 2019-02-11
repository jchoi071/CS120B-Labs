/*  Partner(s) Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu), Ji Houn Huh (jhuh009@ucr.edu)
 *  Lab Section: 23
 *  Assignment: Lab # 8 Exercise # 3
 *  Exercise Description: ADC w/ photocell light values to binary
 *  
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */

#include <avr/io.h>


void ADC_init() {
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
    // ADEN: setting this bit enables analog-to-digital conversion.
    // ADSC: setting this bit starts the first conversion.
    // ADATE: setting this bit enables auto-triggering. Since we are
    //        in Free Running Mode, a new conversion will trigger whenever
    //        the previous conversion completes.
}



int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    
    ADC_init();
    
    /* Replace with your application code */
      while (1)
    {
        //unsigned short x = ADC;  // Value of ADC register now stored in variable x
        if(ADC >= (100 / 2)) {
            PORTB = 0xFF;
            PORTD = 0x03;
        }
        else {
            PORTB = 0x00;
            PORTD = 0x00;
        }
//      unsigned short my_short = ADC;
//      unsigned char my_char = (char)my_short; // my_char = 0xCD
//      my_char = (char)(my_short);
//      PORTB = my_short;
//      my_char = (char)(my_short >> 8); // my_char = 0xBC
//      PORTD = my_char;
    }
}

