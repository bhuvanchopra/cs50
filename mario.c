#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Height: ");
    
    int i=get_int();
     LOOP:
     if(-1<i&&i<24)
    {
      for(int j=0;j<i;j++)
        {
        for(int k=0;k<i+1;k++)
        {
            if (j+k>=i-1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    }
        else
        {
           printf("ERROR:Please enter a positive value less than 24.\n");
           int t=get_int(); 
           i=t;
           goto LOOP;
        }
}

