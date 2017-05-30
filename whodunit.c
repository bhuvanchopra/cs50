#include<stdio.h>
#include<stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    if(argc!=3)
    {
        fprintf(stderr, "Usage ./whodunit inputfile outputfile\n");
        return 1;
    }
FILE *inputfile=fopen(argv[1],"r");
    if (inputfile==NULL)
    {
         fprintf(stderr,"Input file cannot be opened\n");
         return 2;
    }
FILE *outputfile=fopen(argv[2],"w");
    if (outputfile==NULL)
    {
        fprintf(stderr,"Output file cannot be opened\n");
        return 3;
    }
BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inputfile);

   
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inputfile);
    
     if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outputfile);
        fclose(inputfile);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
     fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outputfile);

   
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outputfile);
    
     int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
     
     for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
       
        for (int j = 0; j < bi.biWidth; j++)
        {
            
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inputfile);
            
            if(triple.rgbtRed==0xff)
            {
                triple.rgbtBlue=0xff;
                triple.rgbtGreen=0xff;
            }
            else
            {
                triple.rgbtRed=0x00; 
                triple.rgbtBlue=0xff;    
                triple.rgbtGreen=0x00;
            }
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outputfile);
        }

        fseek(inputfile, padding, SEEK_CUR);

        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outputfile);
        }
    }
    fclose(inputfile);
    fclose(outputfile);
    return 0;
}
