#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "usefulDefines.h"

// checks if a valid mouse click has been made and returns true if so
bool checkMouse(int npTable[ROWS][COLS], int nUserInput, bool* bpPlayerTurn);

// checks for user input, updates the table with the appropriate x or 0 move and switches the turn
bool updateTable(int npTable[ROWS][COLS], int nUserInput, bool* bpPlayerTurn);

// returns ZERO (a define) if 0 won, EX (define for x) if x won and 0 if noone won
int checkWinCondition(int npTable[ROWS][COLS]);

// checks if the player pressed Q and returns true if so, false otherwise
bool checkExit(int nUserInput);

// returns true if the game ended in a draw and false otherwise
bool checkDraw(int p_npTable[ROWS][COLS]);

// prints the winner and returns true if someone won
bool printWinner(int p_npTable[ROWS][COLS]);

// prints that the game ended in a draw and returns true (if so), otherwise returns false
bool printDraw(int p_npTable[ROWS][COLS]);

// stalls the code until the player inputs one of the recognised input keys
void waitForInput();

#endif //GAME_LOGIC_H