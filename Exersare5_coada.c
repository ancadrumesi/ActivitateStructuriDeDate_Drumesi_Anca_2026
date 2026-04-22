#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Carte Carte;
struct Carte
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
	char buffer[100];
	char* sep = ",\n";
	fgets(buffer, 150, sep);
	char* aux;
	Carte c1;
	aux = strtok(buffer, sep);
	c1.id = atoi(aux);
	c1.an = atoi(strtok(NULL, sep));
	c1.pret = atoi(strtok(NULL, sep));
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
	printf("An: %d\n", carte.an);
	printf("Pret: %.2f\n", carte.pret);
	printf("Titlu: %s\n", carte.titlu);
	printf("Autor: %d\n", carte.numeAutor);
	printf("Serie: %c\n", carte.serie);
}

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

};

void enqueue(ListaDubla* coada, Carte carte)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = carte;
	nodNou->next = NULL;
	nodNou->prev = coada->last;
	if (coada->last)
	{
		coada->last->next = nodNou;
	}
	else
	{
		coada->first = nodNou;
	}
	coada->last = nodNou;
}

Carte dequeue(ListaDubla* coada)
{
	Carte rezultat;
	rezultat.id = -1;
	if (coada->first)
	{
		rezultat = coada->first->info;
		Nod* temp = coada->first;
		coada->first = temp->next;
		if (coada->first == NULL)
		{
			coada->last = NULL;
		}
		else
		{
			coada->first->prev = NULL;
		}
		free(temp);
	}
	return rezultat;
}





int main()
{
	ListaDubla coada = ("Carti.txt");

}