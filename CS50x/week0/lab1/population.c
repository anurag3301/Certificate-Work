#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start = 0;
    int end = 0;
    int restult = 0;
    int years = 0;
    
    while (start < 9)
    {
        start = get_int("Start size: ");
    }
    // printf("%i \n", start);
    
    
    // TODO: Prompt for end size
    while (end < start)
    {
        end = get_int("End size: ");
    }
    // printf("%i \n", start);
    
    
    // TODO: Calculate number of years until we reach threshold
    while (!(start >= end))
    {
        start = start + (start / 3) - (start / 4);
        years += 1;
    }
    
    
    // TODO: Print number of years
    printf("Years: %i\n", years);
}