#pragma once
#ifndef __FLIGHT__
#define __FLIGHT__

#include "AirportManager.h"
#include "Date.h"
#include "General.h"
#include "List.h"

typedef struct
{
	char		originCode[CODE_LENGTH + 1];
	char		destCode[CODE_LENGTH + 1];
	float		price;
	Date		date;
}Flight;

void		initFlight(Flight* pFlight, const AirportManager* pManager);
int			isFlightInRoute(const Flight* pFlight, const char* codeSource, const char* codeDest);
void		printFlight(const Flight* pFlight);
float		getFlightPrice();
Airport*	setAiportToFlight(const AirportManager* pManager, const char* msg);
int			countFlightsInRoute(const LIST* pList, const char* codeSource, const char* codeDest);

void		freeFlight(Flight* pFlight);

int			readFlight(FILE* fp, Flight* flight);
int			writeFlight(FILE * fp, Flight * flight);

#endif
