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
    
    int t=strlen(argv[1]);
    
    int a[t],p,z;
    for(int y=0;y<t;y++)
    {
        if(((int)(argv[1][y])<91)&&((int)(argv[1][y])>64))
        {
            a[y]=(int)(argv[1][y])-65; 
        }
        else if(((int)(argv[1][y])<123)&&((int)(argv[1][y])>96))
        {
             a[y]=(int)(argv[1][y])-97;
        }
   else
   {
       printf("Error");
        return 1;
   }
    }
    printf("plaintext:");
   string s=get_string();
    int l=strlen(s);
    int k[l],count=0;
    for (p=0;p<l;p++)
    {
       if(((((int)(s[p])<91)&&((int)(s[p])>64))||(((int)(s[p])<123)&&((int)(s[p])>96))))
       {
        z=(p-count)%t;
        k[p]=a[z];
       }
    else{
        count=count+1;
    }
    }
    
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
            
        
        if (((q[i]<90)&&((q[i]+(k[i]%26))>90))||((q[i]<122)&&((q[i]+(k[i]%26))>122)))
        {
            w[i]=q[i]+(k[i]%26)-26;
           
             g[i]=(char)w[i];
        }
        else 
        {
            w[i]=q[i]+(k[i]%26);
            g[i]=(char)w[i];
        }
          
        }
        
    }
    
    printf("ciphertext:%s\n",g);
}