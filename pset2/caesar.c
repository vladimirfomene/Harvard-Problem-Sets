#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //Sanitize commandline arguments
    while(argc != 2)
    {
        printf("Enter the right commandline Arguments!\n");
        return 1;
    }
    
    //convert the string key entered at the commandline into an integer
    int k = atoi(argv[1]);
    
    //Ask for user input and collect the data
    printf("Enter text please:\n");
    
    string p = GetString();
    
    //Loop through the plain text
    for(int i = 0, n = strlen(p) ; i < n ; i++)
    {
        //Encrypt capital letters and small letters leaving spaces unchanged
        if(p[i] > 64 && p[i] < 91)
        {
            p[i] = ((p[i] + k) > 90)? (65 + ((p[i] + k) % 91)) : (p[i] + k);
            printf("%c", p[i]);
        }
        else if(p[i] > 96 && p[i] < 123)
        {
             p[i] = ((p[i] + k) > 122)? (97 + ((p[i] + k) % 123)) : (p[i] + k);
            printf("%c", p[i]);    
        }
        else
        {
            printf("%c", p[i]);
        }
        
    }
    
    //Goto a newline after printing the cipher text 
    printf("\n");
    return 0;
}
