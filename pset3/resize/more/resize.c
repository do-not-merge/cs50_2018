/*resize.c
Guilherme Albertini
CS50 2019
*/
#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    //scale factor converted to a double
    double f = atof(argv[1]);
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
  
    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
      
    //*****************INFILE***********************//
    //**********************************************//
    
    // read infile's BITMAPFILEHEADER (14 bytes)
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER (40 bytes)
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
    
    //create temporary array to store pixels from infile for processing
    RGBTRIPLE temp[bi.biWidth][abs(bi.biHeight)];
    
    // determine padding for scanlines for infile
    int paddingIn = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            // copy RGB triple to temp
            temp[j][i] = triple;
        }

        // skip over infile padding, if any
        fseek(inptr, paddingIn, SEEK_CUR);
    }
    
      
    //**********OUTFILE (SCALED INFILE)**************//
    //**********************************************//
    
    //scale new bmp vertically and horizontally
    bi.biHeight *= f;
    bi.biWidth  *= f;
   
    // determine new, scaled padding for these scanlines (int arithmetic used)
    int paddingOut = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //determine bytes required for new structure
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + paddingOut) * abs(bi.biHeight);
    
    //determine new size of the bmp which includes the headers (54 bytes)
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over outfile's scanlines (scaled by f)
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            
            // scaling by f using INT arithmetic 
            triple = temp[(int)(j / f)][(int)(i / f)];
           
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr); 
        }
        
        // write the buffer
        for (int k = 0; k < paddingOut; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    return 0;
}


/*Future work: start from scratch. Be individually able to scale width or length or both */