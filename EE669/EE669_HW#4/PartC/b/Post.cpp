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
void shift(int inputtemp[][256][3], int input[][256][3], int x, int y)
{
    FILE *pFile;
    string filename = "pepper";
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
                for (int k = 0; k < 3; ++k)
                {
                    inputtemp[i][j][k] = input[i - x][j - y][k];
                }
            }
        }
    }
    else if (x >= 0 && y < 0)
    {
        for (int i = x; i < size; ++i)
        {
            for (int j = 0; j < size + y; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    inputtemp[i][j][k] = input[i - x][j - y][k];
                }
            }
        }
    }
    else if (x < 0 && y >= 0)
    {
        for (int i = 0; i < size + x; ++i)
        {
            for (int j = y; j < size; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    inputtemp[i][j][k] = input[i - x][j - y][k];
                }
            }
        }
    }
    else if (x < 0 && y < 0)
    {
        for (int i = 0; i < size + x; ++i)
        {
            for (int j = 0; j < size + y; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    inputtemp[i][j][k] = input[i - x][j - y][k];
                }
            }
        }
    }
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                fputc(inputtemp[i][j][k], pFile);
            }
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
    int input[256][256][3], inputtemp[256][256][3];
    pFile = fopen("pepper.raw", "rb");
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                input[i][j][k] = fgetc(pFile);
                inputtemp[i][j][k] = input[i][j][k];
                b++;
            }
        }
    }
    cout << b << ' ' << fgetc(pFile) << ' ' << fgetc(pFile) << ' ' << fgetc(pFile) << ' ' << fgetc(pFile) << ' ' << fgetc(pFile);
    fclose(pFile);

    for (int x = -3; x < 5; x++)
    {
        for (int y = -3; y < 5; y++)
        {
            shift(inputtemp, input,  x, y);
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        inputtemp[i][j][k] = input[i][j][k];
                    }
                }
            }
        }
    }
    qFile = fopen("p.raw", "wb");
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                fputc(input[i][j][k], qFile);
            }
        }
    }
    fclose(qFile);
    return 0;
}