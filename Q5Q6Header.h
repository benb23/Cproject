#ifndef __Q5ANDQ6HEADER_H
#define __Q5ANDQ6HEADER_H

// this funcstion tell us how many bytes we will need for the compressed pixels
int getNumbersOfBytesAcoording2MaxBits(int maxBits, int pixelsNum);

// this funcstion calc the new value of the pixel by the max gray level formola
unsigned char calacTheNewMax(grayImage *image, unsigned char max_gray_level, imgPos curPos);

// the function covert a decimal intiger to "binary intiger" 
int converDecimalToBinary(int n);

//the function converts "binary int" to decimal int
int convertBinaryToDecimal(int n);

// the function gets a "bin int" and convert it to string of the bin
void binIntToBinStr(int num, BYTE * str, int numLen, BOOL unCompress);

//update the new value in the parallelImg;
void updateTheNewVauleInTheMat(imgPos curPos, unsigned char **parallelImg, unsigned char newValue);

//the function convers the bin string to  "binary int"
int convertStr2Int(int n, BYTE * str);

#endif