#include "MainFuncstionsHeader.h"
#include "Q1Header.h"
#include "memoryFuncstionsHeader.h"

grayImage * readPGM(char * fname)
{
	grayImage * img;
	FILE * pgmFile;
	char version[4];
	unsigned int maxGray;
	unsigned int rows, cols;
	int i, j;

	pgmFile = fopen(fname, "r");
	isOpenFileSucceed(pgmFile);

	fgets(version, sizeof(version), pgmFile);

	// allocate the img
	img = (grayImage *)malloc(sizeof(grayImage));
	testMemoryAllocation(img);

	fscanf(pgmFile, "%u", &cols);                 //get the cols form the file
	fscanf(pgmFile, "%u", &rows);	  		      //get the rows form the file
	fscanf(pgmFile, "%u", &maxGray);              //get the maxGray value form the file

												  // alocate the memory for the row and cols (pixsels)
	img->pixels = (unsigned char **)malloc(rows * sizeof(unsigned char *));
	testMemoryAllocation(img->pixels);

	for (i = 0; i < rows; i++)
	{
		img->pixels[i] = (unsigned char *)malloc(cols * sizeof(unsigned char));
		testMemoryAllocation(img->pixels[i]);
	}
	img->cols = (unsigned short)cols;
	img->rows = (unsigned short)rows;

	for (i = 0; i < rows; i++)
	{// get the value of the pixels
		for (j = 0; j < cols; j++)
		{
			fscanf(pgmFile, "%hhu", &(img->pixels[i][j]));
		}
	}
	fclose(pgmFile);
	return img;
}

// The function cheak if the file is opened well
void isOpenFileSucceed(FILE * fp)
{
	if (fp == NULL)
	{
		printf("Oppening file EROR");
		exit(1);
	}
}// end isOpenFileSucceed

