% Name: Chengyu Lu
% USC ID Number: 5157638886
% USC Email: luchengy@usc.edu
% Submission Date: 03/09/2023
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <string.h>
#include <cmath>
#include <bitset>

using namespace std;

void openFile(void *imageData, const char *fileName, int height, int width, int bytesPerPixel)
{
    FILE *file;
    file = fopen(fileName, "rb");
    fread(imageData, sizeof(unsigned char), height * width * bytesPerPixel, file);
    fclose(file);
}

void writeFile(const void *imageData, const char *fileName, int height, int width, int bytesPerPixel)
{
    FILE *file;
    file = fopen(fileName, "wb");
    fwrite(imageData, sizeof(unsigned char), height * width * bytesPerPixel, file);
    fclose(file);
}

template <size_t a, size_t b, size_t x, size_t y, size_t c>
void zeroPadding(unsigned char (&input)[a][b][c], unsigned char (&output)[x][y][c], int paddingSize, int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            output[i + paddingSize][j + paddingSize][0] = input[i][j][0];
        }
    }
    for (int i = 0; i < paddingSize; i++)
    {
        for (int j = 0; j < width + 2 * paddingSize; j++)
        {
            output[i][j][0] = 0;
        }
    }
    for (int i = height + paddingSize; i < height + 2 * paddingSize; i++)
    {
        for (int j = 0; j < width + 2 * paddingSize; j++)
        {
            output[i][j][0] = 0;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < paddingSize; j++)
        {
            output[i + paddingSize][j][0] = 0;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = width + paddingSize; j < width + 2 * paddingSize; j++)
        {
            output[i + paddingSize][j][0] = 0;
        }
    }
}

bool conditionalMark(int pattern)
{
    int patterns[] = {
        0b010011000,
        0b010110000,
        0b000110010,
        0b000011010,

        0b001011001,
        0b111010000,
        0b100110100,
        0b000010111,

        0b110011000,
        0b010011001,
        0b011110000,
        0b001011010,

        0b011011000,
        0b110110000,
        0b000110110,
        0b000011011,

        0b110011001,
        0b011110100,

        0b111011000,
        0b011011001,
        0b111110000,
        0b110110100,
        0b100110110,
        0b000110111,
        0b000011111,
        0b001011011,

        0b111011001,
        0b111110100,
        0b100110111,
        0b001011111,

        0b011011011,
        0b111111000,
        0b110110110,
        0b000111111,

        0b111011011,
        0b011011111,
        0b111111100,
        0b111111001,
        0b111110110,
        0b110110111,
        0b100111111,
        0b001111111,

        0b111011111,
        0b111111101,
        0b111110111,
        0b101111111,
    };
    for (int i = 0; i < 46; i++)
    {
        if (pattern == patterns[i])
        {
            return true;
        }
    }
    return false;
}

bool unconditionalMark(int pattern)
{
    int patterns1[] = {
        0b001010000, 0b100010000, 0b000010010, 0b000011000,
        0b001011000, 0b011010000, 0b110010000, 0b100110000,
        0b000110100, 0b000010110, 0b000010011, 0b000011001,
        0b011110000, 0b110011000, 0b010011001, 0b001011010,
        0b011011100, 0b001011100, 0b011010100, 0b110110001,
        0b100110001, 0b110010001, 0b001110110, 0b001110100,
        0b001010110, 0b100011011, 0b100011001, 0b100010011};
    int patterns2[] = {
        0b110110000, 0b000011011,
        0b010111000, 0b010111000, 0b000111010, 0b000111010,
        0b010110010, 0b010110010, 0b010011010, 0b010011010,
        0b101010001, 0b101010010, 0b101010011, 0b101010100,
        0b101010101, 0b101010110, 0b101010111, 0b100010101,
        0b100011100, 0b100011101, 0b101010100, 0b101010101,
        0b101011100, 0b101011101, 0b001010101, 0b010010101,
        0b011010101, 0b100010101, 0b101010101, 0b110010101,
        0b111010101, 0b001010101, 0b001110001, 0b001110101,
        0b101010001, 0b101010101, 0b101110001, 0b101110101,
        0b010011100, 0b010110001, 0b001110010, 0b100011010};
    int patterns3[] = {
        0b110110000, 0b000011011,
        0b011111011, 0b110111110, 0b110111110, 0b011111011,
        0b010111111, 0b111111010, 0b111111010, 0b010111111,
        0b101010111, 0b101010111, 0b101010111, 0b101010111,
        0b101010111, 0b101010111, 0b101010111, 0b101011111,
        0b101011111, 0b101011111, 0b101011111, 0b101011111,
        0b101011111, 0b101011111, 0b111010101, 0b111010101,
        0b111010101, 0b111010101, 0b111010101, 0b111010101,
        0b111010101, 0b101110101, 0b101110101, 0b101110101,
        0b101110101, 0b101110101, 0b101110101, 0b101110101,
        0b011111110, 0b110111011, 0b011111110, 0b110111011};

    for (int i = 0; i < 28; i++)
    {
        if (pattern == patterns1[i])
        {
            return true;
        }
    }
    for (int i = 0; i < 42; i++)
    {
        if ((pattern & patterns3[i]) == patterns2[i])
        {
            return true;
        }
    }
    return false;
}

template <size_t a, size_t b, size_t c>
int morphological1(unsigned char (&input)[a][b][c], int paddingSize, int height, int width)
{
    int num = 0;
    unsigned char mark[252][252][1];
    unsigned char paddedImage[254][254][1];
    zeroPadding(input, paddedImage, 1, height, width);
    unsigned char temp[252][252][1];
    for (int i = 0; i < 252; i++)
    {
        for (int j = 0; j < 252; j++)
        {
            temp[i][j][0] = input[i][j][0];
        }
    }
    for (int i = 0; i <= 251; i++)
    {
        for (int j = 0; j <= 251; j++)
        {
            int pattern = 0b000000000;
            for (int k = i; k <= i + 2; k++)
            {
                for (int l = j; l <= j + 2; l++)
                {
                    pattern = pattern << 1;
                    if (paddedImage[k][l][0] == 255)
                    {
                        pattern += 1;
                    }
                }
            }
            bool hit = conditionalMark(pattern);
            if (hit == true)
            {
                mark[i][j][0] = 255;
            }
            else
            {
                mark[i][j][0] = 0;
            }
        }
    }
    unsigned char paddedmark[254][254][1];
    zeroPadding(mark, paddedmark, 1, height, width);
    int hit = 0;
    for (int i = 0; i <= 251; i++)
    {
        for (int j = 0; j <= 251; j++)
        {
            if (mark[i][j][0] == 255)
            {
                int pattern = 0b000000000;
                for (int k = i - 1; k <= i + 1; k++)
                {
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        pattern = pattern << 1;
                        if (mark[k][l][0] == 255)
                        {
                            pattern += 1;
                        }
                    }
                }
                bool hit = unconditionalMark(pattern);
                if (hit == true)
                {
                    input[i][j][0] = temp[i][j][0];
                }
                else
                {
                    num += 1;
                    input[i][j][0] = 0;
                }
            }
            else
            {
                input[i][j][0] = temp[i][j][0];
            }
        }
    }
    return num;
}

template <size_t a, size_t b, size_t c>
int morphological2(unsigned char (&input)[a][b][c], int paddingSize, int height, int width)
{
    int num = 0;
    unsigned char mark[247][247][1];
    unsigned char paddedImage[249][249][1];
    zeroPadding(input, paddedImage, 1, height, width);
    unsigned char temp[247][247][1];
    for (int i = 0; i < 247; i++)
    {
        for (int j = 0; j < 247; j++)
        {
            temp[i][j][0] = input[i][j][0];
        }
    }
    for (int i = 0; i <= 246; i++)
    {
        for (int j = 0; j <= 246; j++)
        {
            int pattern = 0b000000000;
            for (int k = i; k <= i + 2; k++)
            {
                for (int l = j; l <= j + 2; l++)
                {
                    pattern = pattern << 1;
                    if (paddedImage[k][l][0] == 255)
                    {
                        pattern += 1;
                    }
                }
            }
            bool hit = conditionalMark(pattern);
            if (hit == true)
            {
                mark[i][j][0] = 255;
            }
            else
            {
                mark[i][j][0] = 0;
            }
        }
    }
    unsigned char paddedmark[249][249][1];
    zeroPadding(mark, paddedmark, 1, height, width);
    for (int i = 0; i <= 246; i++)
    {
        for (int j = 0; j <= 246; j++)
        {
            if (mark[i][j][0] == 255)
            {
                int pattern = 0b000000000;
                for (int k = i - 1; k <= i + 1; k++)
                {
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        pattern = pattern << 1;
                        if (mark[k][l][0] == 255)
                        {
                            pattern += 1;
                        }
                    }
                }
                bool hit = unconditionalMark(pattern);
                if (hit == true)
                {
                    input[i][j][0] = temp[i][j][0];
                }
                else
                {
                    num += 1;
                    input[i][j][0] = 0;
                }
            }
            else
            {
                input[i][j][0] = temp[i][j][0];
            }
        }
    }
    return num;
}

const int heightSpring = 252;
const int widthSpring = 252;
const int bytesPerPixelSpring = 1;
const int heightFlower = 247;
const int widthFlower = 247;
const int bytesPerPixelFlower = 1;
const int heightJar = 252;
const int widthJar = 252;
const int bytesPerPixelJar = 1;

int main()
{
    unsigned char spring[heightSpring][widthSpring][bytesPerPixelSpring];
    unsigned char flower[heightFlower][widthFlower][bytesPerPixelFlower];
    unsigned char jar[heightJar][widthJar][bytesPerPixelJar];
    int iterationSpring = 0;
    int iterationFlower = 0;
    int iterationJar = 0;

    openFile(spring, "spring.raw", heightSpring, widthSpring, bytesPerPixelSpring);
    openFile(flower, "flower.raw", heightFlower, widthFlower, bytesPerPixelFlower);
    openFile(jar, "jar.raw", heightJar, widthJar, bytesPerPixelJar);

    for (int i = 0; i < heightSpring; i++)
    {
        for (int j = 0; j < widthSpring; j++)
        {
            if (spring[i][j][0] >= 180)
            {
                spring[i][j][0] = 255;
            }
            else
            {
                spring[i][j][0] = 0;
            }
        }
    }
    for (int i = 0; i < heightFlower; i++)
    {
        for (int j = 0; j < widthFlower; j++)
        {
            if (flower[i][j][0] >= 180)
            {
                flower[i][j][0] = 255;
            }
            else
            {
                flower[i][j][0] = 0;
            }
        }
    }
    for (int i = 0; i < heightJar; i++)
    {
        for (int j = 0; j < widthJar; j++)
        {
            if (jar[i][j][0] >= 180)
            {
                jar[i][j][0] = 255;
            }
            else
            {
                jar[i][j][0] = 0;
            }
        }
    }

    while (true)
    {
        iterationSpring += 1;
        if (morphological1(spring, 1, heightSpring, widthSpring) == 0)
        {
            cout << "total iterations for thinning spring: " << iterationSpring << endl;
            writeFile(spring, "resultSpring.raw", 252, 252, 1);
            break;
        }        
        if (iterationSpring == 7)
        {
            writeFile(spring, "resultSpring7.raw", 252, 252, 1);
        }
        else if (iterationSpring == 17)
        {
            writeFile(spring, "resultSpring17.raw", 252, 252, 1);
        }
    }
    while (true)
    {
        iterationFlower += 1;
        if (morphological2(flower, 1, heightFlower, widthFlower) == 0)
        {
            
            cout << "total iterations for thinning flower: " << iterationFlower << endl;
            writeFile(flower, "resultFlower.raw", 247, 247, 1);
            break;
        }        
        if (iterationFlower == 10)
        {
            writeFile(flower, "resultFlower10.raw", 247, 247, 1);
        }
        else if (iterationFlower == 20)
        {
            writeFile(flower, "resultFlower20.raw", 247, 247, 1);
        }
    }
    while (true)
    {
        iterationJar += 1;
        if (morphological1(jar, 1, heightJar, widthJar) == 0)
        {
            cout << "total iterations for thinning jar: " << iterationJar << endl;
            writeFile(jar, "resultJar.raw", 252, 252, 1);
            break;
        }        
        if (iterationJar == 17)
        {
            writeFile(jar, "resultJar17.raw", 247, 247, 1);
        }
        else if (iterationJar == 34)
        {
            writeFile(jar, "resultJar34.raw", 247, 247, 1);
        }
    }

    return 0;
}
