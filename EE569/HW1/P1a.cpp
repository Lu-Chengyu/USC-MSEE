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
const int Height = 288;
const int Width = 420;

float Convolution(int i, int j, unsigned char Extended_Image[Height + 2][Width + 2][BytesPerPixel], float matrix[3][3])
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

int main(int argc, char *argv[])
{
	FILE *file;

	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
	}

	unsigned char Imagedata[Height][Width][BytesPerPixel];
	float Vertical[3][3] = {{0, 0.5, 0}, {0, 0, 0}, {0, 0.5, 0}};
	float Horizontal[3][3] = {{0, 0, 0}, {0.5, 0, 0.5}, {0, 0, 0}};
	float Cross[3][3] = {{0, 0.25, 0}, {0.25, 0, 0.25}, {0, 0.25, 0}};
	float X[3][3] = {{0.25, 0, 0.25}, {0, 0, 0}, {0.25, 0, 0.25}};
	unsigned char Extended_Image[Height + 2][Width + 2][BytesPerPixel];
	unsigned char Result[Height][Width][3];

	if (!(file = fopen(argv[1], "rb")))
	{
		cout << "Cannot open file: " << argv[1] << endl;
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

	for (int k = 0; k < 3; ++k)
	{
		for (int i = 0; i < Height; ++i)
		{
			for (int j = 0; j < Width; ++j)
			{
				if (k == 0)
				{
					if (i % 2 == 0 && j % 2 == 0)
					{
						if (Convolution(i, j, Extended_Image, Horizontal) > 255)
						{
							Result[i][j][k] = 255;
						}
						else if (Convolution(i, j, Extended_Image, Horizontal) < 0)
						{
							Result[i][j][k] = 0;
						}
						else
						{
							Result[i][j][k] = (unsigned char)Convolution(i, j, Extended_Image, Horizontal);
						}
					}
					else if (i % 2 != 0 && j % 2 != 0)
					{
						if (Convolution(i, j, Extended_Image, Vertical) > 255)
						{
							Result[i][j][k] = 255;
						}
						else if (Convolution(i, j, Extended_Image, Vertical) < 0)
						{
							Result[i][j][k] = 0;
						}
						else
						{
							Result[i][j][k] = (unsigned char)Convolution(i, j, Extended_Image, Vertical);
						}
					}
					else if (i % 2 != 0 && j % 2 == 0)
					{
						if (Convolution(i, j, Extended_Image, X) > 255)
						{
							Result[i][j][k] = 255;
						}
						else if (Convolution(i, j, Extended_Image, X) < 0)
						{
							Result[i][j][k] = 0;
						}
						else
						{
							Result[i][j][k] = (unsigned char)Convolution(i, j, Extended_Image, X);
						}
					}
					else
					{
						Result[i][j][k] = Extended_Image[i + 1][j + 1][0];
					}
				}
				else if (k == 1)
				{
					if ((i % 2 != 0 && j % 2 == 0) || (i % 2 == 0 && j % 2 != 0))
					{
						if (Convolution(i, j, Extended_Image, Cross) > 255)
						{
							Result[i][j][k] = 255;
						}
						else if (Convolution(i, j, Extended_Image, Cross) < 0)
						{
							Result[i][j][k] = 0;
						}
						else
						{
							Result[i][j][k] = (unsigned char)Convolution(i, j, Extended_Image, Cross);
						}
					}
					else
					{
						Result[i][j][k] = Extended_Image[i + 1][j + 1][0];
					}
				}
				else if (k == 2)
				{
					if (i % 2 == 0 && j % 2 == 0)
					{
						if (Convolution(i, j, Extended_Image, Vertical) > 255)
						{
							Result[i][j][k] = 255;
						}
						else if (Convolution(i, j, Extended_Image, Vertical) < 0)
						{
							Result[i][j][k] = 0;
						}
						else
						{
							Result[i][j][k] = (unsigned char)Convolution(i, j, Extended_Image, Vertical);
						}
					}
					else if (i % 2 != 0 && j % 2 != 0)
					{
						if (Convolution(i, j, Extended_Image, Horizontal) > 255)
						{
							Result[i][j][k] = 255;
						}
						else if (Convolution(i, j, Extended_Image, Horizontal) < 0)
						{
							Result[i][j][k] = 0;
						}
						else
						{
							Result[i][j][k] = (unsigned char)Convolution(i, j, Extended_Image, Horizontal);
						}
					}
					else if (i % 2 == 0 && j % 2 != 0)
					{
						if (Convolution(i, j, Extended_Image, X) > 255)
						{
							Result[i][j][k] = 255;
						}
						else if (Convolution(i, j, Extended_Image, X) < 0)
						{
							Result[i][j][k] = 0;
						}
						else
						{
							Result[i][j][k] = (unsigned char)Convolution(i, j, Extended_Image, X);
						}
					}
					else
					{
						Result[i][j][k] = Extended_Image[i + 1][j + 1][0];
					}
				}
			}
		}
	}

	if (!(file = fopen(argv[2], "wb")))
	{
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Result, sizeof(unsigned char), Height * Width * 3, file);
	fclose(file);

	return 0;
}
