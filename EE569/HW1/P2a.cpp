// Name: Chengyu Lu
// USC ID Number: 5157638886
// USC Email: luchenggy@usc.edu
// Submission Date: 01/29/2023
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

const int BytesPerPixel = 1;
int Size = 256;
const int Height = 240;
const int Width = 400;

float Convolution_3(int i, int j, unsigned char Extended_Image[Height + 2][Width + 2][BytesPerPixel], float matrix[3][3])
{
    float result = 0;
    for (int z = 0; z < BytesPerPixel; ++z)
    {
        for (int x = 0; x < 3; ++x)
        {
            for (int y = 0; y < 3; ++y)
            {
                result += (float)Extended_Image[i + x][j + y][z] * matrix[x][y];
            }
        }
    }
    return result;
}

float Convolution_5(int i, int j, unsigned char Extended_Image[Height + 4][Width + 4][BytesPerPixel], float matrix[5][5])
{
    float result = 0;
    for (int z = 0; z < BytesPerPixel; ++z)
    {
        for (int x = 0; x < 5; ++x)
        {
            for (int y = 0; y < 5; ++y)
            {
                result += (float)Extended_Image[i + x][j + y][z] * matrix[x][y];
            }
        }
    }
    return result;
}

int main()
{
    FILE *file, *file1, *file2, *file3;

    unsigned char Imagedata[Height][Width][BytesPerPixel];
    float Uniform[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    float Gaussian_3[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
    float Gaussian_5[5][5] = {{1, 4, 7, 4, 1}, {4, 16, 26, 16, 4}, {7, 26, 41, 26, 7}, {4, 16, 26, 16, 4}, {1, 4, 7, 4, 1}};
    unsigned char Extended_Image_1[Height + 2][Width + 2][BytesPerPixel];
    unsigned char Extended_Image_2[Height + 4][Width + 4][BytesPerPixel];
    unsigned char Result_Uniform[Height][Width][BytesPerPixel];
    unsigned char Result_Gaussian_3[Height][Width][BytesPerPixel];
    unsigned char Result_Gaussian_5[Height][Width][BytesPerPixel];

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
                Result_Uniform[i][j][k] = (unsigned char)(Convolution_3(i, j, Extended_Image_1, Uniform) / 9);
            }
        }
    }

    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height; ++i)
        {
            for (int j = 0; j < Width; ++j)
            {
                Result_Gaussian_3[i][j][k] = (unsigned char)(Convolution_3(i, j, Extended_Image_1, Gaussian_3) / 16);
            }
        }
    }

    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height; ++i)
        {
            for (int j = 0; j < Width; ++j)
            {
                Result_Gaussian_5[i][j][k] = (unsigned char)(Convolution_5(i, j, Extended_Image_2, Gaussian_5) / 273);
            }
        }
    }

    if (!(file1 = fopen("Pepper_gray1.raw", "wb")))
    {
        cout << "Cannot open file: "
             << "Pepper_gray1" << endl;
        exit(1);
    }
    fwrite(Result_Uniform, sizeof(unsigned char), Height * Width * BytesPerPixel, file1);
    fclose(file);

    if (!(file2 = fopen("Pepper_gray2.raw", "wb")))
    {
        cout << "Cannot open file: "
             << "Pepper_gray2" << endl;
        exit(1);
    }
    fwrite(Result_Gaussian_3, sizeof(unsigned char), Height * Width * BytesPerPixel, file2);
    fclose(file);

    if (!(file3 = fopen("Pepper_gray3.raw", "wb")))
    {
        cout << "Cannot open file: "
             << "Pepper_gray3" << endl;
        exit(1);
    }
    fwrite(Result_Gaussian_5, sizeof(unsigned char), Height * Width * BytesPerPixel, file3);
    fclose(file);

    return 0;
}
