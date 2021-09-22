#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AirportManager.h"

int	initManager(AirportManager* pManager)
{
	printf("-----------  Init airport Manager\n");
	pManager->airportsCount = 0;
	pManager->airportsArr = NULL;

	int count = 0;
	do {
		printf("How many airport?\t");
		scanf("%d", &count);
	} while (count < 0);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	if (count == 0)
		return 1;

	pManager->airportsArr = (Airport*)malloc(count * sizeof(Airport));
	if (!pManager->airportsArr)
		return 0;

	L_init(&(pManager->allCountries));
	for (int i = 0; i < count; i++)
	{
		setAirport(&pManager->airportsArr[i], pManager);
		pManager->airportsCount++;


		addCountryToList(pManager, i);

	}

	return 1;
}

void addCountryToList(AirportManager* pManager, int index)
{
	//list without duplicate countryes
	char* country = pManager->airportsArr[index].country;
	if (index == 0 || !isSameCountry(pManager->airportsArr, index, country))
		L_insert(&pManager->allCountries.head, country);
}

int		isSameCountry(Airport* arr, int size, char* country)
{
	for (int i = 0; i < size; i++)
	{
		char* current = arr[i].country;
		if (strcmp(current, country) == 0)
			return 1;
	}

	return 0;
}

int	addAirport(AirportManager* pManager)
{
	pManager->airportsArr = (Airport*)realloc(pManager->airportsArr, (pManager->airportsCount + 1) * sizeof(Airport));
	if (!pManager->airportsArr)
		return 0;


	setAirport(&pManager->airportsArr[pManager->airportsCount], pManager);
	addCountryToList(pManager, pManager->airportsCount);

	pManager->airportsCount++;

	

	return 1;
}

void  setAirport(Airport* pPort, AirportManager* pManager)
{
	while (1)
	{
		getAirportCode(pPort->code);
		if (checkUniqeCode(pPort->code, pManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	initAirportNoCode(pPort);
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
	for (int i = 0; i < pManager->airportsCount; i++)
	{
		if (isAirportCode(&pManager->airportsArr[i], code))
			return &pManager->airportsArr[i];
	}
	return NULL;
}

int checkUniqeCode(const char* code, const AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager, code);

	if (port != NULL)
		return 0;

	return 1;
}

void sortOptionsManu(AirportManager * pManager)
{
	int(*compare)(const void* port1, const void* port2) = NULL;
	printf("choose how you want to sort the airports array :\n");
	printf("1-sort by name\n");
	printf("2-sort by country\n");
	printf("3-sort by IATA code\n");
	printf("0-not sorted\n");
	scanf("%d", &pManager->eSort);
	switch (pManager->eSort)
	{
	case sortByName:
		compare = compareByName;
		break;


	case sortByCountry:
		compare = compareByCountry;
		break;


	case sortByIATACode:
		compare = compareByIATACode;
		break;

	case notSorted:
		break;

	default:
		printf("Wrong option\n");
		break;
	}

	if (compare != NULL)
		qsort(pManager->airportsArr, pManager->airportsCount, sizeof(Airport), compare);

}

void		findPort(const AirportManager* pManager)
{
	int(*compare)(const void* air1, const void* air2) = NULL;
	Airport* tmp = (Airport*)malloc(sizeof(Airport));

	switch (pManager->eSort)
	{
	case notSorted:
		printf("Array not sorted, cant search airport\n");
		free(tmp);
		break;
	
	case sortByName:
		tmp->name = getStrExactName("Enter airport name");
		compare = compareByName;
		break;

	case sortByCountry:
		tmp->country = getStrExactName("Enter airport country");
		compare = compareByCountry;
		break;

	case sortByIATACode:
		getAirportCode(tmp->code);
		compare = compareByIATACode;
		break;
	}

	if (compare != NULL)
	{
		Airport* thePort = bsearch(tmp, pManager->airportsArr, pManager->airportsCount, sizeof(Airport), compare);
		if (thePort != NULL)
		{
			printf("Port found: ");
			printAirport(thePort);
		}
		else
			printf("Airport not found.\n");
	}

	else
		printf("Array not sorted, cant search airport\n");


	free(tmp);
}

void	printAirports( AirportManager* pManager)
{
	printf("there are %d airports\n", pManager->airportsCount);
	
	generalArrayFunction((void*)pManager->airportsArr, pManager->airportsCount, sizeof(Airport), printAirport);

	printf("\nThe list of countries:\n");
	L_print(&pManager->allCountries, printCountry);
}

void	printCountry( void* pCountry)
{
	char* country = ( char*)pCountry;
	printf("%s ", country);
	printf("\n");
}

void	freeManager(AirportManager* pManager)
{

	generalArrayFunction((void*)pManager->airportsArr, pManager->airportsCount, sizeof(Airport), freeAirport);
	free(pManager->airportsArr);
	L_free(&pManager->allCountries);
}

int readManagerFromBFile(const char* fileName, AirportManager* pManager)
{
	printf("Reading manager from binary file...\n");

	FILE* fp;
	fp = fopen(fileName, "rb");
	if (!fp)
	{
		printf("Error open manager file\n");
		return 0;
	}
	   	 
	//fseek(fp, 0, SEEK_END); // sending to end of the file
	//if (ftell(fp) == 0)
	//{
	//	printf("File is empty\n");
	//	F_CLOSE(fp, 0);
	//}
	//else
	//	fseek(fp, 0, SEEK_SET);
	//
	//I SUBMITTED WIHT THIS PART. 
	///- NEED TO ASK - IF NOT NEEDED WHILE DELING WITH TEXT FILES

	
	////number of airports
	if (fread(&pManager->airportsCount, sizeof(int), 1, fp) != 1)
		F_CLOSE(fp, 0);

	pManager->airportsArr = (Airport*)malloc(pManager->airportsCount * sizeof(Airport));
	if (!(pManager->airportsArr))
		F_CLOSE(fp, 0);

	// the way ports are sorted
	if (fread(&pManager->eSort, sizeof(int), 1, fp) != 1)
		F_CLOSE(fp, 0);

	//reading the airports array
	if (!readPortsArrFromBFile(fp, pManager))
		F_CLOSE(fp, 0);


	printf("Done: %d airports added successfuly\n", pManager->airportsCount);
	printf("\n");
	F_CLOSE(fp, 1);

}

int readPortsArrFromBFile(FILE* fp,  AirportManager* pManager)
{
	L_init(&pManager->allCountries);

	for (int i = 0; i < pManager->airportsCount; i++)
	{
		if (!readPort(fp, &pManager->airportsArr[i]))
			return 0;

		addCountryToList(pManager, i);


	}
	return 1;
}

int writeManagerToBFile(const char* fileName, AirportManager* pManager)
{
	printf("Writing manager from binary file...\n");

	FILE* fp;
	fp = fopen(fileName, "wb");
	if (!fp)
	{
		printf("Error open manager file\n");
		return 0;
	}


	////number of airports
	if (fwrite(&pManager->airportsCount, sizeof(int), 1, fp) != 1)
		F_CLOSE(fp, 0);

	// the way ports are sorted
	if (fwrite(&pManager->eSort, sizeof(int), 1, fp) != 1)
		F_CLOSE(fp, 0);

	//reading the airports array
	if (!writePortsArrFromBFile(fp, pManager))
		F_CLOSE(fp, 0);


	printf("Done: %d airports saved successfuly\n", pManager->airportsCount);
	printf("\n");
	F_CLOSE(fp, 1);

}

int writePortsArrFromBFile(FILE* fp, AirportManager* pManager)
{

	for (int i = 0; i < pManager->airportsCount; i++)
	{
		if (!writePort(fp, &pManager->airportsArr[i]))
			return 0;


	}
	return 1;
}