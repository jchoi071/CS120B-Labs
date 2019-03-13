/*
 * Custom Lab Test 3.c
 *
 * Created: 3/5/2019 2:32:50 PM
 * Author : snesi
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    Block rotations[4][4];

    char lowest[4];
    char left[4];
    char right[4];

    unsigned char digit;
} Tetromino;

// -----------------------------------------------------------------------------
// Tetris
// -----------------------------------------------------------------------------

typedef struct Tetris
{
    Tetromino tetrominoes[6];

} Tetris;

// -----------------------------------------------------------------------------
// Tetris Pieces
// -----------------------------------------------------------------------------

struct Tetris tetris;
void initTetris()
{
	// T
    tetris.tetrominoes[0].rotations[0][0].x = 1;
    tetris.tetrominoes[0].rotations[0][0].y = 0;

    tetris.tetrominoes[0].rotations[0][1].x = 0;
    tetris.tetrominoes[0].rotations[0][1].y = 1;

    tetris.tetrominoes[0].rotations[0][2].x = 1;
    tetris.tetrominoes[0].rotations[0][2].y = 1;

    tetris.tetrominoes[0].rotations[0][3].x = 2;
    tetris.tetrominoes[0].rotations[0][3].y = 1;

	tetris.tetrominoes[0].rotations[1][0].x = 1;
	tetris.tetrominoes[0].rotations[1][0].y = 0;

	tetris.tetrominoes[0].rotations[1][1].x = 1;
	tetris.tetrominoes[0].rotations[1][1].y = 1;

	tetris.tetrominoes[0].rotations[1][2].x = 2;
	tetris.tetrominoes[0].rotations[1][2].y = 1;

	tetris.tetrominoes[0].rotations[1][3].x = 1;
	tetris.tetrominoes[0].rotations[1][3].y = 2;
	
	tetris.tetrominoes[0].rotations[2][0].x = 0;
	tetris.tetrominoes[0].rotations[2][0].y = 1;

	tetris.tetrominoes[0].rotations[2][1].x = 1;
	tetris.tetrominoes[0].rotations[2][1].y = 1;

	tetris.tetrominoes[0].rotations[2][2].x = 2;
	tetris.tetrominoes[0].rotations[2][2].y = 1;

	tetris.tetrominoes[0].rotations[2][3].x = 1;
	tetris.tetrominoes[0].rotations[2][3].y = 2;
	
	tetris.tetrominoes[0].rotations[3][0].x = 1;
	tetris.tetrominoes[0].rotations[3][0].y = 0;

	tetris.tetrominoes[0].rotations[3][1].x = 0;
	tetris.tetrominoes[0].rotations[3][1].y = 1;

	tetris.tetrominoes[0].rotations[3][2].x = 1;
	tetris.tetrominoes[0].rotations[3][2].y = 1;

	tetris.tetrominoes[0].rotations[3][3].x = 1;
	tetris.tetrominoes[0].rotations[3][3].y = 2;

    tetris.tetrominoes[0].lowest[0] = 1;
	tetris.tetrominoes[0].left[0] = 0;
    tetris.tetrominoes[0].right[0] = 2;
	
	tetris.tetrominoes[0].lowest[1] = 2;
	tetris.tetrominoes[0].left[1] = 1;
	tetris.tetrominoes[0].right[1] = 2;
	
	tetris.tetrominoes[0].lowest[2] = 2;
	tetris.tetrominoes[0].left[2] = 0;
	tetris.tetrominoes[0].right[2] = 2;
	
	tetris.tetrominoes[0].lowest[3] = 2;
	tetris.tetrominoes[0].left[3] = 0;
	tetris.tetrominoes[0].right[3] = 1;
}

unsigned char lines[8][8];
unsigned char lines = 0, score = 0;
void displayTetromino(Tetromino tetromino, signed char x_offset, unsigned char y_offset, unsigned char rotation, unsigned char intensity)
{
    LED_Pixel(tetromino.rotations[rotation][0].x + x_offset, tetromino.rotations[rotation][0].y + y_offset, 1, intensity);
    LED_Pixel(tetromino.rotations[rotation][1].x + x_offset, tetromino.rotations[rotation][1].y + y_offset, 1, intensity);
    LED_Pixel(tetromino.rotations[rotation][2].x + x_offset, tetromino.rotations[rotation][2].y + y_offset, 1, intensity);
    LED_Pixel(tetromino.rotations[rotation][3].x + x_offset, tetromino.rotations[rotation][3].y + y_offset, 1, intensity);
}

void displayLines(unsigned char lines[8][8], unsigned char intensity)
{
    unsigned char a, b;

    for (a = 0; a < 8; ++a)
    {
        for (b = 0; b < 8; ++b)
        {
            if (lines[a][b]) LED_Pixel(a, b, lines[a][b], intensity);
        }
    }
}

unsigned char collision(Tetromino tetromino, unsigned char lines[8][8], signed char x_offset, unsigned char y_offset, unsigned char rotation)
{
    unsigned char t;
    unsigned char returnValue = 0;

    for (t = 0; t < 4; ++t)
    {
        if (lines[tetromino.rotations[rotation][t].x + x_offset][tetromino.rotations[rotation][t].y + y_offset])
        {
            returnValue = 1;
            break;
        }
    }
    return returnValue;
}

void shiftDown(unsigned char lines[8][8], unsigned char removeLine)
{
    unsigned char a, b;
    for (b = removeLine, b >= 0, --a)
    {
        for (a = 0, a < 8, ++a)
        {
            lines[a][b] = lines[a][b - 1]; 
        }
    }
}

enum Transform_States { Transform_Start, Transform_Init, Transform } Transform_State;
unsigned char counter = 0;
unsigned char currentTet, nextTet = 0;
signed char move_x = 0;
unsigned char move_y = 0;
void TickFct_Transform()
{
    switch (Transform_State)
    {
        case Transform_Start:
            Transform_State = Transform_Init;
            break;

        case Transform_Init:
            Transform_State = Transform;
            break;

        case Transform:
			Transform_State = Transform;
            break;

        default:
            Transform_State = Transform_Init;
            break;
    }

    switch (Transform_State)
    {
        case Transform_Start:
            break;

        case Transform_Init:
            initTetris();
            break;

        case Transform:
			if ((~PINB & 0x01) == 0x01)
			{
				if (counter < 3)
				{
                    if ((tetris.tetrominoes[currentTet].left[counter + 1] + move_x >= 0) && (tetris.tetrominoes[currentTet].right[counter + 1] + move_x <= 7) && (tetris.tetrominoes[currentTet].lowest[counter + 1] + move_y <= 7) && (!collision(tetris.tetrominoes[currentTet], lines, move_x, move_y, counter + 1)))
                    {
					    ++counter;
                        LED_ClearScreen(0);
                    }
				}
				else
				{
                    if ((tetris.tetrominoes[currentTet].left[0] + move_x >= 0) && (tetris.tetrominoes[currentTet].right[0] + move_x <= 7) && (tetris.tetrominoes[currentTet].lowest[counter + 1] + move_y <= 7) && (!collision(tetris.tetrominoes[currentTet], lines, move_x, move_y, counter + 1)))
                    {
					    counter = 0;
                        LED_ClearScreen(0);
                    }
				}
			}
			
			if ((~PINB & 0x02) >> 1 == 0x01)
			{
				if ((tetris.tetrominoes[currentTet].left[counter] + move_x - 1 >= 0) && (!collision(tetris.tetrominoes[currentTet], lines, move_x - 1, move_y, counter)))
				{
					--move_x;
                    LED_ClearScreen(0);
				}
			}
			
			if ((~PINB & 0x04) >> 2 == 0x01)
			{
				if ((tetris.tetrominoes[currentTet].right[counter] + move_x + 1 <= 7) && (!collision(tetris.tetrominoes[currentTet], lines, move_x + 1, move_y, counter)))
				{
					++move_x;
                    LED_ClearScreen(0);
				}
			}
			break;

        default:
            break;
    }
}

enum Tetris_States { Tetris_Start, Tetris_Init, Tetris_Spawn, Tetris_Drop, Tetris_Score, Tetris_End } Tetris_State;
unsigned char down = 0;
unsigned char intersect = 0;
unsigned char loop_time = 0;

void TickFct_Tetris()
{
    switch (Tetris_State)
    {
        case Tetris_Start:
            if (intersect)
            {
                Tetris_State = Tetris_End;
            }
            else
            {
                Tetris_State = Tetris_Spawn;
            }
            break;

        case Tetris_Init:
            Tetris_State = Tetris_Spawn;
            break;

        case Tetris_Spawn:
            Tetris_State = Tetris_Drop;
            break;

        case Tetris_Drop:
            if (down)
            {
                Tetris_State = Tetris_Score;
            }
            else
            {
                Tetris_State = Tetris_Drop;
            }
            break;

        case Tetris_Score:
            Tetris_State = Tetris_Spawn;
            break;

        case Tetris_End:
            Tetris_State = Tetris_End;
            break;

        default:
            Tetris_State = Tetris_Spawn;
            break;
    }

    switch (Tetris_State)
    {
        case Tetris_Start:
            break;

        case Tetris_Init:
            //srand(time(0));
            //nextTet = rand() % 6;
            break;

        case Tetris_Spawn:
            //currentTet = nextTet;
            //nextTet = rand() % 6;
            break;

        case Tetris_Drop:
            if (loop_time < 50)
            {
                ++loop_time;
            }
            else
            {
                loop_time = 0;
                if ((tetris.tetrominoes[currentTet].lowest[counter] + move_y + 1 <= 7) && (!collision(tetris.tetrominoes[currentTet], lines, move_x, move_y + 1, counter)))
                {
                    LED_ClearScreen(0);
                    ++move_y;
                }
                else
                {
                    LED_ClearScreen(0);
                    
                    lines[tetris.tetrominoes[currentTet].rotations[counter][0].x + move_x][tetris.tetrominoes[currentTet].rotations[counter][0].y + move_y] = 1;
                    lines[tetris.tetrominoes[currentTet].rotations[counter][1].x + move_x][tetris.tetrominoes[currentTet].rotations[counter][1].y + move_y] = 1;
                    lines[tetris.tetrominoes[currentTet].rotations[counter][2].x + move_x][tetris.tetrominoes[currentTet].rotations[counter][2].y + move_y] = 1;
                    lines[tetris.tetrominoes[currentTet].rotations[counter][3].x + move_x][tetris.tetrominoes[currentTet].rotations[counter][3].y + move_y] = 1;

                    move_y = 0;
                    down = 1;
                }
            }
            break;

        case Tetris_Score:
            down = 0;
            unsigned char numOnes = 0;
            unsigned char a, b;
            unsigned char fullLine[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
            for (b = 0, b < 8, ++b)
            {
                for (a = 0, a < 8, ++a)
                {
                    if (lines[a][b])
                    {
                        ++numOnes;
                    }
                }
                if (numOnes == 8)
                {
                    ++lines;
                    fullLine[b] = 1;
                }
                numOnes = 0;
            }

            for (b = 0, b < 8, ++b)
            {
                if (fullLine[b])
                {

                }
            }

            break;

        case Tetris_End:
            break;

        default:
            break;
    }
}

enum Tetris_Display_States {Tetris_Display_Start, Tetris_Display } Tetris_Display_State;

void TickFct_Tetris_Display()
{
    switch (Tetris_Display_State)
    {
        case Tetris_Display_Start:
            Tetris_Display_State = Tetris_Display;
            break;

        case Tetris_Display:
            Tetris_Display_State = Tetris_Display;
            break;

        default:
            Tetris_Display_State = Tetris_Display;
            break;
    }

    switch (Tetris_Display_State)
    {

    case Tetris_Display_Start:
        break;

    case Tetris_Display:
        displayTetromino(tetris.tetrominoes[currentTet], move_x, move_y, counter, 15);
        displayLines(lines, 5);
        break;

    default:
        break;
    }
}

enum Display_States { Disp_Start, Disp_Init, Display } Display_State;
const char MSG[] = "Lines:          Score:";

void TickFct_DisplayMsg()
{
    switch (Display_State)
    {
        case Disp_Start:
			Display_State = Disp_Init;
			break;
        
        case Disp_Init:
            Display_State = Display;

        case Display:
			Display_State = Display;
			break;
        
        default:
			Display_State = Disp_Init;
			break;
    }
    
    switch (Display_State)
    {
        case Disp_Start:
			break;
        
        case Disp_Init:
            LCD_ClearScreen();
            LCD_DisplayString(1, MSG);
            break;

        case Display:
            
            break;
    }
}

int main(void)
{
	DDRB = 0x00; PORTB = 0xFF;
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

    unsigned long Tetris_elapsedTime = 20;
    unsigned long Transform_elapsedTime = 100;
    unsigned long TD_elapsedTime = 20;
    unsigned long Display_elapsedTime = 1000;
    const unsigned long timerPeriod = 1;

    Tetris_State = Tetris_Start;
    Transform_State = Transform_Start;
    Tetris_Display_State = Tetris_Display_Start;
	Display_State = Disp_Start;
	
	TimerSet(timerPeriod);
	TimerOn();
	
	LCD_init();

    while (1) 
    {
        if (Tetris_elapsedTime >= 20)
        {
            TickFct_Tetris();
            Tetris_elapsedTime = 0;
        }
        
        if (Transform_elapsedTime >= 100)
        {
            TickFct_Transform();
            Transform_elapsedTime = 0;
        }

        if (TD_elapsedTime >= 20)
        {
            TickFct_Tetris_Display();
            TD_elapsedTime = 0;
        }
		
        if (Display_elapsedTime >= 1000)
        {
            TickFct_DisplayMsg();
            Display_elapsedTime = 0;
        }
        
        while(!TimerFlag);
        TimerFlag = 0;
        Tetris_elapsedTime += timerPeriod;
        Transform_elapsedTime += timerPeriod;
        TD_elapsedTime += timerPeriod;
        Display_elapsedTime += timerPeriod;
    }
}

