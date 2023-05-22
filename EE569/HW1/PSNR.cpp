// Name: Chengyu Lu
// USC ID Number: 5157638886
// USC Email: luchenggy@usc.edu
// Submission Date: 01/29/2023

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <math.h>
#define MAX_CHAR 256
const int Height = 240;
const int Width = 400;
using namespace std;
int main()
{
    FILE *pFile, *qFile;
    float MSE = 0;
    int b, c;
    pFile = fopen("Pepper.raw", "rb");
    // Pepper_gray
    // Pepper
    qFile = fopen("Pepper_RGB2.raw", "rb"); 
    // Pepper_gray1,Pepper_gray2,Pepper_gray3
    // Pepper_gray4_5_5, Pepper_gray4_5_20, Pepper_gray4_5_50, Pepper_gray4_20_5, Pepper_gray4_20_20, Pepper_gray4_20_50, Pepper_gray4_50_5, Pepper_gray4_50_20, Pepper_gray4_50_50
    // Pepper_gray5_5_5, Pepper_gray5_5_20, Pepper_gray5_5_50, Pepper_gray5_20_5, Pepper_gray5_20_20, Pepper_gray5_20_50, Pepper_gray5_50_5, Pepper_gray5_50_20, Pepper_gray5_50_50
    // Pepper_NLM5_5, Pepper_NLM21_5, Pepper_NLM21_21, Pepper_NLM29_5, Pepper_NLM29_21, Pepper_NLM29_29
    // Pepper_RGB, Pepper_RGB1, Pepper_RGB2
    if (pFile == NULL || qFile == NULL)
    {
        perror("Error opening file");
    }
    else
    {
        do
        {
            c = fgetc(pFile);
            b = fgetc(qFile);
            if (c != EOF && b != EOF)
            {
                MSE += pow((b - c), 2);
            }
        } while (c != EOF && b != EOF);
        fclose(qFile);
        fclose(pFile);
    }
    //MSE/=((float)Height*Width) ;
    MSE/=((float)Height*Width*3.0);
    cout<<"MSE:"<<MSE<<endl<<"PSNR:"<<10.0*log10(pow(255,2)/MSE)<<endl;
    return 0;
}