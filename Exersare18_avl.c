#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Serial Serial;
struct Serial
{
	int id;
	int nrSezoane;
	char* numeSerial;
	char* personaj;
	float rating;
};

typedef struct NodArbore NodArbore;
struct NodArbore
{
	Serial info;
	NodArbore* stanga;
	NodArbore* dreapta;
};

Serial citireSerialDinFisier(FILE* file)
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Serial s;
	aux = strtok(buffer, sep);
	s.id = atoi(aux);
	aux = strtok(NULL, sep);
	s.nrSezoane = atoi(aux);
	aux = strtok(NULL, sep);
	s.numeSerial = (char*)malloc(strlen(aux) + 1);
	strcpy_s(s.numeSerial, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	s.personaj = (char*)malloc(strlen(aux) + 1);
	strcpy_s(s.personaj, strlen(aux) + 1, aux);
	s.rating = atof(strtok(NULL, sep));
	return s;
}

void afisareSerial(Serial serial)
{
	printf("Id: %d\n", serial.id);
	printf("Nr sezoane: %d\n", serial.nrSezoane);
	printf("Nume serial: %s\n", serial.numeSerial);
	printf("Personaj: %s\n", serial.personaj);
	printf("Rating: %.2f\n", serial.rating);
}

int calculeazaInaltimeArbore(NodArbore* radacina)
{
	if (radacina == NULL)
	{
		return 0;
	}
	int inaltimeDreapta = calculeazaInaltimeArbore(radacina->dreapta);
	int inaltimeStanga = calculeazaInaltimeArbore(radacina->stanga);
	return 1 + max(inaltimeDreapta, inaltimeStanga);
}

void rotireStanga(NodArbore** radacina)
{
	NodArbore* aux = (*radacina)->dreapta;
	(*radacina)->dreapta = aux->stanga;
	aux->stanga = (*radacina);
	(*radacina) = aux;
}

void rotireDreapta(NodArbore** radacina)
{
	NodArbore* aux = (*radacina)->stanga;
	(*radacina)->stanga = aux->dreapta;
	aux->dreapta = (*radacina);
	(*radacina) = aux;
}

int verificareEchilibru(NodArbore* radacina)
{
	return calculeazaInaltimeArbore(radacina->stanga) - calculeazaInaltimeArbore(radacina->dreapta);
}



int main()
{


	return 0;
}