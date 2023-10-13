#include <ncurses.h>

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
    int nWinner;
    
    initCurses();

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        return 1;
    }

    dealWithColors();

    while(!bExit)
    {
        clear();

        printTable(npBackendTable);
        // actually print on the screen
        refresh();			        
        // wait for user input
        nUserInput = getch();		
        updateTable(npBackendTable, nUserInput, &bPlayerTurn);

        nWinner = checkWinCondition(npBackendTable);        
        if(nWinner)
        {
            clear();
            printTable(npBackendTable);
            refresh();

            mvprintw(0, 0, "the winner is player %d", nWinner);
            refresh();
            getch();
            bExit = true;
        }
        bExit = checkExit(nUserInput) || bExit;
    }
    // End curses mode
    endwin();			

	return 0;
}