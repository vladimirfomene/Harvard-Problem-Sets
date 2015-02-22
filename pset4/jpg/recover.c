/****************************************************************************
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 ***************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <cs50.h>



#define READ_SIZE 512
#define TEST_BYTE 4
#define TITLE 8

typedef uint8_t  BYTE; 

//need a buffer to store read bytes
typedef struct
{
   BYTE store[READ_SIZE];
}
buffer;

//Prototypes
bool is_jpeg(buffer a);

int main(int argc, char* argv[])
{
 
    
    if( argc!= 2)
    {
        printf("Usage : recover filename.\n");
        return 1;
    }
    
    
    buffer storage;
    
    //Need a counter for found files
    int counter = 0;
    
    //keep track of found jpegs
    bool found = false;
    
    //buffer to store jpeg name 
    char title[TITLE];
    
    //Open card file 
    FILE* file = fopen(argv[1], "r");
    
    //Check if card file successfully opened
    if( file == NULL)
    {
        printf("Could not open file\n");
        return 2;
    }
    
    //Initialize a stream for jpeg
    FILE* jpeg;
    
    while(fread(&storage,sizeof(BYTE)*READ_SIZE,1, file) )
    {
        //Check for jpeg start and jpeg not found 
        if(is_jpeg(storage) && !found)
        {
            found = true;
            //Start writing out a jpg
            sprintf(title, "%3d.jpg", counter);
            jpeg = fopen(title, "w");
            //check whether the jpeg file is open
            if(jpeg == NULL)
            {
                printf("Could not write to jpeg\n");
                return 3;
            }
            
            fwrite(&storage,sizeof(BYTE)* READ_SIZE,1, jpeg);
        }
        else if(is_jpeg(storage) && found)
        {
            //Check if jpeg already found and jpeg start
            
            //Close previous jpeg and push it to folder
            fclose(jpeg);
            //update file counter
            counter++; 
            //Open a new jpeg and start writing to it
            sprintf(title, "%3d.jpg", counter);
            jpeg = fopen(title, "w");
            //check whether the jpeg file is open
            if(jpeg == NULL)
            {
                printf("Could not write to jpeg\n");
                return 4;
            }
            
            fwrite(&storage,sizeof(BYTE)* READ_SIZE,1, jpeg);
            
        }
        else if(!(is_jpeg(storage)) && found)
        {
            //check if jpeg already started and continue writing to jpg file
            
            fwrite(&storage,sizeof(BYTE)* READ_SIZE,1, jpeg);
        }
        
        
    
    }
    //close the last jpeg
    fclose(jpeg);
    //close Card file stream
    fclose(file);
 
    return 0;
}

bool is_jpeg(buffer a)
{
    
    BYTE sequenceOne[] = {0xff,0xd8,0xff, 0xe0 };
    BYTE sequenceTwo[] = {0xff,0xd8,0xff, 0xe1 };
    
    if(memcmp(&a.store, &sequenceOne, TEST_BYTE)== 0)
    {
        return true;
    }
    else if(memcmp(&a.store, &sequenceTwo, TEST_BYTE)== 0)
    {
        return true;
    }
    
    return false;
}

