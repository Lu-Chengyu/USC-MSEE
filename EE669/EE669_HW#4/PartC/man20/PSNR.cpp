#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <math.h>
#define MAX_CHAR 256
using namespace std;
int main()
{
    FILE *pFile, *qFile;
    float MSE = 0;
    int b, c;
    pFile = fopen("camera_man.raw", "rb");
    qFile = fopen("camera_manpost.raw", "rb");
    if (pFile == NULL || qFile == NULL)
    {
        perror("Error opening file");
    }
    else
    {
        do
        {
            c = fgetc(pFile); // fgetc得到的是对应字符的ASSICII码int值
            b = fgetc(qFile);
            //cout<<b<<' '<<c<<' ';
            if (c != EOF && b != EOF)
            {
                MSE += pow((b - c), 2);
            }
        } while (c != EOF && b != EOF);
        fclose(qFile);
        fclose(pFile);
    }
    MSE/=65536.0 ;
    cout<<"MSE:"<<MSE<<endl<<"PSNR:"<<10.0*log10(pow(255,2)/MSE)<<endl; //255
    return 0;
}