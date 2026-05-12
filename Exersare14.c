#define _CRT_SECURE_NO_WARNINGS 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Florarie Florarie;
struct Florarie
{
	int id;
	char* tip;
	float pret;
	int cantitate;
};

typedef struct Heap Heap;
struct Heap
{
	int lungime;
	int nrElementeVizibile;
	Florarie* vector;
};

Florarie citireFlorarieDinFisier(FILE* file)
{
	char buffer[50];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Florarie f;
	aux = strtok(buffer, sep);
	f.id = atoi(aux);
	aux = strtok(NULL, sep);
	f.tip = malloc(strlen(aux) + 1);
	strcpy_s(f.tip, strlen(aux) + 1, aux);
	f.pret = atof(strtok(NULL, sep));
	f.cantitate = atoi(strtok(NULL, sep));
	return f;
}

void afisareFloare(Florarie floare)
{
	printf("Id: %d", floare.id);
	printf("Tip: %s", floare.tip);
	printf("Pret: %.2f", floare.pret);
	printf("Cantitate: %d", floare.cantitate);
}



int main()
{
	return 0;
}