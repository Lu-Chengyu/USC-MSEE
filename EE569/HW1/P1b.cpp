// Name: Chengyu Lu
// USC ID Number: 5157638886
// USC Email: luchenggy@usc.edu
// Submission Date: 01/29/2023

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define MAX_VALUE 256
int frequency[MAX_VALUE], transfer[MAX_VALUE], frequency2[MAX_VALUE];
int Width = 596;
int Height = 340;
using namespace std;

int main()
{
    FILE *pFile, *qFile;
    int c;
    pFile = fopen("DimLight.raw", "rb");
    if (pFile == NULL)
    {
        perror("Error opening file");
    }
    else
    {
        for (int i = 0; i < MAX_VALUE; i++)
        {
            frequency[i] = 0;
            transfer[i] = 0;
        }
        do
        {
            c = fgetc(pFile);
            if (c != EOF)
            {
                frequency[c]++;
            }
        } while (c != EOF);
        fclose(pFile);
    }

    int sum = 0;
    cout<<"DimLight.raw"<<endl<<"pixelvalue  frequency  percent transfer"<<endl;
    for (int i = 0; i < MAX_VALUE; i++)
    {
        cout << i << ' ' << frequency[i];
        sum += frequency[i];
        cout << ' ' << (float)sum / (float)(Width * Height);
        transfer[i] = sum * 255 / (Width * Height);
        cout << ' ' << transfer[i] << endl;
    }

    pFile = fopen("DimLight.raw", "rb");
    qFile = fopen("DimLight1.raw", "w+");
    if (pFile == NULL)
    {
        perror("Error opening file");
    }
    else
    {
        do
        {
            c = fgetc(pFile);
            if (c != EOF)
            {
                fputc(transfer[c], qFile);
            }
        } while (c != EOF);
        fclose(pFile);
        fclose(qFile);
    }

    //////////////////////////////////////////////////////////////////////////////////////////

    int average;
    int average_frequency[256];
    int BytesPerPixel = 1;
    unsigned char img[Height][Width][BytesPerPixel];
    int temp[Height][Width][BytesPerPixel];
    unsigned char result[Height][Width][BytesPerPixel];
    FILE *file;
    if (!(file = fopen("DimLight.raw", "rb")))
    {
        cout << "Cannot open file: "
             << "DimLight.raw" << endl;
        exit(1);
    }
    fread(img, sizeof(unsigned char), Height * Width * BytesPerPixel, file);
    fclose(file);
    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            temp[i][j][0] = (int)img[i][j][0];
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
                        result[x][y][0] = (unsigned char)i;
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

    if (!(file = fopen("DimLight2.raw", "wb")))
    {
        cout << "Cannot open file: "
             << "DimLight2.raw" << endl;
        exit(1);
    }
    fwrite(result, sizeof(unsigned char), Height * Width * BytesPerPixel, file);
    fclose(file);

    FILE *File;
    File = fopen("DimLight2.raw", "rb");
    if (pFile == NULL)
    {
        perror("Error opening file");
    }
    else
    {
        for (int i = 0; i < MAX_VALUE; i++)
        {
            frequency2[i] = 0;
        }
        do
        {
            c = fgetc(File);
            if (c != EOF)
            {
                frequency2[c]++;
            }
        } while (c != EOF);
        fclose(File);
    }

    sum = 0;
    cout<<"DimLight2.raw"<<endl<<"pixelvalue  frequency  percent"<<endl;
    for (int i = 0; i < MAX_VALUE; i++)
    {
        cout << i << ' ' << frequency2[i];
        sum += frequency2[i];
        cout << ' ' << (float)sum / (float)(Width * Height)<< endl;
    }

    return 0;
}
