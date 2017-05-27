/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}


int bitXor(int x, int y) 
{
    int a = x & y;
    int b = ~x & ~y;
    int z = ~a & ~b;
    return z;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // TODO
    int count=0;
    for(int z=0;z<d;z++)
    {
        for(int x=0;x<d;x++)
        {
            if(x==d-1 && z==d-1)
            {
              //printf("_");
              // (char)board[z][x]='_';
            }
            else
            {
            board[z][x]=d*d-1-count;
            count=count+1;
            }
        }
    }
    if(d%2==0)
    {
        board[d-1][d-2]=2;
        board[d-1][d-3]=1;
    }
    
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    for(int c=0;c<d;c++)
    {
        for(int v=0;v<d;v++)
        {
            
            
            
            if(board[c][v]==0)
            {
                printf(" _ ");
            }
            else
            {
                printf("%2d ",board[c][v]);
            }
            
        }
    
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO
    int a1,a2,count1=0;
    
    for(int q=0;q<d;q++)
    {
        for(int w=0;w<d;w++)
        {
            if(board[q][w]==tile)
            {
                a1=q;
                a2=w;
            }
        }
    }
    for(int e=0;e<d;e++)
    {
        for(int r=0;r<d;r++)
        {
            if(board[e][r]==0)
            {
                if(bitXor(((e-a1==1 && r==a2) || (e-a1==-1 && r==a2)),((r-a2==1 && e==a1) || (r-a2==-1 && e==a1))))
                {
                    board[e][r]=tile;
                    board[a1][a2]=0;
                    count1=count1+1;
                }
                /*else
                {
                    return false;
                }*/
            }
            
        }
    }
   if(count1!=0)
   {
       return true;
   }
   else
   {
       return false;
   }
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    int t1=0;
    int check2=0;
    for(int t=0;t<d;t++)
    {
        for(int y=0;y<d;y++)
        {
            t1=t1+1;
            if(board[t][y]==t1)
            {
                check2=check2+1;
              
            }
            
        }
    }
   if(check2==d*d-1)
   {
       return true;
   }
   else
   {
       return false;
   }
    
    
}
