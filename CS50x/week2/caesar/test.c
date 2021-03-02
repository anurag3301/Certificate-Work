#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *in[])
{
    string key = (string)in[1];
    for(int i=0; i<strlen(key); i++)
    {
        if (isalpha(key[i]))
        {
            printf("Got");
        }
    }
    return 0;

}