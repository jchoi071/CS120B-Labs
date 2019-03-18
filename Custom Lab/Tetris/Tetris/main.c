/*  Name & E-mail: Ji Hoon Choi (jchoi071@ucr.edu)
 *  Lab Section: 23
 *  Assignment: Custom Lab Project: Tetris
 *  File description: Original code (containing some UCR-provided functions) for the state machines and main game code
 *  
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
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
    Tetromino tetrominoes[7];

} Tetris;

// -----------------------------------------------------------------------------
// Global Variables
// -----------------------------------------------------------------------------

unsigned char lines[8][8];
unsigned long numLines = 0, score = 0;
unsigned char intersect = 0;
unsigned char counter = 0;
unsigned char currentTet = 0, nextTet = 0;
signed char move_x = 3;
unsigned char move_y = 0;
unsigned char reset = 0;
struct Tetris tetris;

// -----------------------------------------------------------------------------
// Global Functions
// -----------------------------------------------------------------------------

void initTetris()
{
    // --------------------------------------------------------------------------------
    // T
    // --------------------------------------------------------------------------------

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

    tetris.tetrominoes[0].digit = 0x72;

    // --------------------------------------------------------------------------------
    // J
    // --------------------------------------------------------------------------------

    tetris.tetrominoes[1].rotations[0][0].x = 0;
    tetris.tetrominoes[1].rotations[0][0].y = 0;

    tetris.tetrominoes[1].rotations[0][1].x = 0;
    tetris.tetrominoes[1].rotations[0][1].y = 1;

    tetris.tetrominoes[1].rotations[0][2].x = 1;
    tetris.tetrominoes[1].rotations[0][2].y = 1;

    tetris.tetrominoes[1].rotations[0][3].x = 2;
    tetris.tetrominoes[1].rotations[0][3].y = 1;

    tetris.tetrominoes[1].rotations[1][0].x = 2;
    tetris.tetrominoes[1].rotations[1][0].y = 0;

    tetris.tetrominoes[1].rotations[1][1].x = 1;
    tetris.tetrominoes[1].rotations[1][1].y = 0;

    tetris.tetrominoes[1].rotations[1][2].x = 1;
    tetris.tetrominoes[1].rotations[1][2].y = 1;

    tetris.tetrominoes[1].rotations[1][3].x = 1;
    tetris.tetrominoes[1].rotations[1][3].y = 2;
    
    tetris.tetrominoes[1].rotations[2][0].x = 2;
    tetris.tetrominoes[1].rotations[2][0].y = 2;

    tetris.tetrominoes[1].rotations[2][1].x = 2;
    tetris.tetrominoes[1].rotations[2][1].y = 1;

    tetris.tetrominoes[1].rotations[2][2].x = 1;
    tetris.tetrominoes[1].rotations[2][2].y = 1;

    tetris.tetrominoes[1].rotations[2][3].x = 0;
    tetris.tetrominoes[1].rotations[2][3].y = 1;
    
    tetris.tetrominoes[1].rotations[3][0].x = 0;
    tetris.tetrominoes[1].rotations[3][0].y = 2;

    tetris.tetrominoes[1].rotations[3][1].x = 1;
    tetris.tetrominoes[1].rotations[3][1].y = 2;

    tetris.tetrominoes[1].rotations[3][2].x = 1;
    tetris.tetrominoes[1].rotations[3][2].y = 1;

    tetris.tetrominoes[1].rotations[3][3].x = 1;
    tetris.tetrominoes[1].rotations[3][3].y = 0;

    tetris.tetrominoes[1].lowest[0] = 1;
    tetris.tetrominoes[1].left[0] = 0;
    tetris.tetrominoes[1].right[0] = 2;
    
    tetris.tetrominoes[1].lowest[1] = 2;
    tetris.tetrominoes[1].left[1] = 1;
    tetris.tetrominoes[1].right[1] = 2;
    
    tetris.tetrominoes[1].lowest[2] = 2;
    tetris.tetrominoes[1].left[2] = 0;
    tetris.tetrominoes[1].right[2] = 2;
    
    tetris.tetrominoes[1].lowest[3] = 2;
    tetris.tetrominoes[1].left[3] = 0;
    tetris.tetrominoes[1].right[3] = 1;

    tetris.tetrominoes[1].digit = 0xE2;

    // --------------------------------------------------------------------------------
    // L
    // --------------------------------------------------------------------------------

    tetris.tetrominoes[2].rotations[0][0].x = 2;
    tetris.tetrominoes[2].rotations[0][0].y = 0;

    tetris.tetrominoes[2].rotations[0][1].x = 0;
    tetris.tetrominoes[2].rotations[0][1].y = 1;

    tetris.tetrominoes[2].rotations[0][2].x = 1;
    tetris.tetrominoes[2].rotations[0][2].y = 1;

    tetris.tetrominoes[2].rotations[0][3].x = 2;
    tetris.tetrominoes[2].rotations[0][3].y = 1;

    tetris.tetrominoes[2].rotations[1][0].x = 2;
    tetris.tetrominoes[2].rotations[1][0].y = 2;

    tetris.tetrominoes[2].rotations[1][1].x = 1;
    tetris.tetrominoes[2].rotations[1][1].y = 0;

    tetris.tetrominoes[2].rotations[1][2].x = 1;
    tetris.tetrominoes[2].rotations[1][2].y = 1;

    tetris.tetrominoes[2].rotations[1][3].x = 1;
    tetris.tetrominoes[2].rotations[1][3].y = 2;
        
    tetris.tetrominoes[2].rotations[2][0].x = 0;
    tetris.tetrominoes[2].rotations[2][0].y = 2;

    tetris.tetrominoes[2].rotations[2][1].x = 2;
    tetris.tetrominoes[2].rotations[2][1].y = 1;

    tetris.tetrominoes[2].rotations[2][2].x = 1;
    tetris.tetrominoes[2].rotations[2][2].y = 1;

    tetris.tetrominoes[2].rotations[2][3].x = 0;
    tetris.tetrominoes[2].rotations[2][3].y = 1;
        
    tetris.tetrominoes[2].rotations[3][0].x = 0;
    tetris.tetrominoes[2].rotations[3][0].y = 0;

    tetris.tetrominoes[2].rotations[3][1].x = 1;
    tetris.tetrominoes[2].rotations[3][1].y = 2;

    tetris.tetrominoes[2].rotations[3][2].x = 1;
    tetris.tetrominoes[2].rotations[3][2].y = 1;

    tetris.tetrominoes[2].rotations[3][3].x = 1;
    tetris.tetrominoes[2].rotations[3][3].y = 0;
    
    tetris.tetrominoes[2].lowest[0] = 1;
    tetris.tetrominoes[2].left[0] = 0;
    tetris.tetrominoes[2].right[0] = 2;
    
    tetris.tetrominoes[2].lowest[1] = 2;
    tetris.tetrominoes[2].left[1] = 1;
    tetris.tetrominoes[2].right[1] = 2;
    
    tetris.tetrominoes[2].lowest[2] = 2;
    tetris.tetrominoes[2].left[2] = 0;
    tetris.tetrominoes[2].right[2] = 2;
    
    tetris.tetrominoes[2].lowest[3] = 2;
    tetris.tetrominoes[2].left[3] = 0;
    tetris.tetrominoes[2].right[3] = 1;

    tetris.tetrominoes[2].digit = 0x8E;

    // --------------------------------------------------------------------------------
    // S
    // --------------------------------------------------------------------------------

    tetris.tetrominoes[3].rotations[0][0].x = 0;
    tetris.tetrominoes[3].rotations[0][0].y = 2;

    tetris.tetrominoes[3].rotations[0][1].x = 1;
    tetris.tetrominoes[3].rotations[0][1].y = 2;

    tetris.tetrominoes[3].rotations[0][2].x = 1;
    tetris.tetrominoes[3].rotations[0][2].y = 1;

    tetris.tetrominoes[3].rotations[0][3].x = 2;
    tetris.tetrominoes[3].rotations[0][3].y = 1;

    tetris.tetrominoes[3].rotations[1][0].x = 1;
    tetris.tetrominoes[3].rotations[1][0].y = 0;

    tetris.tetrominoes[3].rotations[1][1].x = 1;
    tetris.tetrominoes[3].rotations[1][1].y = 1;

    tetris.tetrominoes[3].rotations[1][2].x = 2;
    tetris.tetrominoes[3].rotations[1][2].y = 1;

    tetris.tetrominoes[3].rotations[1][3].x = 2;
    tetris.tetrominoes[3].rotations[1][3].y = 2;
    
    tetris.tetrominoes[3].rotations[2][0].x = 0;
    tetris.tetrominoes[3].rotations[2][0].y = 2;

    tetris.tetrominoes[3].rotations[2][1].x = 1;
    tetris.tetrominoes[3].rotations[2][1].y = 2;

    tetris.tetrominoes[3].rotations[2][2].x = 1;
    tetris.tetrominoes[3].rotations[2][2].y = 1;

    tetris.tetrominoes[3].rotations[2][3].x = 2;
    tetris.tetrominoes[3].rotations[2][3].y = 1;

    tetris.tetrominoes[3].rotations[3][0].x = 1;
    tetris.tetrominoes[3].rotations[3][0].y = 0;

    tetris.tetrominoes[3].rotations[3][1].x = 1;
    tetris.tetrominoes[3].rotations[3][1].y = 1;

    tetris.tetrominoes[3].rotations[3][2].x = 2;
    tetris.tetrominoes[3].rotations[3][2].y = 1;

    tetris.tetrominoes[3].rotations[3][3].x = 2;
    tetris.tetrominoes[3].rotations[3][3].y = 2;
    
    tetris.tetrominoes[3].lowest[0] = 2;
    tetris.tetrominoes[3].left[0] = 0;
    tetris.tetrominoes[3].right[0] = 2;
    
    tetris.tetrominoes[3].lowest[1] = 2;
    tetris.tetrominoes[3].left[1] = 1;
    tetris.tetrominoes[3].right[1] = 2;
    
    tetris.tetrominoes[3].lowest[2] = 2;
    tetris.tetrominoes[3].left[2] = 0;
    tetris.tetrominoes[3].right[2] = 2;
    
    tetris.tetrominoes[3].lowest[3] = 2;
    tetris.tetrominoes[3].left[3] = 1;
    tetris.tetrominoes[3].right[3] = 2;

    tetris.tetrominoes[3].digit = 0x36;

    // --------------------------------------------------------------------------------
    // Z
    // --------------------------------------------------------------------------------

    tetris.tetrominoes[4].rotations[0][0].x = 0;
    tetris.tetrominoes[4].rotations[0][0].y = 1;

    tetris.tetrominoes[4].rotations[0][1].x = 1;
    tetris.tetrominoes[4].rotations[0][1].y = 2;

    tetris.tetrominoes[4].rotations[0][2].x = 1;
    tetris.tetrominoes[4].rotations[0][2].y = 1;

    tetris.tetrominoes[4].rotations[0][3].x = 2;
    tetris.tetrominoes[4].rotations[0][3].y = 2;

    tetris.tetrominoes[4].rotations[1][0].x = 2;
    tetris.tetrominoes[4].rotations[1][0].y = 0;

    tetris.tetrominoes[4].rotations[1][1].x = 1;
    tetris.tetrominoes[4].rotations[1][1].y = 1;

    tetris.tetrominoes[4].rotations[1][2].x = 2;
    tetris.tetrominoes[4].rotations[1][2].y = 1;

    tetris.tetrominoes[4].rotations[1][3].x = 1;
    tetris.tetrominoes[4].rotations[1][3].y = 2;
    
    tetris.tetrominoes[4].rotations[2][0].x = 0;
    tetris.tetrominoes[4].rotations[2][0].y = 1;

    tetris.tetrominoes[4].rotations[2][1].x = 1;
    tetris.tetrominoes[4].rotations[2][1].y = 2;

    tetris.tetrominoes[4].rotations[2][2].x = 1;
    tetris.tetrominoes[4].rotations[2][2].y = 1;

    tetris.tetrominoes[4].rotations[2][3].x = 2;
    tetris.tetrominoes[4].rotations[2][3].y = 2;

    tetris.tetrominoes[4].rotations[3][0].x = 2;
    tetris.tetrominoes[4].rotations[3][0].y = 0;

    tetris.tetrominoes[4].rotations[3][1].x = 1;
    tetris.tetrominoes[4].rotations[3][1].y = 1;

    tetris.tetrominoes[4].rotations[3][2].x = 2;
    tetris.tetrominoes[4].rotations[3][2].y = 1;

    tetris.tetrominoes[4].rotations[3][3].x = 1;
    tetris.tetrominoes[4].rotations[3][3].y = 2;
    
    tetris.tetrominoes[4].lowest[0] = 2;
    tetris.tetrominoes[4].left[0] = 0;
    tetris.tetrominoes[4].right[0] = 2;
    
    tetris.tetrominoes[4].lowest[1] = 2;
    tetris.tetrominoes[4].left[1] = 1;
    tetris.tetrominoes[4].right[1] = 2;
    
    tetris.tetrominoes[4].lowest[2] = 2;
    tetris.tetrominoes[4].left[2] = 0;
    tetris.tetrominoes[4].right[2] = 2;
    
    tetris.tetrominoes[4].lowest[3] = 2;
    tetris.tetrominoes[4].left[3] = 1;
    tetris.tetrominoes[4].right[3] = 2;

    tetris.tetrominoes[4].digit = 0x5A;

    // --------------------------------------------------------------------------------
    // I
    // --------------------------------------------------------------------------------

    tetris.tetrominoes[5].rotations[0][0].x = 0;
    tetris.tetrominoes[5].rotations[0][0].y = 1;

    tetris.tetrominoes[5].rotations[0][1].x = 1;
    tetris.tetrominoes[5].rotations[0][1].y = 1;

    tetris.tetrominoes[5].rotations[0][2].x = 2;
    tetris.tetrominoes[5].rotations[0][2].y = 1;

    tetris.tetrominoes[5].rotations[0][3].x = 3;
    tetris.tetrominoes[5].rotations[0][3].y = 1;

    tetris.tetrominoes[5].rotations[1][0].x = 1;
    tetris.tetrominoes[5].rotations[1][0].y = 0;

    tetris.tetrominoes[5].rotations[1][1].x = 1;
    tetris.tetrominoes[5].rotations[1][1].y = 1;

    tetris.tetrominoes[5].rotations[1][2].x = 1;
    tetris.tetrominoes[5].rotations[1][2].y = 2;

    tetris.tetrominoes[5].rotations[1][3].x = 1;
    tetris.tetrominoes[5].rotations[1][3].y = 3;
    
    tetris.tetrominoes[5].rotations[2][0].x = 0;
    tetris.tetrominoes[5].rotations[2][0].y = 1;

    tetris.tetrominoes[5].rotations[2][1].x = 1;
    tetris.tetrominoes[5].rotations[2][1].y = 1;

    tetris.tetrominoes[5].rotations[2][2].x = 2;
    tetris.tetrominoes[5].rotations[2][2].y = 1;

    tetris.tetrominoes[5].rotations[2][3].x = 3;
    tetris.tetrominoes[5].rotations[2][3].y = 1;

    tetris.tetrominoes[5].rotations[3][0].x = 1;
    tetris.tetrominoes[5].rotations[3][0].y = 0;

    tetris.tetrominoes[5].rotations[3][1].x = 1;
    tetris.tetrominoes[5].rotations[3][1].y = 1;

    tetris.tetrominoes[5].rotations[3][2].x = 1;
    tetris.tetrominoes[5].rotations[3][2].y = 2;

    tetris.tetrominoes[5].rotations[3][3].x = 1;
    tetris.tetrominoes[5].rotations[3][3].y = 3;
    
    tetris.tetrominoes[5].lowest[0] = 1;
    tetris.tetrominoes[5].left[0] = 0;
    tetris.tetrominoes[5].right[0] = 3;
    
    tetris.tetrominoes[5].lowest[1] = 3;
    tetris.tetrominoes[5].left[1] = 1;
    tetris.tetrominoes[5].right[1] = 1;
    
    tetris.tetrominoes[5].lowest[2] = 1;
    tetris.tetrominoes[5].left[2] = 0;
    tetris.tetrominoes[5].right[2] = 3;
    
    tetris.tetrominoes[5].lowest[3] = 3;
    tetris.tetrominoes[5].left[3] = 1;
    tetris.tetrominoes[5].right[3] = 1;

    tetris.tetrominoes[5].digit = 0xF2;

    // --------------------------------------------------------------------------------
    // O
    // --------------------------------------------------------------------------------

    tetris.tetrominoes[6].rotations[0][0].x = 0;
    tetris.tetrominoes[6].rotations[0][0].y = 0;

    tetris.tetrominoes[6].rotations[0][1].x = 0;
    tetris.tetrominoes[6].rotations[0][1].y = 1;

    tetris.tetrominoes[6].rotations[0][2].x = 1;
    tetris.tetrominoes[6].rotations[0][2].y = 0;

    tetris.tetrominoes[6].rotations[0][3].x = 1;
    tetris.tetrominoes[6].rotations[0][3].y = 1;

    tetris.tetrominoes[6].rotations[1][0].x = 0;
    tetris.tetrominoes[6].rotations[1][0].y = 0;

    tetris.tetrominoes[6].rotations[1][1].x = 0;
    tetris.tetrominoes[6].rotations[1][1].y = 1;

    tetris.tetrominoes[6].rotations[1][2].x = 1;
    tetris.tetrominoes[6].rotations[1][2].y = 0;

    tetris.tetrominoes[6].rotations[1][3].x = 1;
    tetris.tetrominoes[6].rotations[1][3].y = 1;

    tetris.tetrominoes[6].rotations[2][0].x = 0;
    tetris.tetrominoes[6].rotations[2][0].y = 0;

    tetris.tetrominoes[6].rotations[2][1].x = 0;
    tetris.tetrominoes[6].rotations[2][1].y = 1;

    tetris.tetrominoes[6].rotations[2][2].x = 1;
    tetris.tetrominoes[6].rotations[2][2].y = 0;

    tetris.tetrominoes[6].rotations[2][3].x = 1;
    tetris.tetrominoes[6].rotations[2][3].y = 1;

    tetris.tetrominoes[6].rotations[3][0].x = 0;
    tetris.tetrominoes[6].rotations[3][0].y = 0;

    tetris.tetrominoes[6].rotations[3][1].x = 0;
    tetris.tetrominoes[6].rotations[3][1].y = 1;

    tetris.tetrominoes[6].rotations[3][2].x = 1;
    tetris.tetrominoes[6].rotations[3][2].y = 0;

    tetris.tetrominoes[6].rotations[3][3].x = 1;
    tetris.tetrominoes[6].rotations[3][3].y = 1;
        
    tetris.tetrominoes[6].lowest[0] = 1;
    tetris.tetrominoes[6].left[0] = 0;
    tetris.tetrominoes[6].right[0] = 1;
        
    tetris.tetrominoes[6].lowest[1] = 1;
    tetris.tetrominoes[6].left[1] = 0;
    tetris.tetrominoes[6].right[1] = 1;
        
    tetris.tetrominoes[6].lowest[2] = 1;
    tetris.tetrominoes[6].left[2] = 0;
    tetris.tetrominoes[6].right[2] = 1;
        
    tetris.tetrominoes[6].lowest[3] = 1;
    tetris.tetrominoes[6].left[3] = 0;
    tetris.tetrominoes[6].right[3] = 1;

    tetris.tetrominoes[6].digit = 0x46;
}

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

// UCR-provided code for microcontroller ADC
void ADC_init()
{
ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
// ADEN: setting this bit enables analog-to-digital conversion.
// ADSC: setting this bit starts the first conversion.
// ADATE: setting this bit enables auto-triggering. Since we are
//        in Free Running Mode, a new conversion will trigger whenever
//        the previous conversion completes.
}

// -----------------------------------------------------------------------------
// Transform SM
// -----------------------------------------------------------------------------

enum Transform_States { Transform_Start, Transform_Init, Transform, Transform_End } Transform_State;
volatile unsigned char analog_rot = 0;

void TickFct_Transform()
{
    switch (Transform_State)
    {
        case Transform_Start:
            Transform_State = Transform_Init;
            break;

        case Transform_Init:
            if ((~PINB & 0x01) == 0x00)
            {
                Transform_State = Transform;
            }
            else
            {
                Transform_State = Transform_Init;
            }
            break;

        case Transform:
            if ((~PINB & 0x01) == 0x00)
            {
                if (!intersect)
                {
                    Transform_State = Transform;
                }
                else
                {
                    Transform_State = Transform_End;
                }
            }
            else
            {
                Transform_State = Transform_Init;
            }
            
            break;

        case Transform_End:
            if ((~PINB & 0x01) == 0x00)
            {
                Transform_State = Transform_End;
            }
            else
            {
                Transform_State = Transform_Init;
            }

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
            analog_rot = ((ADC - 32) / 267);
            if (analog_rot < 0) analog_rot = 0;
            counter = analog_rot;
            break;

        case Transform:

            analog_rot = ((ADC - 30) / 267);
            if (analog_rot < 0) analog_rot = 0;
            if (analog_rot > 3) analog_rot = 3;

            if ((counter >= 3) || (((tetris.tetrominoes[currentTet].left[counter + 1] + move_x >= 0) && (tetris.tetrominoes[currentTet].right[counter + 1] + move_x <= 7) && (tetris.tetrominoes[currentTet].lowest[counter + 1] + move_y <= 7) && (!collision(tetris.tetrominoes[currentTet], lines, move_x, move_y, counter + 1))) && counter < 3))
            {
                counter = analog_rot;
                LED_ClearScreen(0);
            }

            
            if ((~PINB & 0x20) == 0x20)
            {
                if ((tetris.tetrominoes[currentTet].left[counter] + move_x - 1 >= 0) && (!collision(tetris.tetrominoes[currentTet], lines, move_x - 1, move_y, counter)))
                {
                    --move_x;
                    LED_ClearScreen(0);
                }
            }
            
            if ((~PINB & 0x40) == 0x40)
            {
                if ((tetris.tetrominoes[currentTet].right[counter] + move_x + 1 <= 7) && (!collision(tetris.tetrominoes[currentTet], lines, move_x + 1, move_y, counter)))
                {
                    ++move_x;
                    LED_ClearScreen(0);
                }
            }
            break;

        case Transform_End:
            break;

        default:
            break;
    }
}

// -----------------------------------------------------------------------------
// Tetris Logic SM
// -----------------------------------------------------------------------------

enum Tetris_States { Tetris_Start, Tetris_Init, Tetris_Spawn, Tetris_Drop, Tetris_Score, Tetris_End } Tetris_State;
unsigned char down = 0;
unsigned char loop_time = 0;

void TickFct_Tetris()
{
    switch (Tetris_State)
    {
        case Tetris_Start:
            Tetris_State = Tetris_Init;
            break;

        case Tetris_Init:
            if ((~PINB & 0x01) == 0x00)
            {
                Tetris_State = Tetris_Spawn;
            }
            else
            {
                Tetris_State = Tetris_Init;
            }
            break;

        case Tetris_Spawn:
            if ((~PINB & 0x01) == 0x00)
            {
                if (!intersect)
                {
                    Tetris_State = Tetris_Drop;
                }
                else
                {
                    Tetris_State = Tetris_End;
                }
            }
            else
            {
                Tetris_State = Tetris_Init;
            }
            break;

        case Tetris_Drop:
            if ((~PINB & 0x01) == 0x00)
            {
                if (down)
                {
                    Tetris_State = Tetris_Score;
                }
                else
                {
                    Tetris_State = Tetris_Drop;
                }
            }
            else
            {
                Tetris_State = Tetris_Init;
            }
            break;

        case Tetris_Score:
            if ((~PINB & 0x01) == 0x00)
            {
                Tetris_State = Tetris_Spawn;
            }
            else
            {
                Tetris_State = Tetris_Init;
            } 
            break;

        case Tetris_End:
            if ((~PINB & 0x01) == 0x00)
            {
                Tetris_State = Tetris_End;
            }
            else
            {
                Tetris_State = Tetris_Init;
            }
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
            srand(rand());
            nextTet = (rand() % 7);
            intersect = 0;
            move_x = 3;
            move_y = 0;
            numLines = 0;
            score = 0;
            break;

        case Tetris_Spawn:
            currentTet = nextTet;
            nextTet = (rand() % 7);

            move_x = 3;
            move_y = 0;
            intersect = collision(tetris.tetrominoes[currentTet], lines, move_x, 0, counter);

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

                    down = 1;
                }
            }
            break;

        case Tetris_Score:
            down = 0;
            unsigned char numOnes = 0;
            unsigned char l = 0;
            unsigned char a, b, c;
            unsigned char fullLine[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
            for (b = 0; b < 8; ++b)
            {
                for (a = 0; a < 8; ++a)
                {
                    if (lines[a][b])
                    {
                        ++numOnes;
                    }
                }
                if (numOnes == 8)
                {
                    ++l;
                    fullLine[b] = 1;
                }
                numOnes = 0;
            }

            unsigned char m, n;
            for (c = 0; c < 8; ++c)
            {
                if (fullLine[c])
                {
                    for (n = c; n > 0; --n)
                    {
                        for (m = 0; m < 8; ++m)
                        {
                            lines[m][n] = lines[m][n - 1];
                        }
                    }
                }
            }

            if (l == 1)
            {
                score += 40;
            }
            else if (l == 2)
            {
                score += 100;
            }
            else if (l == 3)
            {
                score += 300;
            }
            else if (l >= 4)
            {
                score += 1200;
            }

            numLines += l;
            break;

        case Tetris_End:
            break;

        default:
            break;
    }
}

// -----------------------------------------------------------------------------
// LED Matrix SM
// -----------------------------------------------------------------------------

enum Tetris_Display_States {Tetris_Display_Start, Tetris_Display_Init, Tetris_Display, Tetris_Display_End } Tetris_Display_State;
unsigned char end_counter = 0;
void TickFct_Tetris_Display()
{
    switch (Tetris_Display_State)
    {
        case Tetris_Display_Start:
            Tetris_Display_State = Tetris_Display_Init;
            break;

        case Tetris_Display_Init:
            if ((~PINB & 0x01) == 0x00)
            {
                Tetris_Display_State = Tetris_Display;
            }
            else
            {
                Tetris_Display_State = Tetris_Display_Init;
            }
            break;

        case Tetris_Display:
            if ((~PINB & 0x01) == 0x00)
            {
                if (!intersect)
                {
                    Tetris_Display_State = Tetris_Display;
                }
                else
                {
                    Tetris_Display_State = Tetris_Display_End;
                }
            }
            else
            {
                Tetris_Display_State = Tetris_Display_Init;
            }
            break;

        case Tetris_Display_End:
            if ((~PINB & 0x01) == 0x00)
            {
                Tetris_Display_State = Tetris_Display_End;
            }
            else
            {
                Tetris_Display_State = Tetris_Display_Init;
            }
            break;

        default:
            Tetris_Display_State = Tetris_Display_Init;
            break;
    }

    switch (Tetris_Display_State)
    {
        case Tetris_Display_Start:
            break;

        case Tetris_Display_Init:
            end_counter = 0;
            PORTA = 0xFF;
            unsigned char a, b;
            for (a = 0; a < 8; ++a)
            {
                for (b = 0; b < 8; ++b)
                {
                    lines[a][b] = 0;
                }
            }
            LED_ClearScreen(5);
            break;

        case Tetris_Display:
            displayTetromino(tetris.tetrominoes[currentTet], move_x, move_y, counter, 5);
            displayLines(lines, 5);
            PORTA = tetris.tetrominoes[nextTet].digit;
            break;

        case Tetris_Display_End:
            if (!end_counter)
            {
                displayTetromino(tetris.tetrominoes[currentTet], move_x, move_y, counter, 5);
            }

            if (end_counter < 8)
            {
                unsigned char d = 0;
                for (d = 0; d < 8; ++d)
                {
                    LED_Pixel(d, 7 - end_counter, 0, 5);
                }
                ++end_counter;
            }
            PORTA = 0xFF;
            break;

        default:
            break;
    }
}

// -----------------------------------------------------------------------------
// LCD SM
// -----------------------------------------------------------------------------

enum Display_States { Disp_Start, Disp_Init, Display, GameOver } Display_State;
const unsigned char MSG[] = "Lines:          Score:          ";
const unsigned char GAMEOVER[] = "   Game  Over   ";
const unsigned char INITMSG[] = "  INITIALIZING  ";
unsigned char display_counter = 0;

void TickFct_DisplayMsg()
{
    char* lines_string = "        ";
    char* score_string = "        ";;

    switch (Display_State)
    {
        case Disp_Start:
            Display_State = Disp_Init;
            break;
        
        case Disp_Init:
            if ((~PINB & 0x01) == 0x00)
            {
                Display_State = Display;
            }
            else
            {
                Display_State = Disp_Init;
            }
            break;

        case Display:
            if ((~PINB & 0x01) == 0x00)
            {
                if (!intersect)
                {
                    Display_State = Display;
                }
                else
                {
                    Display_State = GameOver;
                }
            }
            else
            {
                Display_State = Disp_Init;
            }
            break;
        
        case GameOver:
            if ((~PINB & 0x01) == 0x00)
            {
                Display_State = GameOver;
            }
            else
            {
                Display_State = Disp_Init;
            }
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
            LCD_DisplayString(1, INITMSG);
            display_counter = 20;
            break;

        case Display:
            if (display_counter < 20)
            {
                ++display_counter;
            }
            else
            {
                LCD_DisplayString(1, MSG);

                sprintf(lines_string, "%8d", numLines);
                LCD_DisplayString(9, lines_string);

                sprintf(score_string, "%8d", score);
                LCD_DisplayString(25, score_string);

                display_counter = 0;
            }
            break;

        case GameOver:
            LCD_DisplayString(1, GAMEOVER);
            break;
    }
}

// -----------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------

int main(void)
{
    DDRA = 0xFC; PORTA = 0x03;
    DDRB = 0x08; PORTB = 0xF7;
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
    ADC_init();

    unsigned long Tetris_elapsedTime = 20;
    unsigned long Transform_elapsedTime = 100;
    unsigned long TD_elapsedTime = 20;
    unsigned long Display_elapsedTime = 100;
    const unsigned long timerPeriod = 1;

    Tetris_State = Tetris_Start;
    Transform_State = Transform_Start;
    Tetris_Display_State = Tetris_Display_Start;
    Display_State = Disp_Start;
    
    TimerSet(timerPeriod);
    TimerOn();
    
    LCD_init();
    srand(ADC);
    srand(rand());

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
        
        if (Display_elapsedTime >= 50)
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

