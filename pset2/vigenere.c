#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    //Sanitize commandline arguments
    if(argc != 2)
    {
        printf("Enter the right commandline Arguments!\n");
        return 1;
    }
    //Ensure that the keyword is comprised of alphabets
    for(int j = 0,m = strlen(argv[1]); j < m ;j++)
    {
        if(argv[1][j] < 97 || argv[1][j]> 122)
        {
            printf("Enter an alphabetical keyword:\n");
            return 1;   
        }
    
    }
    
    //Store the keyword entered at the commandline 
    string key = argv[1];
    int len = strlen(key);
    
    //Ask for user input and collect the data
    printf("Enter text please:\n");
    
    string p = GetString();
    
    //helper variable
    int counter = 0;
    //Loop through the plain text
    for(int i = 0, n = strlen(p) ; i < n ; i++)
    {
        //use each character of the keyword as a caesar cipher key
        int index = counter % len;
        int k = key[index] - 97;
        
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
            continue;
        }
        
        counter++;
        
    }
    
    //Goto a newline after printing the cipher text 
    printf("\n");
    return 0;
}
