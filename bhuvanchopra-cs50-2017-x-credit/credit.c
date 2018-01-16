#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    printf("Number: ");
    long long n;
    int f;
    n=get_long_long();
    int length =(int)ceil( log10(n));
    int digit[length];
    long long num=n*10;
    for(f=0;f<length;f++)
    {
       num=num/10;
       
        digit[length-1-f]=num%10;
    }
    int j,k;
    int p=floor(length/2);
    int q=length-p;
    int dg1[p],dg2[q];
    for(j=0;j<length-1;j=j+2)
    {
        dg1[(j/2)]=digit[length-2-j];
    }
    for(k=0;k<length;k=k+2)
    {
        dg2[(k/2)]=digit[length-1-k];
    }
    int dg3[p];
    long long b=0;
    for(n=0;n<p;n++)
    {
    dg3[n]=2*dg1[n];    
    b=b+dg3[n]*pow(10,n);
    }
    int length1 =(int)ceil( log10(b));
    int dg4[length1];
    long long num1=b*10;
    for(f=0;f<length1;f++)
    {
       num1=num1/10;
       
        dg4[length1-1-f]=num1%10;
    }
    
    
    int l,m,t1=0,t2=0;
    for(l=0;l<length1;l++)
    {
        t1=t1+dg4[l];
    }
    for(m=0;m<q;m++)
    {
        t2=t2+dg2[m];
    }
    int r=t1+t2;
    if(r%10==0)
    {
        if(digit[0]==3)
        {
            printf("AMEX\n");
        }
        else if (digit[0]==5)
        {
            printf("MASTERCARD\n");
        }
        else if(digit[0]==4)
        {
            printf("VISA\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
   
    
}