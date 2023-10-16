#include <ncurses.h>
#include "gameLogic.h"
#include "printing.h"

bool checkMouse(int npTable[3][3], int nUserInput, bool* bpPlayerTurn){

    // if()

    return false;
}

void updateTable(int npTable[3][3], int nUserInput, bool* bpPlayerTurn)
{
    switch(nUserInput)
    { 
        case 'q': 
            if(npTable[0][0] == 0)
                npTable[0][0] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 'w': 
            if(npTable[0][1] == 0)
                npTable[0][1] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 'e':
            if(npTable[0][2] == 0) 
                npTable[0][2] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 'a': 
            if(npTable[1][0] == 0)
                npTable[1][0] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 's': 
            if(npTable[1][1] == 0)
                npTable[1][1] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 'd':
            if(npTable[1][2] == 0) 
                npTable[1][2] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 'z': 
            if(npTable[2][0] == 0)
                npTable[2][0] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 'x': 
            if(npTable[2][1] == 0)
                npTable[2][1] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 'c': 
            if(npTable[2][2] == 0)
                npTable[2][2] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        default: 
            if(!checkMouse(npTable, nUserInput, bpPlayerTurn))
            {
                return;
            }
            break;
    }

    // change turn if the other player made a valid move, else, let him try again 
    // if(mouseInput)
    // {
        *bpPlayerTurn = !(*bpPlayerTurn);
    // }
}

// returns the winning player
int checkWinCondition(int p_npTable[3][3])
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
        winCondition = winCondition && (p_npTable[i][2-i] == p_npTable[i+1][2-(i+1)]) && (p_npTable[i][i] != 0);
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

bool printWinner(int p_npTable[3][3])
{
    int nWinner = checkWinCondition(p_npTable);        
    if(nWinner)
    {
        clear();
        printTable(p_npTable);
        refresh();

        mvprintw(0, 0, "the winner is %c", nWinner == 1 ? '0' : 'X' );
        
        refresh();
        getch();
        return true;
    }
    return false;
}

bool checkDraw(int p_npTable[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(p_npTable[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

bool printDraw(int p_npTable[3][3])
{
    bool bWasDraw = checkDraw(p_npTable);

    if(bWasDraw)
    {
        clear();
        printTable(p_npTable);
        refresh();

        mvprintw(0, 0, "The game ended in a DRAW");
        
        refresh();
        getch();
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
