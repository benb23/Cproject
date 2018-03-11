#ifndef __Q3HEADER_H
#define __Q3HEADER_H

//funcstion that get a segment and convert it to a pos list
void convertSegmentToImgPosList(treeNodeListCell * segment, imgPosList * imgPosLst /*imgPos headPos*/);

//a funcation that make an emptey imgposlist
void makeEmptyImgPosList(imgPosList * segments);

// a funcstion that insert data to end of list
void insertDataToEndImgPosList(imgPosList * segments, imgPos * segPos);

// a funcstion that insert a cell to end of list
void insertCellToEndList(imgPosList * segments, imgPosCell * tail);

//a funcsion that check is it is empty
BOOL isEmptyImgPosList(imgPosList * lst);

imgPosCell * createNewListCell(imgPos * segPos, imgPosCell * next, imgPosCell * prev);
#endif
