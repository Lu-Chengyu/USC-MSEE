// Name: Chengyu Lu
// USC ID Number: 5157638886
// USC Email: luchengy@usc.edu
// Submission Date: 02/19/2023
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

const int BytesPerPixel = 3;
const int Height = 795;
const int Width = 1280;

enum class MBVQ
{
    KRGB,
    CMYW,
    MYGC,
    RGMY,
    RGBM,
    CMGB
};

enum class RGB
{
    R,
    G,
    B,
    C,
    M,
    Y,
    W,
    K
};

const double FS[3][3] = {
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 7.0},
    {3.0, 5.0, 1.0}};

const double FSF[3][3] = {
    {0.0, 0.0, 0.0},
    {7.0, 0.0, 0.0},
    {1.0, 5.0, 3.0}};

MBVQ MBVQdecision1(int i, int j, float Imagedata[Height][Width][BytesPerPixel])
{
    if ((Imagedata[i][j][0] + Imagedata[i][j][1]) > 255)
    {
        if ((Imagedata[i][j][2] + Imagedata[i][j][1]) > 255)
        {
            if ((Imagedata[i][j][0] + Imagedata[i][j][1] + Imagedata[i][j][2]) > 510)
            {
                return MBVQ::CMYW;
            }
            else
            {
                return MBVQ::MYGC;
            }
        }
        else
        {
            return MBVQ::RGMY;
        }
    }
    else
    {
        if (!((Imagedata[i][j][2] + Imagedata[i][j][1]) > 255))
        {
            if (!((Imagedata[i][j][2] + Imagedata[i][j][1] + Imagedata[i][j][0]) > 255))
            {
                return MBVQ::KRGB;
            }
            else
            {
                return MBVQ::RGBM;
            }
        }
        else
        {
            return MBVQ::CMGB;
        }
    }
}

RGB MBVQdecision2(MBVQ mbvq, int i, int j, float Imagedata[Height][Width][BytesPerPixel])
{
    float R = Imagedata[i][j][0];
    float G = Imagedata[i][j][1];
    float B = Imagedata[i][j][2];

    if (mbvq == MBVQ::CMYW)
    {
        if (B < 127)
        {
            if (B <= R)
            {
                if (B <= G)
                {
                    return RGB::Y;
                }
            }
        }
        if (G < 127)
        {
            if (G <= B)
            {
                if (G <= R)
                {
                    return RGB::M;
                }
            }
        }
        if (R < 127)
        {
            if (R <= B)
            {
                if (R <= G)
                {
                    return RGB::C;
                }
            }
        }
        return RGB::W;
    }
    else if (mbvq == MBVQ::MYGC)
    {
        if (G >= B)
        {
            if (R >= B)
            {
                if (R >= 127)
                {
                    return RGB::Y;
                }
                else
                {
                    return RGB::G;
                }
            }
        }
        if (G >= R)
        {
            if (B >= R)
            {
                if (B >= 127)
                {
                    return RGB::C;
                }
                else
                {
                    return RGB::G;
                }
            }
        }
        return RGB::M;
    }
    else if (mbvq == MBVQ::RGMY)
    {
        if (B > 127)
        {
            if (R > 127)
            {
                if (B >= G)
                {
                    return RGB::M;
                }
                else
                {
                    return RGB::Y;
                }
            }
            else
            {
                if (G > (B + R))
                {
                    return RGB::G;
                }
                else
                {
                    return RGB::M;
                }
            }
        }
        else
        {
            if (R >= 127)
            {
                if (G >= 127)
                {
                    return RGB::Y;
                }
                else
                {
                    return RGB::R;
                }
            }
            else
            {
                if (R >= G)
                {
                    return RGB::R;
                }
                else
                {
                    return RGB::G;
                }
            }
        }
    }
    else if (mbvq == MBVQ::KRGB)
    {
        if (B > 127)
        {
            if (B >= R)
            {
                if (B >= G)
                {
                    return RGB::B;
                }
            }
        }
        if (G > 127)
        {
            if (G >= B)
            {
                if (G >= R)
                {
                    return RGB::G;
                }
            }
        }
        if (R > 127)
        {
            if (R >= B)
            {
                if (R >= G)
                {
                    return RGB::R;
                }
            }
        }
        return RGB::K;
    }
    else if (mbvq == MBVQ::RGBM)
    {
        if (R > G)
        {
            if (R >= B)
            {
                if (B < 127)
                {
                    return RGB::R;
                }
                else
                {
                    return RGB::M;
                }
            }
        }
        if (B > G)
        {
            if (B >= R)
            {
                if (R < 127)
                {
                    return RGB::B;
                }
                else
                {
                    return RGB::M;
                }
            }
        }
        return RGB::G;
    }
    else if (mbvq == MBVQ::CMGB)
    {
        if (B > 127)
        {
            if (R > 127)
            {
                if (G >= R)
                {
                    return RGB::C;
                }
                else
                {
                    return RGB::M;
                }
            }
            else
            {
                if (G > 127)
                {
                    return RGB::C;
                }
                else
                {
                    return RGB::B;
                }
            }
        }
        else
        {
            if (R > 127)
            {
                if ((R - G + B) >= 127)
                {
                    return RGB::M;
                }
                else
                {
                    return RGB::G;
                }
            }
            else
            {
                if (G >= B)
                {
                    return RGB::G;
                }
                else
                {
                    return RGB::B;
                }
            }
        }
    }
}

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
    for (int i = 0; i < Height; ++i)
    {
        if (i % 2 != 0)
        {
            for (int j = 0; j < Width; ++j)
            {
                float temp[1][1][3] = {0, 0, 0};
                if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::R)
                {
                    temp[0][0][0] = input[i][j][0] - 255;
                    temp[0][0][1] = input[i][j][1];
                    temp[0][0][2] = input[i][j][2];
                    input[0][0][0] = 255;
                    input[0][0][1] = 0;
                    input[0][0][2] = 0;
                }
                else if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::G)
                {
                    temp[0][0][0] = input[i][j][0];
                    temp[0][0][1] = input[i][j][1] - 255;
                    temp[0][0][2] = input[i][j][2];
                    input[0][0][0] = 0;
                    input[0][0][1] = 255;
                    input[0][0][2] = 0;
                }
                else if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::B)
                {
                    temp[0][0][0] = input[i][j][0];
                    temp[0][0][1] = input[i][j][1];
                    temp[0][0][2] = input[i][j][2] - 255;
                    input[0][0][0] = 0;
                    input[0][0][1] = 0;
                    input[0][0][2] = 255;
                }
                else if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::C)
                {
                    temp[0][0][0] = input[i][j][0];
                    temp[0][0][1] = input[i][j][1] - 255;
                    temp[0][0][2] = input[i][j][2] - 255;
                    input[0][0][0] = 0;
                    input[0][0][1] = 255;
                    input[0][0][2] = 255;
                }
                else if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::M)
                {
                    temp[0][0][0] = input[i][j][0] - 255;
                    temp[0][0][1] = input[i][j][1];
                    temp[0][0][2] = input[i][j][2] - 255;
                    input[0][0][0] = 255;
                    input[0][0][1] = 0;
                    input[0][0][2] = 255;
                }
                else if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::Y)
                {
                    temp[0][0][0] = input[i][j][0] - 255;
                    temp[0][0][1] = input[i][j][1] - 255;
                    temp[0][0][2] = input[i][j][2];
                    input[0][0][0] = 255;
                    input[0][0][1] = 255;
                    input[0][0][2] = 0;
                }
                else if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::K)
                {
                    temp[0][0][0] = input[i][j][0];
                    temp[0][0][1] = input[i][j][1];
                    temp[0][0][2] = input[i][j][2];
                    input[0][0][0] = 0;
                    input[0][0][1] = 0;
                    input[0][0][2] = 0;
                }
                else if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::W)
                {
                    temp[0][0][0] = input[i][j][0] - 255;
                    temp[0][0][1] = input[i][j][1] - 255;
                    temp[0][0][2] = input[i][j][2] - 255;
                    input[0][0][0] = 255;
                    input[0][0][1] = 255;
                    input[0][0][2] = 255;
                }

                for (int x = 0; x < size; x++)
                {
                    for (int y = 0; y < size; y++)
                    {
                        if (test(i, j, x, y, size))
                        {
                            input[i - size / 2 + x][j - size / 2 + y][0] += FS[x][y] * temp[0][0][0] / 16;
                            input[i - size / 2 + x][j - size / 2 + y][1] += FS[x][y] * temp[0][0][1] / 16;
                            input[i - size / 2 + x][j - size / 2 + y][2] += FS[x][y] * temp[0][0][2] / 16;
                        }
                    }
                }
            }
        }
        else
        {
            for (int j = Width - 1; j >= 0; --j)
            {
                float temp[1][1][3] = {0, 0, 0};
                if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::R)
                {
                    temp[0][0][0] = input[i][j][0] - 255;
                    temp[0][0][1] = input[i][j][1];
                    temp[0][0][2] = input[i][j][2];
                    input[0][0][0] = 255;
                    input[0][0][1] = 0;
                    input[0][0][2] = 0;
                }
                else if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::G)
                {
                    temp[0][0][0] = input[i][j][0];
                    temp[0][0][1] = input[i][j][1] - 255;
                    temp[0][0][2] = input[i][j][2];
                    input[0][0][0] = 0;
                    input[0][0][1] = 255;
                    input[0][0][2] = 0;
                }
                else if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::B)
                {
                    temp[0][0][0] = input[i][j][0];
                    temp[0][0][1] = input[i][j][1];
                    temp[0][0][2] = input[i][j][2] - 255;
                    input[0][0][0] = 0;
                    input[0][0][1] = 0;
                    input[0][0][2] = 255;
                }
                else if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::C)
                {
                    temp[0][0][0] = input[i][j][0];
                    temp[0][0][1] = input[i][j][1] - 255;
                    temp[0][0][2] = input[i][j][2] - 255;
                    input[0][0][0] = 0;
                    input[0][0][1] = 255;
                    input[0][0][2] = 255;
                }
                else if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::M)
                {
                    temp[0][0][0] = input[i][j][0] - 255;
                    temp[0][0][1] = input[i][j][1];
                    temp[0][0][2] = input[i][j][2] - 255;
                    input[0][0][0] = 255;
                    input[0][0][1] = 0;
                    input[0][0][2] = 255;
                }
                else if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::Y)
                {
                    temp[0][0][0] = input[i][j][0] - 255;
                    temp[0][0][1] = input[i][j][1] - 255;
                    temp[0][0][2] = input[i][j][2];
                    input[0][0][0] = 255;
                    input[0][0][1] = 255;
                    input[0][0][2] = 0;
                }
                else if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::K)
                {
                    temp[0][0][0] = input[i][j][0];
                    temp[0][0][1] = input[i][j][1];
                    temp[0][0][2] = input[i][j][2];
                    input[0][0][0] = 0;
                    input[0][0][1] = 0;
                    input[0][0][2] = 0;
                }
                else if (MBVQdecision2(MBVQdecision1(i, j, input), i, j, input) == RGB::W)
                {
                    temp[0][0][0] = input[i][j][0] - 255;
                    temp[0][0][1] = input[i][j][1] - 255;
                    temp[0][0][2] = input[i][j][2] - 255;
                    input[0][0][0] = 255;
                    input[0][0][1] = 255;
                    input[0][0][2] = 255;
                }

                for (int x = 0; x < size; x++)
                {
                    for (int y = 0; y < size; y++)
                    {
                        if (test(i, j, x, y, size))
                        {
                            input[i - size / 2 + x][j - size / 2 + y][0] += FSF[x][y] * temp[0][0][0] / 16;
                            input[i - size / 2 + x][j - size / 2 + y][1] += FSF[x][y] * temp[0][0][1] / 16;
                            input[i - size / 2 + x][j - size / 2 + y][2] += FSF[x][y] * temp[0][0][2] / 16;
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

unsigned char fish[Height][Width][BytesPerPixel];
float fishFS[Height][Width][BytesPerPixel];
unsigned char resultFS[Height][Width][BytesPerPixel];

int main()
{
    openFile("fish.raw", fish);
    transfer(fish, fishFS);
    errorDifusionFS(3, fishFS);
    transferBack(resultFS, fishFS);
    writeFile("fishEDFSMBVQ.raw", resultFS);

    return 0;
}