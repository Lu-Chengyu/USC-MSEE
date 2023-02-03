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
}

int main()
{
    FILE *pFile;
    float MSE = 0;
    int c;
    int b = 0;
    int input[256][256][3], inputtemp[256][256][3], shiftsum[256][256][3];

    for (int x = -3; x < 5; x++)
    {
        for (int y = -3; y < 5; y++)
        {
            FILE *qFile;
            string filename = "pepper";
            filename.append(to_string(x));
            filename.append(to_string(y));
            filename.append(".raw");
            qFile = fopen(filename.c_str(), "rb");
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        input[i][j][k] = fgetc(qFile);
                        inputtemp[i][j][k] = input[i][j][k];
                    }
                }
            }
            cout<<fgetc(qFile)<<' '<<fgetc(qFile)<<' '<<fgetc(qFile)<<' ';
            shift(inputtemp, input, -x, -y);
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        shiftsum[i][j][k] += inputtemp[i][j][k];
                    }
                }
            }
            fclose(qFile);
        }
    }

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                shiftsum[i][j][k] /= 64;
            }
        }
    }

    pFile = fopen("pepperpost.raw", "wb");
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                fputc(shiftsum[i][j][k], pFile);
            }
        }
    }
    fclose(pFile);

    return 0;
}