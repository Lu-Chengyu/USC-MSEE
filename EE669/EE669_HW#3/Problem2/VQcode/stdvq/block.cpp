#include<iostream>
#include<vector>

using namespace std;

vector <int> image;

void openfile(const char* filepath){
    int c;
    int n = 0;
    FILE * pFile;
    pFile = fopen(filepath,"rb"); 
    if (pFile==NULL) {
        perror ("Error opening file");
    } else {
        do {
            c = fgetc (pFile); 
            if ( c != EOF ) {
                image.push_back(c);
                n++;
                //cout<<n<<c<<endl;
            }
        } while (c != EOF);   
    }
    fclose (pFile);
}

void writetofile(const char* filepath,int blockheight, int blockwidth){
    int c;
    int n = 0;
    FILE * pFile;
    pFile = fopen(filepath,"wb"); 
    // for(int number=0;number<3;++number){
    for(int x = 0; x<(256/blockheight); ++x){
        for(int y =0; y<(256/blockwidth); ++y){
            for(int i =0; i<blockheight; ++i){
                for(int j = 0; j<blockwidth; ++j){
                    //fputc (image[(j+256*i+x*blockheight*256+y*blockwidth+number*65536)], pFile);
                    fputc (image[(j+256*i+x*blockheight*256+y*blockwidth)], pFile);
                    cout<<(j+256*i+x*blockheight*256+y*blockwidth)<<endl;
                }    
            }
        }
    }
    // }
    fclose (pFile);
}

int main(){
    
    openfile("../../../images/bike.raw");
    writetofile("./images/blockedbike64.raw", 8, 8);
    image.clear();
    openfile("../../../images/boat.raw");
    writetofile("./images/blockedboat64.raw", 8, 8);
    image.clear();
    openfile("../../../images/hat.raw");
    writetofile("./images/blockedhat64.raw", 8, 8);
    image.clear();
    openfile("../../../images/house.raw");
    writetofile("./images/blockedhouse64.raw", 8, 8);
    image.clear();
    openfile("../../../images/people.raw");
    writetofile("./images/blockedpeople64.raw", 8, 8);
    image.clear();
    openfile("../../../images/plane.raw");
    writetofile("./images/blockedplane64.raw", 8, 8);
    image.clear();
    // writetofile("./TrainingSet/TrainingImage64.raw", 8, 8);
    return 0;
}