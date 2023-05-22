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
const int Height = 321;
const int Width = 481;

void Convolution_3(unsigned char Extended_Image[Height + 2][Width + 2][1], float matrix[3][3], float Result_Image[Height][Width][1])
{

    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            for (int k = 0; k < 1; ++k)
            {
                float result = 0;
                for (int x = 0; x < 3; ++x)
                {
                    for (int y = 0; y < 3; ++y)
                    {
                        result += (float)Extended_Image[i + x][j + y][k] * matrix[x][y];
                    }
                }
                Result_Image[i][j][k] = result;
            }
        }
    }
}

void extendImage(unsigned char Imagedata[Height][Width][1], unsigned char Extended_Image[Height + 2][Width + 2][1])
{
    for (int k = 0; k < 1; ++k)
    {
        for (int i = 0; i < Height + 2; ++i)
        {
            for (int j = 0; j < Width + 2; ++j)
            {
                if (i == 0 && j == 0)
                {
                    Extended_Image[i][j][k] = Imagedata[i + 1][j + 1][k];
                }
                else if (i == 0 && j == Width + 1)
                {
                    Extended_Image[i][j][k] = Imagedata[i + 1][j - 3][k];
                }
                else if (i == Height + 1 && j == 0)
                {
                    Extended_Image[i][j][k] = Imagedata[i - 3][j + 1][k];
                }
                else if (i == Height + 1 && j == Width + 1)
                {
                    Extended_Image[i][j][k] = Imagedata[i - 3][j - 3][k];
                }
                else if (i == 0)
                {
                    Extended_Image[i][j][k] = Imagedata[i + 1][j - 1][k];
                }
                else if (i == Height + 1)
                {
                    Extended_Image[i][j][k] = Imagedata[i - 3][j - 1][k];
                }
                else if (j == 0)
                {
                    Extended_Image[i][j][k] = Imagedata[i - 1][j + 1][k];
                }
                else if (j == Width + 1)
                {
                    Extended_Image[i][j][k] = Imagedata[i - 1][j - 3][k];
                }
                else
                {
                    Extended_Image[i][j][k] = Imagedata[i - 1][j - 1][k];
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

void getY(unsigned char Imagedata[Height][Width][BytesPerPixel], unsigned char Imagedata_Y[Height][Width][1])
{
    for (int i = 0; i < Height + 2; ++i)
    {
        for (int j = 0; j < Width + 2; ++j)
        {
            Imagedata_Y[i][j][0] = 0.2989 * Imagedata[i][j][0] + 0.587 * Imagedata[i][j][1] + 0.114 * Imagedata[i][j][2];
        }
    }
}

void Gradient(float Gradient_x[Height][Width][1], float Gradient_y[Height][Width][1], float Gradient[Height][Width][1])
{
    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            for (int k = 0; k < 1; ++k)
            {
                Gradient[i][j][k] = sqrt(pow(Gradient_x[i][j][k], 2) + pow(Gradient_y[i][j][k], 2));
            }
        }
    }
}

float findMax(float Gradient[Height][Width][1])
{
    float maxValue = 0;
    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            for (int k = 0; k < 1; ++k)
            {
                if (Gradient[i][j][k] > maxValue)
                {
                    maxValue = Gradient[i][j][k];
                }
            }
        }
    }
    return maxValue;
}

void normalize255(float Gradient[Height][Width][1], int maxValue)
{
    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            for (int k = 0; k < 1; ++k)
            {
                Gradient[i][j][k] /= maxValue;
                Gradient[i][j][k] *= 255;
            }
        }
    }
}

void normalize1(float Gradient[Height][Width][1], int maxValue)
{
    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            for (int k = 0; k < 1; ++k)
            {
                Gradient[i][j][k] /= maxValue;
            }
        }
    }
}

void writeFile(const char *fileName, float Imagedata[Height][Width][1])
{
    unsigned char Imagedata1[Height][Width][1];
    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            for (int k = 0; k < 1; ++k)
            {
                Imagedata1[i][j][k] = (unsigned char)Imagedata[i][j][k];
            }
        }
    }
    FILE *file;
    if (!(file = fopen(fileName, "wb")))
    {
        cout << "Cannot open file: "
             << fileName << endl;
        exit(1);
    }
    fwrite(Imagedata1, sizeof(unsigned char), Height * Width * 1, file);
    fclose(file);
}

void writeFileThreshold(const char *fileName, float Imagedata[Height][Width][1], float threshold)
{
    unsigned char Imagedata1[Height][Width][1];
    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            for (int k = 0; k < 1; ++k)
            {
                if (Imagedata[i][j][k] >= threshold)
                {
                    Imagedata1[i][j][k] = 255;
                }
                else
                {
                    Imagedata1[i][j][k] = 0;
                }
            }
        }
    }
    if (abs(threshold - 0.3)<0.00001)
    {
        cout<<"begin"<<endl;
        for (int k = 0; k < 1; ++k)
        {
            for (int i = 0; i < Height; ++i)
            {
                for (int j = 0; j < Width; ++j)
                {
                    cout <<(Imagedata1[i][j][k]/255)<<' ';
                }
                cout<<endl;
            }
        }
        cout<<"end"<<endl;
    }
    FILE *file;
    if (!(file = fopen(fileName, "wb")))
    {
        cout << "Cannot open file: "
             << fileName << endl;
        exit(1);
    }
    fwrite(Imagedata1, sizeof(unsigned char), Height * Width * 1, file);
    fclose(file);
}

int main()
{
    unsigned char Imagedata_tiger[Height][Width][BytesPerPixel];
    unsigned char Imagedata_pig[Height][Width][BytesPerPixel];
    unsigned char Imagedata_tiger_Y[Height][Width][1];
    unsigned char Imagedata_pig_Y[Height][Width][1];
    float x_filter[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    float y_filter[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
    unsigned char Extended_Image_tiger[Height + 2][Width + 2][1];
    unsigned char Extended_Image_pig[Height + 2][Width + 2][1];
    float Gradient_tiger_x[Height][Width][1];
    float Gradient_tiger_y[Height][Width][1];
    float Gradient_pig_x[Height][Width][1];
    float Gradient_pig_y[Height][Width][1];
    float Gradient_tiger[Height][Width][1];
    float Gradient_pig[Height][Width][1];
    float maxTiger_x;
    float maxTiger_y;
    float maxPig_x;
    float maxPig_y;
    float maxTiger;
    float maxPig;
    unsigned char Result_1[Height][Width][1];
    unsigned char Result_2[Height][Width][1];

    openFile("Tiger.raw", Imagedata_tiger);
    openFile("Pig.raw", Imagedata_pig);

    getY(Imagedata_tiger, Imagedata_tiger_Y);
    getY(Imagedata_pig, Imagedata_pig_Y);

    extendImage(Imagedata_tiger_Y, Extended_Image_tiger);
    extendImage(Imagedata_pig_Y, Extended_Image_pig);

    Convolution_3(Extended_Image_tiger, x_filter, Gradient_tiger_x);
    Convolution_3(Extended_Image_tiger, y_filter, Gradient_tiger_y);
    Convolution_3(Extended_Image_pig, x_filter, Gradient_pig_x);
    Convolution_3(Extended_Image_pig, y_filter, Gradient_pig_y);

    Gradient(Gradient_tiger_x, Gradient_tiger_y, Gradient_tiger);
    Gradient(Gradient_pig_x, Gradient_pig_y, Gradient_pig);

    maxTiger = findMax(Gradient_tiger);
    maxPig = findMax(Gradient_pig);
    maxTiger_x = findMax(Gradient_tiger_x);
    maxTiger_y = findMax(Gradient_tiger_y);
    maxPig_x = findMax(Gradient_pig_x);
    maxPig_y = findMax(Gradient_pig_y);

    normalize255(Gradient_tiger, maxTiger);
    normalize255(Gradient_pig, maxPig);
    normalize255(Gradient_tiger_x, maxTiger_x);
    normalize255(Gradient_tiger_y, maxTiger_y);
    normalize255(Gradient_pig_x, maxPig_x);
    normalize255(Gradient_pig_y, maxPig_y);

    writeFile("Tiger_xy.raw", Gradient_tiger);
    writeFile("Pig_xy.raw", Gradient_pig);
    writeFile("Tiger_x.raw", Gradient_tiger_x);
    writeFile("Tiger_y.raw", Gradient_tiger_y);
    writeFile("Pig_x.raw", Gradient_pig_x);
    writeFile("Pig_y.raw", Gradient_pig_y);

    normalize1(Gradient_tiger, 255);
    normalize1(Gradient_pig, 255);

    writeFileThreshold("Tiger_xy0.9.raw", Gradient_tiger, 0.9);
    writeFileThreshold("Pig_xy0.9.raw", Gradient_pig, 0.9);
    writeFileThreshold("Tiger_xy0.8.raw", Gradient_tiger, 0.8);
    writeFileThreshold("Pig_xy0.8.raw", Gradient_pig, 0.8);
    writeFileThreshold("Tiger_xy0.7.raw", Gradient_tiger, 0.7);
    writeFileThreshold("Pig_xy0.7.raw", Gradient_pig, 0.7);
    writeFileThreshold("Tiger_xy0.6.raw", Gradient_tiger, 0.6);
    writeFileThreshold("Pig_xy0.6.raw", Gradient_pig, 0.6);
    writeFileThreshold("Tiger_xy0.5.raw", Gradient_tiger, 0.5);
    writeFileThreshold("Pig_xy0.5.raw", Gradient_pig, 0.5);
    writeFileThreshold("Tiger_xy0.4.raw", Gradient_tiger, 0.4);
    writeFileThreshold("Pig_xy0.4.raw", Gradient_pig, 0.4);
    writeFileThreshold("Tiger_xy0.3.raw", Gradient_tiger, 0.3);
    writeFileThreshold("Pig_xy0.3.raw", Gradient_pig, 0.3);
    writeFileThreshold("Tiger_xy0.2.raw", Gradient_tiger, 0.2);
    writeFileThreshold("Pig_xy0.2.raw", Gradient_pig, 0.2);
    writeFileThreshold("Tiger_xy0.1.raw", Gradient_tiger, 0.1);
    writeFileThreshold("Pig_xy0.1.raw", Gradient_pig, 0.1);

    return 0;
}