#ifndef __FREEHEADER_H
#define __FREEHEADER_H

//this fucnstion will free all the alocation memeory used in Q2 and Q3
void freeSegmentHelper(treeNodeListCell *  listRoot);

//this fucnstion will free all the alocation memeory used in Q2 and Q
void freeSegment(Segment * seg);

//this fucnstion will free all the alocation memeory used in  Q3
void freeImgPosList(imgPosList * lst);

//this fucnstion will free all the alocation memeory used in   Q3
void freeImgPosListHelper(imgPosCell * root);

//this fucnstion will free all the alocation memeory used in qustions with paralle mats
void freeParallelMat(unsigned char ** parallelimg, unsigned short rows);

//this funcsiton test if the allocations succsed
void testMemoryAllocation(void *ptr);

#endif