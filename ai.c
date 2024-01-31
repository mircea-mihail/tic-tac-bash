#include "ai.h"

void getAiMove(int p_BackendTable[3][3], bool p_bPlayerTurn)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(p_BackendTable[i][j] == 0)
            {
                p_BackendTable[i][j] = p_bPlayerTurn ? ZERO : EX;
                return;
            }
        }
    }
}
