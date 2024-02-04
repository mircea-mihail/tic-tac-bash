#include "ai.h"

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

int scoreWinningState(int p_boardState[ROWS][COLS])
{
    int score = 0; 
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(p_boardState[i][j] == EMPTY)
            {
                score ++;
            }
        }
    }

    return score;
}

int scoreTheState(int p_boardState[ROWS][COLS])
{
    int winner = checkWinCondition(p_boardState);
            
    if(winner == EX)
    {
        return MAX_SCORE + scoreWinningState(p_boardState);
    }
    if(winner == ZERO)
    {
        return MIN_SCORE + scoreWinningState(p_boardState);
    }

    int score = 0;

    //check diagonal

    // set first bit of checker if found x and second bit of checker if found 0
    // if found both x and 0 don't do anything to the score
    int checker = 0;
    for(int i = 0; i < ROWS; i++)
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
    for(int i = 0; i < ROWS; i++)
    {
        if(p_boardState[i][ROWS-1-i] == EX)
        {   
            setCheckerX(checker);
        }
        if(p_boardState[i][ROWS-1-i] == ZERO)
        {
            setChecker0(checker);
        }
    }
    score += getScoreFromChecker(checker);
    checker = 0;

    //check columns
    for(int j = 0; j < ROWS; j++)
    {
        for(int i = 0; i < COLS; i++)
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

    for(int j = 0; j < COLS; j++)
    {
        for(int i = 0; i < ROWS; i++)
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

int getMinScore(int p_scores[ROWS][COLS])
{
    int minScore = MAX_INF;
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(p_scores[i][j] != INVALID_VALUE && p_scores[i][j] <= minScore)
            {
                minScore = p_scores[i][j];
            }
        }
    }
    return minScore;
}

int getMaxScore(int p_scores[ROWS][COLS])
{
    int maxScore = MIN_INF;
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(p_scores[i][j] != INVALID_VALUE && p_scores[i][j] >= maxScore)
            {
                maxScore = p_scores[i][j];
            }
        }
    }
    return maxScore;
}

void setFirstFreeSpot(int p_boardState[ROWS][COLS], bool p_turn)
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(p_boardState[i][j] == 0)
            {
                p_boardState[i][j] = p_turn ? ZERO : EX;   
            }
        }
    }   
}

void debugPrintTable(int table[ROWS][COLS])
{
    mvprintw(2, 0, " ");
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            printw("%d ", table[i][j]);
        }
        printw("\n");
    }
}

int getScorePositions(int p_scores[ROWS][COLS], int p_scoreVal, bool p_scorePosVector[ROWS][COLS])
{
    int numberOfScores = 0;
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(p_scores[i][j] == p_scoreVal)
            {
                p_scorePosVector[i][j] = 1;
                numberOfScores ++;
            }
            else
            {
                p_scorePosVector[i][j] = 0;
            }
        }
    }
    return numberOfScores;
}

void setTable(int p_scores[ROWS][COLS], int p_boardState[ROWS][COLS], bool p_turn)
{
    if(p_turn == MAX)
    {
        int maxScore = MIN_INF;
        int bestPosOX = -1;
        int bestPosOY = -1;
        for(int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLS; j++)
            {
                if(p_scores[i][j] != INVALID_VALUE && p_scores[i][j] >= maxScore)
                {
                    maxScore = p_scores[i][j];
                    bestPosOX = i;
                    bestPosOY = j;
                }
            }
        }
        if(bestPosOX == -1 || bestPosOY == -1)
        {
            // if here something went really bad not sure what (never happened during testing)
            setFirstFreeSpot(p_boardState, p_turn);

            // for debug, delete later
            clear();
            printTable(p_boardState);
            int score = scoreTheState(p_boardState);
            mvprintw(0, 1, "current score: ");
            printw("%d", score);  
            refresh();
            waitForInput();

            return;
        }
        
        // makes the game more fun and unpredictable for the player without affecting the bot performance
        if(RANDOM_BEST_MOVE)
        {
            bool maxScorePositions[ROWS][COLS];
            int possibleMoves = getScorePositions(p_scores, maxScore, maxScorePositions);
            srand(time(NULL));
            int moveToMake = rand() % possibleMoves;

            int incrementCounter = 0;
            for(int i = 0; i < ROWS; i++)
            {
                for(int j = 0; j < COLS; j++)
                {
                    if(maxScorePositions[i][j])
                    {
                        if(incrementCounter == moveToMake)
                        {
                            bestPosOX = i;
                            bestPosOY = j;   
                        }
                        incrementCounter ++;
                    }
                }
            }
        }

        p_boardState[bestPosOX][bestPosOY] = EX;
    }
    else
    {
        int minScore = MAX_INF;
        int bestPosOX = -1;
        int bestPosOY = -1;
        for(int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLS; j++)
            {
                if(p_scores[i][j] != INVALID_VALUE && p_scores[i][j] <= minScore)
                {
                    minScore = p_scores[i][j];
                    bestPosOX = i;
                    bestPosOY = j;
                }
            }
        }
        if(bestPosOX == -1 || bestPosOY == -1)
        {
            // if here something went really bad not sure what (never happened during testing)
            setFirstFreeSpot(p_boardState, p_turn);
            
            // for debug, delete later
            clear();
            printTable(p_boardState);
            int score = scoreTheState(p_boardState);
            mvprintw(0, 1, "current score: ");
            printw("%d", score);  
            refresh();
            waitForInput();

            return;
        }

        // makes the game more fun and unpredictable for the player without affecting the bot performance
        if(RANDOM_BEST_MOVE)
        {
            bool minScorePositions[ROWS][COLS];
            int possibleMoves = getScorePositions(p_scores, minScore, minScorePositions);
            srand(time(NULL));
            int moveToMake = rand() % possibleMoves;

            int incrementCounter = 0;
            for(int i = 0; i < ROWS; i++)
            {
                for(int j = 0; j < COLS; j++)
                {
                    if(minScorePositions[i][j])
                    {
                        if(incrementCounter == moveToMake)
                        {
                            bestPosOX = i;
                            bestPosOY = j;   
                        }
                        incrementCounter ++;
                    }
                }
            }
        }

        p_boardState[bestPosOX][bestPosOY] = ZERO;
    }

    // debug
    // clear();
    // printTable(p_boardState);
    // int score = scoreTheState(p_boardState);
    // debugPrintTable(p_scores);
    // refresh();
    // waitForInput();
}

void copyBoardState(int p_originalBoardState[ROWS][COLS], int p_newBoardState[ROWS][COLS])
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            p_newBoardState[i][j] = p_originalBoardState[i][j];
        }
    }
}

int miniMax(int p_boardState[ROWS][COLS], struct node *p_node, int p_turn, int p_depth, int p_maxDepth)
{
    if(p_depth > p_maxDepth)
    {
        return scoreTheState(p_node->m_boardState);
    }

    // stop if someone won or if it is a draw
    int winner = checkWinCondition(p_node->m_boardState);  
    if(winner == EX)
    {
        return MAX_SCORE + scoreWinningState(p_node->m_boardState);
    }
    if(winner == ZERO)
    {
        return MIN_SCORE - scoreWinningState(p_node->m_boardState);
    }
    if(checkDraw(p_node->m_boardState))
    {
        return 0;
    }

    int scoresForMoves[ROWS][COLS];
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            scoresForMoves[i][j] = INVALID_VALUE;
        }
    }

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(p_node->m_boardState[i][j] == 0)
            {
                struct node newNode;
                copyBoardState(p_node->m_boardState, newNode.m_boardState);
                newNode.m_boardState[i][j] = p_turn ? ZERO : EX;
                scoresForMoves[i][j] = miniMax(p_boardState, &newNode, !p_turn, p_depth + 1, p_maxDepth);
            }
        }
    }

    if(p_depth != 0)
    {
        if(p_turn == MAX)
        {
            return getMaxScore(scoresForMoves);
        }
        if(p_turn == MIN)
        {
            return getMinScore(scoresForMoves);
        }
    }
    else // do the best move possible considering previously found scores
    {
        setTable(scoresForMoves, p_boardState, p_turn);
    }
    return 0;
}

void getAiMove(int p_boardState[ROWS][COLS], bool p_PlayerTurn, int p_difficulty)
{
    int maxDepth;

    switch (p_difficulty)
    {
        case easy: 
            maxDepth = 1;
            break;

        case medium: 
            maxDepth = 2;
            break;

        case hard: 
            maxDepth = 4;
            break;

        case impossible:
            maxDepth = MAX_DEPTH;
            break;

        default:
            maxDepth = MAX_DEPTH;
            break;
    }

    struct node currentNode;
    copyBoardState(p_boardState, currentNode.m_boardState);
    miniMax(p_boardState, &currentNode, p_PlayerTurn, 0, maxDepth);
}

// clear();
// printTable(p_BackendTable);
// int score = scoreTheState(p_BackendTable);
// mvprintw(0, 1, "current score: ");
// printw("%d", score);  
// refresh();
// waitForInput();