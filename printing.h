#ifndef PRINTING_H
#define PRINTING_H

#include <ncurses.h>

#define BLACK_PAIR 1
#define RED_PAIR 2
#define GREEN_PAIR 3
#define YELLOW_PAIR 4
#define BLUE_PAIR 5
#define MAGENTA_PAIR 6
#define CYAN_PAIR 7 
#define WHITE_PAIR 8

#define min(a, b) (a < b ? a : b)

void dealWithColors();

void mvPrintX(int p_nRow, int p_nCol, int p_nSize, bool p_bThick);

void mvPrint0(int p_nRow, int p_nCol, int p_nSize, bool p_bThick);

void printTableLines(int p_nRows, int p_nCols, int p_nCellSize, int p_nScreenGap);

void printTable(int npTable[3][3]);

#endif //PRINTING_H