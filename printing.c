#include "printing.h"

void dealWithColors()
{
    start_color();
    
    init_pair(BLACK_PAIR, COLOR_BLACK, COLOR_BLACK);
    init_pair(RED_PAIR, COLOR_RED, COLOR_RED);
    init_pair(GREEN_PAIR, COLOR_GREEN, COLOR_GREEN);
    init_pair(YELLOW_PAIR, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(BLUE_PAIR, COLOR_BLUE, COLOR_BLUE);
    init_pair(MAGENTA_PAIR, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(CYAN_PAIR, COLOR_CYAN, COLOR_CYAN);
    init_pair(WHITE_PAIR, COLOR_WHITE, COLOR_WHITE);

    use_default_colors(); //keeps my background transparrent 
}


void mvPrintX(int p_nRow, int p_nCol, int p_nSize, bool p_bThick)
{
    // mvprintw(p_row, p_col, "\033[;41m \n");
    char ch = ' ';

    for(int i = 0; i <= p_nSize; i++)
    {
        mvaddch(p_nRow-i/2, p_nCol+i/2, ch | COLOR_PAIR(BLUE_PAIR));
        mvaddch(p_nRow+i/2, p_nCol-i/2, ch | COLOR_PAIR(BLUE_PAIR));
    }
    for(int i = 0; i <= p_nSize; i++)
    {
        mvaddch(p_nRow-i/2, p_nCol-i/2, ch | COLOR_PAIR(BLUE_PAIR));
        mvaddch(p_nRow+i/2, p_nCol+i/2, ch | COLOR_PAIR(BLUE_PAIR));
    }

    if(p_bThick)
    {
        p_nRow += 1;

        for(int i = 0; i <= p_nSize; i++)
        {
            mvaddch(p_nRow-i/2, p_nCol+i/2, ch | COLOR_PAIR(BLUE_PAIR));
            mvaddch(p_nRow+i/2, p_nCol-i/2, ch | COLOR_PAIR(BLUE_PAIR));
        }   

        mvaddch(p_nRow+p_nSize/2, p_nCol-p_nSize/2-1, ch | COLOR_PAIR(BLUE_PAIR));
        mvaddch(p_nRow+p_nSize/2, p_nCol+p_nSize/2+1, ch | COLOR_PAIR(BLUE_PAIR));

        for(int i = 0; i <= p_nSize; i++)
        {
            mvaddch(p_nRow-i/2, p_nCol-i/2, ch | COLOR_PAIR(BLUE_PAIR));
            mvaddch(p_nRow+i/2, p_nCol+i/2, ch | COLOR_PAIR(BLUE_PAIR));
        }

        mvaddch(p_nRow-p_nSize/2-1, p_nCol-p_nSize/2-1, ch | COLOR_PAIR(BLUE_PAIR));
        mvaddch(p_nRow-p_nSize/2-1, p_nCol+p_nSize/2+1, ch | COLOR_PAIR(BLUE_PAIR));
    }
}

void mvPrint0(int p_nRow, int p_nCol, int p_nSize, bool p_bThick)
{
    // mvprintw(p_row, p_col, "\033[;41m \n");
    char ch = ' ';

    for(int i = 1; i < p_nSize; i++)
    {
        mvaddch(p_nRow-i/2, p_nCol-p_nSize/2, ch | COLOR_PAIR(BLUE_PAIR));
        mvaddch(p_nRow+i/2, p_nCol-p_nSize/2, ch | COLOR_PAIR(BLUE_PAIR));
        
        mvaddch(p_nRow-i/2, p_nCol+p_nSize/2, ch | COLOR_PAIR(BLUE_PAIR));
        mvaddch(p_nRow+i/2, p_nCol+p_nSize/2, ch | COLOR_PAIR(BLUE_PAIR));
    }

    for(int i = 1; i < p_nSize; i++)
    {
        mvaddch(p_nRow-p_nSize/2, p_nCol+i/2, ch | COLOR_PAIR(BLUE_PAIR));
        mvaddch(p_nRow-p_nSize/2, p_nCol-i/2, ch | COLOR_PAIR(BLUE_PAIR));

        mvaddch(p_nRow+p_nSize/2, p_nCol-i/2, ch | COLOR_PAIR(BLUE_PAIR));
        mvaddch(p_nRow+p_nSize/2, p_nCol+i/2, ch | COLOR_PAIR(BLUE_PAIR));
    }

    if(p_bThick)
    {
        for(int i = 1; i < p_nSize; i++)
        {
            mvaddch(p_nRow-i/2, p_nCol-p_nSize/2-1, ch | COLOR_PAIR(BLUE_PAIR));
            mvaddch(p_nRow+i/2, p_nCol-p_nSize/2-1, ch | COLOR_PAIR(BLUE_PAIR));
            
            mvaddch(p_nRow-i/2, p_nCol+p_nSize/2+1, ch | COLOR_PAIR(BLUE_PAIR));
            mvaddch(p_nRow+i/2, p_nCol+p_nSize/2+1, ch | COLOR_PAIR(BLUE_PAIR));
        }
        
    }
}

void printTableLines(int p_nRows, int p_nCols, int p_nCellSize, int p_nScreenGap)
{
    // |   |
    int nColumnStart = (p_nCols-p_nCellSize)/2;
    for( int i = p_nScreenGap; i < p_nRows - p_nScreenGap; i++)
    {
        char ch = ' ';
        mvaddch(i, nColumnStart, ch | COLOR_PAIR(RED_PAIR));
        mvaddch(i, nColumnStart + 1, ch | COLOR_PAIR(RED_PAIR));
        mvaddch(i, nColumnStart + p_nCellSize, ch | COLOR_PAIR(RED_PAIR));
        mvaddch(i, nColumnStart + p_nCellSize + 1, ch | COLOR_PAIR(RED_PAIR));
    }
    int nColumnLength = p_nRows - 2*p_nScreenGap + 3; // 3 is an arbitrary number to make horizontal lines a bit longer
    // a char is twice as tall as is is wide so the cellsize needs adjustment
    p_nCellSize /= 2; 

    int nRowStart = (p_nRows-p_nCellSize)/2;
    
    for( int i = p_nCols/2; i < p_nCols/2 + nColumnLength; i++)
    {
        char ch = ' ';
        //add to the right of the center
        mvaddch(nRowStart, i, ch | COLOR_PAIR(RED_PAIR));
        mvaddch(nRowStart + p_nCellSize, i, ch | COLOR_PAIR(RED_PAIR));

        //and to the left
        mvaddch(nRowStart, p_nCols - i, ch | COLOR_PAIR(RED_PAIR));
        mvaddch(nRowStart + p_nCellSize, p_nCols - i, ch | COLOR_PAIR(RED_PAIR));
    }
}

void printTable(int npTable[3][3])
{
    bool bThickLetters = false;
    int nRows, nCols;
    int nStartRow, nStartCol;

    getmaxyx(stdscr, nRows, nCols);

    if(min(nRows, nCols) > 43)
    {
        bThickLetters = true;
    }

    int nCellSize =  min(nRows, nCols) / CELL_SIZE_DIV_FACTOR;
    int nScreenGap = min(nRows, nCols) / SCREEN_GAP_DIV_FACTOR;

    nStartRow = nRows/2-1;
    nStartCol = (nCols-6)/2;

    printTableLines(nRows, nCols, nCellSize, nScreenGap);

    // mvPrintX(nRows/2, nCols/2, nScreenGap-1, bThickLetters);
    // mvPrint0(nRows/2, nCols/2, nScreenGap-1, bThickLetters);
    
    for(int i = 0; i < 3; i++)
    {
        move(nStartRow, nStartCol);
        for(int j = 0; j < 3; j++)
        {
            // printw("%d ", npTable[i][j]);
            if(npTable[i][j] == 1)
            {
                mvPrint0(nRows/2+(i-1)*nCellSize/2, nCols/2+(j-1)*nCellSize, nScreenGap-1, bThickLetters);
            }
            if(npTable[i][j] == 2){
                mvPrintX(nRows/2+(i-1)*nCellSize/2, nCols/2+(j-1)*nCellSize, nScreenGap-1, bThickLetters);
            }
        }
        nStartRow +=1;
    } 
}