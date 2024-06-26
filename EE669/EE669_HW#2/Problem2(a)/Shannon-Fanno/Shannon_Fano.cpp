/*
 * Compress text file by using Shannon-Fano (No real compression,
 * just get the 0101 code)
 *
 *
 * Please free feel to use this code in any way
 *
 * Compile:
 * linux> c++ Shannon_Fano.cpp
 *
 * Usage:
 * linux> ./a.out
 * (the input text file is hardcoded as text1.txt)
 */

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<fstream>

#define MAX_CHAR 256

using namespace std;

/*
 * Define SymbolCode Class
 */
class SymbolCode {
private:
    char symbol;
    int frequency;
    string code;
public:
    SymbolCode( char in_symbol, int in_frequency );
    char getSymbol( void );
    int getFrequency( void );
    string getCode( void );
    void addCode( string in_code );
};

SymbolCode::SymbolCode( char in_symbol, int in_frequency ) { //
    symbol = in_symbol;
    frequency = in_frequency;
    code = "";
}

char SymbolCode::getSymbol( void ) {
    return symbol;
}

int SymbolCode::getFrequency( void ) {
    return frequency;
}

string SymbolCode::getCode( void ) {
    return code;
}

void SymbolCode::addCode( string in_code ) {
    code += in_code;
}
/*
 * End SymbolCode Class
 */

// store the symbol sorted by frequency of which frequency not zero
vector<SymbolCode> symbol;

// store the input frequency
int  frequency[ MAX_CHAR ];

void printSymbolCode( SymbolCode in_symbol,  ofstream &ofs ) {
    cout << "Symbol: " << in_symbol.getSymbol();
    cout << " Freq: " << in_symbol.getFrequency();
    cout << " Code: " << in_symbol.getCode() << endl;
    ofs<<in_symbol.getSymbol()<< "sep," << in_symbol.getFrequency()<< "sep," << in_symbol.getCode()<< endl;
}

void shannonFano( int in_begin, int in_end ) { 
    if ( in_begin >= in_end ) {
        return;
    }
    
    if ( in_begin == in_end - 1 ) {
        symbol.at( in_begin ).addCode( "0" );
        symbol.at( in_end ).addCode( "1" );
        return;
    }

    int highPtr = in_begin;
    int lowPtr = in_end;
    int highSum = symbol.at( highPtr ).getFrequency();
    int lowSum = symbol.at( lowPtr ).getFrequency();
    
    while ( highPtr != lowPtr - 1 ) {
        if ( highSum > lowSum ) {
            lowPtr --;
            lowSum += symbol.at( lowPtr ).getFrequency();
        } else {
            highPtr ++;
            highSum += symbol.at( highPtr ).getFrequency();
        }
    }
    
    int i;
    for ( i=in_begin; i<=highPtr; i++ ) {
        symbol.at( i ).addCode( "0" );
    }
    for ( i=lowPtr; i<=in_end; i++ ) {
        symbol.at( i ).addCode( "1" );
    }
    
    shannonFano( in_begin, highPtr );
    shannonFano( lowPtr, in_end );
}

int main () {
    FILE * pFile;
    int c;
    int n = 0;
    pFile = fopen("image.dat","rb"); // audio.dat binary.dat, Fimage.dat, text.dat
    if (pFile==NULL) {
        perror ("Error opening file");
    } else {
        int i;
        for ( i=0; i<MAX_CHAR; i++ ) {
            frequency[ i ] = 0;
        }
        do {
            c = fgetc (pFile);
            if ( c != EOF ) {
                frequency[ c ] ++;
                printf( "%c", c );
            }
        } while (c != EOF);

    
        fclose (pFile);
    }
    
    cout << endl << endl;
    int i;
    for ( i=0; i<MAX_CHAR; i++ ) {
        if ( frequency[ i ] != 0 ) {
            printf( "%d, %c: %d\n", i, i, frequency[ i ] );
        }
    }
    
    printf( "\n\n" );
    for ( i=0; i<MAX_CHAR; i++ ) {
        if ( frequency[ i ] != 0 ) {
            if ( symbol.empty() ) {
                SymbolCode newSymbol( i, frequency[ i ] );
                symbol.push_back( newSymbol );
            } else {
                int j;
                vector<SymbolCode>::iterator it;
                it = symbol.begin();
                for ( j=0; j<symbol.size(); j++ ) {
                    if ( frequency[ i ] >= symbol[ j ].getFrequency() ) {
                        SymbolCode newSymbol( i, frequency[ i ] );
                        symbol.insert( it, newSymbol );
                        break;
                    } else if ( j == symbol.size() - 1 ) {
                        SymbolCode newSymbol( i, frequency[ i ] );
                        symbol.push_back( newSymbol );
                        break;
                    }
                    it ++;
                }
            }
        }
    }
    
    shannonFano( 0, symbol.size() - 1 );
    
    printf( "\n\n" );
    ofstream ofs;
    ofs.open("image.txt",ios::out); // audio.txt, binary.txt, Fimage.txt, text.txt
    for_each( symbol.begin(), symbol.end(), bind2nd(ptr_fun(printSymbolCode), ofs));
    ofs.close();
    return 0;
}
