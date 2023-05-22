// Name: Chengyu Lu
// USC ID Number: 5157638886
// USC Email: luchengy@usc.edu
// Submission Date: 02/19/2023
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

const int BytesPerPixel = 1;
const int Height = 1000;
const int Width = 1500;

const double FS[3][3] = {
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 7.0},
    {3.0, 5.0, 1.0}};

const double FSF[3][3] = {
    {0.0, 0.0, 0.0},
    {7.0, 0.0, 0.0},
    {1.0, 5.0, 3.0}};

const double JJN[5][5] = {
    {0.0, 0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 7.0, 5.0},
    {3.0, 5.0, 7.0, 5.0, 3.0},
    {1.0, 3.0, 5.0, 3.0, 1.0}};

const double JJNF[5][5] = {
    {0.0, 0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0, 0.0},
    {5.0, 7.0, 0.0, 0.0, 0.0},
    {3.0, 5.0, 7.0, 5.0, 3.0},
    {1.0, 3.0, 5.0, 3.0, 1.0}};

const double S[5][5] = {
    {0.0, 0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 8.0, 4.0},
    {2.0, 4.0, 8.0, 4.0, 2.0},
    {1.0, 2.0, 4.0, 2.0, 1.0}};

const double SF[5][5] = {
    {0.0, 0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0, 0.0},
    {4.0, 8.0, 0.0, 0.0, 0.0},
    {2.0, 4.0, 8.0, 4.0, 2.0},
    {1.0, 2.0, 4.0, 2.0, 1.0}};

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

bool test(int i, int j, int x, int y, int size)
{
    if ((i - size / 2 + x) >= 0 && (i - size / 2 + x) < Height && (j - size / 2 + y) >= 0 && (j - size / 2 + y) < Width)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void errorDifusionFS(int size, float input[Height][Width][BytesPerPixel])
{
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height; ++i)
        {
            if (i % 2 != 0)
            {
                for (int j = 0; j < Width; ++j)
                {
                    int temp = 0;
                    if (input[i][j][k] > 128)
                    {
                        temp = input[i][j][k] - 255;
                        input[i][j][k] = 255;
                    }
                    else
                    {
                        temp = input[i][j][k];
                        input[i][j][k] = 0;
                    }
                    for (int x = 0; x < size; x++)
                    {
                        for (int y = 0; y < size; y++)
                        {
                            if (test(i, j, x, y, size))
                            {
                                input[i - size / 2 + x][j - size / 2 + y][k] += FS[x][y] * temp / 16;
                            }
                        }
                    }
                }
            }
            else
            {
                for (int j = Width - 1; j >= 0; --j)
                {
                    int temp = 0;
                    if (input[i][j][k] > 128)
                    {
                        temp = input[i][j][k] - 255;
                        input[i][j][k] = 255;
                    }
                    else
                    {
                        temp = input[i][j][k];
                        input[i][j][k] = 0;
                    }
                    for (int x = 0; x < size; x++)
                    {
                        for (int y = 0; y < size; y++)
                        {
                            if (test(i, j, x, y, size))
                            {
                                input[i - size / 2 + x][j - size / 2 + y][k] += FSF[x][y] * temp / 16;
                            }
                        }
                    }
                }
            }
        }
    }
}

void errorDifusionJJN(int size, float input[Height][Width][BytesPerPixel])
{
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height; ++i)
        {
            if (i % 2 != 0)
            {
                for (int j = 0; j < Width; ++j)
                {
                    int temp = 0;
                    if (input[i][j][k] > 128)
                    {
                        temp = input[i][j][k] - 255;
                        input[i][j][k] = 255;
                    }
                    else
                    {
                        temp = input[i][j][k];
                        input[i][j][k] = 0;
                    }
                    for (int x = 0; x < size; x++)
                    {
                        for (int y = 0; y < size; y++)
                        {
                            if (test(i, j, x, y, size))
                            {
                                input[i - size / 2 + x][j - size / 2 + y][k] += JJN[x][y] * temp / 48;
                            }
                        }
                    }
                }
            }
            else
            {
                for (int j = Width - 1; j >= 0; --j)
                {
                    int temp = 0;
                    if (input[i][j][k] > 128)
                    {
                        temp = input[i][j][k] - 255;
                        input[i][j][k] = 255;
                    }
                    else
                    {
                        temp = input[i][j][k];
                        input[i][j][k] = 0;
                    }
                    for (int x = 0; x < size; x++)
                    {
                        for (int y = 0; y < size; y++)
                        {
                            if (test(i, j, x, y, size))
                            {
                                input[i - size / 2 + x][j - size / 2 + y][k] += JJNF[x][y] * temp / 48;
                            }
                        }
                    }
                }
            }
        }
    }
}

void errorDifusionS(int size, float input[Height][Width][BytesPerPixel])
{
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height; ++i)
        {
            if (i % 2 != 0)
            {
                for (int j = 0; j < Width; ++j)
                {
                    int temp = 0;
                    if (input[i][j][k] > 128)
                    {
                        temp = input[i][j][k] - 255;
                        input[i][j][k] = 255;
                    }
                    else
                    {
                        temp = input[i][j][k];
                        input[i][j][k] = 0;
                    }
                    for (int x = 0; x < size; x++)
                    {
                        for (int y = 0; y < size; y++)
                        {
                            if (test(i, j, x, y, size))
                            {
                                input[i - size / 2 + x][j - size / 2 + y][k] += S[x][y] * temp / 42;
                            }
                        }
                    }
                }
            }
            else
            {
                for (int j = Width - 1; j >= 0; --j)
                {
                    int temp = 0;
                    if (input[i][j][k] > 128)
                    {
                        temp = input[i][j][k] - 255;
                        input[i][j][k] = 255;
                    }
                    else
                    {
                        temp = input[i][j][k];
                        input[i][j][k] = 0;
                    }
                    for (int x = 0; x < size; x++)
                    {
                        for (int y = 0; y < size; y++)
                        {
                            if (test(i, j, x, y, size))
                            {
                                input[i - size / 2 + x][j - size / 2 + y][k] += SF[x][y] * temp / 42;
                            }
                        }
                    }
                }
            }
        }
    }
}

void transfer(unsigned char landscape[Height][Width][BytesPerPixel], float landscape1[Height][Width][BytesPerPixel])
{
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height; ++i)
        {
            for (int j = 0; j < Width; ++j)
            {
                landscape1[i][j][k] = (float)landscape[i][j][k];
            }
        }
    }
}

void transferBack(unsigned char landscape[Height][Width][BytesPerPixel], float landscape1[Height][Width][BytesPerPixel])
{
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height; ++i)
        {
            for (int j = 0; j < Width; ++j)
            {
                landscape[i][j][k] = (unsigned char)landscape1[i][j][k];
            }
        }
    }
}

unsigned char landscape[Height][Width][BytesPerPixel];
float landscapeFS[Height][Width][BytesPerPixel];
float landscapeJJN[Height][Width][BytesPerPixel];
float landscapeS[Height][Width][BytesPerPixel];
unsigned char resultFS[Height][Width][BytesPerPixel];
unsigned char resultJJN[Height][Width][BytesPerPixel];
unsigned char resultS[Height][Width][BytesPerPixel];

int main()
{
    openFile("landscape.raw", landscape);
    transfer(landscape, landscapeFS);
    transfer(landscape, landscapeJJN);
    transfer(landscape, landscapeS);
    errorDifusionFS(3, landscapeFS);
    errorDifusionJJN(5, landscapeJJN);
    errorDifusionS(5, landscapeS);
    transferBack(resultFS, landscapeFS);
    transferBack(resultJJN, landscapeJJN);
    transferBack(resultS, landscapeS);
    writeFile("landscapeEDFS.raw", resultFS);
    writeFile("landscapeEDJJN.raw", resultJJN);
    writeFile("landscapeEDS.raw", resultS);

    return 0;
}