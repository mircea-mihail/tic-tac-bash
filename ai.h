#ifndef AI_H
#define AI_H

#include <ncurses.h>
#include "usefulDefines.h"

#define MAX_CHILDREN 9 // 9 possible empty table positions
#define MAX_DEPTH 2

#define MAX_SCORE 100
#define MIN_SCORE -100

struct node
{
    int m_boardState[3][3];
    int m_score;
    struct node *m_parent;
    struct node *m_children[MAX_CHILDREN];
};

void getAiMove(int p_BackendTable[3][3], bool p_bPlayerTurn);

#endif