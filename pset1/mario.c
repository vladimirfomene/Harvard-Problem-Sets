#include <cs50.h>
#include <stdio.h>


int main(void)
{
    int height;
    //request height from user 
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while(height < 0 || height > 23);
    
    int s = height - 2;
    //write as many line as the height
    for(int i = 0; i < height; i++)
    {
        //prints the blank before the hash
        for(int j = s; j >= 0; j--)
        {
            printf(" ");
        }
        //Prints the hash
        for(int k = s; k < height; k++)
        {
            printf("#");
        }
        //Goes to a newline ready to print the next line
        printf("\n");
        s--;
    }
    
    return 0;
}
