#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "usefulDefines.h"

// checks for user input, updates the table with the appropriate x or 0 move and switches the turn
bool updateTable(int npTable[3][3], int nUserInput, bool* bpPlayerTurn);

// returns ZERO (a define) if 0 won, EX (define for x) if x won and 0 if noone won
int checkWinCondition(int npTable[3][3]);

// checks if the player pressed Q and returns true if so, false otherwise
bool checkExit(int nUserInput);

// returns true if the game ended in a draw and false otherwise
bool checkDraw(int p_npTable[3][3]);

// prints the winner and returns true if someone won
bool printWinner(int p_npTable[3][3]);

// prints that the game ended in a draw and returns true (if so), otherwise returns false
bool printDraw(int p_npTable[3][3]);

// stalls the code until the player inputs one of the recognised input keys
void waitForInput();

#endif //GAME_LOGIC_H