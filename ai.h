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
    int m_boardState[ROWS][COLS];
};

// generates the next move of the ai based on the mini max algorithm 
void getAiMove(int p_BackendTable[ROWS][COLS], bool p_bPlayerTurn, int p_difficulty);

// returns the score a state has by checking how many ways a symbol can win based on the board state. 
// zero is min so for each way 0 can win you add -1 and X is max so for each way x can win you add 1
int scoreTheState(int p_boardState[ROWS][COLS]);

// the checker is a bit mask that has b01 set if it found an x and has b10 set if found a 0. 
// this function returns 0 if it finds both x and 0, 1 if x is found and -1 if found 0 (0 is min, x max)
int getScoreFromChecker(int checker);

// counts the number of 0s and returns it. This way, wins that lead to the least amount of moves are prioritised
int scoreWinningState(int p_boardState[ROWS][COLS]);

// returns the smallest score found in p_scores table
int getMinScore(int p_scores[ROWS][COLS]);

// returns the biggest score found in p_scores table
int getMaxScore(int p_scores[ROWS][COLS]);

// this function sets the first empty spot on the board with the correct symbol
// the only purpose of this function is to keep the ai bot functional if the worst is to come. 
// So far there has been no point in which it was needed but it is here just in case
void setFirstFreeSpot(int p_boardState[ROWS][COLS], bool p_turn);

// function used for debugging that prints the tic tac toe table
void debugPrintTable(int table[ROWS][COLS]);

// returns the number of same score positions and a mask with ones for the positons of the scores and zeros for everywhere else
int getScorePositions(int p_scores[ROWS][COLS], int p_scoreVal, bool p_scorePosVector[ROWS][COLS]);

// this function chooses the next move of the ai, after the minimax algorithm has run
void setTable(int p_scores[ROWS][COLS], int p_boardState[ROWS][COLS], bool p_turn);

// copies the board state from the original to the new one
void copyBoardState(int p_originalBoardState[ROWS][COLS], int p_newBoardState[ROWS][COLS]);

// recursively runs the minimax algorithm returning the best move of the zq
int miniMax(int p_boardState[ROWS][COLS], struct node *p_node, int p_turn, int p_depth, int p_maxDepth);

// calls the minimax algorithm with a different maximum depth depending on the difficulty chosen by the player
void getAiMove(int p_boardState[ROWS][COLS], bool p_PlayerTurn, int p_difficulty);

#endif