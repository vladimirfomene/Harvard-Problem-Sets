#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //Getting user input 
    printf("O hai!How much change is owed?\n");
    float input = GetFloat();
    int change = roundf(input * 100);
    //Sanitizing user input  
    while(change < 0)
    {
        printf("How much change is owed?\n");
        input = GetFloat();
        change = roundf(input * 100);
    }
    
    int coins = 0;
    //Giving change
    while (change > 0)
    {
        while(change >= 25 )
        {
            change = change - 25;
            coins++; 
        } 
        while(change >= 10)
        {
           change = change - 10;
           coins++; 
        }
        while(change >= 5)
        {
            change = change - 5;
            coins++; 
        }
        while(change >= 1)
        {
            change = change - 1;
            coins++; 
        }
    }
    
    printf(" %d\n", coins); 
    return 0;
}
