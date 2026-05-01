#define _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Florarie Florarie;
struct Florarie
{
	int id;
	char* denumire;
	float pret;
	int stoc;
};

typedef struct Nod Nod;
struct Nod
{
	Nod* stanga;
	Nod* dreapta;
	Florarie info;
};

Florarie citireFloareDinFisier(FILE* file)
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Florarie f1;
	aux = strtok(buffer, sep);
	f1.id = atoi(aux);
	aux = strtok(NULL, sep);
	f1.denumire = malloc(strlen(aux) + 1);
	strcpy_s(f1.denumire, strlen(aux) + 1, aux);
	f1.pret = atof(strtok(NULL, sep));
	f1.stoc = atoi(strtok(NULL, sep));
	return f1;
}

void afisareFlorarie(Florarie florarie)
{
	printf("Id: %d\n", florarie.id);
	printf("Floare: %s\n", florarie.denumire);
	printf("Pret: %.2f\n", florarie.pret);
	printf("Stoc: %d\n", florarie.stoc);
}

void adaugaFloareInArbore(Nod** radacina, Florarie floareNoua)
{
	if (*radacina)
	{
		if ((*radacina)->info.id < floareNoua.id)
		{
			adaugaFloareInArbore(&(*radacina)->dreapta, floareNoua);
		}

		if ((*radacina)->info.id > floareNoua.id)
		{
			adaugaFloareInArbore(&(*radacina)->stanga, floareNoua);
		}
	}
	else
	{
		Nod* nodNou = (Nod*)malloc(sizeof(Nod));
		nodNou->info = floareNoua;
		nodNou->stanga = NULL;
		nodNou->dreapta = NULL;
		*radacina = nodNou;
	}
}

void* citireArboreDeMasiniDinFisier(const char* numeFisier)
{
	Nod* radacina = NULL;
	FILE* file = fopen(numeFisier, "r");
	while (!feof(file))
	{
		adaugaFloareInArbore(&radacina, citireFloareDinFisier(file));
	}
	fclose(file);
	return radacina;
}

void afisareFloriDinArborePreordine(Nod* radacina)
{
	if (radacina)
	{
		afisareFlorarie(radacina->info);
		afisareFloriDinArborePreordine(radacina->stanga);
		afisareFloriDinArborePreordine(radacina->dreapta);
	}
}

void afisareFloriDinArboreInordine(Nod* radacina)
{
	if (radacina)
	{
		afisareFloriDinArboreInordine(radacina->stanga);
		afisareFlorarie(radacina->info);
		afisareFloriDinArboreInordine(radacina->dreapta);
	}
}

void dezalocareArbore(Nod** radacina)
{
	if (*radacina) 
	{
		dezalocareArbore(&(*radacina)->stanga);
		dezalocareArbore(&(*radacina)->dreapta);
		free((*radacina)->info.denumire);
		free(*radacina);
		*radacina = NULL;
	}
}


int main()
{
	Nod* radacina = citireArboreDeMasiniDinFisier("florarie_arbore.txt");
	afisareFloriDinArboreInordine(radacina);

	dezalocareArbore(&radacina);
	printf("dupa dezalocare\n");
	afisareFloriDinArboreInordine(radacina);

	return 0;
}