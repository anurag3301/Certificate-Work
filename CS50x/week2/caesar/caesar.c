#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *in[])
{   
    if (argc == 2 && atoi(in[1]) > 0)
    {
        
        bool ischar = true;
        string tempkey = (string)in[1];
        for (int i = 0; i < strlen(tempkey); i++)
        {
            if (isalpha(tempkey[i]))
            {
                ischar = false;
            }
        }
        
        if (ischar)
        {
            int key = atoi(in[1]);
            string message = get_string("plaintext:  ");
            printf("ciphertext: ");
            // int key = 13;
            // string message = "be sure to drink your Ovaltine";
            for (int i = 0; i < strlen(message); i++)
            {
                if (isalpha(message[i]))
                {
                    int sub = (((int)message[i] < 91) ? 64 : 98);
                    int index = (int)message[i] - sub;
                    int enc = (index + key) % 26;
                    int chifer = enc + sub;
                    if ((chifer > 90 && chifer < 97) || chifer > 122)
                    {
                        chifer -= 26;
                    }
    
                    printf("%c", (char)(chifer));
                }
                else
                {
                    printf("%c", message[i]);
                }
    
            }
            printf("\n");
            return 0;
        }
        else
        {
            printf("Usage: ./caesar key");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key");
        return 1;
    }

}