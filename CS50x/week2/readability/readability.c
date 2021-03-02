#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string sen = get_string("Text: ");
    // string sen = "Harry Potter was a highly unusual boy in many ways. For one thing, he hated the summer holidays more than any other time of year. For another, he really wanted to do his homework, but was forced to do it in secret, in the dead of the night. And he also happened to be a wizard.";
    // string sen = "Congratulations! Today is your day. You're off to Great Places! You're off and away!";
    int charcount = strlen(sen);
    int wordcount = 0;
    int specialcount = 0;
    int sentencecount = 0;
    for (int i = 0; i < charcount; i++)
    {
        if (sen[i] == ' ')
        {
            wordcount += 1;
        }
    
        if (sen[i] == '.' || sen[i] == '!' || sen[i] == '?')
        {
            sentencecount += 1;
        }
   
        if (!((sen[i] > 64 && sen[i] < 91) || (sen[i] > 96 && sen[i] < 123) || sen[i] == ' '))
        {
            specialcount += 1;
        }
    }
    wordcount += 1;
    charcount = charcount - (specialcount + wordcount) + 1;
    
    float L = ((float)charcount / (float)wordcount) * 100;
    float S = ((float)sentencecount / (float)wordcount) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = (int)round(index);
    // printf("%i \n", specialcount);
    // printf("%i \n", wordcount);
    // printf("%i \n", sentencecount);
    // printf("%i \n", charcount);
    // printf("%f \n", L);
    // printf("%f \n", S);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}