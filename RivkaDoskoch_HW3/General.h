#ifndef __GENERAL__
#define __GENERAL__

#include "List.h"


//macro to close file and return 0/1
#define F_CLOSE(fp , num)	{fclose(fp);\
							 return num;}

#define MAX_STR_LEN 255
#define CODE_LENGTH 3

char*	getStrExactName(const char* msg);
char*	myGets(char* buffer, int size);
char*	getDynStr(char* str);
char**	splitCharsToWords(char* str, int* pCount, int* pTotalLength);
void	swapFlightsLst( NODE* a,  NODE* b);
void	generalArrayFunction(const void* arr, int size, int typeSize, void((*f)(void* element)));
char*	myGetsF(char* buffer, int size, FILE* fp);
#endif

