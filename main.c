#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "gameLogic.h"
#include "printing.h"
#include "ai.h"

#define X_TURN 0
#define Z_TURN 1 // zero = true

#define DEFAULT_INPUT_VALUE 0

enum menuOptions{multiPlayer, singlePlayer, exitGame};
enum aiMenuOptions{playWithX, playWith0, aiDifficulty};

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

void enterAiMenu(bool *isAi0)
{
    bool changedState = true;
    bool inAiMenu = true;
    int input;
    int menuOptionSelected = playWithX;

    while(inAiMenu)
    {
        int rows, cols;
        getmaxyx(stdscr, rows, cols);

        if(!changedState)
        {
            input = getch();
        }

        switch(menuOptionSelected)
        {
            case playWithX:
                if(changedState)
                {
                    clear();
                    attron(COLOR_PAIR(RED_WHITE_PAIR));
                    attron(A_BOLD);
                    mvprintw(rows/2-2, cols/2 - 9, "Play with X");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(RED_WHITE_PAIR));
                    mvprintw(rows/2-1, cols/2 - 9, "Play with 0");
                    mvprintw(rows/2, cols/2 - 9, "Difficulty (default max)");
                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP)
                {
                    menuOptionSelected = aiDifficulty;
                    changedState = true;
                    input = DEFAULT_INPUT_VALUE;
                }

                if(input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = (menuOptionSelected + 1) % 3;
                    changedState = true;
                    input = DEFAULT_INPUT_VALUE;
                }

                if(input == '\n' || input == ' ')
                {
                    *isAi0 = true;
                    inAiMenu = false;
                }

                break;

            case playWith0:
                if(changedState)
                {
                    clear();
                    mvprintw(rows/2-2, cols/2 - 9, "Play with X");
                    attron(COLOR_PAIR(RED_WHITE_PAIR));
                    attron(A_BOLD);
                    mvprintw(rows/2-1, cols/2 - 9, "Play with 0");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(RED_WHITE_PAIR));
                    mvprintw(rows/2, cols/2 - 9, "Difficulty (default max)");
                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP)
                {
                    menuOptionSelected = (menuOptionSelected - 1) % 3;
                    changedState = true;
                    input = DEFAULT_INPUT_VALUE;
                }
                
                if(input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = (menuOptionSelected + 1) % 3;
                    changedState = true;
                    input = DEFAULT_INPUT_VALUE;
                }

                if(input == '\n' || input == ' ')
                {
                    *isAi0 = false;
                    inAiMenu = false;
                }

                break;
            
            case aiDifficulty:
                if(changedState)
                {
                    clear();
                    mvprintw(rows/2-2, cols/2 - 9, "Play with X");
                    mvprintw(rows/2-1, cols/2 - 9, "Play with 0");
                    attron(COLOR_PAIR(RED_WHITE_PAIR));
                    attron(A_BOLD);
                    mvprintw(rows/2, cols/2 - 9, "Difficulty (default max)");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(RED_WHITE_PAIR));
                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP)
                {
                    menuOptionSelected = (menuOptionSelected - 1) % 3;
                    changedState = true;
                    input = DEFAULT_INPUT_VALUE;
                }
                
                if(input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = (menuOptionSelected + 1) % 3;
                    changedState = true;
                    input = DEFAULT_INPUT_VALUE;
                }

                if(input == '\n' || input == ' ')
                {

                }

                break;
        }
    }
}

bool selectGameMode(bool *isAi0, bool *aiEnabled)
{
    bool changedState = true;
    bool inMainMenu = true;
    int menuOptionSelected = multiPlayer;
    int input = DEFAULT_INPUT_VALUE; 

    while(inMainMenu)
    {
        int rows, cols;
        getmaxyx(stdscr, rows, cols);
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
                    attron(COLOR_PAIR(RED_WHITE_PAIR));
                    attron(A_BOLD);
                    mvprintw(rows/2-2, cols/2-9, "Play with a friend");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(RED_WHITE_PAIR));
                    mvprintw(rows/2-1, cols/2-9, "Play against the AI");
                    mvprintw(rows/2, cols/2-9, "Exit");
                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP)
                {
                    menuOptionSelected = exitGame;
                    changedState = true;
                    input = DEFAULT_INPUT_VALUE;
                }
                
                if(input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = (menuOptionSelected + 1) % 3;
                    changedState = true;
                    input = DEFAULT_INPUT_VALUE;
                }

                if(input == '\n' || input == ' ')
                {
                    *aiEnabled = false;
                    inMainMenu = false;
                }

                break;

            case singlePlayer:
                if(changedState)
                {
                    clear();
                    mvprintw(rows/2-2, cols/2-9, "Play with a friend");
                    attron(COLOR_PAIR(RED_WHITE_PAIR));
                    attron(A_BOLD);
                    mvprintw(rows/2-1, cols/2-9, "Play against the AI");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(RED_WHITE_PAIR));
                    mvprintw(rows/2, cols/2-9, "Exit");
                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP)
                {
                    menuOptionSelected = (menuOptionSelected - 1) % 3;
                    changedState = true;
                    input = DEFAULT_INPUT_VALUE;
                }
                
                if(input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = (menuOptionSelected + 1) % 3;
                    changedState = true;
                    input = DEFAULT_INPUT_VALUE;
                }

                if(input == '\n' || input == ' ')
                {
                    *aiEnabled = true;
                    inMainMenu = false;
                }

                break;
            
            case exitGame:
                if(changedState)
                {
                    clear();
                    mvprintw(rows/2-2, cols/2-9, "Play with a friend");
                    mvprintw(rows/2-1, cols/2-9, "Play against the AI");
                    attron(COLOR_PAIR(RED_WHITE_PAIR));
                    attron(A_BOLD);
                    mvprintw(rows/2, cols/2-9, "Exit");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(RED_WHITE_PAIR));
                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP)
                {
                    menuOptionSelected = (menuOptionSelected - 1) % 3;
                    changedState = true;
                    input = DEFAULT_INPUT_VALUE;
                }
                
                if(input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = (menuOptionSelected + 1) % 3;
                    changedState = true;
                    input = DEFAULT_INPUT_VALUE;
                }

                if(input == '\n' || input == ' ')
                {
                    return true;
                }

                break;
        }
    }

    if(*aiEnabled)
    {
        enterAiMenu(isAi0);
    }

    return false;
}

void clearTable(int table[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            table[i][j] = 0;
        }
    }
}

int main()
{
    bool isAi0 = true;
    bool aiEnabled = false;
    // setAiVariables(argc, argv, );

    bool bExit = false;
    bool bPlayerTurn = X_TURN;
    int nUserInput;	
    int npBackendTable[3][3] = { 
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                };

    initCurses();

    bExit = selectGameMode(&isAi0, &aiEnabled);
    if(aiEnabled && isAi0 == false)
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
        if(aiEnabled && successfulUpdate && bPlayerTurn == isAi0)
        {
            getAiMove(npBackendTable, bPlayerTurn);
            bPlayerTurn = !bPlayerTurn;
        }

        bExit = checkExit(nUserInput) || printWinner(npBackendTable) || printDraw(npBackendTable);
        
        if(bExit)
        {
            bExit = selectGameMode(&isAi0, &aiEnabled);
            clearTable(npBackendTable);
            bPlayerTurn = X_TURN;

            if(aiEnabled && isAi0 == false)
            {
                getAiMove(npBackendTable, bPlayerTurn);
                bPlayerTurn = !bPlayerTurn;
            }
        }
    }
    // End curses mode
    endwin();			

	return 0;
}