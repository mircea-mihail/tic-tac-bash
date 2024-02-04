#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "usefulDefines.h"
#include "gameLogic.h"
#include "printing.h"
#include "ai.h"

#define X_TURN 0
#define Z_TURN 1 // zero = true

#define MAIN_MENU_OPTIONS 3
#define AI_MENU_OPTIONS 3
#define AI_SUBMENU_OPTIONS 7

#define VALID_MENU_INPUTS 6
#define DEFAULT_INPUT_VALUE 0

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

void enterAiMenu(bool *isAi0, int *p_difficulty)
{
    int validInputs[VALID_MENU_INPUTS] = {'\n', ' ', 'w', 's', KEY_UP, KEY_DOWN};
    bool displayDiffSubmenu = false;
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

        if(changedState)
        {
            clear();
            mvprintw(rows/2-2, cols/2 - 9, "Play with X");
            mvprintw(rows/2-1, cols/2 - 9, "Play with 0");
            mvprintw(rows/2, cols/2 - 9, "Difficulty");
            printw("(now ");
            switch(*p_difficulty)
            {
                case easy:
                    printw("easy)");
                    break;
                case medium:
                    printw("medium)");
                    break;
                case hard:
                    printw("hard)");
                    break;
                case impossible:
                    printw("impossible)");
                    break;
                default:
                    printw("impossible");
                    break;
            }

            if(displayDiffSubmenu)
            {
                mvprintw(rows/2+1, cols/2 - 7, "easy");
                mvprintw(rows/2+2, cols/2 - 7, "medium");
                mvprintw(rows/2+3, cols/2 - 7, "hard");
                mvprintw(rows/2+4, cols/2 - 7, "impossible");
            }
            refresh();
        }

        switch(menuOptionSelected)
        {
            case playWithX:
                if(changedState)
                {
                    attron(COLOR_PAIR(RED_WHITE_PAIR));
                    attron(A_BOLD);
                    mvprintw(rows/2-2, cols/2 - 9, "Play with X");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(RED_WHITE_PAIR));
                    
                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP)
                {
                    if(displayDiffSubmenu)
                    {
                        menuOptionSelected = impossible;
                    }
                    else
                    {
                        menuOptionSelected = aiDifficulty;
                    }
                }

                if(input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = (menuOptionSelected + 1) % AI_MENU_OPTIONS;
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
                    attron(COLOR_PAIR(RED_WHITE_PAIR));
                    attron(A_BOLD);
                    mvprintw(rows/2-1, cols/2 - 9, "Play with 0");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(RED_WHITE_PAIR));
                    
                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP)
                {
                    menuOptionSelected = (menuOptionSelected - 1) % AI_MENU_OPTIONS;
                }
                
                if(input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = (menuOptionSelected + 1) % AI_MENU_OPTIONS;
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
                    attron(COLOR_PAIR(RED_WHITE_PAIR));
                    attron(A_BOLD);
                    mvprintw(rows/2, cols/2 - 9, "Difficulty ");
                    printw("(now ");
                    switch(*p_difficulty)
                    {
                        case easy:
                            printw("easy)");
                            break;
                        case medium:
                            printw("medium)");
                            break;
                        case hard:
                            printw("hard)");
                            break;
                        case impossible:
                            printw("impossible)");
                            break;
                        default:
                            printw("impossible");
                            break;
                    }
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(RED_WHITE_PAIR));

                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP)
                {
                    menuOptionSelected = (menuOptionSelected - 1) % AI_MENU_OPTIONS;
                }
                
                if(input == 's' || input == KEY_DOWN)
                {
                    if(displayDiffSubmenu)
                    {
                        menuOptionSelected = (menuOptionSelected + 1) % AI_SUBMENU_OPTIONS;
                    }
                    else
                    {
                        menuOptionSelected = (menuOptionSelected + 1) % AI_MENU_OPTIONS;
                    }
                }

                if(input == '\n' || input == ' ')
                {
                    displayDiffSubmenu = !displayDiffSubmenu;
                }   

                break;

            case easy:
                if(changedState)
                {
                    attron(COLOR_PAIR(RED_WHITE_PAIR));
                    attron(A_BOLD);
                    mvprintw(rows/2+1, cols/2 - 7, "easy");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(RED_WHITE_PAIR));

                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP)
                {
                    menuOptionSelected = (menuOptionSelected - 1) % AI_SUBMENU_OPTIONS;
                }
                
                if(input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = (menuOptionSelected + 1) % AI_SUBMENU_OPTIONS;
                }

                if(input == '\n' || input == ' ')
                {
                    *p_difficulty = easy;
                    menuOptionSelected = aiDifficulty;
                    displayDiffSubmenu = !displayDiffSubmenu;
                }   

                break;

            case medium:
                if(changedState)
                {
                    attron(COLOR_PAIR(RED_WHITE_PAIR));
                    attron(A_BOLD);
                    mvprintw(rows/2+2, cols/2 - 7, "medium");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(RED_WHITE_PAIR));

                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP)
                {
                    menuOptionSelected = (menuOptionSelected - 1) % AI_SUBMENU_OPTIONS;
                }
                
                if(input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = (menuOptionSelected + 1) % AI_SUBMENU_OPTIONS;
                }

                if(input == '\n' || input == ' ')
                {
                    *p_difficulty = medium;
                    menuOptionSelected = aiDifficulty;
                    displayDiffSubmenu = !displayDiffSubmenu;
                }   

                break;
                        
            case hard:
                if(changedState)
                {
                    attron(COLOR_PAIR(RED_WHITE_PAIR));
                    attron(A_BOLD);
                    mvprintw(rows/2+3, cols/2 - 7, "hard");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(RED_WHITE_PAIR));

                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP)
                {
                    menuOptionSelected = (menuOptionSelected - 1) % AI_SUBMENU_OPTIONS;
                }
                
                if(input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = (menuOptionSelected + 1) % AI_SUBMENU_OPTIONS;
                }

                if(input == '\n' || input == ' ')
                {
                    *p_difficulty = hard;
                    menuOptionSelected = aiDifficulty;
                    displayDiffSubmenu = !displayDiffSubmenu;
                }   

                break;
            
            case impossible:
                if(changedState)
                {
                    attron(COLOR_PAIR(RED_WHITE_PAIR));
                    attron(A_BOLD);
                    mvprintw(rows/2+4, cols/2 - 7, "impossible");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(RED_WHITE_PAIR));

                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP)
                {
                    menuOptionSelected = (menuOptionSelected - 1) % AI_SUBMENU_OPTIONS;
                }
                
                if(input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = (menuOptionSelected + 1) % AI_SUBMENU_OPTIONS;
                }

                if(input == '\n' || input == ' ')
                {
                    *p_difficulty = impossible;
                    menuOptionSelected = aiDifficulty;
                    displayDiffSubmenu = !displayDiffSubmenu;
                }   

                break;
        }
        
        // must be done after each valid input
        for(int i = 0; i < VALID_MENU_INPUTS; i++)
        {
            if(validInputs[i] == input)
            {
                changedState = true;
                input = DEFAULT_INPUT_VALUE;
            }
        }
    }
}

bool selectGameMode(bool *isAi0, bool *aiEnabled, int *p_difficulty)
{
    int validInputs[VALID_MENU_INPUTS] = {'\n', ' ', 'w', 's', KEY_UP, KEY_DOWN};
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
        
        if(changedState)
        {
            clear();
            mvprintw(rows/2-2, cols/2-9, "Play with a friend");
            mvprintw(rows/2-1, cols/2-9, "Play against the AI");
            mvprintw(rows/2, cols/2-9, "Exit");
            refresh();
        }

        switch(menuOptionSelected)
        {
            case multiPlayer:
                if(changedState)
                {
                    attron(COLOR_PAIR(RED_WHITE_PAIR));
                    attron(A_BOLD);
                    mvprintw(rows/2-2, cols/2-9, "Play with a friend");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(RED_WHITE_PAIR));

                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP)
                {
                    menuOptionSelected = exitGame;
                }
                
                if(input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = (menuOptionSelected + 1) % MAIN_MENU_OPTIONS;
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
                    attron(COLOR_PAIR(RED_WHITE_PAIR));
                    attron(A_BOLD);
                    mvprintw(rows/2-1, cols/2-9, "Play against the AI");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(RED_WHITE_PAIR));

                    refresh();
                    changedState = false;
                }

                if(input == 'w' || input == KEY_UP)
                {
                    menuOptionSelected = (menuOptionSelected - 1) % MAIN_MENU_OPTIONS;
                }
                
                if(input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = (menuOptionSelected + 1) % MAIN_MENU_OPTIONS;
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
                    menuOptionSelected = (menuOptionSelected - 1) % MAIN_MENU_OPTIONS;
                }
                
                if(input == 's' || input == KEY_DOWN)
                {
                    menuOptionSelected = (menuOptionSelected + 1) % MAIN_MENU_OPTIONS;
                }

                if(input == '\n' || input == ' ')
                {
                    return true;
                }

                break;
        }

        // must be done after each valid input
        for(int i = 0; i < VALID_MENU_INPUTS; i++)
        {
            if(validInputs[i] == input)
            {
                changedState = true;
                input = DEFAULT_INPUT_VALUE;
            }
        }

    }

    if(*aiEnabled)
    {
        enterAiMenu(isAi0, p_difficulty);
    }

    return false;
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

    bExit = selectGameMode(&isAi0, &aiEnabled, &difficulty);
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
            bExit = selectGameMode(&isAi0, &aiEnabled, &difficulty);
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