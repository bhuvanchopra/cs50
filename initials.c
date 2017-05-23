#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>

int main(void)
{
    //printf("Please enter your full name: ");
    string s=get_string();
    //int l=sizeof(s)/sizeof(s[0]);
    int l=strlen(s);
    int count=0;
    for (int j=0;j<l;j++)
    {
        if(s[j]==' ')
        {
            if(s[(j+1)]!=' ')
            {
            count=count+1;
            }
        }
    }
    int b[count];
    int m=0;
    for (int k=0;k<l;k++)
    {
        if(s[k]==' '&&k!=l-1)
        {
            if(s[(k+1)]!=' ')
            {
            b[m]=k+1;
            m=m+1;
            }
        }
    }
    if (s[0]!=' ')
    {
    printf("%c",toupper(s[0])); 
    }
    for (int i=0;i<m;i++)
    {
        printf("%c",toupper(s[b[i]])); 
    }
    printf("\n");
}