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
    pFile = fopen("image.dat","rb"); // audio.dat, binary.dat, image.dat, text.dat
    qFile = fopen("encodedImage.txt","w+"); // encodedAudio.txt, encodedBinary.txt, encodedImage.txt, encodedText.txt
    if (pFile==NULL) {
        perror ("Error opening file");
    } else {
        do {
            c = fgetc (pFile);
            if ( c != EOF ) {
                n = Transform(c); 
                for(int i =0; i< n.size(); i++){
                     fputc(48+n[i], qFile);
                }
            }
        } while (c != EOF);

    
        fclose (pFile);
        fclose (qFile);
    }
    return 0;
}