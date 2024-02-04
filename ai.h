#ifndef AI_H
#define AI_H

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h> // for random number generation
#include "printing.h"
#include "usefulDefines.h"
#include "gameLogic.h"

#define RANDOM_BEST_MOVE 1

#define MAX_CHILDREN 9 // 9 possible empty table positions
#define MAX_DEPTH 10 // not possible to go deeper

#define MAX_SCORE 100
#define MIN_SCORE -100

#define MAX_INF 10000
#define MIN_INF -10000
#define INVALID_VALUE 1000

#define X_BIT 1
#define Z_BIT 2

#define setCheckerX(checker) checker = checker | X_BIT
#define setChecker0(checker) checker = checker | Z_BIT

struct node
{
    int m_boardState[3][3];
};

// generates the next move of the ai based on the mini max algorithm 
void getAiMove(int p_BackendTable[3][3], bool p_bPlayerTurn, int p_difficulty);

// returns the score a state has by checking how many ways a symbol can win based on the board state. 
// zero is min so for each way 0 can win you add -1 and X is max so for each way x can win you add 1
int scoreTheState(int p_boardState[3][3]);

#endif