#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Company.h"
#include "Airport.h"
#include "General.h"

void	initCompany(Company* pComp)
{
	printf("-----------  Init Airline Company\n");
	pComp->name = getStrExactName("Enter company name");
	pComp->address = getCompanyAddress();
	L_init(&pComp->flightsList);
	pComp->flightCount = 0;
}

char*	getCompanyAddress()
{
	//0 - country, 1 - city, 2 - street
	char* paramsArr[3];
	char* paramsArrStr[3] = { "country","city","street" };
	int num;
	char numStr[MAX_STR_LEN];

	printf("Enter airline adrees:\n");
	for (int i = 0; i < 3; i++)
	{
		paramsArr[i] = getParam(paramsArrStr[i]);
		if (!paramsArr[i])
			return NULL;
	}
	printf("\nEnter house number:\t");
	scanf("%d", &num);
	sprintf(numStr, "%d", num);

	char* address = combineParams(paramsArr, 3, numStr);

	for (int i = 0; i < 3; i++)
		free(paramsArr[i]);

	return address;
}

int	addFlight(Company* pComp, const AirportManager* pManager)
{
	if (pManager->airportsCount < 2)
	{
		printf("There are not enoght airport to set a flight\n");
		return 0;
	}

	Flight* pFlight = (Flight*)calloc(1, sizeof(Flight));
	if (!pFlight)
		return 0;

	initFlight(pFlight, pManager);

	L_insert(&pComp->flightsList.head, pFlight);
	
	if (pComp->flightCount >= 1)
		sortLstByDate(pComp);

	pComp->flightCount++;
	return 1;
}

// Bubble sort flights linked list 
void sortLstByDate(Company* pComp)
{
	int swapped;
	struct node* beginning = pComp->flightsList.head.next;
	NODE* temp;
	NODE* another = NULL;

	// Checking for empty list
	if (beginning == NULL)
		return;

	do
	{
		swapped = 0;
		temp = beginning;

		while (temp->next != another)
		{
			const Flight* flight1 = (const Flight*)temp->key;
			const Flight* flight2 = (const Flight*)temp->next->key;

			//send to swap by years
			if (flight1->date.year > flight2->date.year)
			{
				swapFlightsLst(temp, temp->next);
				swapped = 1;
			}

			//send to swap by monthes
			if (flight1->date.month > flight2->date.month)
			{
				swapFlightsLst(temp, temp->next);
				swapped = 1;
			}

			//send to swap by days
			if (flight1->date.day > flight2->date.day)
			{
				swapFlightsLst(temp, temp->next);
				swapped = 1;
			}

			temp = temp->next;
		}
		another = temp;
	} while (swapped);
}

void printCompany(const Company* pComp)
{
	
	printf("Company %s\t Address:%s\n", pComp->name, pComp->address);
	printf("Has %d flights\n", pComp->flightCount);
	printFlightArr(&pComp->flightsList, pComp->flightCount);
}

void	printFlightsCount(const Company* pComp)
{
	char codeOrigin[CODE_LENGTH + 1];
	char codeDestination[CODE_LENGTH + 1];

	if (pComp->flightCount == 0)
	{
		printf("No flight to search\n");
		return;
	}

	printf("Origin Airport\n");
	getAirportCode(codeOrigin);
	printf("Destination Airport\n");
	getAirportCode(codeDestination);

	const char* org = (const char*)codeOrigin;
	const char* dest = (const char*)codeDestination;

	int count = countFlightsInRoute(&pComp->flightsList, org, dest);
	if (count != 0)
		printf("There are %d flights ", count);
	else
		printf("There are No flights ");

	printf("from %s to %s\n", codeOrigin, codeDestination);
}

void	printFlightArr(const LIST* lst, int size)
{
	if (!lst)
		return;

	NODE* temp = lst->head.next;

	for (temp = lst->head.next; temp; temp = temp->next)
		printFlight((Flight*)(temp->key));
}

void	freeCompany(Company* pComp)
{
	L_free(&pComp->flightsList);
	free(pComp->name);
	free(pComp->address);
}

char*	getParam(const char* msg)
{
	char temp[MAX_STR_LEN];
	char* param;

	printf("Enter %s:\t", msg);
	myGets(temp, MAX_STR_LEN);

	param = fixAddressParam(temp);

	return param;
}

char*	fixAddressParam(char* param)
{
	char* fixParamStr;
	char** wordsArray = NULL;
	int totalLength;
	int count;

	wordsArray = splitCharsToWords(param, &count, &totalLength);
	//add size for the '_' between words
	fixParamStr = (char*)calloc(totalLength + count, sizeof(char));
	if (!fixParamStr)
	{
		for (int i = 0; i < count; i++)
			free(wordsArray[i]);
		free(wordsArray);
		return NULL;
	}

	if (count == 1)
	{
		wordsArray[0][0] = toupper(wordsArray[0][0]);
		strcpy(fixParamStr, wordsArray[0]);
	}
	else {

		int len;
		for (int i = 0; i < count; i++)
		{
			len = (int)strlen(wordsArray[i]);
			if (len % 2 == 1) //odd number of letters
				changeEvenWord(wordsArray[i]);
			else {
				if (i == count - 1) //last but not only!
					wordsArray[i][0] = toupper(wordsArray[i][0]); //big
				else
					wordsArray[i][0] = tolower(wordsArray[i][0]); //small
			}
			strcat(fixParamStr, wordsArray[i]);
			if (i != count - 1) //not last
				strcat(fixParamStr, "_");
		}
	}
	for (int i = 0; i < count; i++)
		free(wordsArray[i]);
	free(wordsArray);

	return fixParamStr;

}

void	changeEvenWord(char* str)
{
	int index = 0;
	while (*str)
	{
		if (index % 2 == 0)
			*str = tolower(*str);
		else
			*str = toupper(*str);
		str++;
		index++;
	}
}

char*	combineParams(char** strArr, int length, char* numStr)
{
	char* address;
	//totalLength  - combine length + 3# + 1 '\0'
	size_t totalLength = 4 + strlen(numStr);
	for (int i = 0; i < length; i++)
		totalLength += strlen(strArr[i]);

	address = (char*)calloc(totalLength, sizeof(char));
	if (!address)
		return NULL;

	strcpy(address, strArr[0]);
	for (int i = 1; i < length; i++)
	{
		strcat(address, "#");
		strcat(address, strArr[i]);
	}
	strcat(address, "#");
	strcat(address, numStr);
	return address;
}

int readCompanyFromTextFile(const char * pFName, Company * pComp)
{
	printf("Reading company from text file...\n");

	FILE* fp = fopen(pFName, "r");
	if (!fp)
	{
		fclose(fp);
		printf("Company isn't exist.\n");
		return 0;
	}

	fseek(fp, 0, SEEK_END); // sending to end of the file
	if (ftell(fp) == 0)
	{
		fclose(fp);
		printf("File is empty.\n");
		return 0;
	}
	else
		fseek(fp, 0, SEEK_SET);

	char name[MAX_STR_LEN];
	char add[MAX_STR_LEN];
	
	do {
		myGetsF(name, MAX_STR_LEN, fp);
	} while (strlen(name) < 2);
	pComp->name = getDynStr(name);


	do {
		myGetsF(add, MAX_STR_LEN, fp);
	} while (strlen(add) < 2);
	pComp->address = getDynStr(add);


	//number of flights
	fscanf(fp, "%d", &pComp->flightCount);
	if (!pComp->flightCount)
		printf("Done: company has no flights\n");
	else
	{
		L_init(&pComp->flightsList);


		//reading flights and set into list
		if (!readFlightsFromTextFile(fp, pComp))
		{
			printf("Can't read flights.\n");
			F_CLOSE(fp, 0);

		}
	}
	
	printf("Done: %d flights added successfuly\n", pComp->flightCount);
	printf("\n");
	F_CLOSE(fp, 1);

}

int readFlightsFromTextFile(FILE* fp, Company* pComp)
{
	NODE* pNode = &pComp->flightsList.head;
	for (int i = 0; i < pComp->flightCount; i++) 
	{
		Flight* flight = (Flight*)malloc(sizeof(Flight));
		if (!flight)
			return 0;

		//char ch = fgetc(fp);
		if (!readFlight(fp, flight))
			return 0;

		pNode = L_insert(pNode, flight);
		
	}

	return 1;
}

int writeCompanyToTextFile(const char * pFName, Company * pComp)
{
	printf("Reading company from text file...\n");

	FILE* fp = fopen(pFName, "w");
	if (!fp)
	{
		fclose(fp);
		printf("Company isn't exist.\n");
		return 0;
	}

	fprintf(fp, "%s\n", pComp->name);
	fprintf(fp, "%s\n", pComp->address);
	


	//number of flights
	fprintf(fp, "%d", pComp->flightCount);
	
	//writing flights 
	writeFlightsFromTextFile(fp, pComp);
		
	printf("Done: %d flights saved successfuly\n", pComp->flightCount);
	printf("\n");
	F_CLOSE(fp, 1);

}

int writeFlightsFromTextFile(FILE* fp, Company* pComp)
{
	NODE	*tmp;

	for (tmp = (&pComp->flightsList)->head.next; tmp; tmp = tmp->next )
	{

		if (!writeFlight(fp, (Flight*)tmp))
			return 0;


	}

	return 1;
}