#include "ai.h"

#define X_BIT 1
#define Z_BIT 2

#define setCheckerX(checker) checker = checker | X_BIT
#define setChecker0(checker) checker = checker | Z_BIT

int getScoreFromChecker(int checker)
{
    if((checker & X_BIT) && (checker & Z_BIT))
    {
        return 0;
    }
    if(checker & X_BIT)
    {
        return 1;
    }
    if(checker & Z_BIT)
    {
        return -1;
    }
    return 0;
}

int scoreTheState(int p_boardState[3][3])
{
    int winner = checkWinCondition(p_boardState);
            
    if(winner == EX)
    {
        return MAX_SCORE;
    }
    if(winner == ZERO)
    {
        return MIN_SCORE;
    }

    int score = 0;

    //check diagonal

    // set first bit of checker if found x and second bit of checker if found 0
    // if found both x and 0 don't do anything to the score
    int checker = 0;
    for(int i = 0; i < 3; i++)
    {
        if(p_boardState[i][i] == EX)
        {   
            setCheckerX(checker);
        }
        if(p_boardState[i][i] == ZERO)
        {
            setChecker0(checker);
        }
    }
    score += getScoreFromChecker(checker);

    checker = 0;

    //check other diagonal
    for(int i = 0; i < 3; i++)
    {
        if(p_boardState[i][2-i] == EX)
        {   
            setCheckerX(checker);
        }
        if(p_boardState[i][2-i] == ZERO)
        {
            setChecker0(checker);
        }
    }
    score += getScoreFromChecker(checker);

    checker = 0;

    //check columns
    for(int j = 0; j < 3; j++)
    {
        for(int i = 0; i < 3; i++)
        {
            if(p_boardState[j][i] == EX)
            {   
                setCheckerX(checker);
            }
            if(p_boardState[j][i] == ZERO)
            {
                setChecker0(checker);
            }
        }
        score += getScoreFromChecker(checker);

        checker = 0;
    }
    
    //check rows

    for(int j = 0; j < 3; j++)
    {

        for(int i = 0; i < 3; i++)
        {
            if(p_boardState[i][j] == EX)
            {   
                setCheckerX(checker);
            }
            if(p_boardState[i][j] == ZERO)
            {
                setChecker0(checker);
            }
        }
        score += getScoreFromChecker(checker);

        checker = 0;
    }
    return score;
}

void getAiMove(int p_BackendTable[3][3], bool p_bPlayerTurn)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(p_BackendTable[i][j] == 0)
            {
                p_BackendTable[i][j] = p_bPlayerTurn ? ZERO : EX;
              
                clear();
                printTable(p_BackendTable);
                int score = scoreTheState(p_BackendTable);
                mvprintw(0, 1, "current score: ");
                printw("%d", score);  
                refresh();
                waitForInput();

                return;
            }
        }
    }
}


// clear();
    
// printTable(p_npTable);
// mvprintw(0, 0, "The game ended in a DRAW");  

// refresh();