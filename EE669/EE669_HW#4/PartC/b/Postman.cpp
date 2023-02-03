#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <string.h>
#define size 256
using namespace std;
void shift(int inputtemp[][256], int input[][256], int x, int y)
{
    FILE *pFile;
    string filename = "camera_man";
    filename.append(to_string(x));
    filename.append(to_string(y));
    filename.append(".bmp");
    pFile = fopen(filename.c_str(), "wb");
    if (x >= 0 && y >= 0)
    {
        for (int i = x; i < size; ++i)
        {
            for (int j = y; j < size; ++j)
            {
                inputtemp[i][j] = input[i - x][j - y];
            }
        }
    }
    else if (x >= 0 && y < 0)
    {
        for (int i = x; i < size; ++i)
        {
            for (int j = 0; j < size + y; ++j)
            {
                inputtemp[i][j] = input[i - x][j - y];
            }
        }
    }
    else if (x < 0 && y >= 0)
    {
        for (int i = 0; i < size + x; ++i)
        {
            for (int j = y; j < size; ++j)
            {
                inputtemp[i][j] = input[i - x][j - y];
            }
        }
    }
    else if (x < 0 && y < 0)
    {
        for (int i = 0; i < size + x; ++i)
        {
            for (int j = 0; j < size + y; ++j)
            {
                inputtemp[i][j] = input[i - x][j - y];
            }
        }
    }
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            fputc(inputtemp[i][j], pFile);
        }
    }
    fclose(pFile);
}

int main()
{
    FILE *pFile, *qFile;
    float MSE = 0;
    int c;
    int b = 0;
    int input[256][256], inputtemp[256][256];
    pFile = fopen("camera_man.raw", "rb");
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            input[i][j] = fgetc(pFile);
            inputtemp[i][j] = input[i][j];
            b++;
        }
    }
    cout << b << ' ' << fgetc(pFile) << ' ' << fgetc(pFile) << ' ' << fgetc(pFile) << ' ' << fgetc(pFile) << ' ' << fgetc(pFile);
    fclose(pFile);

    for (int x = -3; x < 5; x++)
    {
        for (int y = -3; y < 5; y++)
        {
            shift(inputtemp, input, x, y);
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    inputtemp[i][j] = input[i][j];
                }
            }
        }
    }
    qFile = fopen("p.raw", "wb");
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            fputc(input[i][j], qFile);
        }
    }
    fclose(qFile);
    return 0;
}