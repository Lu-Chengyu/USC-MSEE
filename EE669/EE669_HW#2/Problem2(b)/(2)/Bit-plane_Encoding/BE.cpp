#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include<vector>

using namespace std;


vector<int> Transform(int n)
{
    vector<int>m;
    for(int i =7; i>=0; i--)
    {
        m.push_back( ( (n>>i) & 1) );
    }
    return m;
}

int main () {
    FILE * pFile, * qFile;
    int c, start;
    vector<int> n;
    vector<vector<int>> m, o;
    vector<int> matrix[256][256];
    pFile = fopen("image.dat","rb"); // audio.dat, binary.dat, image.dat, text.dat
    qFile = fopen("encodedImage.txt","w+"); // encodedAudio.txt, encodedBinary.txt, encodedImage.txt, encodedText.txt
    if (pFile==NULL) {
        perror ("Error opening file");
    } else {
        do {
            c = fgetc (pFile);
            if ( c != EOF ) {
                n = Transform(c); 
                m.push_back(n);
            }
        } while (c != EOF);

    for(int k =0; k<256 ; k++){
        for(int l =0; l<256;l++){
            matrix[k][l] = m[k*l];
        }
    }
    for (int i=0; i<256 ; i++ )
    {
        if (i%2==1)
        {
            for (int j=0; j<=i ; j++ )
            {
                o.push_back(matrix[j][i-j]);
            }
        }
        else
        {
            for (int j=0; j<=i ; j++ )
            {
                o.push_back(matrix[i-j][j]);
            }

        }
    }
    start=1;
    for (int i=256; i<=2*(256-1) ; i++ )
    {
        if (i%2==1)
        {
            for (int j=start; j<=(i-start) ; j++ )
            {
                o.push_back(matrix[j][i-j]);
            }
        }
        else
        {
            for (int j=start; j<=(i-start) ; j++ )
            {
                o.push_back(matrix[i-j][j]);
            }
        }
        start++;
    }


    for(int i =0; i< 8; i++){
        for(int j = 0; j< o.size(); j++){
            fputc(48+o[j][i], qFile);
        }
     }
        fclose (pFile);
        fclose (qFile);
    }
    return 0;
}