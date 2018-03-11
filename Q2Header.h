#ifndef __Q2HEADER_H
#define __Q2HEADER_H

//alocate memory funcstion for a segment
Segment * allocateSegmentMemory(imgPos position); 

//helper for the Q2 funcstion (recorsive)
void findSingleSegmentHelper(grayImage *img, unsigned char threshold, unsigned char ** parallelImg, treeNodeListCell * listRoot, imgPos start);

//a funcstion to mark who is allready a neighbor
void updateparallelImg(imgPos cur, unsigned char ** parallelImg);

//a funcstion thats make a parallel mat so we can remmber who is check or nieghbor allready
unsigned char ** makeParallelImage(unsigned short rows, unsigned short cols);

//a funcsion thats make the nieghbor list 
void makeSubNirghborsList(imgPos start, imgPos nieghborStart, grayImage *img, unsigned char threshold, unsigned char ** parallelImg, treeNodeListCell * listRoot);

//a fucnsotn thats tell us where to start scaning till where by where is the pixel 
void getStartPosToSanImg(imgPos posibleNieghborPos, imgPos startScanPosition, unsigned short * maxRow, unsigned short * maxCol);

//helper for getstartpostoscan
void updateMaxRowAndCol(unsigned short * maxRow, unsigned short * maxCol, unsigned short maxRowVal, unsigned short maxColVal);

//helper for getstartpostoscan
void updateStartPosition(imgPos startScanPosition, unsigned short startRow, unsigned short startCol);

//calc the gap betwin 2 pixsels (by the threshold) and tell us if they are nieghbor 
BOOL isNieghbor(unsigned char startData, unsigned char curData, unsigned char threshold);


#endif

