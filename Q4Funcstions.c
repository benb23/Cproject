#include "MainFuncstionsHeader.h"
#include "Q4Header.h"
#include "memoryFuncstionsHeader.h"

grayImage * colorSegments(imgPosList * segments, unsigned int size)
{
	grayImage * img;
	imgPos * maxPos;  //bottom right corrner pixel postison
	int i, j;
	unsigned short row, col;
	imgPosCell * curr;

	curr = segments[0].head;
	img = (grayImage *)malloc(sizeof(grayImage));
	testMemoryAllocation(img);

	maxPos = findMaxPos(segments, size); //to get the row and cols of the image we look for the bottom right corrner pixel
    //iput the data we found form maxPos (+1 becuse we foun the postion of the pixels but it start form 0)
	img->cols = (*maxPos)[0] + 1;
	img->rows = (*maxPos)[1] + 1;


	col = (*maxPos)[0] + 1;
	row = (*maxPos)[1] + 1;
	//alocate memory for the pixels rows*cols
	img->pixels = (unsigned char **)malloc(row * sizeof(unsigned char *));
	testMemoryAllocation(img->pixels);


	for (i = 0; i < row; i++)
	{
		img->pixels[i] = (unsigned char *)malloc(col * sizeof(unsigned char));
		testMemoryAllocation(img->pixels[i]);
	}
	//end of the alocatsion of pixels
	for (i = 0; i < size; i++)
	{// loop which go over each segments
		curr = segments[i].head;
		while (curr != NULL)// loop which go over each nieghbor in the segments and update the new value
		{
			row = curr->position[1];
			col = curr->position[0];

			img->pixels[row][col] = i*255 / (size - 1);

			curr = curr->next;
		}// end of the while loop
		curr = segments[i].head->next;
	}// end of the for loop
	free(maxPos);
	return img;
}

imgPos * findMaxPos(imgPosList * segments, int size)
{
	int i = 0;
	imgPosCell * curr;
	imgPos *maxPos;

	maxPos = (imgPos *)malloc(sizeof(imgPos));
	testMemoryAllocation(maxPos);

	(*maxPos)[0] = segments[0].head->position[0];
	(*maxPos)[1] = segments[0].head->position[1];

	for (i = 0; i < size; i++)
	{
		curr = segments[i].head;
		while (curr != NULL)
		{
			if (curr->position[0] >= (*maxPos)[0])
				(*maxPos)[0] = curr->position[0];

			if (curr->position[1] >= (*maxPos)[1])
				(*maxPos)[1] = curr->position[1];

			curr = curr->next;
		}

	}
	return maxPos;
}