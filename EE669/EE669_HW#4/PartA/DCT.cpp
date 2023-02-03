#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#define PI acos(-1)
using namespace std;

// Here we assume the image is of size 256*256 and is of raw format
// You will need to make corresponding changes to accommodate images of different sizes and types

#define Size 16

void DCT(vector<vector<float>> &ori, vector<vector<float>> &dct, float N)
{
	for (int m = 0; m < N; m++)
	{
		for (int n = 0; n < N; n++)
		{
			dct[0][0] += (1 / (2 * sqrt(2 * N))) * ori[m][n];
		}
	}
	for (int l = 1; l < N; l++)
	{
		for (int m = 0; m < N; m++)
		{
			for (int n = 0; n < N; n++)
			{
				dct[0][l] += (1 / (2 * sqrt(N))) * (ori[m][n]) * cos((2 * n + 1) * l * PI / (2 * N));
			}
		}
	}
	for (int k = 1; k < N; k++)
	{
		for (int m = 0; m < N; m++)
		{
			for (int n = 0; n < N; n++)
			{
				dct[k][0] += (1 / sqrt(2 * N)) * (ori[m][n]) * cos((2 * m + 1) * k * PI / (2 * N));
			}
		}
	}

	for (int k = 1; k < N; k++)
	{
		for (int l = 1; l < N; l++)
		{
			for (int m = 0; m < N; m++)
			{
				for (int n = 0; n < N; n++)
				{
					dct[k][l] += (2 / N) * (ori[m][n]) * (cos((2 * m + 1) * k * PI / (2 * N))) * (cos((2 * n + 1) * l * PI / (2 * N)));
				}
			}
		}
	}
}

int main()

{
	// file pointer
	FILE *file;
	int BytesPerPixel;
	const int N = 8;
	int n = 10;

	// image data array
	unsigned char Imagedata[Size][Size];
	float Imagetemp[Size][Size];

	// read image "ride.raw" into image data matrix
	if (!(file = fopen("../Original_Images/lena.raw", "rb")))
	{
		cout << "Cannot open file: "
			 << "../Original_Images/lena.raw" << endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size * Size, file);
	fclose(file);

	// do some image processing task...
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			Imagetemp[i][j] = (Imagedata[i][j] - 128);
		}
	}
	vector<vector<float>> oriMatrix;
	vector<vector<float>> dctMatrix;
	vector<float> temp;
	for (int i = 0; i < N; i++)
	{
		temp.push_back(0);
	}
	for (int i = 0; i < N; i++)
	{
		oriMatrix.push_back(temp);
	}
	dctMatrix = oriMatrix;
	for (int x = 0; x < Size / N; x++)
	{
		for (int y = 0; y < Size / N; y++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					oriMatrix[i][j] = Imagetemp[i + x * N][j + y * N];
				}
			}
			DCT(oriMatrix, dctMatrix, N);
			cout << "The matrix  after DCT transform:" << endl;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					printf("%-10.4f", dctMatrix[i][j]);
				}
				cout << endl;
			}
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					Imagetemp[i + x * N][j + y * N] = dctMatrix[i][j];
				}
			}
		}
	}

	float Q50[N][N] = {
		{16, 11, 10, 16, 24, 40, 51, 61},
		{12, 12, 14, 19, 26, 58, 60, 55},
		{14, 13, 16, 24, 40, 57, 69, 56},
		{14, 17, 22, 29, 51, 87, 80, 62},
		{18, 22, 37, 56, 68, 109, 103, 77},
		{24, 35, 55, 64, 81, 104, 113, 92},
		{49, 64, 78, 87, 103, 121, 120, 101},
		{72, 92, 95, 98, 112, 100, 103, 99}};

	for (int x = 0; x < Size / N; x++)
	{
		for (int y = 0; y < Size / N; y++)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (n > 50)
					{
						Imagetemp[i + x * N][j + y * N] /= ((100 - n) * Q50[i][j] / 50);
					}
					else if (n <= 50)
					{
						Imagetemp[i + x * N][j + y * N] /= (50 * Q50[i][j] / n);
					}
				}
			}
		}
	}

	cout << "Q10：" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (n > 50)
			{
				printf("%-10.0f", ((100 - n) * Q50[i][j] / 50));
			}
			else if (n <= 50)
			{
				printf("%-10.0f", (50 * Q50[i][j] / n));
			}
		}
		cout << endl;
	}

	cout << "Imagetemp：" << endl;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			printf("%-10.0f", Imagetemp[i][j]);
		}
		cout << endl;
	}

	return 0;
}
