#ifndef PRINTING_H
#define PRINTING_H

#include <ncurses.h>
#include "usefulDefines.h"

#define BLACK_PAIR 1
#define RED_PAIR 2
#define GREEN_PAIR 3
#define YELLOW_PAIR 4
#define BLUE_PAIR 5
#define MAGENTA_PAIR 6
#define CYAN_PAIR 7 
#define WHITE_PAIR 8
#define RED_WHITE_PAIR 9

#define min(a, b) (a < b ? a : b)

#define CELL_SIZE_DIV_FACTOR 2
#define SCREEN_GAP_DIV_FACTOR 5

// initialises background/foreground text colors
void dealWithColors();

// prints an x using a mathematical formula in the correct row and col
// not the character but a "drawing" using full terminal char spots
void mvPrintX(int p_nRow, int p_nCol, int p_nSize, bool p_bThick);

// prints a 0 using a mathematical formula in the correct row and col
// not the character but a "drawing" using full terminal char spots
void mvPrint0(int p_nRow, int p_nCol, int p_nSize, bool p_bThick);

// prints the lines of the tic tac toe game table
void printTableLines(int p_nRows, int p_nCols, int p_nCellSize, int p_nScreenGap);

// gets the table data structure and prints it using the printing functions to make it big and nice 
void printTable(int npTable[ROWS][COLS]);

#endif //PRINTING_H