#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "gameLogic.h"
#include "printing.h"

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

void setAiVariables(int p_argc, char *p_argv[], bool *p_playWithX, bool *p_aiEnabled)
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
                *p_playWithX = true;
            }   
            if(strcmp(p_argv[1],"-0") == 0 || strcmp(p_argv[2],"-0") == 0)
            {
                *p_playWithX = false;
            }   
        }
        else if(strcmp(p_argv[1],"-ai") == 0)
        {
            *p_aiEnabled = true;
        }
    }
}

int main(int argc, char *argv[])
{
    bool playWithX = true;
    bool aiEnabled = false;

    setAiVariables(argc, argv, &playWithX, &aiEnabled);

    printf("ai %d, x %d", aiEnabled, playWithX);
    return 0;

    bool bExit = 0;
    bool bPlayerTurn = 0;
    int nUserInput;	
    int npBackendTable[3][3] = { 
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                };

    initCurses();

    while(!bExit)
    {
        clear();
        
        printTable(npBackendTable);
        // actually print on the screen
        refresh();			        
        // wait for user input
        nUserInput = getch();		
        
        updateTable(npBackendTable, nUserInput, &bPlayerTurn);

        bExit = checkExit(nUserInput) || printWinner(npBackendTable) || printDraw(npBackendTable);
    }
    // End curses mode
    endwin();			

	return 0;
}