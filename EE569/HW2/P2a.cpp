// Name: Chengyu Lu
// USC ID Number: 5157638886
// USC Email: luchengy@usc.edu
// Submission Date: 02/19/2023
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <ctime>

using namespace std;

const int BytesPerPixel = 1;
const int Height = 1000;
const int Width = 1500;

void openFile(const char *fileName, unsigned char Imagedata[Height][Width][BytesPerPixel])
{
    FILE *file;
    if (!(file = fopen(fileName, "rb")))
    {
        cout << "Cannot open file: "
             << fileName << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Height * Width * BytesPerPixel, file);
    fclose(file);
}

void writeFile(const char *fileName, unsigned char Imagedata[Height][Width][BytesPerPixel])
{
    FILE *file;
    if (!(file = fopen(fileName, "wb")))
    {
        cout << "Cannot open file: "
             << fileName << endl;
        exit(1);
    }
    fwrite(Imagedata, sizeof(unsigned char), Height * Width * BytesPerPixel, file);
    fclose(file);
}

void fixedThresholding(unsigned char Imagedata[Height][Width][BytesPerPixel])
{
    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            for (int k = 0; k < BytesPerPixel; ++k)
            {
                if (Imagedata[i][j][k] < 128)
                {
                    Imagedata[i][j][k] = 0;
                }
                else
                {
                    Imagedata[i][j][k] = 255;
                }
            }
        }
    }
}

void randomThresholding(unsigned char Imagedata[Height][Width][BytesPerPixel])
{
    unsigned char Rand[Height][Width][BytesPerPixel];
    srand((unsigned char)time(NULL));
    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            for (int k = 0; k < BytesPerPixel; ++k)
            {
                Rand[i][j][k] = rand() % 256;
            }
        }
    }
    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            for (int k = 0; k < BytesPerPixel; ++k)
            {
                if (Imagedata[i][j][k] < Rand[i][j][k])
                {
                    Imagedata[i][j][k] = 0;
                }
                else
                {
                    Imagedata[i][j][k] = 255;
                }
            }
        }
    }
}

void dithering32(int n, float inputblock[2][2][BytesPerPixel], float outputblock[32][32][BytesPerPixel])
{
    int m = 2;
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                outputblock[i][j][k] = inputblock[i][j][k];
            }
        }
    }
    while (m != n)
    {
        for (int k = 0; k < BytesPerPixel; ++k)
        {
            for (int i = m; i < 2 * m; ++i)
            {
                for (int j = m; j < 2 * m; ++j)
                {
                    outputblock[i][j][k] = 4 * outputblock[i - m][j - m][k];
                }
            }
        }
        for (int k = 0; k < BytesPerPixel; ++k)
        {
            for (int i = 0; i < m; ++i)
            {
                for (int j = m; j < 2 * m; ++j)
                {
                    outputblock[i][j][k] = 4 * outputblock[i][j - m][k];
                    outputblock[i][j][k] += 2;
                }
            }
        }
        for (int k = 0; k < BytesPerPixel; ++k)
        {
            for (int i = m; i < 2 * m; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    outputblock[i][j][k] = 4 * outputblock[i - m][j][k];
                    outputblock[i][j][k] += 3;
                }
            }
        }
        for (int k = 0; k < BytesPerPixel; ++k)
        {
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    outputblock[i][j][k] *= 4;
                    outputblock[i][j][k]++;
                }
            }
        }
        m *= 2;
    }
}

void dithering8(int n, float inputblock[2][2][BytesPerPixel], float outputblock[8][8][BytesPerPixel])
{
    int m = 2;
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                outputblock[i][j][k] = inputblock[i][j][k];
            }
        }
    }
    while (m != n)
    {
        for (int k = 0; k < BytesPerPixel; ++k)
        {
            for (int i = m; i < 2 * m; ++i)
            {
                for (int j = m; j < 2 * m; ++j)
                {
                    outputblock[i][j][k] = 4 * outputblock[i - m][j - m][k];
                }
            }
        }
        for (int k = 0; k < BytesPerPixel; ++k)
        {
            for (int i = 0; i < m; ++i)
            {
                for (int j = m; j < 2 * m; ++j)
                {
                    outputblock[i][j][k] = 4 * outputblock[i][j - m][k];
                    outputblock[i][j][k] += 2;
                }
            }
        }
        for (int k = 0; k < BytesPerPixel; ++k)
        {
            for (int i = m; i < 2 * m; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    outputblock[i][j][k] = 4 * outputblock[i - m][j][k];
                    outputblock[i][j][k] += 3;
                }
            }
        }
        for (int k = 0; k < BytesPerPixel; ++k)
        {
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    outputblock[i][j][k] *= 4;
                    outputblock[i][j][k]++;
                }
            }
        }
        m *= 2;
    }
}

void ditheringResult2(int n, float inputblock[2][2][BytesPerPixel], unsigned char result[Height][Width][BytesPerPixel])
{
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if ((inputblock[i][j][k] + 0.5) * 255 / (n * n) > 255)
                {
                    inputblock[i][j][k] = 255;
                }
                else
                {
                    inputblock[i][j][k] = (inputblock[i][j][k] + 0.5) * 255 / (n * n);
                }
            }
        }
    }
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height; ++i)
        {
            for (int j = 0; j < Width; ++j)
            {
                if (result[i][j][k] <= inputblock[i % n][j % n][k])
                {
                    result[i][j][k] = 0;
                }
                else
                {
                    result[i][j][k] = 255;
                }
            }
        }
    }
}

void ditheringResult8(int n, float inputblock[8][8][BytesPerPixel], unsigned char result[Height][Width][BytesPerPixel])
{
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if ((inputblock[i][j][k] + 0.5) * 255 / (n * n) > 255)
                {
                    inputblock[i][j][k] = 255;
                }
                else
                {
                    inputblock[i][j][k] = (inputblock[i][j][k] + 0.5) * 255 / (n * n);
                }
            }
        }
    }
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height; ++i)
        {
            for (int j = 0; j < Width; ++j)
            {
                if (result[i][j][k] <= inputblock[i % n][j % n][k])
                {
                    result[i][j][k] = 0;
                }
                else
                {
                    result[i][j][k] = 255;
                }
            }
        }
    }
}

void ditheringResult32(int n, float inputblock[32][32][BytesPerPixel], unsigned char result[Height][Width][BytesPerPixel])
{
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if ((inputblock[i][j][k] + 0.5) * 255 / (n * n) > 255)
                {
                    inputblock[i][j][k] = 255;
                }
                else
                {
                    inputblock[i][j][k] = (inputblock[i][j][k] + 0.5) * 255 / (n * n);
                }
            }
        }
    }
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height; ++i)
        {
            for (int j = 0; j < Width; ++j)
            {
                if (result[i][j][k] <= inputblock[i % n][j % n][k])
                {
                    result[i][j][k] = 0;
                }
                else
                {
                    result[i][j][k] = 255;
                }
            }
        }
    }
}

void display2(int n, float inputblock[2][2][BytesPerPixel])
{
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cout << inputblock[i][j][k] << " ";
            }
            cout << endl;
        }
    }
}

void display8(int n, float inputblock[8][8][BytesPerPixel])
{
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cout << inputblock[i][j][k] << " ";
            }
            cout << endl;
        }
    }
}

void display32(int n, float inputblock[32][32][BytesPerPixel])
{
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cout << inputblock[i][j][k] << " ";
            }
            cout << endl;
        }
    }
}

unsigned char ImagedataLandscapeFixed[Height][Width][BytesPerPixel];
unsigned char ImagedataLandscapeRandom[Height][Width][BytesPerPixel];
float ditheringInput[2][2][BytesPerPixel] = {{1, 2}, {3, 0}};
float ditheringOutput8[8][8][BytesPerPixel];
float ditheringOutput32[32][32][BytesPerPixel];
unsigned char ditheringResult_2[Height][Width][BytesPerPixel];
unsigned char ditheringResult_8[Height][Width][BytesPerPixel];
unsigned char ditheringResult_32[Height][Width][BytesPerPixel];

int main()
{
    // unsigned char ImagedataLandscapeFixed[Height][Width][BytesPerPixel];
    // unsigned char ImagedataLandscapeRandom[Height][Width][BytesPerPixel];
    // float ditheringInput[2][2][BytesPerPixel] = {{1, 2}, {3, 0}};
    // float ditheringOutput8[8][8][BytesPerPixel];
    // float ditheringOutput32[32][32][BytesPerPixel];
    // unsigned char ditheringResult_2[Height][Width][BytesPerPixel];
    // unsigned char ditheringResult_8[Height][Width][BytesPerPixel];
    // unsigned char ditheringResult_32[Height][Width][BytesPerPixel];

    openFile("landscape.raw", ImagedataLandscapeFixed);
    fixedThresholding(ImagedataLandscapeFixed);
    writeFile("landscapeFixed.raw", ImagedataLandscapeFixed);

    openFile("landscape.raw", ImagedataLandscapeRandom);
    randomThresholding(ImagedataLandscapeRandom);
    writeFile("landscapeRandom.raw", ImagedataLandscapeRandom);

    openFile("landscape.raw", ditheringResult_2);
    openFile("landscape.raw", ditheringResult_8);
    openFile("landscape.raw", ditheringResult_32);
    dithering32(32, ditheringInput, ditheringOutput32);
    dithering8(8, ditheringInput, ditheringOutput8);
    display32(32, ditheringOutput32);
    display8(8, ditheringOutput8);
    display2(2, ditheringInput);
    ditheringResult32(32, ditheringOutput32, ditheringResult_32);
    ditheringResult8(8, ditheringOutput8, ditheringResult_8);
    ditheringResult2(2, ditheringInput, ditheringResult_2);
    writeFile("landscapeDithering32.raw", ditheringResult_32);
    writeFile("landscapeDithering8.raw", ditheringResult_8);
    writeFile("landscapeDithering2.raw", ditheringResult_2);

    return 0;
}