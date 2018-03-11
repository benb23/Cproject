#include "MainFuncstionsHeader.h" 
#include "Q1Header.h"
#include "Q2Header.h"
#include "Q3Header.h"
#include "Q4Header.h"
#include "Q5&Q6Header.h"
#include "menuHeader.h"
#include "memoryFuncstionsHeader.h"


void main()
{
	int choice;
	char filename[250], compressedFilename[250], PGMFilename[250], binFile[250], newfilename[250];
	unsigned char * maxGrayLevel;
	int isFileLoaded = FALSE;
	int isAllSigmentsFound = FALSE;
	int notDone = FALSE;
	unsigned char threshold;
	grayImage * image1;
	grayImage * image2;
	imgPosList * segments;
	unsigned int size;

	//print the menu and ask for user choise
	printMenu();
	scanf("%d", &choice);

	// the while loop make sure thats the user will load a PGM file
	while (choice != 1 && isFileLoaded==FALSE)  
	{
		printf("You need to load an Image file first \n");
		printf("Please enter a PGM file name to read (remeber to add .pgm): ");
		scanf("%s", &filename);
		image1 = readPGM(filename);
		isFileLoaded = TRUE;
	}
	if (isFileLoaded == TRUE)
	{// print the menu again after the user loaded a PGM file
		printMenu();
		scanf("%d", &choice);
	}
	do
	{
		// activate the functions according the user choise from the menu
		switch (choice)
		{
			case 1:
			{// the user want to load a new PGM file
				if(isFileLoaded==TRUE)
					freeParallelMat(image1->pixels, image1->rows);
				printf("Please enter a PGM file name to read (remeber to add .pgm): ");
				scanf("%s", &filename);
				image1 = readPGM(filename);
				isFileLoaded = TRUE;
				printMenu();
				scanf("%d", &choice);
				break;
			}

			case 2:
			{// find all the segments
				//if (isFileLoaded == FALSE)
				//{// chaek if the user loaded a PGM file
				//	printf("You did'nt entered a PGM File or you enteresd a worng file please enter file name again: ");
				//	scanf("%s", &filename);
				//	isFileLoaded = TRUE;
				//	printMenu();
				//	scanf("%d", &choice);
				//}
				/*else
				{*/// asking for a threshold for the segments
					printf("Please Enter a threshold: ");
					scanf("%u", &threshold);
					size = (unsigned int)findAllSegments(image1, threshold, &segments);
					isAllSigmentsFound = TRUE;
					printMenu();
					scanf("%d", &choice);
					break;
				/*}*/
			}
			case 3:
			{// color all the segmets
				if (isAllSigmentsFound == FALSE  )
				{// cheaking if all the segments was found
					printf("Not all segments was found please re-enter a threshold: ");
					scanf("%u", &threshold);
					size = (unsigned int)findAllSegments(image1, threshold, &segments);
					isAllSigmentsFound = TRUE;
				}
				else
				{// color all the segmets
					image2 = colorSegments(segments, size);
					printMenu();
					scanf("%d", &choice);
				}
				break;
			}
			case 4:
			{//compress the colored file (after colorSegments was used)
				printf("Please Enter a name for the bin file (remeber to add .bin): ");
				scanf("%s", &binFile);
				printf("Please Enter a max gray level (between 0 to 127): ");
				scanf("%u", &maxGrayLevel);
				saveCompressed(/*the colored image*/binFile, image2, maxGrayLevel); //ñòéó 5
				printMenu();
				scanf("%d", &choice);
				break;
			}
			case 5:
			{//compress the origin file before the colorSegments 
				printf("Please enter a new file name and max gray level: ");
				scanf("%s", &newfilename);
				scanf("%u", &maxGrayLevel);
				saveCompressed(/*the original one before the color function*/newfilename, image1, maxGrayLevel);
				printMenu();
				scanf("%d", &choice);
				break;
			}
			case 6:
			{	// uncompress a compressed bin file and create a PGM file 
				printf("Please enter a bin file name (remeber to add .bin): ");
				scanf("%s", &compressedFilename);
				printf("Please enter the result PGM file name (rember to add .pgm): ");
				scanf("%s", &PGMFilename);
				convertCompressedImageToPGM(compressedFilename, PGMFilename); //ñòéó 6
				printMenu();
				scanf("%d", &choice);
				break;
			}
			case 7:
			{ // free all the memory allocations and exit from the program
				freeParallelMat(image1->pixels, image1->rows);
				freeParallelMat(image2->pixels, image2->rows);
				freeImgPosList(segments);

				printf("Good bye\n");
			
				notDone = TRUE;
				break;
			}
			default:
			{ // wrong user choise
				printf("Wrong Choice. Enter again\n");
				printMenu();
				scanf("%d", &choice);
				break;
			}
		}
		
	} while (notDone == FALSE);
}
	void printMenu()
	{
		printf("\n");
		printf("#################################### MENU #####################################\n");
		printf("## Press 1 to  - Read an image file in PGM format		   	     ##\n");
		printf("## Press 2 to  - Find all segments					     ##\n");
		printf("## Press 3 to  - Color the segments					     ##\n");
		printf("## Press 4 to  - Save the colored image in a compressed format		     ##\n");
		printf("## Press 5 to  - Compress and save the original image in a compressed format ##\n");
		printf("## Press 6 to  - Convert a compressed image to PGM format		     ##\n");
		printf("## Press 7 to  - Free all the allocated memory and Exit			     ##\n");
		printf("###############################################################################\n");
		printf("Please enter your choise: ");
	}

