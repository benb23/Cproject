#include "MainFuncstionsHeader.h"
#include "Q5&Q6Header.h"
#include "memoryFuncstionsHeader.h"

void convertCompressedImageToPGM(char * compressed_file_name, char * pgm_file_name)
{
	FILE * compFp; // the compressed file
	FILE * resFp;  // the file we return
	unsigned short rows, cols;
	int maxBits, numOfPixels, compBytesNum;
	int i, k, j, temp;
	BYTE max_gray_level;
	BYTE *tempByte, *resArr, *compArr; // arrays we use to uncompreesed
	BYTE tempInput, ch2Print;
	int intChar2print;


	// open the commpressed PGM image
	compFp = fopen(compressed_file_name, "rb");
	isOpenFileSucceed(compFp);



	// read the image info
	fread(&cols, sizeof(unsigned short), 1, compFp);
	fread(&rows, sizeof(unsigned short), 1, compFp);
	fread(&max_gray_level, sizeof(BYTE), 1, compFp);


	maxBits = (int)(log2((double)max_gray_level)) + 1;							// max bits number to compress
	numOfPixels = cols*rows;													// The number of the total pixels
	compBytesNum = getNumbersOfBytesAcoording2MaxBits(maxBits, numOfPixels);		// The total bytes number of 
	compArr = (BYTE *)malloc((compBytesNum * EIGHT_BITS + 1) * sizeof(BYTE));	// array that will cotain the pixels matrix
	testMemoryAllocation(compArr);
	resArr = (BYTE *)calloc(numOfPixels * EIGHT_BITS + 1, sizeof(BYTE));		// the compress bits array
	testMemoryAllocation(resArr);
	tempByte = (BYTE *)malloc((EIGHT_BITS + 1) * sizeof(BYTE));						// temp byte array
	testMemoryAllocation(tempByte);


	//read the compressed image into bits arrays
	k = 0;
	for (i = 0; i < compBytesNum; i++)
	{
		fread(&tempInput, sizeof(BYTE), 1, compFp);
		temp = (int)tempInput;
		temp = converDecimalToBinary(temp);
		binIntToBinStr(temp, &compArr[k], EIGHT_BITS, TRUE);
		k += EIGHT_BITS;
	}

	// fill back the uncompreesed array
	for (i = 0; i < numOfPixels; i++)
	{
		for (k = 0; k < (EIGHT_BITS - maxBits); k++)
		{
			resArr[i*EIGHT_BITS + k] = '0';
		}
		for (j = 0; j < maxBits; j++)
		{
			resArr[i*EIGHT_BITS + (EIGHT_BITS - maxBits) + j] = compArr[i*maxBits + j];
		}
	}


	fclose(compFp);

	// open new file to write the new PGM image
	resFp = fopen(pgm_file_name, "w");
	isOpenFileSucceed(resFp);


	fprintf(resFp, "P2\n");
	fprintf(resFp, "%u ", cols);
	fprintf(resFp, "%u\n", rows);
	fprintf(resFp, "%u\n", 255);

	for (i = 0; i < numOfPixels; i++)
	{// write the compressed matrix to the bin file
		intChar2print = convertStr2Int(EIGHT_BITS, (resArr + i * EIGHT_BITS));
		intChar2print = convertBinaryToDecimal(intChar2print);
		ch2Print = (BYTE)intChar2print;
		ch2Print = (ch2Print * 255) / (max_gray_level);
		fprintf(resFp, "%hhu ", ch2Print);

		if ((i + 1) % cols == 0)
			fprintf(resFp, "\n");
	}

	free(compArr);
	free(resArr);
	free(tempByte);
	fclose(resFp);
}