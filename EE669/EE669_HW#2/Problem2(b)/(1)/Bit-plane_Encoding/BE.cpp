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
    int c;
    vector<int> n;
    vector<vector<int>> m;
    pFile = fopen("text.dat","rb"); // audio.dat, binary.dat, image.dat, text.dat
    qFile = fopen("encodedText.txt","w+"); // encodedAudio.txt, encodedBinary.txt, encodedImage.txt, encodedText.txt
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
    for(int i =0; i< 8; i++){
        for(int j = 0; j< m.size(); j++){
            fputc(48+m[j][i], qFile);
        }
     }
        fclose (pFile);
        fclose (qFile);
    }
    return 0;
}