#include "helpers.h"
#include <stdio.h>
#include <math.h>

void print(int height, int width, RGBTRIPLE image[height][width], char channel);

RGBTRIPLE getblurValue(int x, int y, int height, int width, RGBTRIPLE image[height][width]){
    RGBTRIPLE sec[3][3];
    int rSum = 0, gSum = 0, bSum = 0, rAvg , gAvg, bAvg;
    RGBTRIPLE blurValue;
    
    for(int i=y-1; i<y+2; i++){
        for(int j=x-1; j<x+2; j++ ){
            if((i>-1 && i<height) && (j>-1 && j<width)){
                sec[i-(y-1)][j-(x-1)] = image[i][j];
            }
            else{
                sec[i-(y-1)][j-(x-1)].rgbtRed = 0;
                sec[i-(y-1)][j-(x-1)].rgbtGreen = 0;
                sec[i-(y-1)][j-(x-1)].rgbtBlue = 0;
            }
            
        }
    }
    
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            rSum += sec[i][j].rgbtRed;
            gSum += sec[i][j].rgbtGreen;
            bSum += sec[i][j].rgbtBlue;
        }
    }
    
    rAvg = round((float)rSum/3);
    gAvg = round((float)gSum/3);
    bAvg = round((float)bSum/3);
    
    blurValue.rgbtRed = (rAvg<0)?0:(rAvg>255)?255:rAvg;
    blurValue.rgbtGreen = (gAvg<0)?0:(gAvg>255)?255:gAvg;
    blurValue.rgbtBlue = (bAvg<0)?0:(bAvg>255)?255:bAvg;
    
    return blurValue;
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{ 
    RGBTRIPLE temp[height][width];
    RGBTRIPLE blurValue;
    
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            temp[i][j] = image[i][j];
        }
    }
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            blurValue = getblurValue(j, i, height, width, temp);
            
            image[i][j].rgbtRed = blurValue.rgbtRed;
            image[i][j].rgbtGreen = blurValue.rgbtGreen;
            image[i][j].rgbtBlue = blurValue.rgbtBlue;
        }
    }
    
    return;
}


int main(){
    
    int height = 10, width=10;
    
    RGBTRIPLE image[height][width];
    
    for(int i=1; i<=height; i++){
        for(int j=1; j<=width; j++ ){
            image[i-1][j-1].rgbtRed = j;
            image[i-1][j-1].rgbtBlue = j;
            image[i-1][j-1].rgbtGreen = j;
        }
    }
    
    print(height, width, image, 'r');
    
    edges(height, width, image);
    
    print(height, width, image, 'r');
    
    
    
    
    
    return 0;
}


void print(int height, int width, RGBTRIPLE image[height][width], char channel){
    
    if(channel == 'r' || channel == 'a'){
        printf("\nRed Channel\n");
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++ ){
                printf("%i  ", image[i][j].rgbtRed);
            }
            printf("\n");
        }
    }
    
    if(channel == 'g' || channel == 'a'){
        printf("\nGreen Channel\n");
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++ ){
                printf("%i  ", image[i][j].rgbtGreen);
            }
            printf("\n");
        }
    }
        
    if(channel == 'b' || channel == 'a'){
        printf("\nBlue Channel\n");
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++ ){
                printf("%i  ", image[i][j].rgbtBlue);
            }
            printf("\n");
        }
    }
        
}
