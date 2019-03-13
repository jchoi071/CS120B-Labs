/*
 * Custom Lab Test 3.c
 *
 * Created: 3/5/2019 2:32:50 PM
 * Author : snesi
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "max7219.h"
#include "led_matrix.h"
#include "io.h"
#include "timer.h"

// -----------------------------------------------------------------------------
// Block
// -----------------------------------------------------------------------------
typedef struct Block
{
    unsigned char x, y;
} Block;

// -----------------------------------------------------------------------------
// Tetromino
// -----------------------------------------------------------------------------

typedef struct Tetromino
{
    Block rota[4];
    Block rotb[4];
    Block rotc[4];
    Block rotd[4];

    unsigned char lowesta;
    unsigned char lowestb;
    unsigned char lowestc;
    unsigned char lowestd;

	unsigned char lefta;
	unsigned char leftb;
	unsigned char leftc;
	unsigned char leftd;

    unsigned char righta;
    unsigned char rightb;
    unsigned char rightc;
    unsigned char rightd;

    unsigned char digit;
} Tetromino;

// -----------------------------------------------------------------------------
// Tetris
// -----------------------------------------------------------------------------

typedef struct Tetris
{
    Tetromino L_left;
    Tetromino L_right;
    Tetromino O;
    Tetromino I;
    Tetromino S;
    Tetromino T;
} Tetris;

// -----------------------------------------------------------------------------
// Tetris Pieces
// -----------------------------------------------------------------------------

struct Tetris tetris;
void initTetris()
{
	// T
    tetris.T.rota[0].x = 1;
    tetris.T.rota[0].y = 0;

    tetris.T.rota[1].x = 0;
    tetris.T.rota[1].y = 1;

    tetris.T.rota[2].x = 1;
    tetris.T.rota[2].y = 1;

    tetris.T.rota[3].x = 2;
    tetris.T.rota[3].y = 1;

	tetris.T.rotb[0].x = 1;
	tetris.T.rotb[0].y = 0;

	tetris.T.rotb[1].x = 1;
	tetris.T.rotb[1].y = 1;

	tetris.T.rotb[2].x = 2;
	tetris.T.rotb[2].y = 1;

	tetris.T.rotb[3].x = 1;
	tetris.T.rotb[3].y = 2;
	
	tetris.T.rotc[0].x = 0;
	tetris.T.rotc[0].y = 1;

	tetris.T.rotc[1].x = 1;
	tetris.T.rotc[1].y = 1;

	tetris.T.rotc[2].x = 2;
	tetris.T.rotc[2].y = 1;

	tetris.T.rotc[3].x = 1;
	tetris.T.rotc[3].y = 2;
	
	tetris.T.rotd[0].x = 1;
	tetris.T.rotd[0].y = 0;

	tetris.T.rotd[1].x = 0;
	tetris.T.rotd[1].y = 1;

	tetris.T.rotd[2].x = 1;
	tetris.T.rotd[2].y = 1;

	tetris.T.rotd[3].x = 1;
	tetris.T.rotd[3].y = 2;

    tetris.T.lowesta = 1;
	tetris.T.lefta = 0;
    tetris.T.righta = 2;
	
	tetris.T.lowestb = 2;
	tetris.T.leftb = 1;
	tetris.T.rightb = 2;
	
	tetris.T.lowestc = 2;
	tetris.T.leftc = 0;
	tetris.T.rightc = 2;
	
	tetris.T.lowestd = 2;
	tetris.T.leftd = 0;
	tetris.T.rightd = 1;
}


void displayTetromino(struct Tetromino tetromino, unsigned char x_offset, unsigned char y_offset, unsigned char rotation, unsigned char intensity)
{
	switch (rotation)
	{
		case 0:
			LED_Pixel(tetromino.rota[0].x + x_offset, tetromino.rota[0].y + y_offset, 1, intensity);
			LED_Pixel(tetromino.rota[1].x + x_offset, tetromino.rota[1].y + y_offset, 1, intensity);
			LED_Pixel(tetromino.rota[2].x + x_offset, tetromino.rota[2].y + y_offset, 1, intensity);
			LED_Pixel(tetromino.rota[3].x + x_offset, tetromino.rota[3].y + y_offset, 1, intensity);
			break;
			
		case 1:
			LED_Pixel(tetromino.rotb[0].x + x_offset, tetromino.rotb[0].y + y_offset, 1, intensity);
			LED_Pixel(tetromino.rotb[1].x + x_offset, tetromino.rotb[1].y + y_offset, 1, intensity);
			LED_Pixel(tetromino.rotb[2].x + x_offset, tetromino.rotb[2].y + y_offset, 1, intensity);
			LED_Pixel(tetromino.rotb[3].x + x_offset, tetromino.rotb[3].y + y_offset, 1, intensity);
			break;
			
		case 2:
			LED_Pixel(tetromino.rotc[0].x + x_offset, tetromino.rotc[0].y + y_offset, 1, intensity);
			LED_Pixel(tetromino.rotc[1].x + x_offset, tetromino.rotc[1].y + y_offset, 1, intensity);
			LED_Pixel(tetromino.rotc[2].x + x_offset, tetromino.rotc[2].y + y_offset, 1, intensity);
			LED_Pixel(tetromino.rotc[3].x + x_offset, tetromino.rotc[3].y + y_offset, 1, intensity);
			break;
			
		case 3:
			LED_Pixel(tetromino.rotd[0].x + x_offset, tetromino.rotd[0].y + y_offset, 1, intensity);
			LED_Pixel(tetromino.rotd[1].x + x_offset, tetromino.rotd[1].y + y_offset, 1, intensity);
			LED_Pixel(tetromino.rotd[2].x + x_offset, tetromino.rotd[2].y + y_offset, 1, intensity);
			LED_Pixel(tetromino.rotd[3].x + x_offset, tetromino.rotd[3].y + y_offset, 1, intensity);
			break;
			
		default:
			LED_Pixel(tetromino.rota[0].x + x_offset, tetromino.rota[0].y + y_offset, 1, intensity);
			LED_Pixel(tetromino.rota[1].x + x_offset, tetromino.rota[1].y + y_offset, 1, intensity);
			LED_Pixel(tetromino.rota[2].x + x_offset, tetromino.rota[2].y + y_offset, 1, intensity);
			LED_Pixel(tetromino.rota[3].x + x_offset, tetromino.rota[3].y + y_offset, 1, intensity);
			break;
	}
    
}

enum Tetris_States { Start, Init, Rotate } Tetris_State;
unsigned char counter = 0;
unsigned char move_x = 0, move_y = 0;
void TickFct_Tetris()
{
    switch (Tetris_State)
    {
        case Start:
            Tetris_State = Init;
            break;

        case Init:
            Tetris_State = Rotate;
            break;

        case Rotate:
			Tetris_State = Rotate;
            break;

        default:
            Tetris_State = Init;
            break;
    }

    switch (Tetris_State)
    {
        case Start:
            break;

        case Init:
            initTetris();
            break;

        case Rotate:
			displayTetromino(tetris.T, move_x, move_y, counter, 15);
			if ((~PINA & 0x01) == 0x01)
			{
				if (counter < 3)
				{
					++counter;
				}
				else
				{
					counter = 0;
				}
			}
			
			if ((~PINA & 0x02) >> 1 == 0x01)
			{
				if (tetris.T.lefta + move_x > 0)
				{
					--move_x;
				}
			}
			
			if ((~PINA & 0x04) >> 2 == 0x01)
			{
				if (tetris.T.righta + move_x < 7)
				{
					++move_x;
				}
			}
			break;

        default:
            break;
    }
}

enum DisplayStates { Disp_Start, Display } DisplayState;
const char TOP_MSG[] = " Rotation  Test ";
const char BOTTOM_MSG[] = "Rotating T tetromino";
char buffer[] = "                ";
unsigned short pos = 0;
const unsigned char BUFFER_SIZE = 16;
unsigned short msg_size = strlen(BOTTOM_MSG);

void TickFct_DisplayMsg()
{
    unsigned char counter = 0;
    switch (DisplayState)
    {
        case Disp_Start:
			DisplayState = Display;
			break;
        
        case Display:
			DisplayState = Display;
			break;
        
        default:
			DisplayState = Display;
			break;
    }
    
    switch (DisplayState)
    {
        case Disp_Start:
			break;
        
        case Display:
			if ((!strcmp(buffer, "                ")) && (pos != 0))
			{
				pos = 0;
			}
			if (pos == 0)
			{
				buffer[BUFFER_SIZE - 1] = BOTTOM_MSG[0];
			}
			else if ((pos > 0) && (pos < msg_size))
			{
				for (counter = 1; counter < BUFFER_SIZE; ++counter)
				{
					buffer[counter - 1] = buffer[counter];
				}
				buffer[BUFFER_SIZE - 1] = BOTTOM_MSG[pos];
			}
			else
			{
				for (counter = 1; counter < BUFFER_SIZE; ++counter)
				{
					buffer[counter - 1] = buffer[counter];
				}
				buffer[BUFFER_SIZE - 1] = 0x20;
			}
			++pos;
			LCD_DisplayStringBottom(1, buffer);
			break;
    }
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
    DDRD = 0xFF; PORTD = 0x00; // LCD control lines
	
    max7219_init();

    uint8_t ic = 0;

    //init ic
    ic = 0;
    max7219_shutdown(ic, 1); //power on
    max7219_test(ic, 0); //test mode off
    max7219_decode(ic, 0); //use led matrix
    max7219_intensity(ic, 15); //intensity
    max7219_scanlimit(ic, 7); //set number of digit to drive
	LED_ClearScreen(15);

    Tetris_State = Start;
	DisplayState = Disp_Start;
	
	TimerSet(300);
	TimerOn();
	
	LCD_init();
	LCD_DisplayStringTop(1, TOP_MSG);
	
    while (1) 
    {
        LED_ClearScreen(0);
		TickFct_Tetris();
		TickFct_DisplayMsg();
        while(!TimerFlag);
        TimerFlag = 0;
    }
}

