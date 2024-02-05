#ifndef MENU_H
#define MENU_H

#include <ncurses.h>

#include "printing.h"
#include "usefulDefines.h"

#define MAIN_MENU_OPTIONS 3
#define AI_MENU_OPTIONS 3
#define AI_SUBMENU_OPTIONS 7

#define VALID_MENU_INPUTS 6
#define DEFAULT_INPUT_VALUE 0

// prints the ai menu and allows the player to play with 0 x and to choose the difficulty of the game
void enterAiMenu(bool *isAi0, int *p_difficulty);

// prints the menu and allows the player to decide to play against the ai or another player
bool selectGameMode(bool *isAi0, bool *aiEnabled);

#endif