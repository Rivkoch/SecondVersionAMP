#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"

typedef struct
{
	char*		name;
	char*		address;
	int			flightCount;
	/*Flight**	flightArr;*/
	LIST		flightsList;
}Company;

void	initCompany(Company* pComp);
char*	getCompanyAddress();
int		addFlight(Company* pComp, const AirportManager* pManager);
void	printCompany(const Company* pComp);
void	printFlightsCount(const Company* pComp);
void	sortLstByDate(Company* pComp);
void	printFlightArr(const LIST* lst, int size);

void	freeCompany(Company* pComp);

char*	getParam(const char* msg);
char*	fixAddressParam(char* param);
void	changeEvenWord(char* str);
char*	combineParams(char** strArr, int length, char* numStr);


int readCompanyFromTextFile(const char * pFName, Company * pComp);
int readFlightsFromTextFile(FILE* fp, Company* pComp);

int writeCompanyToTextFile(const char * pFName, Company * pComp);
int writeFlightsFromTextFile(FILE* fp, Company* pComp);

#endif

