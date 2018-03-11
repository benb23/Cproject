menuFuncsions: menuFuncsions.o memoryFuncstions.o  Q1Funcstions.o Q2Funcstions.o Q3Funcstions.o Q4Funcstions.o Q5Funcstions.o Q6Funcstions.o
	gcc menuFuncsions.o memoryFuncstions.o  Q1Funcstions.o Q2Funcstions.o Q3Funcstions.o Q4Funcstions.o Q5Funcstions.o Q6Funcstions.o -o project -lm
	
menuFuncsions.o: menuFuncsions.c menuHeader.h MainFuncstionsHeader.h Q1Header.h Q2Header.h Q3Header.h Q4Header.h Q5&Q6Header.h memoryFuncstionsHeader.h
	gcc -c menuFuncsions.c
	
memoryFuncsions.o: memoryFuncsions.c memoryFuncstionsHeader.h MainFuncstionsHeader.h
	gcc -c memoryFuncstionsHeader.c
	
Q1Funcstions.o: Q1Funcstions.c Q1Header.h MainFuncstionsHeader.h memoryFuncstionsHeader.h
	gcc -c Q1Funcstions.c

Q2Funcstions.o: Q2Funcstions.c Q2Header.h MainFuncstionsHeader.h memoryFuncstionsHeader.h
	gcc -c Q2Funcstions.c

Q3Funcstions.o: Q3Funcstions.c Q3Header.h MainFuncstionsHeader.h memoryFuncstionsHeader.h
	gcc -c Q3Funcstions.c

Q4Funcstions.o: Q4Funcstions.c Q4Header.h MainFuncstionsHeader.h memoryFuncstionsHeader.h
	gcc -c Q4Funcstions.c

Q5Funcstions.o: Q5Funcstions.c Q5&Q6Header.h MainFuncstionsHeader.h memoryFuncstionsHeader.h
	gcc -c Q5Funcstions.c 

Q6Funcstions.o: Q6Funcstions.c Q5&Q6Header.h MainFuncstionsHeader.h memoryFuncstionsHeader.h
	gcc -c Q6Funcstions.c 
