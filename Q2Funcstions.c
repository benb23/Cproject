#include "MainFuncstionsHeader.h"
#include "Q2Header.h"
#include "memoryFuncstionsHeader.h"

//The function is getting grayImage, star position and threshold
//The function return a Segment of the grayImage according the treshold, the Segment root is the start position pixel 
Segment findSingleSegment(grayImage *img, imgPos start, unsigned char threshold)
{
	Segment * resSegment;			//	result segment
	treeNodeListCell * listRoot;	//	neighbors ROOT MAIN LIST
	unsigned char ** parallelImg;	//	parallel img to sing the pixels thats already in the segment
	resSegment = allocateSegmentMemory(start);	// Allocating memory to the resSegment from root of the start posotion


	listRoot = resSegment->root->next_possible_positions;

	parallelImg = makeParallelImage(img->rows, img->cols);		 // create the parallel img
	updateparallelImg(start, parallelImg);						// update the parallelImg in the start position

	findSingleSegmentHelper(img, threshold, parallelImg, listRoot, start);	// recursive function thats creat the SUB LIST NIEGHBORS

	freeParallelMat(parallelImg, img->rows);	// free parallel matrix memory aloocation

	return *resSegment;
}
// end findSingleSegment function

void findSingleSegmentHelper(grayImage *img, unsigned char threshold, unsigned char ** parallelImg, treeNodeListCell * listRoot, imgPos start)
{
	if (listRoot->next == NULL)
		return;
	else
	{
		if (listRoot->node == NULL)
		{// Create the main segment ROOT NEIGHBORS
			makeSubNirghborsList(start, start, img, threshold, parallelImg, listRoot);
			findSingleSegmentHelper(img, threshold, parallelImg, listRoot, start);
		}// end if - create ROOT NIEGBORS
		else
		{// create the rest of the neighbors
			makeSubNirghborsList(start, listRoot->node->position, img, threshold, parallelImg, listRoot);
			findSingleSegmentHelper(img, threshold, parallelImg, listRoot->node->next_possible_positions, start);
			findSingleSegmentHelper(img, threshold, parallelImg, listRoot->next, start);
		}// end if - create the rest of the neighbors
	}
}
// End findSingleSegmentHelper

Segment * allocateSegmentMemory(imgPos position)
{
	Segment * segment;
	segment = (Segment *)malloc(sizeof(Segment));
	testMemoryAllocation(segment);

	segment->root = (treeNode *)malloc(sizeof(treeNode));
	testMemoryAllocation(segment->root);

	segment->root->next_possible_positions = (treeNodeListCell *)malloc(sizeof(treeNodeListCell));
	testMemoryAllocation(segment->root->next_possible_positions);

	segment->root->position[0] = position[0];
	segment->root->position[1] = position[1];

	segment->root->next_possible_positions->node = (treeNode*)malloc(sizeof(treeNode));
	testMemoryAllocation(segment->root->next_possible_positions->node);
	segment->root->next_possible_positions->node = NULL;

	return segment;
}
// End allocateSegmentMemory

// The function is getting row and cols integers 
// The function  returns a new matrix
unsigned char ** makeParallelImage(unsigned short rows, unsigned short cols)
{
	unsigned char ** imgMatrix;
	int i, j;

	imgMatrix = (unsigned char **)calloc(rows, sizeof(unsigned char *));
	testMemoryAllocation(imgMatrix);

	for (i = 0; i < rows; i++)
	{
		imgMatrix[i] = (unsigned char *)calloc(cols, sizeof(unsigned char));
		testMemoryAllocation(imgMatrix[i]);
	}

	return imgMatrix;
}
// End makeParallelImageMatrix function

void makeSubNirghborsList(imgPos start, imgPos nieghborStart, grayImage *img, unsigned char threshold, unsigned char ** parallelImg, treeNodeListCell * listRoot)
{
	unsigned int i, j;			// for loops index
	unsigned short * maxRow;	// max row scan limit
	unsigned short * maxCol;	// max col scan limit
	imgPos  startScanPos;		// The start scan position  
	imgPos curPos;				// The current neighbor position
	treeNodeListCell * resNieghborList;	//nieghbors list

										// Allocate scan limits vars
	maxRow = (unsigned short *)malloc(sizeof(unsigned short));
	maxCol = (unsigned short *)malloc(sizeof(unsigned short));
	testMemoryAllocation(maxRow);
	testMemoryAllocation(maxCol);

	resNieghborList = listRoot;

	if (start != nieghborStart)
	{// Allocation for the first ROOT NIEGHBOR
		updateparallelImg(nieghborStart, parallelImg);
		resNieghborList->node->next_possible_positions = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
		testMemoryAllocation(resNieghborList->node->next_possible_positions);
		resNieghborList = resNieghborList->node->next_possible_positions;
	}// end if - first ROOT NIEGHBOR

	 // Initilize maxCol and maxRow
	*maxCol = img->cols - 1;
	*maxRow = img->rows - 1;

	getStartPosToSanImg(nieghborStart, startScanPos, maxRow, maxCol);

	// Update scan position according to the start scan position 
	*maxRow += startScanPos[1];
	*maxCol += startScanPos[0];

	// Scan and allocate the nieghbors
	for (i = startScanPos[1]; i < *maxRow; i++)
	{
		for (j = startScanPos[0]; j < *maxCol; j++)
		{
			curPos[1] = i;
			curPos[0] = j;
			if (parallelImg[i][j] == '\0')
			{// if the current position is NOT sign yet in the parallel img
				if (isNieghbor(img->pixels[start[1]][start[0]], img->pixels[i][j], threshold) == TRUE)
				{// if is nieghbor
					updateparallelImg(curPos, parallelImg);
					resNieghborList->next = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
					testMemoryAllocation(resNieghborList->next);
					resNieghborList->node = (treeNode*)malloc(sizeof(treeNode));
					testMemoryAllocation(resNieghborList->node);
					resNieghborList->node->position[0] = curPos[0];
					resNieghborList->node->position[1] = curPos[1];
					resNieghborList = resNieghborList->next;

				}// End if - is nieghbor
			}// End if - NOT sign yet in the parallel
		}// End Cols for loop
	}// End Rows for loop

	resNieghborList->next = NULL;
	free(maxCol);
	free(maxRow);
}
// End makeSubNirghborsList


BOOL isNieghbor(unsigned char startData, unsigned char curData, unsigned char threshold)
{
	if (abs((int)curData - (int)startData) < (int)threshold)
		return TRUE;
	else
		return FALSE;
}
// End isNieghbor


void getStartPosToSanImg(imgPos posibleNieghborPos, imgPos startScanPosition, unsigned short * maxRow, unsigned short * maxCol)
{
	unsigned short startRow = posibleNieghborPos[1];
	unsigned short startCol = posibleNieghborPos[0];
	BOOL isScaned = FALSE;

	if (isScaned == FALSE)
	{// the problematics scan cases
		if (startRow == FIRST_ROW)
		{// start position is in thr first row
			if (startCol == *maxCol || startCol == FIRST_COL)
			{
				if (startCol == *maxCol)
				{ // start position is in the last col - TOP_RIGHT_CORNER
					updateStartPosition(startScanPosition, startRow, startCol - 1);
					updateMaxRowAndCol(maxRow, maxCol, MAX_2, MAX_2);
				}
				else if (startCol == FIRST_COL)
				{// start position is in the first col - TOP_LEFT_CORNER
					updateStartPosition(startScanPosition, startRow, startCol);
					updateMaxRowAndCol(maxRow, maxCol, MAX_2, MAX_2);
				}
			}
			else
			{// start position is in the middle of the first row
				updateStartPosition(startScanPosition, startRow, startCol - 1);
				updateMaxRowAndCol(maxRow, maxCol, MAX_2, MAX_3);
			}
			isScaned = TRUE;	//problematic case is scaned
		}
		else if (startRow == *maxRow)
		{// start position is in the last row
			if (startCol == *maxCol || startCol == FIRST_COL)
			{
				if (startCol == *maxCol)
				{ // start position is in the last col - BOTTOM_RIGHT_CORNER
					updateStartPosition(startScanPosition, startRow - 1, startCol - 1);
					updateMaxRowAndCol(maxRow, maxCol, MAX_2, MAX_2);
				}
				else if (startCol == FIRST_COL)
				{// start position is in the first col - BOTTOM_LEFT_CORNER
					updateStartPosition(startScanPosition, startRow - 1, startCol);
					updateMaxRowAndCol(maxRow, maxCol, MAX_2, MAX_2);
				}
			}
			else
			{// start position is in the middle of the LAST row
				updateStartPosition(startScanPosition, startRow - 1, startCol - 1);
				updateMaxRowAndCol(maxRow, maxCol, MAX_2, MAX_3);
			}
			isScaned = TRUE;	//problematic case is scaned
		}//end if - last row
		else if (posibleNieghborPos[0] == FIRST_COL)
		{// start position is in the middle of the FIRST col
			updateStartPosition(startScanPosition, startRow - 1, startCol);
			updateMaxRowAndCol(maxRow, maxCol, MAX_3, MAX_2);
			isScaned = TRUE;	//problematic case is scaned
		}
		else if (posibleNieghborPos[0] == *maxCol)
		{// start position is in the middle of the LAST col
			updateStartPosition(startScanPosition, startRow - 1, startCol - 1);
			updateMaxRowAndCol(maxRow, maxCol, MAX_3, MAX_2);
			isScaned = TRUE;	//problematic case is scaned
		}
	}// end if - problematic scan cases

	if (isScaned == FALSE)
	{// Regular nieghbors scan case
		updateStartPosition(startScanPosition, startRow - 1, startCol - 1);
		updateMaxRowAndCol(maxRow, maxCol, MAX_3, MAX_3);
	}// end if - regular scan
}
// End getStartPosToSanImg

void updateStartPosition(imgPos startScanPosition, unsigned short startRow, unsigned short startCol)
{
	startScanPosition[0] = startCol;
	startScanPosition[1] = startRow;
}
// End updateStartPosition

void updateMaxRowAndCol(unsigned short * maxRow, unsigned short * maxCol, unsigned short maxRowVal, unsigned short maxColVal)
{
	*maxRow = maxRowVal;
	*maxCol = maxColVal;
}
// End updateMaxRowAndCol

void updateparallelImg(imgPos cur, unsigned char ** parallelImg)
{
	parallelImg[cur[1]][cur[0]] = IS_NEIGHBOR;
}
// End updateparallelImg