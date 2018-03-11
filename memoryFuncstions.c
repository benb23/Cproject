#include "MainFuncstionsHeader.h"
#include "memoryFuncstionsHeader.h"


void freeSegment(Segment * seg)
{
	freeSegmentHelper(seg->root->next_possible_positions);
	free(seg->root);
	free(seg);
}

void freeSegmentHelper(treeNodeListCell *  listRoot)
{
	if (listRoot->next == NULL)
		return;
	else
	{
		freeSegmentHelper(listRoot->node->next_possible_positions);
		freeSegmentHelper(listRoot->next);

		free(listRoot);
	}
}

void freeImgPosList(imgPosList * lst)
{
	freeImgPosListHelper(lst->head);
}

void freeImgPosListHelper(imgPosCell * root)
{
	if (root->next == NULL)
		return;
	else
		freeImgPosListHelper(root->next);

	free(root);
}

void freeParallelMat(unsigned char ** parallelimg, unsigned short rows)
{
	int i;

	for (i = rows; i < rows; i++)
		free(parallelimg[i]);

	free(parallelimg);
}

void testMemoryAllocation(void *ptr)
{
	if (ptr == NULL)
	{
		puts("Memory allocation error");
		exit(1);
	}
}
// End testMemoryAllocation