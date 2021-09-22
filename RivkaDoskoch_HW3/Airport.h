#ifndef __AIRPORT__
#define __AIRPORT__

#include "General.h"

typedef struct
{
	char*	name;
	char*	country;
	char	code[CODE_LENGTH + 1];
}Airport;

int		isSameAirport(const Airport* pPort1, const Airport* pPort2);
int		isAirportCode(const Airport* pPort1, const char* code);
void	initAirportNoCode(Airport* pPort);

int		compareByName(const void * pPort1, const void * pPort2);
int		compareByIATACode(const void * pPort1, const void * pPort2);
int		compareByCountry(const void * pPort1, const void * pPort2);

void	printAirport(const Airport* pPort);
void    getAirportCode(char* code);
void	freeAirport(Airport* pPort);

int		writePort(FILE * fp, Airport * pPort);
int		readPort(FILE* fp, Airport* pPort);
#endif