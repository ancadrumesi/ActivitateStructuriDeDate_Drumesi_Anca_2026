#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pilot Pilot;
struct Pilot
{
	int id;
	float greutate;
	char* echipa;
	int nrMembri;
};

typedef struct Nod Nod;
struct Nod
{
	Nod* stanga; 
	Nod* dreapta;
	Pilot info;
};

Pilot citirePilotDinFisier(FILE* file)
{

}


int main()
{

	return 0;
}