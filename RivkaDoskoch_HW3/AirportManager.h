#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__

#include "Airport.h"

typedef enum
{
	notSorted, sortByName, sortByCountry, sortByIATACode, eNosOptions
} eSortOptions;

typedef struct
{
	Airport*	airportsArr;
	int			airportsCount;
	LIST		allCountries;
	eSortOptions eSort;
}AirportManager;

int			initManager(AirportManager* pManager);
int			addAirport(AirportManager* pManager);
void		addCountryToList(AirportManager* pManager, int index);
int			isSameCountry(Airport* arr, int size, char* country);
void		setAirport(Airport* pPort, AirportManager* pManager);

Airport*	findAirportByCode(const AirportManager* pManager, const char* code);
int			checkUniqeCode(const char* code, const AirportManager* pManager);

void		sortOptionsManu(AirportManager * pManager);
void		findPort(const AirportManager* pManager);

void		printAirports( AirportManager* pManager);
void		printCountry( void* pCoutry);
void		freeManager(AirportManager* pManager);

int			readManagerFromBFile(const char* fileName, AirportManager* pManager);
int			readPortsArrFromBFile(FILE* fp,  AirportManager* pManager);


int writeManagerToBFile(const char* fileName, AirportManager* pManager);
int writePortsArrFromBFile(FILE* fp, AirportManager* pManager);

#endif