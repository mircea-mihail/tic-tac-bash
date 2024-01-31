#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "usefulDefines.h"

bool updateTable(int npTable[3][3], int nUserInput, bool* bpPlayerTurn);

int checkWinCondition(int npTable[3][3]);

bool checkExit(int nUserInput);

bool checkDraw(int p_npTable[3][3]);

bool printWinner(int p_npTable[3][3]);

bool printDraw(int p_npTable[3][3]);

#endif //GAME_LOGIC_H