/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    /* TODO: This code is written to do sanity check so that the program knows the number of random numbers 
    * to print and also the random seed value for generating the same random numbers again.
    * The user is prompted again and again till he/she provdies the number of random numbers required.
    */
    
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    /* TODO: Converting the string data type of number of random numbers into integer data type.
    */
    int n = atoi(argv[1]);
    
    /* TODO: If the user provides a random seed number, then the following code calls the srand48 function and passes the seed number to the function. If the user does'nt provides the seed number,
    *  then the code passes null to the srand48 function.
    */
    
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    // TODO: This code prints the random number less than the LIMIT number one by one and prints a newline every time.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
