#include "menu.h"

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
            mvprintw(rows/2, cols/2 - 9, "Difficulty: ");
            switch(*p_difficulty)
            {
                case easy:
                    printw("Easy");
                    break;
                case medium:
                    printw("Medium");
                    break;
                case hard:
                    printw("Hard");
                    break;
                case impossible:
                    printw("Impossible");
                    break;
                default:
                    printw("Impossible");
                    break;
            }

            if(displayDiffSubmenu)
            {
                mvprintw(rows/2+1, cols/2 - 7, "Easy");
                mvprintw(rows/2+2, cols/2 - 7, "Medium");
                mvprintw(rows/2+3, cols/2 - 7, "Hard");
                mvprintw(rows/2+4, cols/2 - 7, "Impossible");
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
                    mvprintw(rows/2, cols/2 - 9, "Difficulty: ");
                    switch(*p_difficulty)
                    {
                        case easy:
                            printw("Easy");
                            break;
                        case medium:
                            printw("Medium");
                            break;
                        case hard:
                            printw("Hard");
                            break;
                        case impossible:
                            printw("Impossible");
                            break;
                        default:
                            printw("Impossible");
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
                    mvprintw(rows/2+1, cols/2 - 7, "Easy");
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
                    mvprintw(rows/2+2, cols/2 - 7, "Medium");
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
                    mvprintw(rows/2+3, cols/2 - 7, "Hard");
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
                    mvprintw(rows/2+4, cols/2 - 7, "Impossible");
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

bool selectGameMode(bool *isAi0, bool *aiEnabled)
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

    return false;
}
