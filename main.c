#include <ncurses.h>
#include <stdlib.h>

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

    // Enables keypad mode. This makes (at least for me) mouse events getting
    // reported as KEY_MOUSE, instead as of random letters.
    // keypad(stdscr, TRUE);

    // Don't mask any mouse events
    mousemask(BUTTON1_CLICKED | REPORT_MOUSE_POSITION, NULL);

    // printf("\033[?1003h\n"); // Makes the terminal report mouse movement events
}

int main()
{
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

        // if(nUserInput == KEY_MOUSE)
        // {
        //     MEVENT event;
        //     if (getmouse(&event) == OK) 
        //     {
        //         printw("Mouse at row=%d, column=%d bstate=0x%08lx", 
        //                         event.y,   event.x,  event.bstate);
        //         if(event.bstate & BUTTON1_PRESSED)
        //         {
        //             printw("YES THE LEFT CLICK IS WINNER");
        //         }
        //     }
        //     else 
        //     {
        //         printw("Got bad mouse event.");
        //     }
        // }
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