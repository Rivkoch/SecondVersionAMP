#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Company.h"
#include "AirportManager.h"
#include "General.h"

#define MANAGER_FILE_NAME "airport_authority.bin"
#define COMPANY_FILE_NAME "company.txt"

typedef enum
{
	eAddFlight, eAddAirport, ePrintCompany, ePrintAirports,
	ePrintFlightOrigDest, eSortPorts, eSearchPort, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Flight", "Add Airport",
								"PrintCompany", "Print all Airports",
								"Print flights between origin-destination",
								"Sort ports arr" , "Serch airport" };

#define EXIT			-1
int menu();

int main()
{
	AirportManager	manager;
	Company			company;
 

	if(!readManagerFromBFile(MANAGER_FILE_NAME, &manager))
		initManager(&manager);

	if (!readCompanyFromTextFile(COMPANY_FILE_NAME, &company))
		initCompany(&company);

	int option;
	int stop = 0;

	do
	{
		option = menu();
		switch (option)
		{
		case eAddFlight:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			break;


		case eAddAirport:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			break;

		case ePrintCompany:
			printCompany(&company);
			break;

		case ePrintAirports:
			printAirports(&manager);
			break;

		case ePrintFlightOrigDest:
			printFlightsCount(&company);
			break;

		case eSortPorts:
			sortOptionsManu(&manager);
			break;

		case eSearchPort:
			findPort(&manager);
			break;


		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	writeManagerToBFile(MANAGER_FILE_NAME, &manager);
	writeCompanyToTextFile(COMPANY_FILE_NAME, &company);

	freeManager(&manager);
	freeCompany(&company);
	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofOptions; i++)
		printf("%d - %s\n", i, str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}