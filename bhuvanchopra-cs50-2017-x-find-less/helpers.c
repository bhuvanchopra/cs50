/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    
    if(n<=0)
    {
        return false;
    }
    else
    {
        
        int lower=0;
        int upper=n-1;
    
        while(upper>=lower)
        {
        int middle=(upper+lower)/2;
    
        if(value==values[middle])
        {
            return true;
            break;
        }
        else if(value>values[middle])
        {
            lower=middle+1;
        }
        else
        {
            upper=middle-1;
        }
        }
       
     return false;
    }
    
    
        
}
    
    
    // TODO: implement a searching algorithm
    

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    
    int b,count;
    
    LOOP: count=0;
    // TODO: implement a sorting algorithm
    for(int i=0;i<n-1;i++)
    {
        if(values[i]<=values[i+1])
        {
            
        }
        else
        {
           b=values[i];
           values[i]=values[i+1];
           values[i+1]=b;
           count=count+1;
        }
        
    }
    if(count!=0)
    {
        goto LOOP;
    }
    
    
    return;
}
