#include "helpers.h"
#include <math.h>
#include <stdio.h>

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

// Detect edges

RGBTRIPLE getedgeValue(int x, int y, int height, int width, RGBTRIPLE image[height][width])
{
    int kernalX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int kernalY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE sec[3][3];
    int rGx = 0, gGx = 0, bGx = 0, rGy = 0, gGy = 0, bGy = 0, fR, fG, fB;
    RGBTRIPLE edgeValue;
    
    for (int i = y - 1; i < y + 2; i++)
    {
        for (int j = x - 1; j < x + 2; j++)
        {
            if ((i > - 1 && i < height) && (j > - 1 && j < width))
            {
                sec[i - (y - 1)][j - (x - 1)] = image[i][j];
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
            rGx += kernalX[i][j] * sec[i][j].rgbtRed;
            gGx += kernalX[i][j] * sec[i][j].rgbtGreen;
            bGx += kernalX[i][j] * sec[i][j].rgbtBlue;
        }
    }
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            rGy += kernalY[i][j] * sec[i][j].rgbtRed;
            gGy += kernalY[i][j] * sec[i][j].rgbtGreen;
            bGy += kernalY[i][j] * sec[i][j].rgbtBlue;
        }
    }
    
    fR = round(sqrt(pow(rGx, 2) + pow(rGy, 2)));
    fG = round(sqrt(pow(gGx, 2) + pow(gGy, 2)));
    fB = round(sqrt(pow(bGx, 2) + pow(bGy, 2)));
    
    edgeValue.rgbtRed = (fR < 0) ? 0 : (fR > 255) ? 255 : fR;
    edgeValue.rgbtGreen = (fG < 0) ? 0 : (fG > 255) ? 255 : fG;
    edgeValue.rgbtBlue = (fB < 0) ? 0 : (fB > 255) ? 255 : fB;
    
    return edgeValue;
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{ 
    RGBTRIPLE temp[height][width];
    RGBTRIPLE edgeValue;
    
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
            edgeValue = getedgeValue(j, i, height, width, temp);
            
            image[i][j].rgbtRed = edgeValue.rgbtRed;
            image[i][j].rgbtGreen = edgeValue.rgbtGreen;
            image[i][j].rgbtBlue = edgeValue.rgbtBlue;
        }
    }
    
    return;
}


