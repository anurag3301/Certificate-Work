#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *in[])
{

    if (argc == 2){
        
        if (strlen(in[1])==26)
        {
            for (int i=0; i<strlen(in[1]); i++)
            {
                if(!isalpha(in[1][i]))
                {
                    printf("Should contain only character");
                    return 1;
                }
                for (int j=0; j<strlen(in[1]); j++)
                {
                }
                
                
            }
        }
        else
        {
            printf("Key must contain 26 characters.");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    
}
