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
#include "timer.h"

typedef struct Block
{
    unsigned char x, y;
} Block;

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

typedef struct Tetris
{
    Tetromino L_left;
    Tetromino L_right;
    Tetromino O;
    Tetromino I;
    Tetromino S;
    Tetromino T;
} Tetris;

struct Tetris tetris;
void initTetris()
{
    tetris.T.rota[0].x = 1;
    tetris.T.rota[0].y = 0;

    tetris.T.rota[1].x = 0;
    tetris.T.rota[1].y = 1;

    tetris.T.rota[2].x = 1;
    tetris.T.rota[2].y = 1;

    tetris.T.rota[3].x = 2;
    tetris.T.rota[3].y = 1;

    tetris.T.lowesta = 1;
    tetris.T.lefta = 0;
    tetris.T.righta = 2;
}


void displayTetromino(struct Tetromino tetromino, unsigned char x_offset, unsigned char y_offset, unsigned char intensity)
{
    LED_Pixel(tetromino.rota[0].x + x_offset, tetromino.rota[0].y + y_offset, 1, intensity);
    LED_Pixel(tetromino.rota[1].x + x_offset, tetromino.rota[1].y + y_offset, 1, intensity);
    LED_Pixel(tetromino.rota[2].x + x_offset, tetromino.rota[2].y + y_offset, 1, intensity);
    LED_Pixel(tetromino.rota[3].x + x_offset, tetromino.rota[3].y + y_offset, 1, intensity);
}

enum Tetris_States { Start, Init, Down, Side } Tetris_State;
unsigned char counter = 0;
void TickFct_Tetris()
{
    switch (Tetris_State)
    {
        case Start:
            Tetris_State = Init;
            break;

        case Init:
            Tetris_State = Down;
            break;

        case Down:
            if ((tetris.T.lowesta + counter) < 8) Tetris_State = Down;
            else Tetris_State = Side;
            break;
        
        case Side:
            if ((tetris.T.righta + counter) < 8) Tetris_State = Side;
            else Tetris_State = Down;
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

        case Down:
            if ((tetris.T.lowesta + counter) < 8)
            {
                displayTetromino(tetris.T, 2, counter, 5);
                ++counter;
            }
            
            else counter = 0;
            break;

        case Side:
            if ((tetris.T.righta + counter) < 8)
            {
                displayTetromino(tetris.T, counter, 2, 5);
                ++counter;
            }
            else counter = 0;
            break;

        default:
            break;
    }
}

int main(void)
{
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
	TimerSet(300);
	TimerOn();
    while (1) 
    {
        LED_ClearScreen(0);
		TickFct_Tetris();
        while(!TimerFlag);
        TimerFlag = 0;
    }
}

