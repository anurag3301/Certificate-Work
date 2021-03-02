#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    while (true)
    {
        // Get user input
        float dollars = get_float("Change owed: ");
        if (dollars > 0.0)
        {
            /* do the magic*/
            
            int cents = round(dollars * 100);
            int val25 = cents / 25;
            cents -= val25 * 25;
            
            int val10 = cents / 10;
            cents -= val10 * 10;
            
            int val5 = cents / 5;
            cents -= val5 * 5;
            
            int val1 = cents / 1;
            cents -= val1 * 1;
            
            printf("%i\n", val10 + val25 + val5 + val1);
            return 0;
        }
    }
}