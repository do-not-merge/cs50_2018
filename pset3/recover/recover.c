/*
recover.c
Guilherme Albertini
CS50 2019
*/

#include <stdio.h>

#define BLOCK 512
typedef unsigned char BYTE;

int main(int argc, char *argv[])
{
    //ensure proper input
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover image\n");
        return 1;
    }
    
    //input forensic image file
    char *raw_file = argv[1];
    
    //open input file
    FILE *fp = fopen(raw_file, "r");
    if (!fp)
    {
        fprintf(stderr, "Could not open %s.\n", raw_file);
        return 2;
    }
    
    BYTE buffer[BLOCK]; 
    
    //stream that we will manipulate
    FILE *img = NULL; 
    
    int count = 0;
    int jpegStart = 0;
    
    //arbitrarily large (512) "string" for file name
    char filename[BLOCK];
    
    // man fread: if error occurs or EOF reached return value is short item count (or zero)
    while (fread(buffer, BLOCK, 1, fp) != 0)
    {
        // verify first four bytes are a jpeg start
        if (buffer[0] == 0xff 
            && buffer[1] == 0xd8 
            && buffer[2] == 0xff
            && (buffer[3] & 0xe0) == 0xe0)
        {
            //if new jpeg found close current image 
            (jpegStart != 0) ? (fclose(img)) : (jpegStart = 1);
            
            //make new jpeg in order they are found
            sprintf(filename, "%03d.jpg", count);
            
            //open new file including writing permissions
            img = fopen(filename, "a+");
            count++;
        }
        
        //means if (jpegStart != 0)
        if (jpegStart)
        {
            fwrite(buffer, BLOCK, 1, img);
        }
        
    }

    // close remianing files
    fclose(img);
    fclose(fp);

    return 0;
}

/*introduce jpeg struct with properties buffer, count, etc. Better ways to verify jpeg or read/write? */
