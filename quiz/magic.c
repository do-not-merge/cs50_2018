
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;

// need first 4 bytes only for comparisons
#define BLOCK 4

int main(int argc, char *argv[])
{
    //remember image file
    char *infile = argv[1];
    
    //check for correct usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: argc mismatch %s.\n", infile);
        return 1;
    }
    
    // open input file
    FILE *inptr = fopen(infile, "r");
    if (!inptr)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }
    
    // will read BLOCK bytes at a time and store in buffer
    BYTE buffer[BLOCK];
    
    for (int i = 0; i < BLOCK; i++)
    {
        fread(&buffer[i], 1, 1, inptr);
    }
    
    // determine file types from initial bytes
    if (buffer[0] == 0xff && buffer[1] == 0xd8  && buffer[2] == 0xff
        && (buffer[3] & 0xe0) == 0xe0)
    {
        printf("JPEG\n");  
    }
    else if (buffer[0] == 0x42 && buffer[1] == 0x4d)
    {
        printf("BMP\n");
    }
    else if (buffer[0] == 0x25 && buffer[1] == 0x50 && buffer[2] == 0x44 
             && buffer[3] == 0x46)
    {
        printf("PDF\n");
    }
    else
    {
        printf("\n");   
    } 

    // close infile
    fclose(inptr);

    // success
    return 0;
        
}
    