#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <math.h>

#define MAX_CHAR 256

using namespace std;

// store the input frequency
int  frequency[ MAX_CHAR ];
float  quantization[ MAX_CHAR ];

float MSE(){
    float mse = 0;
    for(int i =0; i<MAX_CHAR; ++i ){
        mse += pow((quantization[i]-i),2)*frequency[i];
    }
    return (mse/(65536.0*3.0));
}

float PSNR(){
    float psnr = 0;
    psnr = 10*(log10(pow(255,2)/MSE()));
    return psnr;
}

void init_centroid(int gapnumber){
    int i = 0, j = 255;
    int gap = (j-i+1)/gapnumber;
    int k = i;
    while(k<j){
        for(int l = 0; l<gap; ++l){
            quantization[k+l] = (k+gap/2);
        }
        k+=gap;
    }
}



void one_iteration(int gapnumber, float* quantizedValue){
    int i = 0, j = 255, k , l ,  gapnum = 0, temp, number;
    k = i;
    float tempmse;

    while(k<=j){
        quantizedValue[gapnum] = 0;
        number = 0;
        l=0;
        if(k!=0 && quantization[k-1]==-1){
            quantizedValue[gapnum]+=(k-1)*frequency[k-1];
            number+=frequency[k-1];
        }
        while((k+l+1)!=256 && quantization[k+l] == quantization[k+l+1]){
            quantizedValue[gapnum]+=(k+l)*frequency[k+l];
            number+=frequency[k+l];
            ++l;
        }
        quantizedValue[gapnum]+=(k+l)*frequency[k+l];
        number+=frequency[k+l];
        ++l;
        if((k+l)!=256 && quantization[k+l]==-1){
            quantizedValue[gapnum]+=(k+l)*frequency[k+l];
            number+=frequency[k+l];
            ++l;
        }
        quantizedValue[gapnum] /= number;
        k+=l;
        ++gapnum;
    }
   
    for(int m = 0; m<=j; ++m){
        tempmse = 99999;
        temp = 0;
        for(int n = 0; n<gapnumber; ++n){
            if(tempmse>pow((m- quantizedValue[n]),2)){
                tempmse=pow((m- quantizedValue[n]),2);
                temp = n;
            }else if(tempmse==pow((m- quantizedValue[n]),2)){
                temp = -1;
                break;
            }
        }
        if(temp == -1){
            quantization[m]=-1;
        }else{
            quantization[m]=quantizedValue[temp];
        }
    }
}

void openfile(const char* filepath){
    int c;
    int n = 0;
    FILE * pFile;
    pFile = fopen(filepath,"rb"); // "../images/plane.raw"bike.raw, boat.raw, hat.raw, house.raw, people.raw, plane.raw
    if (pFile==NULL) {
        perror ("Error opening file");
    } else {
        do {
            c = fgetc (pFile);
            if ( c != EOF ) {
                frequency[ c ] ++;
                printf( "%c", c );
            }
        } while (c != EOF);   
        fclose (pFile);
    }
}

void codebook(int gapnumber, float* quantizedValue){
    ofstream ofs;
    ofs.open("codebook.txt",ios::out);
    for( int i = 0; i< gapnumber; ++i) ofs<<"code:"<<quantizedValue[i] << "index:" << i<< endl;
    ofs.close();
}

void decodeImage(const char* filepath, const char* filepath1,int gapnumber, float* quantizedValue){
    int c;
    int n = 0;
    FILE * pFile, *qFile;
    pFile = fopen(filepath,"rb");
    qFile = fopen(filepath1,"wb"); 
    if (pFile==NULL) {
        perror ("Error opening file");
    } else {
        do {
            c = fgetc (pFile);
            if ( c != EOF ) {
                if(quantizedValue[c]>=(floor(quantizedValue[c])+0.5)) {
                    fputc(ceil(quantizedValue[c]), qFile);
                }
                else{
                    fputc(floor(quantizedValue[c]), qFile);
                }
            }
        } while (c != EOF);   
        fclose (pFile);
        fclose (qFile);
    }
}

void encodeImage(const char* filepath, const char* filepath1,int gapnumber, float* quantizedValue){
    int c;
    int n = 0;
    FILE * pFile, *qFile;
    pFile = fopen(filepath,"rb");
    qFile = fopen(filepath1,"wb"); 
    if (pFile==NULL) {
        perror ("Error opening file");
    } else {
        do {
            c = fgetc (pFile);
            if ( c != EOF ) {
                for(int i=0;i<gapnumber;++i){
                    if(quantization[ c ]==quantizedValue[i]) fputc(i, qFile);
                }
            }
        } while (c != EOF);   
        fclose (pFile);
        fclose (qFile);
    }
}

void historgam(const char* filepath, const char* filepath1,int gapnumber, float* quantizedValue){
    int c, d, frequent[gapnumber];
    int n = 0;
    FILE * pFile;
    pFile = fopen(filepath,"rb");
    ofstream ofs;
    ofs.open(filepath1,ios::out);
    if (pFile==NULL) {
        perror ("Error opening file");
    } else {
        int i;
        for ( i=0; i<gapnumber; i++ ) {
            frequent[ i ] = 0;
        }
        do {
            c = fgetc (pFile);
            if ( c != EOF ) {
                frequent[c]++;
            }
        } while (c != EOF);   
        for(int j =0 ; j<gapnumber;++j){
            ofs<<quantizedValue[j]<<","<<frequent[ j ]<<endl;
        }
        fclose (pFile);
        ofs.close();
    }
}

void entropy(const char* filepath,int gapnumber, float* quantizedValue)
{
    int c, d;
    int n = 0;
    float entropy=0, frequent[gapnumber];
    FILE * pFile;
    pFile = fopen(filepath,"rb");
    if (pFile==NULL) {
        perror ("Error opening file");
    } else {
        int i;
        for ( i=0; i<gapnumber; i++ ) {
            frequent[ i ] = 0; 
        }
        do {
            c = fgetc (pFile);
            if ( c != EOF ) {
                frequent[c]++;
            }
        } while (c != EOF);   
        for(int j =0 ; j<gapnumber;++j){
            if(frequent[j]!=0){
                entropy-=((frequent[j]/65536.0)*log2(frequent[j]/65536.0));
            }
        }
        fclose (pFile);
        cout<<"entropy:"<<entropy<<endl;
    }
    for (int i = 0; i < MAX_CHAR; ++i)
    {
    }
}

void PSNRForOne(const char* filepath){
    int c, d;
    int n = 0;
    float entropy=0, frequent[MAX_CHAR];
    FILE * pFile;
    pFile = fopen(filepath,"rb");
    if (pFile==NULL) {
        perror ("Error opening file");
    } else {
        int i;
        for ( i=0; i<MAX_CHAR; i++ ) {
            frequent[ i ] = 0; 
        }
        do {
            c = fgetc (pFile);
            if ( c != EOF ) {
                frequent[c]++;
            }
        } while (c != EOF);   
        fclose (pFile);
    }
    float mse = 0;
    for(int j =0; j<MAX_CHAR; ++j ){
        mse += pow((quantization[j]-j),2)*frequent[j];
    }
    mse/=65536.0;
    float psnr = 0;
    psnr = 10*(log10(pow(255,2)/mse));
    cout<<endl<<"psnr:"<<psnr;
}

int main () {
    
    int c, i;
    int n = 0;

    for ( i=0; i<MAX_CHAR; i++ ) {
        frequency[ i ] = 0;
    }

    openfile("../images/people.raw");
    cout << endl << endl;
    openfile("../images/bike.raw");
    cout << endl << endl;
    openfile("../images/boat.raw");

    // print the frequency information
    cout << endl << endl;
    
    for ( i=0; i<MAX_CHAR; i++ ) {
        if ( frequency[ i ] != 0 ) {
            printf( "%d, %c: %d\n", i, i, frequency[ i ] );
        }
    }

    for ( i=0; i<MAX_CHAR; i++ ) {
            quantization[ i ] = 0; 
    }

    int bitsnumber = 3; // 1, 3, 5

    vector<float> mse, psnr;
    int iteration = 0;
    int gapnumber = pow(2, bitsnumber);
    init_centroid(gapnumber);
    float quantizedValue[gapnumber];
    while(true){
        one_iteration(gapnumber, quantizedValue);
        mse.push_back(MSE());
        psnr.push_back(PSNR());
        if(iteration > 1 && fabs((mse[iteration-1]-mse[iteration])/mse[iteration])< 0.001){
            break;
        }
        ++iteration;
    }
    

    printf( "\n\n" );

    for( i = 0; i< gapnumber; ++i) cout<<quantizedValue[i]<<' ';

    printf( "\n\n" );

    for( i = 0; i< 256; ++i) cout<<quantization[i]<<' ';

    printf( "\n\n" );

    for(i = 0; i<mse.size();++i) cout<<mse[i]<<' ';

    printf( "\n\n" );

    for(i = 0; i<psnr.size();++i) cout<<psnr[i]<<' ';

    //codebook
    codebook(gapnumber, quantizedValue);

    encodeImage("../images/bike.raw","encodedbike.raw", gapnumber, quantizedValue);
    encodeImage("../images/boat.raw","encodedboat.raw", gapnumber, quantizedValue);
    encodeImage("../images/hat.raw","encodedhat.raw", gapnumber, quantizedValue);
    encodeImage("../images/house.raw","encodedhouse.raw", gapnumber, quantizedValue);
    encodeImage("../images/people.raw","encodedpeople.raw", gapnumber, quantizedValue);
    encodeImage("../images/plane.raw","encodedplane.raw", gapnumber, quantizedValue);

    decodeImage("encodedbike.raw", "decodedbike.raw", gapnumber, quantizedValue);
    decodeImage("encodedboat.raw", "decodedboat.raw", gapnumber, quantizedValue);
    decodeImage("encodedhat.raw", "decodedhat.raw", gapnumber, quantizedValue);
    decodeImage("encodedhouse.raw", "decodedhouse.raw", gapnumber, quantizedValue);
    decodeImage("encodedpeople.raw", "decodedpeople.raw", gapnumber, quantizedValue);
    decodeImage("encodedplane.raw", "decodedplane.raw", gapnumber, quantizedValue);

    historgam("encodedbike.raw", "historgambike.txt", gapnumber, quantizedValue);
    historgam("encodedboat.raw", "historgamboat.txt", gapnumber, quantizedValue);
    historgam("encodedhat.raw", "historgamhat.txt", gapnumber, quantizedValue);
    historgam("encodedhouse.raw", "historgamhouse.txt", gapnumber, quantizedValue);
    historgam("encodedpeople.raw", "historgampeople.txt", gapnumber, quantizedValue);
    historgam("encodedplane.raw", "historgamplane.txt", gapnumber, quantizedValue);

    printf( "\n\n" );

    entropy("encodedbike.raw", gapnumber, quantizedValue);
    entropy("encodedboat.raw", gapnumber, quantizedValue);
    entropy("encodedhat.raw", gapnumber, quantizedValue);
    entropy("encodedhouse.raw", gapnumber, quantizedValue);
    entropy("encodedpeople.raw", gapnumber, quantizedValue);
    entropy("encodedplane.raw", gapnumber, quantizedValue);

    printf( "\n\n" );

    PSNRForOne("../images/bike.raw");
    PSNRForOne("../images/boat.raw");
    PSNRForOne("../images/hat.raw");
    PSNRForOne("../images/house.raw");
    PSNRForOne("../images/people.raw");
    PSNRForOne("../images/plane.raw");

    return 0;
}