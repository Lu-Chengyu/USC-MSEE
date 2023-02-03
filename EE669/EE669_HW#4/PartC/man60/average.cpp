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
}

int main()
{
    FILE *pFile;
    float MSE = 0;
    int c;
    int b = 0;
    int input[256][256], inputtemp[256][256], shiftsum[256][256];

    for (int x = -3; x < 5; x++)
    {
        for (int y = -3; y < 5; y++)
        {
            FILE *qFile;
            string filename = "camera_man";
            filename.append(to_string(x));
            filename.append(to_string(y));
            filename.append(".raw");
            qFile = fopen(filename.c_str(), "rb");
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    input[i][j] = fgetc(qFile);
                    inputtemp[i][j] = input[i][j];
                }
            }
            cout << fgetc(qFile) << ' ' << fgetc(qFile) << ' ' << fgetc(qFile) << ' ';
            shift(inputtemp, input, -x, -y);
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {

                    shiftsum[i][j] += inputtemp[i][j];
                }
            }
            fclose(qFile);
        }
    }

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            shiftsum[i][j] /= 64;
        }
    }

    pFile = fopen("camera_manpost.raw", "wb");
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            fputc(shiftsum[i][j], pFile);
        }
    }
    fclose(pFile);
    return 0;
}