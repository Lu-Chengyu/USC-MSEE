// Name: Chengyu Lu
// USC ID Number: 5157638886
// USC Email: luchenggy@usc.edu
// Submission Date: 01/29/2023

#include <iostream>
#include <stdlib.h>

using namespace std;

const int BytesPerPixel = 3;
int Size = 256;
#define MAX_VALUE 256
int frequency[MAX_VALUE], transfer[MAX_VALUE], frequency2[MAX_VALUE], transfer2[MAX_VALUE];
const int Height = 422;
const int Width = 750;

int main()
{
    FILE *file;
    unsigned char Imagedata[Height][Width][BytesPerPixel];
    unsigned char YUV_Image[Height][Width][BytesPerPixel];
    unsigned char Result1[Height][Width][BytesPerPixel];
    unsigned char Result2[Height][Width][BytesPerPixel];

    if (!(file = fopen("City.raw", "rb")))
    {
        cout << "Cannot open file: "
             << "City.raw" << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Height * Width * BytesPerPixel, file);
    fclose(file);

    for (int i = 0; i < MAX_VALUE; i++)
    {
        frequency[i] = 0;
        transfer[i] = 0;
    }

    for (int k = 0; k < BytesPerPixel; ++k)
    {
        for (int i = 0; i < Height; ++i)
        {
            for (int j = 0; j < Width; ++j)
            {
                if (k == 0)
                {
                    YUV_Image[i][j][k] = (unsigned char)(0.257 * (float)Imagedata[i][j][0] + 0.504 * (float)Imagedata[i][j][1] + 0.098 * (float)Imagedata[i][j][2] + 16);
                    frequency[YUV_Image[i][j][k]]++;
                }
                else if (k == 1)
                {
                    YUV_Image[i][j][k] = (unsigned char)(-0.148 * (float)Imagedata[i][j][0] - 0.291 * (float)Imagedata[i][j][1] + 0.439 * (float)Imagedata[i][j][2] + 128);
                }
                else if (k == 2)
                {
                    YUV_Image[i][j][k] = (unsigned char)(0.439 * (float)Imagedata[i][j][0] - 0.368 * (float)Imagedata[i][j][1] - 0.071 * (float)Imagedata[i][j][2] + 128);
                }
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < MAX_VALUE; i++)
    {
        sum += frequency[i];
        transfer[i] = sum * 255 / (Width * Height);
    }

    FILE *qFile;
    qFile = fopen("City1.raw", "w+");

    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            for (int k = 0; k < BytesPerPixel; ++k)
            {
                if (k == 0)
                {
                    if ((1.164 * ((float)transfer[YUV_Image[i][j][0]] - 16) + 1.596 * ((float)YUV_Image[i][j][2] - 128)) > 255)
                    {
                        Result1[i][j][k] = 255;
                    }
                    else if ((1.164 * ((float)transfer[YUV_Image[i][j][0]] - 16) + 1.596 * ((float)YUV_Image[i][j][2] - 128)) < 0)
                    {
                        Result1[i][j][k] = 0;
                    }
                    else
                    {
                        Result1[i][j][k] = (unsigned char)(1.164 * ((float)transfer[YUV_Image[i][j][0]] - 16) + 1.596 * ((float)YUV_Image[i][j][2] - 128));
                    }
                }
                else if (k == 1)
                {
                    if ((1.164 * ((float)transfer[YUV_Image[i][j][0]] - 16) - 0.813 * ((float)YUV_Image[i][j][2] - 128) - 0.391 * ((float)YUV_Image[i][j][1] - 128)) > 255)
                    {
                        Result1[i][j][k] = 255;
                    }
                    else if ((1.164 * ((float)transfer[YUV_Image[i][j][0]] - 16) - 0.813 * ((float)YUV_Image[i][j][2] - 128) - 0.391 * ((float)YUV_Image[i][j][1] - 128)) < 0)
                    {
                        Result1[i][j][k] = 0;
                    }
                    else
                    {
                        Result1[i][j][k] = (unsigned char)(1.164 * ((float)transfer[YUV_Image[i][j][0]] - 16) - 0.813 * ((float)YUV_Image[i][j][2] - 128) - 0.391 * ((float)YUV_Image[i][j][1] - 128));
                    }
                }
                else if (k == 2)
                {
                    if ((1.164 * ((float)transfer[YUV_Image[i][j][0]] - 16) + 2.018 * ((float)YUV_Image[i][j][1] - 128)) > 255)
                    {
                        Result1[i][j][k] = 255;
                    }
                    else if ((1.164 * ((float)transfer[YUV_Image[i][j][0]] - 16) + 2.018 * ((float)YUV_Image[i][j][1] - 128)) < 0)
                    {
                        Result1[i][j][k] = 0;
                    }
                    else
                    {
                        Result1[i][j][k] = (unsigned char)(1.164 * ((float)transfer[YUV_Image[i][j][0]] - 16) + 2.018 * ((float)YUV_Image[i][j][1] - 128));
                    }
                }
            }
        }
    }
    fwrite(Result1, sizeof(unsigned char), Height * Width * BytesPerPixel, qFile);
    fclose(qFile);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    int average;
    int average_frequency[256];
    unsigned char img[Height][Width][1];
    int temp[Height][Width][1];
    unsigned char result_Y[Height][Width][1];

    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            temp[i][j][0] = (int)YUV_Image[i][j][0];
        }
    }

    if ((Width * Height) % 256)
    {
        average = (Width * Height) / 255;
    }
    else
    {
        average = (Width * Height) / 256;
    }
    for (int i = 0; i < 255; ++i)
    {
        average_frequency[i] = average;
    }
    average_frequency[255] = Width * Height - average * 255;

    int point;
    for (int i = 0; i < 256; ++i)
    {
        while (average_frequency[i] != 0)
        {
            for (int j = 0; j < 256; ++j)
            {
                if (frequency[j] != 0)
                {
                    point = j;
                    break;
                }
            }
            for (int x = 0; x < Height; ++x)
            {
                for (int y = 0; y < Width; ++y)
                {
                    if (temp[x][y][0] == point)
                    {
                        result_Y[x][y][0] = (unsigned char)i;
                        frequency[point]--;
                        average_frequency[i]--;
                        temp[x][y][0] = -1;
                    }
                    if (frequency[point] == 0 || average_frequency[i] == 0)
                    {
                        break;
                    }
                }
                if (frequency[point] == 0 || average_frequency[i] == 0)
                {
                    break;
                }
            }
        }
    }

    qFile = fopen("City2.raw", "w+");

    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            for (int k = 0; k < BytesPerPixel; ++k)
            {
                if (k == 0)
                {
                    if ((1.164 * ((float)result_Y[i][j][0] - 16) + 1.596 * ((float)YUV_Image[i][j][2] - 128)) > 255)
                    {
                        Result2[i][j][k] = 255;
                    }
                    else if ((1.164 * ((float)result_Y[i][j][0] - 16) + 1.596 * ((float)YUV_Image[i][j][2] - 128)) < 0)
                    {
                        Result2[i][j][k] = 0;
                    }
                    else
                    {
                        Result2[i][j][k] = (unsigned char)(1.164 * ((float)result_Y[i][j][0] - 16) + 1.596 * ((float)YUV_Image[i][j][2] - 128));
                    }
                }
                else if (k == 1)
                {
                    if ((1.164 * ((float)result_Y[i][j][0] - 16) - 0.813 * ((float)YUV_Image[i][j][2] - 128) - 0.391 * ((float)YUV_Image[i][j][1] - 128)) > 255)
                    {
                        Result2[i][j][k] = 255;
                    }
                    else if ((1.164 * ((float)result_Y[i][j][0] - 16) - 0.813 * ((float)YUV_Image[i][j][2] - 128) - 0.391 * ((float)YUV_Image[i][j][1] - 128)) < 0)
                    {
                        Result2[i][j][k] = 0;
                    }
                    else
                    {
                        Result2[i][j][k] = (unsigned char)(1.164 * ((float)result_Y[i][j][0] - 16) - 0.813 * ((float)YUV_Image[i][j][2] - 128) - 0.391 * ((float)YUV_Image[i][j][1] - 128));
                    }
                }
                else if (k == 2)
                {
                    if ((1.164 * ((float)result_Y[i][j][0] - 16) + 2.018 * ((float)YUV_Image[i][j][1] - 128)) > 255)
                    {
                        Result2[i][j][k] = 255;
                    }
                    else if ((1.164 * ((float)result_Y[i][j][0] - 16) + 2.018 * ((float)YUV_Image[i][j][1] - 128)) < 0)
                    {
                        Result2[i][j][k] = 0;
                    }
                    else
                    {
                        Result2[i][j][k] = (unsigned char)(1.164 * ((float)result_Y[i][j][0] - 16) + 2.018 * ((float)YUV_Image[i][j][1] - 128));
                    }
                }
            }
        }
    }
    fwrite(Result2, sizeof(unsigned char), Height * Width * BytesPerPixel, qFile);
    fclose(qFile);

    return 0;
}