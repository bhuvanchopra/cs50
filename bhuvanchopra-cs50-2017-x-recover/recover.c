#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        fprintf(stderr,"Usage: ./recover card.raw\n");
        return 1;
    }
FILE *inputfile=fopen(argv[1],"r");
if (inputfile==NULL)
{
    fprintf(stderr,"File cannot be opened.\n");
        return 2;
}
    typedef uint8_t BYTE;
    BYTE buffer[512]={0};
 
 
    /*typedef uint4_t  HALFBYTE;
    typedef struct
{
    HALFBYTE one;
    HALFBYTE two;
    HALFBYTE three;
    HALFBYTE four;
    HALFBYTE five;
    HALFBYTE six;
    HALFBYTE seven;
} __attribute__((__packed__))
bytestruc;
    
    
    bytestruc b;*/
    
   int q=0;
   //int r;
   char filename[50];
   //FILE *img=NULL;
    while(fread(buffer,sizeof(BYTE),512,inputfile)==512)
    {
        //fread(&buffer,sizeof(BYTE),512,inputfile);
            while(buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && ((buffer[3]&0xf0)==0xe0))
            {
                sprintf(filename,"%03i.jpg",q);
                FILE *img=fopen(filename,"w");
                q=q+1;
                fwrite(buffer,sizeof(BYTE),512,img);
                    while((fread(buffer,sizeof(BYTE),512,inputfile)==512) && ((buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && ((buffer[3]&0xf0)==0xe0))==0))
                    {
                        //fread(&buffer,sizeof(BYTE),512,inputfile);
                        fwrite(buffer,sizeof(BYTE),512,img);
                    }
                fclose(img);
            }
            
        
    }
    fclose(inputfile);
    return 0;
}
