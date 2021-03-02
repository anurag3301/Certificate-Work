#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *in[])
{
    if (argc == 2)
    {
        if (strlen(in[1]) == 26)
        {
            for (int i = 0; i < strlen(in[1]); i++)
            {
                if (!isalpha(in[1][i]))
                {
                    printf("Should contain only character");
                    return 1;
                }
            }

            // string key = "ZABCDEFGHIJKLMNOPQRSTUVWXY";
            // string key = "zabcdefghijklmnopqrstuvwxy";
            // string key = "YTNSHKVEFXRBAUQZCLWDMIPGJO";
            string key = in[1];

            int keyInt[26] = {0};
            for (int i = 0; i < strlen(key); i++)
            {
                if ((int)key[i] < 96)
                {
                    keyInt[i] = (int)key[i] - 64;
                }
                else
                {
                    keyInt[i] = (int)key[i] - 96;
                }
            }
            for (int i = 0; i < 26; i++)
            {
                for (int j = 0; j < 26; j++)
                {
                    if (i == j)
                    {
                        continue;
                    }
                    else if (keyInt[i] == keyInt[j])
                    {
                        printf("Duplicated character detected");
                        return 1;
                    }
                }
            }

            string mes = get_string("plaintext:  ");
            // string mes = "hello";
            printf("ciphertext: ");
            for (int i = 0; i < strlen(mes); i++)
            {
                if (isalpha(mes[i]))
                {
                    int val = 0;
                    if ((int)mes[i] < 96)
                    {
                        val = 64;
                    }
                    else
                    {
                        val = 96;
                    }
                    printf("%c", keyInt[(int)mes[i] - val - 1] + val);
                }
                else
                {
                    printf("%c", mes[i]);
                }
            }
            printf("\n");
            return 0;
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
