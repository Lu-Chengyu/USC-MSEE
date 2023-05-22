// Name: Chengyu Lu
// USC ID Number: 5157638886
// USC Email: luchenggy@usc.edu
// Submission Date: 01/29/2023

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;
const int BytesPerPixel = 1;
const int Height = 240;
const int Width = 400;

float Weight_1(int i, int j, int k, int l, unsigned char Image[Height + 2][Width + 2][BytesPerPixel], float Sigmac, float Sigmas)
{
    float result = exp(-(pow((i - k), 2) + pow((j - l), 2)) / (2 * pow(Sigmac, 2)) - pow((float)(Image[i][j][0] - Image[k][l][0]), 2) / (2 * pow(Sigmas, 2)));
    return result;
}

float Weight_2(int i, int j, int k, int l, unsigned char Image[Height + 4][Width + 4][BytesPerPixel], float Sigmac, float Sigmas)
{
    float result = exp(-(pow((i - k), 2) + pow((j - l), 2)) / (2 * pow(Sigmac, 2)) - pow((float)(Image[i][j][0] - Image[k][l][0]), 2) / (2 * pow(Sigmas, 2)));
    return result;
}

int main()
{
    int Sigmac = 50;
    int Sigmas = 20;
    int kernal_size_1 = 3;
    int kernal_size_2 = 5;
    FILE *file, *file1, *file2, *file3;
    float Sum_Weight = 0;
    float Sum_Mul = 0;
    unsigned char Imagedata[Height][Width][BytesPerPixel];
    unsigned char Extended_Image_1[Height + 2][Width + 2][BytesPerPixel];
    unsigned char Extended_Image_2[Height + 4][Width + 4][BytesPerPixel];
    unsigned char Result[Height][Width][BytesPerPixel];

    if (!(file = fopen("Pepper_gray_noisy.raw", "rb")))
    {
        cout << "Cannot open file: "
             << "Pepper_gray_noisy.raw" << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Height * Width * BytesPerPixel, file);
    fclose(file);

    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height + 2; ++i)
        {
            for (int j = 0; j < Width + 2; ++j)
            {
                if (i == 0 && j == 0)
                {
                    Extended_Image_1[i][j][k] = Imagedata[i + 1][j + 1][k];
                }
                else if (i == 0 && j == Width + 1)
                {
                    Extended_Image_1[i][j][k] = Imagedata[i + 1][j - 3][k];
                }
                else if (i == Height + 1 && j == 0)
                {
                    Extended_Image_1[i][j][k] = Imagedata[i - 3][j + 1][k];
                }
                else if (i == Height + 1 && j == Width + 1)
                {
                    Extended_Image_1[i][j][k] = Imagedata[i - 3][j - 3][k];
                }
                else if (i == 0)
                {
                    Extended_Image_1[i][j][k] = Imagedata[i + 1][j - 1][k];
                }
                else if (i == Height + 1)
                {
                    Extended_Image_1[i][j][k] = Imagedata[i - 3][j - 1][k];
                }
                else if (j == 0)
                {
                    Extended_Image_1[i][j][k] = Imagedata[i - 1][j + 1][k];
                }
                else if (j == Width + 1)
                {
                    Extended_Image_1[i][j][k] = Imagedata[i - 1][j - 3][k];
                }
                else
                {
                    Extended_Image_1[i][j][k] = Imagedata[i - 1][j - 1][k];
                }
            }
        }
    }

    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height + 4; ++i)
        {
            for (int j = 0; j < Width + 4; ++j)
            {
                if ((i == 0 || i == 1) && (j == 0 || j == 1))
                {
                    Extended_Image_2[i][j][k] = Imagedata[i][j][k];
                }
                else if ((i == 0 || i == 1) && (j == Width + 3 || j == Width + 2))
                {
                    Extended_Image_2[i][j][k] = Imagedata[i][j - 4][k];
                }
                else if ((i == Height + 3 || i == Height + 2) && (j == 0 || j == 1))
                {
                    Extended_Image_2[i][j][k] = Imagedata[i - 4][j][k];
                }
                else if ((i == Height + 3 || i == Height + 2) && (j == Width + 3 || j == Width + 2))
                {
                    Extended_Image_2[i][j][k] = Imagedata[i - 4][j - 4][k];
                }
                else if (i == 0 || i == 1)
                {
                    Extended_Image_2[i][j][k] = Imagedata[i][j - 2][k];
                }
                else if (i == Height + 2 || i == Height + 3)
                {
                    Extended_Image_2[i][j][k] = Imagedata[i - 4][j - 2][k];
                }
                else if (j == 0 || j == 1)
                {
                    Extended_Image_2[i][j][k] = Imagedata[i - 2][j][k];
                }
                else if ((j == Width + 2) || (j == Width + 3))
                {
                    Extended_Image_2[i][j][k] = Imagedata[i - 2][j - 4][k];
                }
                else
                {
                    Extended_Image_2[i][j][k] = Imagedata[i - 2][j - 2][k];
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
                for (int x = 0; x < kernal_size_1; ++x)
                {
                    for (int y = 0; y < kernal_size_1; ++y)
                    {
                        Sum_Weight += Weight_1(i + kernal_size_1 / 2, j + kernal_size_1 / 2, i + x, j + y, Extended_Image_1, Sigmac, Sigmas);
                        Sum_Mul += Weight_1(i + kernal_size_1 / 2, j + kernal_size_1 / 2, i + x, j + y, Extended_Image_1, Sigmac, Sigmas) * (float)Extended_Image_1[i + x][j + y][k];
                    }
                }
                Result[i][j][k] = (unsigned char)(Sum_Mul / Sum_Weight);
                Sum_Weight = 0;
                Sum_Mul = 0;
            }
        }
    }

    if (!(file1 = fopen("Pepper_gray4_50_20.raw", "wb")))
    {
        cout << "Cannot open file: "
             << "Pepper_gray4" << endl;
        exit(1);
    }
    fwrite(Result, sizeof(unsigned char), Height * Width * BytesPerPixel, file1);
    fclose(file);

    Sum_Weight = 0;
    Sum_Mul = 0;

    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height; ++i)
        {
            for (int j = 0; j < Width; ++j)
            {
                for (int x = 0; x < kernal_size_2; ++x)
                {
                    for (int y = 0; y < kernal_size_2; ++y)
                    {
                        Sum_Weight += Weight_2(i + kernal_size_2 / 2, j + kernal_size_2 / 2, i + x, j + y, Extended_Image_2, Sigmac, Sigmas);
                        Sum_Mul += Weight_2(i + kernal_size_2 / 2, j + kernal_size_2 / 2, i + x, j + y, Extended_Image_2, Sigmac, Sigmas) * (float)Extended_Image_2[i + x][j + y][k];
                    }
                }
                Result[i][j][k] = (unsigned char)(Sum_Mul / Sum_Weight);
                Sum_Weight = 0;
                Sum_Mul = 0;
            }
        }
    }

    if (!(file2 = fopen("Pepper_gray5_50_20.raw", "wb")))
    {
        cout << "Cannot open file: "
             << "Pepper_gray5" << endl;
        exit(1);
    }
    fwrite(Result, sizeof(unsigned char), Height * Width * BytesPerPixel, file2);
    fclose(file);

    return 0;
}
