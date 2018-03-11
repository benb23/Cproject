#include "MainFuncstionsHeader.h"
#include "Q3Header.h"
#include "memoryFuncstionsHeader.h"


int findAllSegments(grayImage *img, unsigned char threshold, imgPosList **segments)
{
	Segment * seg;
	imgPos curPos;
	imgPosList * helper;
	unsigned char ** parallelImg;
	int i, j;
	int count = 0;

	// make new parallel img
	parallelImg = makeParallelImage(img->rows, img->cols);

	//allocating imgListPos *
	helper = *segments;
	helper = (imgPosList *)malloc(img->cols*img->rows * sizeof(imgPosList));
	testMemoryAllocation(helper);

	for (i = 0; i < img->rows; i++)
	{
		for (j = 0; j < img->cols; j++)
		{
			curPos[1] = i;
			curPos[0] = j;
			if (parallelImg[i][j] == '\0')
			{
				seg = allocateSegmentMemory(curPos);
				updateparallelImg(curPos, parallelImg);

				findSingleSegmentHelper(img, threshold, parallelImg, seg->root->next_possible_positions, curPos);

				
				makeEmptyImgPosList(&helper[count]);
				insertDataToEndImgPosList(&helper[count], &curPos); //insert head
				convertSegmentToImgPosList(seg->root->next_possible_positions, &helper[count]);
				freeSegment(seg);
				count++;


			}
		}
	}


	helper = (imgPosList*)realloc(helper, count * sizeof(imgPosList));
	testMemoryAllocation(helper);

	*segments = helper;

	freeParallelMat(parallelImg, img->rows);

	return count;
}

void convertSegmentToImgPosList(treeNodeListCell * segment, imgPosList * imgPosLst /*imgPos headPos*/)
{
	if (segment->next == NULL)
		return;
	else
	{
		insertDataToEndImgPosList(imgPosLst, &segment->node->position);
		convertSegmentToImgPosList(segment->node->next_possible_positions, imgPosLst);
		convertSegmentToImgPosList(segment->next, imgPosLst);
	}// end if - create the rest of the neighbo
}

void makeEmptyImgPosList(imgPosList * segments)
{
	segments->head = segments->tail = NULL;
}

void insertDataToEndImgPosList(imgPosList * segments, imgPos * segPos)
{
	imgPosCell *newTail;
	newTail = createNewListCell(segPos, NULL, NULL);
	insertCellToEndList(segments, newTail);
}

imgPosCell * createNewListCell(imgPos * segPos, imgPosCell * next, imgPosCell * prev)
{
	imgPosCell * res;
	res = (imgPosCell *)malloc(sizeof(imgPosCell));
	testMemoryAllocation(res);
	res->position[0] = (*segPos)[0];
	res->position[1] = (*segPos)[1];
	res->next = next;
	res->prev = prev;
	return res;
}

void insertCellToEndList(imgPosList * segments, imgPosCell * tail)
{
	if (isEmptyImgPosList(segments) == TRUE)
	{
		tail->next = tail->prev = NULL;
		segments->head = segments->tail = tail;
	}
	else
	{
		tail->next = NULL;
		tail->prev = segments->tail;
		segments->tail->next = tail;
		segments->tail = tail;
	}
}

BOOL isEmptyImgPosList(imgPosList * lst)
{
	if (lst->head == NULL)
		return TRUE;
	else
		return FALSE;
}