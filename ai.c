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

// counts the number of 0s and returns it. This way, wins that lead to the least amount of moves are prioritised
int scoreWinningState(int p_boardState[3][3])
{
    int score = 0; 
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(p_boardState[i][j] == EMPTY)
            {
                score ++;
            }
        }
    }
    return score;
}

int scoreTheState(int p_boardState[3][3])
{
    int winner = checkWinCondition(p_boardState);
            
    if(winner == EX)
    {
        return MAX_SCORE + scoreWinningState(p_boardState);
    }
    if(winner == ZERO)
    {
        return MIN_SCORE - scoreWinningState(p_boardState);
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

int getMinScore(int p_scores[3][3])
{
    int minScore = MAX_SCORE;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(p_scores[i][j] != INVALID_VALUE && p_scores[i][j] <= minScore)
            {
                minScore = p_scores[i][j];
            }
        }
    }
    return minScore;
}

int getMaxScore(int p_scores[3][3])
{
    int maxScore = MIN_SCORE;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(p_scores[i][j] != INVALID_VALUE && p_scores[i][j] >= maxScore)
            {
                maxScore = p_scores[i][j];
            }
        }
    }
    return maxScore;
}

// the only purpose of this function is to keep the ai bot functional 
// if the worst is to come. So far there has been no point in which it was 
// needed but it is here just in case
void setFirstFreeSpot(int p_boardState[3][3], bool p_turn)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(p_boardState[i][j] == 0)
            {
                p_boardState[i][j] = p_turn ? ZERO : EX;   
            }
        }
    }   
}

void debugPrintTable(int table[3][3])
{
    mvprintw(2, 0, " ");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            printw("%d ", table[i][j]);
        }
        printw("\n");
    }
}

// returns the number of same score positions and a mask with ones for the positons of the scores and zeros for everywhere else
int getScorePositions(int p_scores[3][3], int p_scoreVal, bool p_scorePosVector[3][3])
{
    int numberOfScores = 0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
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

void setTable(int p_scores[3][3], int p_boardState[3][3], bool p_turn)
{
    if(p_turn == MAX)
    {
        int maxScore = MIN_SCORE;
        int bestPosOX = -1;
        int bestPosOY = -1;
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
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
            bool maxScorePositions[3][3];
            int possibleMoves = getScorePositions(p_scores, maxScore, maxScorePositions);
            srand(time(NULL));
            int moveToMake = rand() % possibleMoves;

            int incrementCounter = 0;
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
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
        int minScore = MAX_SCORE;
        int bestPosOX = -1;
        int bestPosOY = -1;
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
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
            bool minScorePositions[3][3];
            int possibleMoves = getScorePositions(p_scores, minScore, minScorePositions);
            srand(time(NULL));
            int moveToMake = rand() % possibleMoves;

            int incrementCounter = 0;
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
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

    // this is very interesting, shows the reasoning behind the ai choices and where each decision would have led
    // clear();
    // printTable(p_boardState);
    // int score = scoreTheState(p_boardState);
    // mvprintw(0, 1, "nodes generated: %lld", nodesGenerated);
    // printw("%d", score);  
    // debugPrintTable(p_scores);
    // refresh();
    // waitForInput();
}

void copyBoardState(int p_originalBoardState[3][3], int p_newBoardState[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            p_newBoardState[i][j] = p_originalBoardState[i][j];
        }
    }
}

int miniMax(int p_boardState[3][3], struct node *p_node, int p_turn, int p_depth, int p_maxDepth)
{
    if(p_depth > p_maxDepth)
    {
        return scoreTheState(p_node->m_boardState);
    }

    // stop if someone won or if it is a draw
    int winner = checkWinCondition(p_node->m_boardState);  
    if(winner == EX)
    {
        return MAX_SCORE;
    }
    if(winner == ZERO)
    {
        return MIN_SCORE;
    }
    if(checkDraw(p_node->m_boardState))
    {
        return 0;
    }

    int scoresForMoves[3][3];
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            scoresForMoves[i][j] = INVALID_VALUE;
        }
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(p_node->m_boardState[i][j] == 0)
            {
                struct node newNode;
                copyBoardState(p_node->m_boardState, newNode.m_boardState);
                newNode.m_boardState[i][j] = p_turn ? ZERO : EX;
                scoresForMoves[i][j] = miniMax(p_boardState, &newNode, !p_turn, p_depth + 1, MAX_DEPTH);
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

void getAiMove(int p_boardState[3][3], bool p_PlayerTurn, int p_difficulty)
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