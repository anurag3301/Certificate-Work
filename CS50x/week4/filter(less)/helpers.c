#include <stdio.h>
#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = ((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3;
            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtRed = round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float r = 0, b = 0, g = 0, nr = 0, ng = 0, nb = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            b = image[i][j].rgbtBlue;
            g = image[i][j].rgbtGreen;
            r = image[i][j].rgbtRed;
            nr = 0.393 * r + 0.769 * g + 0.189 * b;
            ng = 0.349 * r + 0.686 * g + 0.168 * b;
            nb = 0.272 * r + 0.534 * g + 0.131 * b;
            
            image[i][j].rgbtRed = nr > 255 ? 255 : round(nr);
            image[i][j].rgbtGreen = ng > 255 ? 255 : round(ng);
            image[i][j].rgbtBlue = nb > 255 ? 255 : round(nb);
        
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tempR, tempG, tempB;
    
    for (int i = 0; i < height; i++)
    {
        int start = 0;
        int end = width - 1;
        while (start < end)
        {
            tempR = image[i][start].rgbtRed;
            tempG = image[i][start].rgbtGreen;
            tempB = image[i][start].rgbtBlue;
            
            image[i][start].rgbtRed = image[i][end].rgbtRed;
            image[i][start].rgbtGreen = image[i][end].rgbtGreen;
            image[i][start].rgbtBlue = image[i][end].rgbtBlue;
            
            image[i][end].rgbtRed = tempR;
            image[i][end].rgbtGreen = tempG;
            image[i][end].rgbtBlue = tempB;
            
            start++;
            end--;
        }   
    }
    
    return;
}

// Blur image
void print(int height, int width, RGBTRIPLE image[height][width], char channel)
{
    
    if (channel == 'r' || channel == 'a')
    {
        printf("\nRed Channel\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%i  ", image[i][j].rgbtRed);
            }
            printf("\n");
        }
    }
    
    if (channel == 'g' || channel == 'a')
    {
        printf("\nGreen Channel\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%i  ", image[i][j].rgbtGreen);
            }
            printf("\n");
        }
    }
        
    if (channel == 'b' || channel == 'a')
    {
        printf("\nBlue Channel\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%i  ", image[i][j].rgbtBlue);
            }
            printf("\n");
        }
    }
}

RGBTRIPLE getblurValue(int x, int y, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE sec[3][3];
    int rSum = 0, gSum = 0, bSum = 0, rAvg, gAvg, bAvg, divider = 0;
    RGBTRIPLE blurValue;
    
    for (int i = y - 1; i < y + 2; i++)
    {
        for (int j = x - 1; j < x + 2; j++)
        {
            if ((i > - 1 && i < height) && (j > - 1 && j < width))
            {
                sec[i - (y - 1)][j - (x - 1)] = image[i][j];
                divider++;
            }
            else
            {
                sec[i - (y - 1)][j - (x - 1)].rgbtRed = 0;
                sec[i - (y - 1)][j - (x - 1)].rgbtGreen = 0;
                sec[i - (y - 1)][j - (x - 1)].rgbtBlue = 0;
            }
            
        }
    }
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            rSum += sec[i][j].rgbtRed;
            gSum += sec[i][j].rgbtGreen;
            bSum += sec[i][j].rgbtBlue;
        }
    }
    
    rAvg = round((float)rSum / divider);
    gAvg = round((float)gSum / divider);
    bAvg = round((float)bSum / divider);
    
    blurValue.rgbtRed = (rAvg < 0) ? 0 : (rAvg > 255) ? 255 : rAvg;
    blurValue.rgbtGreen = (gAvg < 0) ? 0 : (gAvg > 255) ? 255 : gAvg;
    blurValue.rgbtBlue = (bAvg < 0) ? 0 : (bAvg > 255) ? 255 : bAvg;
    
    return blurValue;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    RGBTRIPLE blurValue;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blurValue = getblurValue(j, i, height, width, temp);
            
            image[i][j].rgbtRed = blurValue.rgbtRed;
            image[i][j].rgbtGreen = blurValue.rgbtGreen;
            image[i][j].rgbtBlue = blurValue.rgbtBlue;
        }
    }
    
    return;
}
