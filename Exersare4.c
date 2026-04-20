#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StructuraCarte Carte;
struct StructuraCarte
{
	int id;
	int an;
	char* titlu;
	char* numeAutor; 
	float pret;
	unsigned char serie;
};

Carte citireCarteDinFisier(FILE* file)
{
	char buffer[150];
	char sep = ",\n";
	fgets(buffer, 150, file);
	char* aux;
	Carte c1;
	aux = strtok(buffer, sep);
	c1.id = atoi(aux);
	c1.an = atoi(strtok(NULL, sep));
	c1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	c1.titlu = malloc(strlen(aux) + 1);
	strcpy_s(c1.titlu, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	c1.numeAutor = malloc(strlen(aux) + 1);
	strcpy_s(c1.numeAutor, strlen(aux) + 1, aux);
	c1.serie = *strtok(NULL, sep);
	return c1;
}

void afisareCarte(Carte carte)
{
	printf("ID: %d\n", carte.id);
	printf("An aparitie: %d\n", carte.an);
	printf("Titlu: %s\n", carte.titlu);
	printf("Autor: %s\n", carte.numeAutor);
	printf("Pret: %.2f\n", carte.pret);
	printf("Serie: %c\n", carte.serie);
}


int main()
{
	return 0;
}