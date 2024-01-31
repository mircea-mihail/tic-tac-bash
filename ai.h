#ifndef AI_H
#define AI_H

#include <ncurses.h>
#include "printing.h"
#include "usefulDefines.h"
#include "gameLogic.h"

#define MAX_CHILDREN 9 // 9 possible empty table positions
#define MAX_DEPTH 3

#define MAX_SCORE 100
#define MIN_SCORE -100
#define INVALID_VALUE 1000

struct node
{
    int m_boardState[3][3];
};

// generates the next move of the ai based on the mini max algorithm 
void getAiMove(int p_BackendTable[3][3], bool p_bPlayerTurn);

// returns the score a state has by checking how many ways a symbol can win based on the board state. 
// zero is min so for each way 0 can win you add -1 and X is max so for each way x can win you add 1
int scoreTheState(int p_boardState[3][3]);

#endif