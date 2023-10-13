#include <ncurses.h>

#define ZERO 1
#define EX 2  

#define BLACK_PAIR 1
#define RED_PAIR 2
#define GREEN_PAIR 3
#define YELLOW_PAIR 4
#define BLUE_PAIR 5
#define MAGENTA_PAIR 6
#define CYAN_PAIR 7 
#define WHITE_PAIR 8

#define min(a, b) (a < b ? a : b)

void dealWithColors()
{
    start_color();
    
    init_pair(BLACK_PAIR, COLOR_BLACK, COLOR_BLACK);
    init_pair(RED_PAIR, COLOR_RED, COLOR_RED);
    init_pair(GREEN_PAIR, COLOR_GREEN, COLOR_GREEN);
    init_pair(YELLOW_PAIR, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(BLUE_PAIR, COLOR_BLUE, COLOR_BLUE);
    init_pair(MAGENTA_PAIR, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(CYAN_PAIR, COLOR_CYAN, COLOR_CYAN);
    init_pair(WHITE_PAIR, COLOR_WHITE, COLOR_WHITE);

    use_default_colors(); //keeps my background transparrent 

}
    
void printTableLines(int p_nRows, int p_nCols, int p_nCellSize, int p_nScreenGap)
{
    // |   |
    int nColumnStart = (p_nCols-p_nCellSize)/2;
    for( int i = p_nScreenGap; i < p_nRows - p_nScreenGap; i++)
    {
        char ch = ' ';
        mvaddch(i, nColumnStart, ch | COLOR_PAIR(RED_PAIR));
        mvaddch(i, nColumnStart + 1, ch | COLOR_PAIR(RED_PAIR));
        mvaddch(i, nColumnStart + p_nCellSize, ch | COLOR_PAIR(RED_PAIR));
        mvaddch(i, nColumnStart + p_nCellSize + 1, ch | COLOR_PAIR(RED_PAIR));
    }
    int nColumnLength = p_nRows - 2*p_nScreenGap + 3; // 3 is an arbitrary number to make horizontal lines a bit longer
    // a char is twice as tall as is is wide so the cellsize needs adjustment
    p_nCellSize /= 2; 

    int nRowStart = (p_nRows-p_nCellSize)/2;
    
    for( int i = p_nCols/2; i < p_nCols/2 + nColumnLength; i++)
    {
        char ch = ' ';
        //add to the right of the center
        mvaddch(nRowStart, i, ch | COLOR_PAIR(RED_PAIR));
        mvaddch(nRowStart + p_nCellSize, i, ch | COLOR_PAIR(RED_PAIR));

        //and to the left
        mvaddch(nRowStart, p_nCols - i, ch | COLOR_PAIR(RED_PAIR));
        mvaddch(nRowStart + p_nCellSize, p_nCols - i, ch | COLOR_PAIR(RED_PAIR));
    }
}

void printTable(int npTable[3][3])
{
    bool bThickLetters = false;
    int nRows, nCols;
    int nStartRow, nStartCol;

    getmaxyx(stdscr, nRows, nCols);

    if(min(nRows, nCols) > 43)
    {
        bThickLetters = true;
    }

    int nCellSize =  min(nRows, nCols) / 2;
    int nScreenGap = min(nRows, nCols) / 5;

    nStartRow = nRows/2-1;
    nStartCol = (nCols-6)/2;

    printTableLines(nRows, nCols, nCellSize, nScreenGap);

    movPrintX(nRows/2, nCols/2, nScreenGap-1, bThickLetters);
    // movPrint0(nRows/2, nCols/2, 4);
    
    // for(int i = 0; i < 3; i++)
    // {
    //     move(nStartRow, nStartCol);
    //     for(int j = 0; j < 3; j++)
    //     {
    //         printw("%d ", npTable[i][j]);
    //     }
    //     nStartRow +=1;
    // } 
}

void updateTable(int npTable[3][3], int nUserInput, bool* bpPlayerTurn)
{
    switch(nUserInput)
    { 
        case 'q': 
            if(npTable[0][0] == 0)
                npTable[0][0] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 'w': 
            if(npTable[0][1] == 0)
                npTable[0][1] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 'e':
            if(npTable[0][2] == 0) 
                npTable[0][2] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 'a': 
            if(npTable[1][0] == 0)
                npTable[1][0] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 's': 
            if(npTable[1][1] == 0)
                npTable[1][1] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 'd':
            if(npTable[1][2] == 0) 
                npTable[1][2] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 'z': 
            if(npTable[2][0] == 0)
                npTable[2][0] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 'x': 
            if(npTable[2][1] == 0)
                npTable[2][1] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        case 'c': 
            if(npTable[2][2] == 0)
                npTable[2][2] = *bpPlayerTurn ? ZERO : EX; 
            else
                return;
            break;
        default: break;
    }
    // change turn if the other player made a valid move, else, let him try again 
    *bpPlayerTurn = !*bpPlayerTurn;
}

// returns the winning player
int checkWinCondition(int npTable[3][3])
{
    bool winCondition = true;
    //check diagonal

    for(int i = 0; i < 2; i++)
    {
        winCondition = winCondition && (npTable[i][i] == npTable[i+1][i+1]) && (npTable[i][i] != 0);
    }
    if(winCondition)
    {
        return npTable[0][0];
    }

    //check other diagonal
    winCondition = true;

    for(int i = 0; i < 2; i++)
    {
        winCondition = winCondition && (npTable[i][2-i] == npTable[i+1][2-(i+1)]) && (npTable[i][i] != 0);
    }
    if(winCondition)
    {
        return npTable[0][2];
    }

    //check columns
    //PROBLEMS
    for(int j = 0; j <= 2; j++)
    {
        winCondition = true;

        for(int i = 0; i < 2; i++)
        {
            winCondition = winCondition && (npTable[j][i] == npTable[j][i+1]) && (npTable[j][i] != 0);
        }
        if(winCondition)
        {
            return npTable[j][0];
        }
    }
    
    //check rows

    for(int j = 0; j <= 2; j++)
    {
        winCondition = true;

        for(int i = 0; i < 2; i++)
        {
            winCondition = winCondition && (npTable[i][j] == npTable[i+1][j]) && (npTable[i][j] != 0);
        }
        if(winCondition)
        {
            return npTable[0][j];
        }
    }

    return 0;
}

void movPrintX(int p_nRow, int p_nCol, int p_nSize, bool p_bThick){
    // mvprintw(p_row, p_col, "\033[;41m \n");
    char ch = ' ';

    for(int i = 0; i <= p_nSize; i++)
    {
        mvaddch(p_nRow-i/2, p_nCol+i/2, ch | COLOR_PAIR(BLUE_PAIR));
        mvaddch(p_nRow+i/2, p_nCol-i/2, ch | COLOR_PAIR(BLUE_PAIR));
    }
    for(int i = 0; i <= p_nSize; i++)
    {
        mvaddch(p_nRow-i/2, p_nCol-i/2, ch | COLOR_PAIR(BLUE_PAIR));
        mvaddch(p_nRow+i/2, p_nCol+i/2, ch | COLOR_PAIR(BLUE_PAIR));
    }

    if(p_bThick)
    {
        p_nRow += 1;

        for(int i = 0; i <= p_nSize; i++)
        {
            mvaddch(p_nRow-i/2, p_nCol+i/2, ch | COLOR_PAIR(BLUE_PAIR));
            mvaddch(p_nRow+i/2, p_nCol-i/2, ch | COLOR_PAIR(BLUE_PAIR));
        }   

        mvaddch(p_nRow+p_nSize/2, p_nCol-p_nSize/2-1, ch | COLOR_PAIR(BLUE_PAIR));
        mvaddch(p_nRow+p_nSize/2, p_nCol+p_nSize/2+1, ch | COLOR_PAIR(BLUE_PAIR));

        for(int i = 0; i <= p_nSize; i++)
        {
            mvaddch(p_nRow-i/2, p_nCol-i/2, ch | COLOR_PAIR(BLUE_PAIR));
            mvaddch(p_nRow+i/2, p_nCol+i/2, ch | COLOR_PAIR(BLUE_PAIR));
        }

        mvaddch(p_nRow-p_nSize/2-1, p_nCol-p_nSize/2-1, ch | COLOR_PAIR(BLUE_PAIR));
        mvaddch(p_nRow-p_nSize/2-1, p_nCol+p_nSize/2+1, ch | COLOR_PAIR(BLUE_PAIR));
    }
}

void movPrint0(int p_nRow, int p_nCol, int p_nSize){
    // mvprintw(p_row, p_col, "\033[;41m \n");
    char ch = ' ';

    for(int i = 1; i < p_nSize; i++)
    {
        mvaddch(p_nRow-i, p_nCol, ch | COLOR_PAIR(BLUE_PAIR));
        mvaddch(p_nRow-i, p_nCol+p_nSize, ch | COLOR_PAIR(BLUE_PAIR));
    }

    for(int i = 1; i < p_nSize; i++)
    {
        mvaddch(p_nRow, p_nCol+i, ch | COLOR_PAIR(BLUE_PAIR));
        mvaddch(p_nRow-p_nSize, p_nCol+i, ch | COLOR_PAIR(BLUE_PAIR));
    }
}

bool checkExit(int nUserInput)
{
    if(nUserInput == 'Q'){
        return 1;
    }
    return 0;
}

void initCurses()
{
    // Start curses mode
    initscr();
    // don't show user input unless otherwise stated 			        
    noecho();
    // hide the cursor
    curs_set(0);
}

int main()
{
    bool bExit = 0;
    bool bPlayerTurn = 0;
    int nUserInput;	
    int npBackendTable[3][3] = { 
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                };
    int nWinner;
    
    initCurses();

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        return 1;
    }

    dealWithColors();

    while(!bExit)
    {
        clear();

        printTable(npBackendTable);
        // actually print on the screen
        refresh();			        
        // wait for user input
        nUserInput = getch();		
        updateTable(npBackendTable, nUserInput, &bPlayerTurn);

        nWinner = checkWinCondition(npBackendTable);        
        if(nWinner)
        {
            clear();
            printTable(npBackendTable);
            refresh();

            mvprintw(0, 0, "the winner is player %d", nWinner);
            refresh();
            getch();
            bExit = true;
        }
        bExit = checkExit(nUserInput) || bExit;
    }
    // End curses mode
    endwin();			

	return 0;
}