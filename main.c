#include <ncurses.h>

#define ZERO 1
#define EX 2  

void printTable(int npTable[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            printw("%d ", npTable[i][j]);
        }
        printw("\n");
    } 
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
    *bpPlayerTurn = !*bpPlayerTurn;
}

bool checkExit(int nUserInput)
{
    if(nUserInput == 'Q'){
        return 1;
    }
    return 0;
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
    
    // Start curses mode
    initscr();			        

    while(!bExit)
    {
        clear();
        printTable(npBackendTable);
        //actually print on the screen
        refresh();			        
        //wait for user input
        nUserInput = getch();		
        updateTable(npBackendTable, nUserInput, &bPlayerTurn);

        bExit = checkExit(nUserInput);
    }
    
    endwin();			/* End curses mode		  */

	return 0;
}