#define CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct StructuraCarte Carte;
struct StructuraCarte
{
	int id; 
	int an;
	char* titlu;
	char* numeAutor;
	double pret;
	unsigned char serie;
};

typedef struct Nod Nod;
struct Nod
{
	Nod* next;
	Nod* prev;
	Carte info;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla
{
	Nod* first;
	Nod* last;
	int nrNoduri;
};

Carte citireCarteDinFisier(FILE* file) 
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Carte carte1;
	aux = strtok(buffer, sep);
	carte1.id = atoi(aux);
	carte1.an = atoi(strtok(NULL, sep));
	carte1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	carte1.titlu = malloc(strlen(aux) + 1);
	strcpy_s(carte1.titlu, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	carte1.numeAutor = malloc(strlen(aux) + 1);
	strcpy_s(carte1.numeAutor, strlen(aux) + 1, aux);
	carte1.serie = *strtok(NULL, sep);
	return carte1;
}

void afisareCarte(Carte carte)
{
	printf("Id: %d\n", carte.id);
	printf("Anul aparitiei: %d\n", carte.an);
	printf("Titlul cartii: %s\n", carte.titlu);
	printf("Autor: %s\n", carte.numeAutor);
	printf("Pret: %.2f\n", carte.pret);
	printf("Serie: %c\n\n", carte.serie);
}
