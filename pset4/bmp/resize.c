/****************************************************************************
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes BMP by a given factor of n.
 ***************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

#define BYTE 3
#define HEADER_SIZE 54

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize n infile outfile\n");
        return 1;
    }
    
    //Remember Scale factor
    int n = atoi(argv[1]);
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    //Sanity Check for n
    if( n <= 0 || n > 100)
    {
        printf("Enter a positive and less than 100 n\n");
        return 1;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    //Store the original file parameters
    int ObiWidth = bi.biWidth;
    int ObiHeight = abs(bi.biHeight);
    
    //Update header info(filesize, imagesize, width, height)
    bi.biWidth = (bi.biWidth) * n;
    bi.biHeight = (bi.biHeight) * n;
    bi.biSizeImage = bi.biHeight * bi.biWidth * BYTE;
    bf.bfSize = bi.biSizeImage + HEADER_SIZE;
     
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (ObiWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0; i < ObiHeight; i++)
    {
            RGBTRIPLE store[bi.biWidth];
            int counter = 0;
            // iterate over pixels in scanline
            for (int j = 0; j < ObiWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for(int k = 0; k < n; k++)
                { 
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    store[counter] = triple;
                    counter++;
                }
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            if(((bi.biWidth) % 4) != 0)
            {    
                 //then add the necessary padding 
                 for (int k = 0; k < new_padding; k++)
                     fputc(0x00, outptr);    
            }
            
            for(int m = 0; m < n - 1; m++)
            {
                for(int l = 0; l < (bi.biWidth); l++)
                {
                    
                    fwrite(&store[l], sizeof(RGBTRIPLE), 1, outptr);
                }
                
                if(((bi.biWidth) % 4) != 0)
                {    
                     //then add the necessary padding 
                     for (int k = 0; k < new_padding; k++)
                         fputc(0x00, outptr);    
                }
           }
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
