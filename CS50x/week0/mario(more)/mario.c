#include <stdio.h>
#include <cs50.h>

int main(void)
{
    while (true)
    {
        //Lets take the input
        int input = get_int("Height: ");
        if (input > 0 && input < 9)
        {
            for (int i = 1; i <= input; i++)
            {
                for (int j = 1; j <= input - i; j++)
                {
                    printf(" ");
                }
            
                for (int j = 1; j <= i ; j++)
                {
                    printf("#");
                }
        
                printf("  ");
            
                for (int j = 1; j <= i ; j++)
                {
                    printf("#");
                }
                
                printf("\n");
    
            }
            return 0;
        }
    }
}