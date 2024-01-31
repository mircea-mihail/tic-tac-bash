#ifndef AI_H
#define AI_H

#include <ncurses.h>
#include "printing.h"
#include "usefulDefines.h"
#include "gameLogic.h"

#define MAX_CHILDREN 9 // 9 possible empty table positions
#define MAX_DEPTH 2

#define MAX_SCORE 100
#define MIN_SCORE -100

struct node
{
    int m_boardState[3][3];
    struct node *m_parent;
    struct node *m_children[MAX_CHILDREN];
};

void getAiMove(int p_BackendTable[3][3], bool p_bPlayerTurn);

#endif