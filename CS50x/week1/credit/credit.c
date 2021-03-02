#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long int num = get_long("Number: ");
    if (num > 1000000000000)
    {
        int arr[16] = {0}; 
        int i = 0; 
        int j, r; 
      
        while (num != 0) 
        { 
            r = num % 10; 
            arr[i] = r; 
            i++; 
            num = num / 10; 
        }
        int dino = 0;
        for (int k = 15; k > 10; k--)
        {
            if (arr[k] > 0)
            {
                dino = k;
                // printf("%i %i", dino, arr[k]);
                break;
            } 
        }
        
        int val1 = 0;
        int add = 0;
        for (int k = 1; k < 16; k += 2)
        {
            val1 = arr[k] * 2;
            if (val1 > 9)
            {
                add += val1 % 10;
                add += val1 / 10;
            }
            else
            {
                add += val1;
                
            }
            
        }
        
        for (int l = 0; l < 16; l += 2)
        {
            add += arr[l];
        }
        // printf("%i\n", add);
        
        if (add % 10 == 0)
        {
            if (arr[dino] == 3 && (arr[dino - 1] == 4 || arr[dino - 1] == 7))
            {
                printf("AMEX\n");
            }
            else if (arr[dino] == 5 && (arr[dino - 1] == 1 || arr[dino - 1] == 2 || arr[dino - 1] == 3 
                                        || arr[dino - 1] == 4 || arr[dino - 1] == 5))
            {
                printf("MASTERCARD\n");
            }
            else if (arr[dino] == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
        
        
    }
    else
    {
        printf("INVALID\n");
    }
    
}