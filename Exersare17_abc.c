#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Seriale Seriale;
struct Seriale
{
	int id; 
	int nrSezoane;
	char* numeSerial;
	char* personaj;
	float rating;
};

typedef struct Nod Nod;
struct Nod
{
	Seriale info;
	Nod* stanga;
	Nod* dreapta;
};

Seriale citireSerialDinFisier(FILE* file)
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, sep);
	char* aux;
	Seriale s;
	aux = strtok(buffer, sep);
	s.id = atoi(aux);
	s.nrSezoane = atoi(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	s.numeSerial = malloc(strlen(aux) + 1);
	strcpy_s(s.numeSerial, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	s.personaj = malloc(strlen(aux) + 1);
	strcpy_s(s.personaj, strlen(aux) + 1, aux);
	s.rating = atof(strtok(NULL, sep));
	return s;
}

void afisareSerial(Seriale serial)
{
	printf("Id: %d", serial.id);
	printf("Numar sezoane: %d", serial.nrSezoane);
	printf("Nume serial: %s", serial.numeSerial);
	printf("Personaj: %s", serial.personaj);
	printf("Rating: %.2f", serial.rating);
}

void inserareSerialInArbore(Nod** radacina, Seriale serialNou)
{
	if (*radacina)
	{
		if ((*radacina)->info.id < serialNou.id)
		{
			inserareSerialInArbore(&(*radacina)->dreapta, serialNou);
		}

		if ((*radacina)->info.id > serialNou.id)
		{
			inserareSerialInArbore(&(*radacina)->stanga, serialNou);
		}
	}
	else
	{
		Nod* nodNou = (Nod*)malloc(sizeof(Nod));
		nodNou->info = serialNou;
		nodNou->stanga = NULL;
		nodNou->dreapta = NULL;
		*radacina = nodNou;
	}
}

Nod* citireArboreDeSerialeDinFisier(const char* numeFisier)
{
	Nod* radacina = NULL;
	FILE* file = fopen(numeFisier, "r");
	while (!feof(file))
	{
		inserareSerialInArbore(&radacina, citireSerialDinFisier(file));
	}
	fclose(file);
	return radacina;
}

void afisareSerialeDinArborePreordine(Nod* radacina)
{
	if (radacina)
	{
		afisareSerial(radacina->info);
		afisareSerialeDinArborePreordine(radacina->stanga);
		afisareSerialeDinArborePreordine(radacina->dreapta);
	}
}

void afisareSerialeDinArboreInordine(Nod* radacina)
{
	if (radacina)
	{
		afisareSerialeDinArboreInordine(radacina->stanga);
		afisareSerial(radacina->info);
		afisareSerialeDinArboreInordine(radacina->dreapta);
	}
}

void dezalocareArboreDeSeriale(Nod** radacina)
{
	if (*radacina)
	{
		dezalocareArboreDeSeriale(&(*radacina)->stanga);
		dezalocareArboreDeSeriale(&(*radacina)->dreapta);
		free((*radacina)->info.numeSerial);
		free((*radacina)->info.personaj);
		free((*radacina));
		*radacina = NULL;
	}
}

int main()
{
	Nod* radacina = citireArboreDeSerialeDinFisier("seriale.txt");
	afisareSerialeDinArborePreordine(radacina);

	return 0;
}