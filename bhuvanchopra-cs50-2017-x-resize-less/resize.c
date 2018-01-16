#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    if(argc!=4)
    {
        fprintf(stderr,"Usage : ./resize n inputfile outputfile\n");
        return 1;
    }
    FILE *inputfile = fopen(argv[2], "r");
    if (inputfile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[2]);
        return 2;
    }
    FILE *outputfile = fopen(argv[3], "w");
    if (outputfile == NULL)
    {
        fclose(inputfile);
        fprintf(stderr, "Could not create %s.\n", argv[3]);
        return 3;
    }
    
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inputfile);

    
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inputfile);
    int k1=bi.biHeight;
    int k2=bi.biWidth;
    //int k3=bi.biBitCount;
    //int k4=bi.biSizeImage;
    //int k5=bi.biXPelsPerMeter;
    //int k6=bi.biYPelsPerMeter;
    int paddinginput = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outputfile);
        fclose(inputfile);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    int n=atoi(argv[1]);
    
    //BITMAPINFOHEADER bi1;
    //fread(&bi1, sizeof(BITMAPINFOHEADER), 1, inputfile);
    //bi1.biHeight=bi.biHeight*n;
    //bi1.biWidth=bi.biWidth*n;
    
    bi.biHeight=k1*n;
    bi.biWidth=k2*n;
    //bi.biBitCount=(k3/n)/n;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //bi.biXPelsPerMeter=k5/n;
    //bi.biYPelsPerMeter=k6/n;
    bi.biSizeImage=((sizeof(RGBTRIPLE)*bi.biWidth)+padding)*abs(bi.biHeight);
    bf.bfSize=bi.biSizeImage+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
    
    
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outputfile);

    
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outputfile);
    /*if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outputfile);
        fclose(inputfile);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    */
    
    RGBTRIPLE d[abs(k1)][k2];
  
    for (int i = 0, biHeight = abs(k1); i < biHeight; i++)
    {
        
        for (int j = 0; j < k2; j++)
        {
           
            RGBTRIPLE triple;

           
            fread(&triple, sizeof(RGBTRIPLE), 1, inputfile);
           
           
            
                for(int l=0;l<n;l++)
                {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outputfile);
                
                }
                d[i][j]=triple;
            
            
        }

        
        
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outputfile);
        }
        for(int z=1;z<n;z++)
            {
                for(int j1=i;j1<=i;j1++)
                {
                    for(int l1=0;l1<k2;l1++)
                    {
                        for(int l=0;l<n;l++)
                        {
                            fwrite(&d[j1][l1], sizeof(RGBTRIPLE), 1, outputfile);
                        }
                            
                    }
                }
                for (int k = 0; k < padding; k++)
                    {
                    fputc(0x00, outputfile);
                    }
            }
        
        
        
        
        
        fseek(inputfile, paddinginput, SEEK_CUR);

    }

    
    fclose(inputfile);

    
    fclose(outputfile);

    
    return 0;
    
    
    
}