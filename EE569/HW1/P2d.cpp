// Name: Chengyu Lu
// USC ID Number: 5157638886
// USC Email: luchenggy@usc.edu
// Submission Date: 01/29/2023

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <cstring>

using namespace std;
#define PI 3.1415926535
const int BytesPerPixel = 3;
const int Height = 240;
const int Width = 400;
#define MAX_VALUE 256

void hsv2rgb(double h, double s, double v, int x, int y, unsigned char RGB_res1[Height][Width][BytesPerPixel])
{
    double r, g, b;

    int i = int(h * 6);
    double f = h * 6 - i;
    double p = v * (1 - s);
    double q = v * (1 - f * s);
    double t = v * (1 - (1 - f) * s);

    switch (i % 6)
    {
    case 0:
        r = v, g = t, b = p;
        break;
    case 1:
        r = q, g = v, b = p;
        break;
    case 2:
        r = p, g = v, b = t;
        break;
    case 3:
        r = p, g = q, b = v;
        break;
    case 4:
        r = t, g = p, b = v;
        break;
    case 5:
        r = v, g = p, b = q;
        break;
    }

    RGB_res1[x][y][0] = (unsigned char)(r * 255);
    RGB_res1[x][y][1] = (unsigned char)(g * 255);
    RGB_res1[x][y][2] = (unsigned char)(b * 255);
}

float Convolution_3_6(int i, int j, float Extended_Image[Height + 2][Width + 2][1], float matrix[3][3])
{
    float result = 0;

    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            result += (float)Extended_Image[i + x][j + y][0] * matrix[x][y];
        }
    }

    return result;
}

float Convolution_3_angle(int i, int j, int k, float Extended_Image[Height + 2][Width + 2][1], float matrix[3][3])
{
    float result = 0;
    float sin_value = 0;
    float cos_value = 0;
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            sin_value += sin(Extended_Image[i + x][j + y][k] * matrix[x][y] * 2 * PI);
            cos_value += cos(Extended_Image[i + x][j + y][k] * matrix[x][y] * 2 * PI);
        }
    }
    result = atan2(sin_value, cos_value);
    if (result < 0)
    {
        result += 2 * PI;
    }
    return result;
}

void rgb2hsv(unsigned char r, unsigned char g, unsigned char b, int i, int j, float HSV[Height][Width][BytesPerPixel])
{
    double red = (double)r / 255;
    double green = (double)g / 255;
    double blue = (double)b / 255;
    double max_value = max(red, max(green, blue)), min_value = min(red, min(green, blue));
    double h, s, v = max_value;

    double d = max_value - min_value;
    s = max_value == 0 ? 0 : d / max_value;

    if (max_value == min_value)
    {
        h = 0;
    }
    else
    {
        if (max_value == red)
        {
            h = (green - blue) / d + (green < blue ? 6 : 0);
        }
        else if (max_value == green)
        {
            h = (blue - red) / d + 2;
        }
        else if (max_value == blue)
        {
            h = (red - green) / d + 4;
        }
        h /= 6;
    }
    HSV[i][j][0] = (float)h;
    HSV[i][j][1] = (float)s;
    HSV[i][j][2] = (float)v;
}

float Convolution_3(int i, int j, int k, unsigned char Extended_Image[Height + 2][Width + 2][BytesPerPixel], float matrix[3][3])
{
    float result = 0;
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            result += (float)Extended_Image[i + x][j + y][k] * matrix[x][y];
        }
    }
    return result;
}

void medianFilter(unsigned char *input, unsigned char *result, int width, int height)
{
    memcpy(result, input, width * height * sizeof(unsigned char));
    for (int j = 1; j < height - 1; j++)
    {
        for (int i = 1; i < width - 1; i++)
        {
            int k = 0;
            unsigned char order[9];
            for (int x = j - 1; x < j + 2; ++x)
            {
                for (int y = i - 1; y < i + 2; ++y)
                {
                    order[k++] = input[x * width + y];
                }
            }
            for (int m = 0; m < 5; ++m)
            {
                int min = m;
                for (int n = m + 1; n < 9; ++n)
                {
                    if (order[n] < order[min])
                    {
                        min = n;
                    }
                }
                unsigned char temp = order[m];
                order[m] = order[min];
                order[min] = temp;
            }
            result[j * width + i] = order[4];
        }
    }
}

int main()
{
    FILE *file, *file1, *file2, *file3, *file4, *file5, *file6, *file7, *file8, *file9, *file10, *file11;
    unsigned char Imagedata[Height][Width][BytesPerPixel];
    unsigned char Imagedata1[Height][Width][BytesPerPixel];
    unsigned char Imagedata2[Height][Width][BytesPerPixel];
    unsigned char Red[Height][Width][1];
    unsigned char Green[Height][Width][1];
    unsigned char Blue[Height][Width][1];
    int difference12[Height][Width][BytesPerPixel];
    unsigned char Red_med[Height * Width];
    unsigned char Red_res[Height * Width];
    unsigned char new_Blue[Height][Width][1];
    unsigned char new_Green[Height][Width][1];
    unsigned char RGB_res[Height][Width][BytesPerPixel];
    unsigned char RGB_res1[Height][Width][BytesPerPixel];
    unsigned char RGB_res2[Height][Width][BytesPerPixel];
    map<int, int> frequencyR;
    map<int, int> frequencyG;
    map<int, int> frequencyB;

    if (!(file = fopen("Pepper.raw", "rb")))
    {
        cout << "Cannot open file: "
             << "Pepper.raw" << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Height * Width * BytesPerPixel, file);
    if (!(file1 = fopen("Pepper_noisy1.raw", "rb")))
    {
        cout << "Cannot open file: "
             << "Pepper_noisy1.raw" << endl;
        exit(1);
    }
    fread(Imagedata1, sizeof(unsigned char), Height * Width * BytesPerPixel, file1);
    if (!(file2 = fopen("Pepper_noisy2.raw", "rb")))
    {
        cout << "Cannot open file: "
             << "Pepper_noisy2.raw" << endl;
        exit(1);
    }
    fread(Imagedata2, sizeof(unsigned char), Height * Width * BytesPerPixel, file2);
    fclose(file);
    fclose(file1);
    fclose(file2);

    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height; ++i)
        {
            for (int j = 0; j < Width; ++j)
            {
                difference12[i][j][k] = Imagedata1[i][j][k] - Imagedata[i][j][k];
                if (k == 0)
                {
                    Red[i][j][0] = Imagedata1[i][j][k];
                    if (frequencyR[difference12[i][j][k]])
                    {
                        frequencyR[difference12[i][j][k]]++;
                    }
                    else
                    {
                        frequencyR[difference12[i][j][k]] = 1;
                    }
                }
                else if (k == 1)
                {
                    Green[i][j][0] = Imagedata1[i][j][k];
                    if (frequencyG[difference12[i][j][k]])
                    {
                        frequencyG[difference12[i][j][k]]++;
                    }
                    else
                    {
                        frequencyG[difference12[i][j][k]] = 1;
                    }
                }
                else if (k == 2)
                {
                    Blue[i][j][0] = Imagedata1[i][j][k];
                    if (frequencyB[difference12[i][j][k]])
                    {
                        frequencyB[difference12[i][j][k]]++;
                    }
                    else
                    {
                        frequencyB[difference12[i][j][k]] = 1;
                    }
                }
            }
        }
    }

    if (!(file3 = fopen("Pepper_gray_Red.raw", "wb")))
    {
        cout << "Cannot open file: "
             << "Pepper_gray4" << endl;
        exit(1);
    }
    fwrite(Red, sizeof(unsigned char), Height * Width * 1, file3);
    fclose(file3);
    if (!(file4 = fopen("Pepper_gray_Green.raw", "wb")))
    {
        cout << "Cannot open file: "
             << "Pepper_gray4" << endl;
        exit(1);
    }
    fwrite(Green, sizeof(unsigned char), Height * Width * 1, file4);
    fclose(file4);
    if (!(file5 = fopen("Pepper_gray_Blue.raw", "wb")))
    {
        cout << "Cannot open file: "
             << "Pepper_gray4" << endl;
        exit(1);
    }
    fwrite(Blue, sizeof(unsigned char), Height * Width * 1, file5);
    fclose(file5);

    cout << "R:" << endl;
    for (auto iter = frequencyR.rbegin(); iter != frequencyR.rend(); iter++)
    {
        cout << iter->first << " " << iter->second << endl;
    }
    cout << "G:" << endl;
    for (auto iter = frequencyG.rbegin(); iter != frequencyG.rend(); iter++)
    {
        cout << iter->first << " " << iter->second << endl;
    }
    cout << "B:" << endl;
    for (auto iter = frequencyB.rbegin(); iter != frequencyB.rend(); iter++)
    {
        cout << iter->first << " " << iter->second << endl;
    }

    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            Red_med[i * Width + j] = Red[i][j][0];
        }
    }

    medianFilter(Red_med, Red_res, Width, Height);

    if (!(file6 = fopen("Pepper_gray_Green1.raw", "rb")))
    {
        cout << "Cannot open file: "
             << "Pepper_noisy1.raw" << endl;
        exit(1);
    }
    fread(new_Green, sizeof(unsigned char), Height * Width * 1, file6);
    if (!(file7 = fopen("Pepper_gray_Blue1.raw", "rb")))
    {
        cout << "Cannot open file: "
             << "Pepper_noisy2.raw" << endl;
        exit(1);
    }
    fread(new_Blue, sizeof(unsigned char), Height * Width * 1, file7);
    fclose(file6);
    fclose(file7);
    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height; ++i)
        {
            for (int j = 0; j < Width; ++j)
            {
                if (k == 0)
                {
                    RGB_res[i][j][k] = Red_res[i * Width + j];
                }
                else if (k == 1)
                {
                    RGB_res[i][j][k] = new_Green[i][j][0];
                }
                else if (k == 2)
                {
                    RGB_res[i][j][k] = new_Blue[i][j][0];
                }
            }
        }
    }
    if (!(file8 = fopen("Pepper_RGB.raw", "wb")))
    {
        cout << "Cannot open file: "
             << "Pepper_RGB" << endl;
        exit(1);
    }
    fwrite(RGB_res, sizeof(unsigned char), Height * Width * BytesPerPixel, file8);
    fclose(file8);

    float mean[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    unsigned char Result_Mean[Height][Width][BytesPerPixel];
    unsigned char Extended_Image_1[Height + 2][Width + 2][BytesPerPixel];

    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height + 2; ++i)
        {
            for (int j = 0; j < Width + 2; ++j)
            {
                if (i == 0 && j == 0)
                {
                    Extended_Image_1[i][j][k] = Imagedata2[i + 1][j + 1][k];
                }
                else if (i == 0 && j == Width + 1)
                {
                    Extended_Image_1[i][j][k] = Imagedata2[i + 1][j - 3][k];
                }
                else if (i == Height + 1 && j == 0)
                {
                    Extended_Image_1[i][j][k] = Imagedata2[i - 3][j + 1][k];
                }
                else if (i == Height + 1 && j == Width + 1)
                {
                    Extended_Image_1[i][j][k] = Imagedata2[i - 3][j - 3][k];
                }
                else if (i == 0)
                {
                    Extended_Image_1[i][j][k] = Imagedata2[i + 1][j - 1][k];
                }
                else if (i == Height + 1)
                {
                    Extended_Image_1[i][j][k] = Imagedata2[i - 3][j - 1][k];
                }
                else if (j == 0)
                {
                    Extended_Image_1[i][j][k] = Imagedata2[i - 1][j + 1][k];
                }
                else if (j == Width + 1)
                {
                    Extended_Image_1[i][j][k] = Imagedata2[i - 1][j - 3][k];
                }
                else
                {
                    Extended_Image_1[i][j][k] = Imagedata2[i - 1][j - 1][k];
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
                Result_Mean[i][j][k] = (unsigned char)(Convolution_3(i, j, k, Extended_Image_1, mean) / 9);
            }
        }
    }

    if (!(file9 = fopen("Pepper_RGB1.raw", "wb")))
    {
        cout << "Cannot open file: "
             << "Pepper_RGB1" << endl;
        exit(1);
    }
    fwrite(Result_Mean, sizeof(unsigned char), Height * Width * BytesPerPixel, file9);
    fclose(file9);

    float HSV[Height][Width][BytesPerPixel];
    float HSV1[Height][Width][BytesPerPixel];
    float Extended_HSV[Height + 2][Width + 2][1];

    for (int i = 0; i < Height + 2; ++i)
    {
        for (int j = 0; j < Width + 2; ++j)
        {
            rgb2hsv(Imagedata2[i][j][0], Imagedata2[i][j][1], Imagedata2[i][j][2], i, j, HSV);
        }
    }

    for (int i = 0; i < Height + 2; ++i)
    {
        for (int j = 0; j < Width + 2; ++j)
        {
            if (i == 0 && j == 0)
            {
                Extended_HSV[i][j][0] = HSV[i + 1][j + 1][0];
            }
            else if (i == 0 && j == Width + 1)
            {
                Extended_HSV[i][j][0] = HSV[i + 1][j - 3][0];
            }
            else if (i == Height + 1 && j == 0)
            {
                Extended_HSV[i][j][0] = HSV[i - 3][j + 1][0];
            }
            else if (i == Height + 1 && j == Width + 1)
            {
                Extended_HSV[i][j][0] = HSV[i - 3][j - 3][0];
            }
            else if (i == 0)
            {
                Extended_HSV[i][j][0] = HSV[i + 1][j - 1][0];
            }
            else if (i == Height + 1)
            {
                Extended_HSV[i][j][0] = HSV[i - 3][j - 1][0];
            }
            else if (j == 0)
            {
                Extended_HSV[i][j][0] = HSV[i - 1][j + 1][0];
            }
            else if (j == Width + 1)
            {
                Extended_HSV[i][j][0] = HSV[i - 1][j - 3][0];
            }
            else
            {
                Extended_HSV[i][j][0] = HSV[i - 1][j - 1][0];
            }
        }
    }

    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            HSV1[i][j][0] = Convolution_3_6(i, j,  Extended_HSV, mean)/9;
            HSV1[i][j][1] =HSV[i][j][1];
            HSV1[i][j][2] =HSV[i][j][2];
        }
    }

       for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            hsv2rgb((double)HSV1[i][j][0], (double)HSV1[i][j][1], (double)HSV1[i][j][2], i, j, RGB_res2);
        }
    }

     if (!(file11 = fopen("Pepper_RGB3.raw", "wb")))
    {
        cout << "Cannot open file: "
             << "Pepper_RGB3" << endl;
        exit(1);
    }
    fwrite(RGB_res2, sizeof(unsigned char), Height * Width * BytesPerPixel, file11);
    fclose(file11);

    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            HSV[i][j][0] = Convolution_3_angle(i, j, 0, Extended_HSV, mean) / (2 * PI);
        }
    }

    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            hsv2rgb((double)HSV[i][j][0], (double)HSV[i][j][1], (double)HSV[i][j][2], i, j, RGB_res1);
        }
    }

    if (!(file10 = fopen("Pepper_RGB2.raw", "wb")))
    {
        cout << "Cannot open file: "
             << "Pepper_RGB2" << endl;
        exit(1);
    }
    fwrite(RGB_res1, sizeof(unsigned char), Height * Width * BytesPerPixel, file10);
    fclose(file10);


    return 0;
}
