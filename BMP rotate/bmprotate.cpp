#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int FXPT2DOT30;

typedef struct tagCIEXYZ
{
    FXPT2DOT30 ciexyzX ;
    FXPT2DOT30 ciexyzY ;
    FXPT2DOT30 ciexyzZ ;
}
CIEXYZ, * LPCIEXYZ ;

typedef struct tagCIEXYZTRIPLE {
    CIEXYZ ciexyzRed ;
    CIEXYZ ciexyzGreen ;
    CIEXYZ ciexyzBlue ;
}CIEXYZTRIPLE;


struct  tagBITMAPFILEHEADER{
    DWORD bfSize; 
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
};


struct tagBITMAPINFOHEADER{
    DWORD biSize;
    DWORD biWidth;
    DWORD biHeight;
    WORD biPlanes; 
    WORD biBitCount; 
    DWORD  biCompression; 
    DWORD  biSizeImage; 
    DWORD  biXPelsPerMeter; 
    DWORD  biYPelsPerMeter; 
    DWORD  biClrUsed; 
    DWORD  biClrImportant; 
};

struct Plus{ // for 32 bit pic
    DWORD        bV5RedMask;
    DWORD        bV5GreenMask;
    DWORD        bV5BlueMask;
    DWORD        bV5AlphaMask;
    DWORD        bV5CSType;
    CIEXYZTRIPLE bV5Endpoints;
    DWORD        bV5GammaRed;
    DWORD        bV5GammaGreen;
    DWORD        bV5GammaBlue;
    DWORD        bV5Intent;
    DWORD        bV5ProfileData;
    DWORD        bV5ProfileSize;
    DWORD        bV5Reserved;
};

WORD bfType;
tagBITMAPFILEHEADER srcHead;
tagBITMAPINFOHEADER srcInfo;
Plus srcPlus;
int h,w,size;
int bytePerPixel;

int getDiff(tagBITMAPINFOHEADER & info)
{
    int DataSizePerline = (info.biWidth * info.biBitCount+31) / 8;
    DataSizePerline -= DataSizePerline % 4;
    return DataSizePerline - info.biWidth * bytePerPixel;
}

void rotate(const BYTE* src){
    int newH = w; //switch height and width
    int newW = h;

    FILE *f;
    f=fopen("dest.bmp","wb");
    tagBITMAPFILEHEADER newHead = srcHead;
    tagBITMAPINFOHEADER newInfo = srcInfo;
    Plus newPlus = srcPlus;

    newHead.bfSize = (DWORD)(newHead.bfSize);
    newInfo.biHeight = (DWORD)newH;
    newInfo.biWidth = (DWORD)newW;
    int newDiff = getDiff(newInfo);
    newInfo.biSizeImage = (DWORD)((newInfo.biWidth * bytePerPixel + newDiff) * newInfo.biHeight);

	fwrite(&bfType,1, sizeof(WORD),f);
    fwrite(&newHead,1, sizeof(tagBITMAPFILEHEADER),f);
    fwrite(&newInfo,1, sizeof(tagBITMAPINFOHEADER),f);
    if (newInfo.biBitCount == 32){ //For 32bit pic
        fwrite(&newPlus, 1, sizeof(Plus), f);
    }

    BYTE* target = new BYTE[size * bytePerPixel];
    for (int i = 0; i< newH; i++)
        for (int j = 0; j < newW; j++)
        	for (int k = 0; k < bytePerPixel; k++)
            	*(target + (i * newW + j)*bytePerPixel+ k) = *(src + (j * w + newH - i - 1)*bytePerPixel + k);
        

    for (int i=0; i<newH; i++){
        fwrite(target + i * newW * bytePerPixel, bytePerPixel, newW, f);
        fseek(f, newDiff, SEEK_CUR);
    }

    fclose(f);
    delete []target;
}

int main(){
    FILE* f;
    f = fopen("src.bmp", "rb");
    if (f != NULL){
    	fread(&bfType, 1, sizeof(WORD), f);
        fread(&srcHead,1, sizeof(tagBITMAPFILEHEADER), f);
        fread(&srcInfo,1, sizeof(tagBITMAPINFOHEADER), f);
        if (srcInfo.biBitCount == 32){
            fread(&srcPlus, 1, sizeof(Plus), f);
        }
        h=srcInfo.biHeight;
        w=srcInfo.biWidth;
        size = w * h;
        bytePerPixel = srcInfo.biBitCount/8;

        BYTE *imgdata=new BYTE[size * bytePerPixel];
        int diff = getDiff(srcInfo);

        for (int i=0;i<h;i++){
            fread(imgdata + i * w * bytePerPixel, bytePerPixel, w, f);
            fseek(f, diff, SEEK_CUR); //Move pointer to "diff" bytes after current position
        }
        fclose(f);
        rotate(imgdata);
        delete []imgdata;
    }
    else{
    	cout << "Unable to open file!" << endl;
	}
}
