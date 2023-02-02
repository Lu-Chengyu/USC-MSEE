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
#include <fstream>

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

void printSymbol( SymbolCode in_symbol,  ofstream &ofs) {
    cout << "Symbol: " << in_symbol.getSymbol();
    cout << " Freq: " << in_symbol.getFrequency()<< endl;
    ofs<<in_symbol.getSymbol()<< " Freq: " << in_symbol.getFrequency()<< endl;
}


int main () {
    FILE * pFile;
    int c;
    int n = 0;
    pFile = fopen("text.dat","rb"); // audio.dat, binary.dat, image.dat, text.dat
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
                frequency[ c ] ++; //把对应ASSICII码处的值加一，frequency是char类型的,人家就这么用，记得转换就行
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
                        symbol.insert( it, newSymbol );  //插在大的位置
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
    
    printf( "\n\n" );

    ofstream ofs;
    ofs.open("SandFtext.txt",ios::out); // SandFaudio.txt, SandFbinary.txt, SandFimage.txt, SandFtext.txt
    for_each( symbol.begin(), symbol.end(), bind2nd(ptr_fun(printSymbol), ofs));
    ofs.close();
    return 0;
}
