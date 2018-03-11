#ifndef __PROJECTHEADER_H  
#define __PROJECTHEADER_H

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct _grayImage
{
	unsigned short rows, cols;
	unsigned char **pixels;
}grayImage;

typedef unsigned short imgPos[2];

typedef struct _treeNode
{
	imgPos position;
	struct _treeNodeListCell *next_possible_positions;
}treeNode;

typedef struct _treeNodeListCell
{
	treeNode *node;
	struct _treeNodeListCell *next;
}treeNodeListCell;

typedef struct _segment
{
	treeNode *root;
}Segment;

typedef struct _imgPosCell
{
	imgPos position;
	struct _imgPosCell *next, *prev;
}imgPosCell;

typedef struct _imgPosList
{
	imgPosCell *head, *tail;
}imgPosList;


typedef unsigned char BYTE;
#define EIGHT_BITS 8

typedef int BOOL;
#define FALSE 0
#define TRUE 1

#define FIRST_ROW 0
#define FIRST_COL 0

#define MAX_2 2
#define MAX_3 3

#define SUB_NIEGBOR 1
#define ROOT_NIEGBOR 0

#define MAIN_NIGHBORS 1
#define SUB_NIGHBORS 2

#define IS_NEIGHBOR '1'

#define UN_COMPRESS = 1

//Main project funcstions

//A funcstion which gets a txt file and creat a image out of the data insde
grayImage *readPGM(char *fname);                                                         //Question 1

//A funcsiton which find only one segments with all his nieghbors(in threshold gap) with a given start (specific pixel)
Segment findSingleSegment(grayImage *img, imgPos start, unsigned char threshold);        //Question 2

//A funcsiton which find all the segments form a given img 
int findAllSegments(grayImage *img, unsigned char threshold, imgPosList **segments);     //Question 3
																						 
//A funcstion which color all the pixel of each segments with the same "color" with a given formola
grayImage * colorSegments(imgPosList * segments, unsigned int size);                     //Question 4

//A funcsiton which get a image and a max gray level and creat a binFile with the new pixels value compressed 
void saveCompressed(char *file_name, grayImage *image, unsigned char max_gray_level);    //Question 5

//A funcsiton which get the compressed binFile and creat a PGM file by uncomprssing the binfile to the original pixeles values
void convertCompressedImageToPGM(char *compressed_file_name, char *pgm_file_name);       //Question 6

#endif