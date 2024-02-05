#include <ncurses.h>
#include "gameLogic.h"
#include "printing.h"

bool checkMouse(int npTable[ROWS][COLS], int nUserInput, bool* bpPlayerTurn)
{
    int nRows, nCols;
    getmaxyx(stdscr, nRows, nCols);

    MEVENT mMouseEvent;
    int nClickRow, nClickCol;
    int nTableIndexRow, nTableIndexCol;

    // int nCellSize =  min(nRows, nCols) / CELL_SIZE_DIV_FACTOR;
    int nScreenGap = min(nRows, nCols) / SCREEN_GAP_DIV_FACTOR;

    int nColumnLength = nRows - 2*nScreenGap + 3;

    if (nUserInput == KEY_MOUSE && getmouse(&mMouseEvent) == OK)
    {
        nClickCol = mMouseEvent.x, nClickRow = mMouseEvent.y;
        if (   (mMouseEvent.bstate & (BUTTON1_CLICKED | BUTTON1_PRESSED)) 
            || (mMouseEvent.bstate & (BUTTON3_CLICKED | BUTTON3_PRESSED)))
        {
            if( nScreenGap > nClickRow || nRows - nScreenGap < nClickRow 
                || nCols/2 + nColumnLength < nClickCol || nCols/2 - nColumnLength > nClickCol )
            {
                return false;
            }
            
            nTableIndexRow = min((int)((nClickRow-nScreenGap) / ((float)(nRows-2*nScreenGap)) * 3), 2);
            nTableIndexCol = min((int)((nClickCol-(nCols-nColumnLength*2)/2.0) / (float)(nColumnLength*2) * 3), 2);

            if(npTable[nTableIndexRow][nTableIndexCol] == 0)
            {
                npTable[nTableIndexRow][nTableIndexCol] = *bpPlayerTurn ? ZERO : EX;
                return true;
            }
        }
    }

    return false;
}

bool updateTable(int npTable[ROWS][COLS], int nUserInput, bool* bpPlayerTurn)
{
    switch(nUserInput)
    { 
        case 'q': 
            if(npTable[0][0] == 0)
                npTable[0][0] = *bpPlayerTurn ? ZERO : EX; 
            else
                return false;
            break;
        case 'w': 
            if(npTable[0][1] == 0)
                npTable[0][1] = *bpPlayerTurn ? ZERO : EX; 
            else
                return false;
            break;
        case 'e':
            if(npTable[0][2] == 0) 
                npTable[0][2] = *bpPlayerTurn ? ZERO : EX; 
            else
                return false;
            break;
        case 'a': 
            if(npTable[1][0] == 0)
                npTable[1][0] = *bpPlayerTurn ? ZERO : EX; 
            else
                return false;
            break;
        case 's': 
            if(npTable[1][1] == 0)
                npTable[1][1] = *bpPlayerTurn ? ZERO : EX; 
            else
                return false;
            break;
        case 'd':
            if(npTable[1][2] == 0) 
                npTable[1][2] = *bpPlayerTurn ? ZERO : EX; 
            else
                return false;
            break;
        case 'z': 
            if(npTable[2][0] == 0)
                npTable[2][0] = *bpPlayerTurn ? ZERO : EX; 
            else
                return false;
            break;
        case 'x': 
            if(npTable[2][1] == 0)
                npTable[2][1] = *bpPlayerTurn ? ZERO : EX; 
            else  
                return false;
            break;
        case 'c': 
            if(npTable[2][2] == 0)
                npTable[2][2] = *bpPlayerTurn ? ZERO : EX; 
            else
                return false;
            break;
        default: 
            if(!checkMouse(npTable, nUserInput, bpPlayerTurn))
            {
                return false;
            }
            break;
    }

    *bpPlayerTurn = !(*bpPlayerTurn);
    return true;
}

// returns the winning player
int checkWinCondition(int p_npTable[ROWS][COLS])
{
    bool winCondition = true;
    //check diagonal

    for(int i = 0; i < 2; i++)
    {
        winCondition = winCondition && (p_npTable[i][i] == p_npTable[i+1][i+1]) && (p_npTable[i][i] != 0);
    }
    if(winCondition)
    {
        return p_npTable[0][0];
    }

    //check other diagonal
    winCondition = true;

    for(int i = 0; i < 2; i++)
    {
        winCondition = winCondition && (p_npTable[i][2-i] == p_npTable[i+1][2-(i+1)]) && (p_npTable[i][2-i] != 0);
    }
    if(winCondition)
    {
        return p_npTable[0][2];
    }

    //check columns
    //PROBLEMS
    for(int j = 0; j <= 2; j++)
    {
        winCondition = true;

        for(int i = 0; i < 2; i++)
        {
            winCondition = winCondition && (p_npTable[j][i] == p_npTable[j][i+1]) && (p_npTable[j][i] != 0);
        }
        if(winCondition)
        {
            return p_npTable[j][0];
        }
    }
    
    //check rows

    for(int j = 0; j <= 2; j++)
    {
        winCondition = true;

        for(int i = 0; i < 2; i++)
        {
            winCondition = winCondition && (p_npTable[i][j] == p_npTable[i+1][j]) && (p_npTable[i][j] != 0);
        }
        if(winCondition)
        {
            return p_npTable[0][j];
        }
    }

    return 0;
}

void waitForInput()
{
    int cValidEndKey = 0;
    MEVENT mMouseEvent;

    while(   (cValidEndKey < 'A' || cValidEndKey > 'z' 
             || (cValidEndKey > 'Z' && cValidEndKey < 'a'))
             && cValidEndKey != ' ' && cValidEndKey != '\n')
    {
        cValidEndKey = getch();
    
        if (cValidEndKey == KEY_MOUSE && getmouse(&mMouseEvent) == OK)
        {
            if (   (mMouseEvent.bstate & (BUTTON1_CLICKED | BUTTON1_PRESSED)) 
                || (mMouseEvent.bstate & (BUTTON3_CLICKED | BUTTON3_PRESSED)))
            {
                return;
            }
        }   
    }
}

bool printWinner(int p_npTable[ROWS][COLS])
{
    int nWinner = checkWinCondition(p_npTable);        
    if(nWinner)
    {
        clear();
        printTable(p_npTable);
        
        int rows, cols;
        getmaxyx(stdscr, rows, cols);

        attron(COLOR_PAIR(RED_WHITE_PAIR));
        attron(A_BOLD);
        mvprintw(rows/2, cols/2-3, " %c WON ", nWinner == 1 ? '0' : 'X' );
        attroff(COLOR_PAIR(RED_WHITE_PAIR));
        attroff(A_BOLD);

        refresh();

        waitForInput();
        return true;
    }
    return false;
}

bool checkDraw(int p_npTable[ROWS][COLS])
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(p_npTable[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

bool printDraw(int p_npTable[ROWS][COLS])
{
    bool bWasDraw = checkDraw(p_npTable);

    if(bWasDraw)
    {
        clear();
        printTable(p_npTable);

        int rows, cols;
        getmaxyx(stdscr, rows, cols);
        
        attron(COLOR_PAIR(RED_WHITE_PAIR));
        attron(A_BOLD);
        mvprintw(rows/2, cols/2-3, " DRAW ");  
        attroff(COLOR_PAIR(RED_WHITE_PAIR));
        attroff(A_BOLD);
        
        refresh();

        waitForInput();
        return true;
    }
    return false;    
}

bool checkExit(int nUserInput)
{
    if(nUserInput == 'Q'){
        return 1;
    }
    return 0;
}
