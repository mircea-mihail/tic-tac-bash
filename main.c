#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "usefulDefines.h"
#include "gameLogic.h"
#include "printing.h"
#include "ai.h"
#include "menu.h"

void initCurses()
{
    // Start curses mode
    initscr();
    // don't show user input unless otherwise stated 			        
    noecho();
    // hide the cursor
    curs_set(0);

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    dealWithColors();

    keypad(stdscr, TRUE);
    printw(("\033[?1003h\n"));

    // Don't mask any mouse events
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
}

void setAiVariables(int p_argc, char *p_argv[], bool *isAi0, bool *p_aiEnabled)
{
    if(p_argc > 1)
    {
        if(p_argc > 2)
        {
            if(strcmp(p_argv[1],"-ai") == 0 || strcmp(p_argv[2],"-ai") == 0)
            {
                *p_aiEnabled = true;
            }
            if(strcmp(p_argv[1],"-x") == 0 || strcmp(p_argv[2],"-x") == 0)
            {
                *isAi0 = true;
            }   
            if(strcmp(p_argv[1],"-0") == 0 || strcmp(p_argv[2],"-0") == 0)
            {
                *isAi0 = false;
            }   
        }
        else if(strcmp(p_argv[1],"-ai") == 0)
        {
            *p_aiEnabled = true;
        }
    }
}

void clearTable(int table[ROWS][COLS])
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            table[i][j] = 0;
        }
    }
}

int main()
{
    bool isAi0 = true;
    bool aiEnabled = false;
    int difficulty = impossible;
    // setAiVariables(argc, argv, );

    bool bExit = false;
    bool bPlayerTurn = X_TURN;
    int nUserInput;	
    int npBackendTable[ROWS][COLS] = { 
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                };

    initCurses();

    bExit = selectGameMode(&isAi0, &aiEnabled);
    if(aiEnabled && !bExit)
    {
        enterAiMenu(&isAi0, &difficulty);
    }

    if(aiEnabled && isAi0 == false)
    {
        getAiMove(npBackendTable, bPlayerTurn, difficulty);
        bPlayerTurn = !bPlayerTurn;
    }

    while(!bExit)
    {
        clear();
        
        printTable(npBackendTable);
        // actually print on the screen
        refresh();			        
        // wait for user input
        nUserInput = getch();		
        
        bool successfulUpdate = updateTable(npBackendTable, nUserInput, &bPlayerTurn);
        if(aiEnabled && successfulUpdate && bPlayerTurn == isAi0)
        {
            getAiMove(npBackendTable, bPlayerTurn, difficulty);
            bPlayerTurn = !bPlayerTurn;
        }

        bExit = checkExit(nUserInput) || printWinner(npBackendTable) || printDraw(npBackendTable);
        
        if(bExit)
        {
            bExit = selectGameMode(&isAi0, &aiEnabled);
            if(aiEnabled && !bExit)
            {
                enterAiMenu(&isAi0, &difficulty);
            }

            clearTable(npBackendTable);
            bPlayerTurn = X_TURN;

            if(aiEnabled && isAi0 == false)
            {
                getAiMove(npBackendTable, bPlayerTurn, difficulty);
                bPlayerTurn = !bPlayerTurn;
            }
        }
    }
    // End curses mode
    endwin();			

	return 0;
}