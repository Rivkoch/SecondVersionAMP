#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "Airport.h"
#include "General.h"


int	isSameAirport(const Airport* pPort1, const Airport* pPort2)
{
	if (!pPort1 || !pPort2)
		return 0;
	if (strcmp(pPort1->code, pPort2->code) == 0)
		return 1;

	return 0;
}

int	isAirportCode(const Airport* pPort1, const char* code)
{
	if (!pPort1)
		return 0;
	if (strcmp(pPort1->code, code) == 0)
		return 1;

	return 0;
}

void	initAirportNoCode(Airport* pPort)
{
	pPort->name = getStrExactName("Enter airport name");
	pPort->country = getStrExactName("Enter airport country");

}

int compareByName(const void * pPort1, const void * pPort2)
{
	const Airport* portA = (const Airport*)pPort1;
	const Airport* portB = (const Airport*)pPort2;

	return strcmp(portA->name, portB->name);
}

int compareByCountry(const void * pPort1, const void * pPort2)
{
	const Airport* portA = (const Airport*)pPort1;
	const Airport* portB = (const Airport*)pPort2;

	return strcmp(portA->country, portB->country);
}

int compareByIATACode(const void * pPort1, const void * pPort2)
{
	const Airport* portA = (const Airport*)pPort1;
	const Airport* portB = (const Airport*)pPort2;

	return strcmp(portA->code, portB->code);
}

void	printAirport(const Airport* pPort)
{
	printf("Airport name:%-20s\t", pPort->name);
	printf("Country: %-20s\t Code:%s\n", pPort->country, pPort->code);

}

void getAirportCode(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter airport code  - %d UPPER CASE letters\t", CODE_LENGTH);
		myGets(temp, MAX_STR_LEN);
		if (strlen(temp) != CODE_LENGTH)
		{
			printf("code should be %d letters\n", CODE_LENGTH);
			ok = 0;
		}
		else {
			for (int i = 0; i < 3; i++)
			{
				if (isupper(temp[i]) == 0)
				{
					printf("Need to be upper case letter\n");
					ok = 0;
					break;
				}
			}
		}
	} while (!ok);

	strcpy(code, temp);
}

void	freeAirport(Airport* pPort)
{
	free(pPort->name);
	free(pPort->country);
}

int readPort(FILE * fp, Airport * pPort)
{
	int nameLen, countryLen;

	if (fread(&nameLen, sizeof(int), 1, fp) != 1)
		return 0;

	pPort->name = (char*)malloc(nameLen * sizeof(char));
	if (!pPort->name)
		return 0;

	if (fread(pPort->name, sizeof(char), nameLen, fp) != nameLen)
		return 0;

	if (fread(&countryLen, sizeof(int), 1, fp) != 1)
		return 0;

	pPort->country = (char*)malloc(countryLen * sizeof(char));
	if (!pPort->country)
		return 0;

	if (fread(pPort->country, sizeof(char), countryLen, fp) != countryLen)
		return 0;

	if (fread(&pPort->code, sizeof(char), 3, fp) != 3)
		return 0;



	return 1;
}

int writePort(FILE * fp, Airport * pPort)
{
	int nameLen, countryLen, codeLen;
	nameLen = (int)(strlen(pPort->name) + 1);
	countryLen = (int)(strlen(pPort->country)+ 1 );
	codeLen = (int)(strlen(pPort->code) + 1);

	if (fwrite(&nameLen, sizeof(int), 1, fp) != 1)
		return 0;


	if (fwrite(pPort->name, sizeof(char), nameLen, fp) != nameLen)
		return 0;

	if (fwrite(&countryLen, sizeof(int), 1, fp) != 1)
		return 0;

	if (fwrite(pPort->country, sizeof(char), countryLen, fp) != countryLen)
		return 0;

	if (fwrite(&pPort->code, sizeof(char), codeLen, fp) != codeLen)
		return 0;



	return 1;
}