/*
 * Compress text file by using Shannon-Fano (No real compression,
 * just get the 0101 code)
 *
 * Author: bonep
 * Last update: 20120425
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
class SymbolCode { //压缩编码类
private:
    char symbol; //被压缩的源码
    int frequency; ////对应的频率
    string code; //压缩的编码
public:
    SymbolCode( char in_symbol, int in_frequency ); //对private里的值进行定义或者初始化
    char getSymbol( void ); //返回symbol
    int getFrequency( void ); //返回symbol的概率
    string getCode( void ); //返回symbol定义的编码
    void addCode( string in_code ); //给初始化的编码赋值
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
    ofs<< "Fre," << in_symbol.getFrequency()<< ",od," << in_symbol.getCode()<< endl;
}

void shannonFano( int in_begin, int in_end ) { // The value of in_begin is 0, which represents the first element in the sorted SymbolCode vector 'symbol', the value of in_end is the number of elements in the sorted SymbolCode vector 'symbol' - 1, which represent the last element in 'symbol'.
    // not a valid parameters input
    if ( in_begin >= in_end ) { // Determines whether there are elements in the vector. If not, end encoding by return.
        return;
    }
    
    // only 2 symbol left
    if ( in_begin == in_end - 1 ) { // Determine whether there are only two elements in the vector. If so, encode the symbol with higher probability as 0 and the symbol with lower probability as 1
        symbol.at( in_begin ).addCode( "0" );
        symbol.at( in_end ).addCode( "1" );
        return;
    }

    // highPtr will go downward
    int highPtr = in_begin; // Assign the position of the most frequent symbol in sorted SymbolCode vector 'symbol' to highPtr.
    int lowPtr = in_end; // Assign the position of the least frequent symbol in sorted SymbolCode vector 'symbol' to lowPtr.
    int highSum = symbol.at( highPtr ).getFrequency(); // Assign the number of occurrences of the most frequent symbol to highSum.
    int lowSum = symbol.at( lowPtr ).getFrequency(); // Assign the number of occurrences of the least frequent symbol to lowSum.
    
    // move the highPtr down and lowPtr up until highSum and lowSum close
    while ( highPtr != lowPtr - 1 ) { // When the pointer pointing to symbols with higher probability of occurrence 'highPtr' and the pointer pointing to symbols with lower probability of occurrence 'lowPtr' are next to each other, the loop is stopped. This is the procedure how the splitting boundary is found.
        if ( highSum > lowSum ) { // When the sum of the occurrence times of symbols with higher frequency 'highSum' is greater than that of symbols with lower frequency 'lowSum', move the pointer 'lowPtr' one bit forward. Then 'lowSum' would plus the occurrence times of the symbol pointed by the pointer 'lowPtr'. 
            lowPtr --;
            lowSum += symbol.at( lowPtr ).getFrequency();
        } else { // When the sum of the occurrence times of symbols with higher frequency 'highSum' is less than that of symbols with lower frequency 'lowSum', move the pointer 'highPtr' one bit backward. Then 'highSum' would plus the occurrence times of the symbol pointed by the pointer 'highPtr'. 
            highPtr ++;
            highSum += symbol.at( highPtr ).getFrequency();
        }
    }
    
    int i;
    for ( i=in_begin; i<=highPtr; i++ ) { // Add a code 0 for all symbols whose index values are on the smaller side of the splitting boundary
        symbol.at( i ).addCode( "0" );
    }
    for ( i=lowPtr; i<=in_end; i++ ) { // Add a code 1 for all symbols whose index values are on the bigger side of the splitting boundary
        symbol.at( i ).addCode( "1" );
    }
    
    shannonFano( in_begin, highPtr ); // All symbols whose index values are less than splitting boundary are encoded again
    shannonFano( lowPtr, in_end ); // All symbols whose index values are bigger than splitting boundary are encoded again
}

int main () {
    FILE * pFile;
    int c;
    int n = 0;
    pFile = fopen("audio.dat","rb"); // audio.dat binary.dat, Fimage.dat, text.dat
    if (pFile==NULL) {
        perror ("Error opening file");
    } else {
        int i;
        for ( i=0; i<MAX_CHAR; i++ ) {
            frequency[ i ] = 0; //char c=0; 这被称为“空字符”，常用作字符串的串尾符。https://zhidao.baidu.com/question/2123165226230489667.html
        }
        do {
            c = fgetc (pFile); //fgetc得到的是对应字符的ASSICII码int值
            if ( c != EOF ) {
                // cout<< c<<endl;
                frequency[ c ] ++; //把对应ASSICII码处的值加一，但是frequency是char类型的阿？人家就这么用，也不是不能用，记得转换就行
                printf( "%c", c );
            }
        } while (c != EOF);

    
        fclose (pFile);
    }
    
    // print the frequency information
    cout << endl << endl;
    int i;
    for ( i=0; i<MAX_CHAR; i++ ) {
        if ( frequency[ i ] != 0 ) {
            printf( "%d, %c: %d\n", i, i, frequency[ i ] );
        }
    }
    
    // insert and sort the symbol
    printf( "\n\n" );
    for ( i=0; i<MAX_CHAR; i++ ) {
        if ( frequency[ i ] != 0 ) {
            if ( symbol.empty() ) {
                SymbolCode newSymbol( i, frequency[ i ] );
                symbol.push_back( newSymbol ); //第一个就直接推进symbol的末尾了，其余的需要排序
            } else {
                int j;
                vector<SymbolCode>::iterator it;
                it = symbol.begin();
                for ( j=0; j<symbol.size(); j++ ) {
                    if ( frequency[ i ] >= symbol[ j ].getFrequency() ) { //在symbol这个vector里大的frequency的项目放在前面
                        SymbolCode newSymbol( i, frequency[ i ] );
                        symbol.insert( it, newSymbol );  //插在大的位置，如何通过it实现的？
                        break;
                    } else if ( j == symbol.size() - 1 ) { //比遍了都没插进去，就直接插在最后面
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
    ofs.open("audio.txt",ios::out); // audio.txt, binary.txt, Fimage.txt, text.txt
    for_each( symbol.begin(), symbol.end(), bind2nd(ptr_fun(printSymbolCode), ofs));
    ofs.close();
    return 0;
}
