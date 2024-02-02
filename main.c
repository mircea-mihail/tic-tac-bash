#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "gameLogic.h"
#include "printing.h"
#include "ai.h"

#define X_TURN 0
#define Z_TURN 1 // zero = true

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
    // Enables keypad mode. This makes (at least for me) mouse events getting
    // reported as KEY_MOUSE, instead as of random letters.
    // keypad(stdscr, TRUE);

    // Don't mask any mouse events
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    // printf("\033[?1003h\n"); // Makes the terminal report mouse movement events
}

void setAiVariables(int p_argc, char *p_argv[], bool *isAiX, bool *p_aiEnabled)
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
                *isAiX = true;
            }   
            if(strcmp(p_argv[1],"-0") == 0 || strcmp(p_argv[2],"-0") == 0)
            {
                *isAiX = false;
            }   
        }
        else if(strcmp(p_argv[1],"-ai") == 0)
        {
            *p_aiEnabled = true;
        }
    }
}

#define DEFAULT_INPUT_VALUE 0
enum menuOptions{multiPlayer, singlePlayer, playWithX, playWith0};

void selectGameMode()
{
    bool passGetch = false;
    bool passedOnce = false;
    bool changedState = true;
    bool inMainMenu = true;
    int menuOptionSelected = multiPlayer;
    int input = DEFAULT_INPUT_VALUE; 

    while(inMainMenu)
    {
        if(!changedState)
        {
            input = getch();
        }

        switch(menuOptionSelected)
        {
            case multiPlayer:
                if(changedState)
                {
                    clear();
                    mvprintw(0, 0, "in multi player");
                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP || input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = singlePlayer;
                    changedState = true;
                    input = DEFAULT_INPUT_VALUE;
                }

                break;

            case singlePlayer:
                if(changedState)
                {
                    clear();
                    mvprintw(0, 0, "in single player");
                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP || input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = multiPlayer;
                    changedState = true;
                    input = DEFAULT_INPUT_VALUE;
                }

                break;
        }
    }
}

int main(int argc, char *argv[])
{
    bool isAiX = true;
    bool aiEnabled = false;
    // setAiVariables(argc, argv, &isAiX, &aiEnabled);

    bool bExit = false;
    bool bPlayerTurn = X_TURN;
    int nUserInput;	
    int npBackendTable[3][3] = { 
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                };

    initCurses();

    selectGameMode();

    if(aiEnabled && isAiX == false)
    {
        getAiMove(npBackendTable, bPlayerTurn);
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
        if(aiEnabled && successfulUpdate && bPlayerTurn == isAiX)
        {
            getAiMove(npBackendTable, bPlayerTurn);
            bPlayerTurn = !bPlayerTurn;
        }

        bExit = checkExit(nUserInput) || printWinner(npBackendTable) || printDraw(npBackendTable);
    }
    // End curses mode
    endwin();			

	return 0;
}