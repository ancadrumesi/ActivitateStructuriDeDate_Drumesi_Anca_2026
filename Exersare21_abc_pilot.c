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
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Pilot p;
	aux = strtok(buffer, sep);
	p.id = atoi(aux);
	aux = strtok(NULL, sep);
	p.greutate = atof(aux);
	aux = strtok(NULL, sep);
	if (aux)
	{
		p.echipa = (char*)malloc(strlen(aux) + 1);
		strcpy(p.echipa, aux);
	}
	aux = strtok(NULL, sep);
	p.nrMembri = atoi(aux);
	return p;
}

void afisarePilot(Pilot pilot)
{
	printf("Id: %d\n", pilot.id);
	printf("Greutate: %.2f\n", pilot.greutate);
	printf("Echipa: %s\n", pilot.echipa);
	printf("Numar membri: %d\n", pilot.nrMembri);
}

void inserarePilotInArbore(Nod** radacina, Pilot pilotNou)
{
	if (*radacina)
	{
		if ((*radacina)->info.id > pilotNou.id)
		{
			inserarePilotInArbore(&(*radacina)->stanga, pilotNou);
		}
		if ((*radacina)->info.id < pilotNou.id)
		{
			inserarePilotInArbore(&(*radacina)->dreapta, pilotNou);
		}
	}
	else
	{
		Nod* nodNou = (Nod*)malloc(sizeof(Nod));
		nodNou->stanga = NULL;
		nodNou->dreapta = NULL;
		nodNou->info = pilotNou;
		*radacina = nodNou;
	}
}

Nod* citireArboreDePilotiDinFisier(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(file))
	{
		inserarePilotInArbore(&radacina, citirePilotDinFisier(file));
	}
	fclose(file);
	return radacina;
}

void afisarePilotiDinArboreInordine(Nod* radacina)
{
	if (radacina)
	{
		afisarePilotiDinArboreInordine(radacina->stanga);
		afisarePilot(radacina->info);
		afisarePilotiDinArboreInordine(radacina->dreapta);
	}
}

Pilot getPilotById(Nod* radacina, int idCautat)
{
	if (radacina)
	{
		if (radacina->info.id = idCautat)
		{
			Pilot p = radacina -> info;
			p.echipa = (char*)malloc(strlen(radacina->info.echipa) + 1);
			strcpy(p.echipa, radacina->info.echipa);
			return p;
			
			if (radacina->info.id < idCautat)
				return getPilotById(radacina->dreapta, idCautat);
			if (radacina->info.id > idCautat)
				return getPilotById(radacina->stanga, idCautat);
		}
	}
	else
	{
		Pilot p;
		p.id = -1;
		return p;
	}
}

void dezalocareArbore(Nod** radacina)
{
	if (*radacina)
	{
		dezalocareArbore(&(*radacina)->stanga);
		dezalocareArbore(&(*radacina)->dreapta);
		free((*radacina)->info.echipa);
		free(*radacina);
		*radacina = NULL;
	}
}

int main()
{
	Nod* radacina = citireArboreDePilotiDinFisier("pilot.txt");
	afisarePilotiDinArboreInordine(radacina);
	afisarePilot(getPilotById(radacina, 1));
	dezalocareArbore(&radacina);
	printf("Arborele a fost dezalocat!");

	return 0;
}