#include "MainFuncstionsHeader.h"
#include "Q5&Q6Header.h"
#include "memoryFuncstionsHeader.h"



void saveCompressed(char *file_name, grayImage *image, unsigned char max_gray_level)
{
	int i, j, k = 0;              // indexes
	unsigned char ** parallelImg; // parallel mat
	unsigned char newPixelValue;  // save the new value
	imgPos curPos;                // which pixels postiosn
	BYTE * arr, *temp, *resArr;   // arrays to use 
	BYTE ch2Print;
	int intChar2print, numOfPixels, maxBits;
	int currPixel, currPixelbin, newBytesNum;
	BYTE  curr, byteToPrint;
	FILE * fp2;


	maxBits = (int)(log2((double)max_gray_level)) + 1;							// max bits number to compress
	numOfPixels = image->cols*image->rows;										// The number of the total pixels
	newBytesNum = getNumbersOfBytesAcoording2MaxBits(maxBits, numOfPixels);		// The total bytes number of 
	arr = (BYTE *)malloc(numOfPixels * sizeof(BYTE));							// array that will cotain the pixels matrix
	testMemoryAllocation(arr);
	resArr = (BYTE *)calloc(newBytesNum * EIGHT_BITS + 1, sizeof(BYTE));		// the compress bits array
	testMemoryAllocation(arr);
	temp = (BYTE *)malloc((EIGHT_BITS + 1) * sizeof(BYTE));						// temp byte array
	testMemoryAllocation(arr);

	parallelImg = makeParallelImage(image->rows, image->cols);

	//convert the pixels matrix to an array with the new values 
	for (i = 0; i < image->rows; i++)
	{
		for (j = 0; j < image->cols; j++)
		{
			curPos[1] = i;
			curPos[0] = j;
			newPixelValue = calacTheNewMax(image, max_gray_level, curPos);
			updateTheNewVauleInTheMat(curPos, parallelImg, newPixelValue);

			arr[k] = parallelImg[i][j];
			k++;
		}
	}
	//end - convert to array and calculate new values

	// dealing the first pixel case
	currPixel = arr[0];
	currPixelbin = converDecimalToBinary(currPixel);


	//getBin(currPixel, resArr, maxBits);
	binIntToBinStr(currPixel, resArr, maxBits, FALSE);
	//end first pixel case

	for (i = 1; i < numOfPixels; i++)
	{ // creating the compressed bits array
		currPixel = arr[i];
		currPixelbin = converDecimalToBinary(currPixel);
		binIntToBinStr(currPixelbin, temp, maxBits, FALSE);
		strcat((char *)resArr, (char *)temp);

		if (i == numOfPixels)
		{// last pixel case
			binIntToBinStr(0, temp, (newBytesNum * EIGHT_BITS) % maxBits, FALSE);
			//getBin(0, temp, (newBytesNum * EIGHT_BITS) % maxBits);
			strcat((char *)resArr, (char *)temp);
		}// end last pixel case
	} // end compress bits array

	  //open binary file
	fp2 = fopen(file_name, "wb");
	isOpenFileSucceed(fp2);

	fwrite(&(image->cols), sizeof(unsigned short), 1, fp2);
	fwrite(&(image->rows), sizeof(unsigned short), 1, fp2);
	fwrite(&(max_gray_level), sizeof(BYTE), 1, fp2);

	for (i = 0; i < newBytesNum; i++)
	{// write the compressed matrix to the bin file
		intChar2print = convertStr2Int(EIGHT_BITS, resArr + i*EIGHT_BITS);
		intChar2print = convertBinaryToDecimal(intChar2print);
		ch2Print = (BYTE)intChar2print;
		fwrite(&ch2Print, sizeof(BYTE), 1, fp2);
	}// end writing bin file

	freeParallelMat(parallelImg, image->rows);
	fclose(fp2);
}// end saveCompressed

int getNumbersOfBytesAcoording2MaxBits(int maxBits, int pixelsNum)
{

	if (maxBits * pixelsNum % EIGHT_BITS == 0)
		return  maxBits * pixelsNum / EIGHT_BITS;
	else
		return  maxBits * pixelsNum / EIGHT_BITS + 1;

}

unsigned char calacTheNewMax(grayImage *image, unsigned char max_gray_level, imgPos curPos)
{
	unsigned char newPixelValue;

	newPixelValue = (((image->pixels[curPos[1]][curPos[0]])*max_gray_level) / 255);

	return newPixelValue;
}

void updateTheNewVauleInTheMat(imgPos curPos, unsigned char **parallelImg, unsigned char newValue)
{
	parallelImg[curPos[1]][curPos[0]] = newValue;
}

// the function covert a decimal intiger to "binary intiger" 
int converDecimalToBinary(int n)
{
	int remainder;
	int binary = 0, i = 1;

	while (n != 0) {
		remainder = n % 2;
		n = n / 2;
		binary = binary + (remainder*i);
		i = i * 10;
	}
	return binary;
}

// the function gets a "bin int" and convert it to string of the bin
void binIntToBinStr(int num, BYTE * str, int numLen, BOOL unCompress)
{
	int i;

	str[numLen] = '\0';

	if (unCompress == TRUE)
	{

		for (i = 0; i < 8 - numLen; i++)
			str[i] = '0';
	}


	for (i = 0; i < numLen; i++)
	{
		if (num % 10 == 0)
			str[numLen - 1 - i] = '0';
		else // if (num % 10 == 1)
			str[numLen - 1 - i] = '1';
		num /= 10;
	}
}

//the function convers the bin string to  "binary int"
int convertStr2Int(int n, BYTE * str)
{
	int i;
	int bin = 0;

	for (i = 0; i<n; i++)
		bin = bin * 10 + (str[i] - '0');

	return bin;
}

//the function converts "binary int" to decimal int
int convertBinaryToDecimal(int n)
{
	int dec = 0, i = 0, remainder;

	while (n != 0)
	{
		remainder = n % 10;
		n /= 10;
		dec += remainder*pow(2, i);
		++i;
	}
	return dec;
}