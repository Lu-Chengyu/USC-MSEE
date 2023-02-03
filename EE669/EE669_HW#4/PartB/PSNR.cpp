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
    pFile = fopen("boat.raw", "rb"); // bike.raw, boat.raw, hat.raw, house.raw, people.raw, plane.raw
    qFile = fopen("boat100.raw", "rb");
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
    MSE/=262144.0 ;
    cout<<"MSE:"<<MSE<<endl<<"PSNR:"<<10.0*log10(pow(255,2)/MSE)<<endl;
    return 0;
}