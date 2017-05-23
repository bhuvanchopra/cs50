#include<stdio.h>
#include<string.h>
#include<cs50.h>
#include<stdlib.h>

int main(int argc, string argv[])
{
    if (argc!=2)
    {
        printf("Error");
        return 1;
    }
    printf("plaintext:");
    int k=atoi(argv[1]);
    string s=get_string();
    int l=strlen(s);
    string g=s;
    int q[l],w[l];
    for(int m=0;m<l;m++)
    {
    q[m]=(int)s[m];
    w[m]=(int)g[m];
    }
    //printf("ciphertext:");
    for(int i=0;i<l;i++)
        {
        if((q[i]>64&&q[i]<91)||(q[i]>96&&q[i]<123))
        {
            
        
        if (((q[i]<90)&&((q[i]+(k%26))>90))||((q[i]<122)&&((q[i]+(k%26))>122)))
        {
            w[i]=q[i]+(k%26)-26;
           
             g[i]=(char)w[i];
        }
        else 
        {
            w[i]=q[i]+(k%26);
            g[i]=(char)w[i];
        }
          
        }
        
    }
    
    printf("ciphertext:%s\n",g);
}