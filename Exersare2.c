#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraCarte {
		int id;
		int anPublicatie;
		char* titlu;
		char* autor;
		float pret;
		char gen;
};
typedef struct StructuraCarte Carte;

struct Nod {
	Carte info;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

struct ListaDubla {
	Nod* first;
	Nod* last;
	int nrNoduri;
};
typedef struct ListaDubla ListaDubla;

Carte citireCarteDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Carte c1;
	aux = strtok(buffer, sep);
	c1.id = atoi(aux);
	c1.anPublicatie = atoi(strtok(NULL, sep));
	c1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	c1.titlu = malloc(strlen(aux) + 1);
	strcpy_s(c1.titlu, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	c1.autor = malloc(strlen(aux) + 1);
	strcpy_s(c1.autor, strlen(aux) + 1, aux);
	c1.gen = *strtok(NULL, sep);
	return c1;
}

void afisareCarte(Carte carte) {
	printf("Id: %d\n", carte.id);
	printf("An publicatie: %d\n", carte.anPublicatie);
	printf("Titlu: %s\n", carte.titlu);
	printf("Autor: %s\n", carte.autor);
	printf("Pret carte: %.2f\n", carte.pret);
	printf("Gen: %c\n\n", carte.gen);
}

void afisareListaCartiDeLaInceput(ListaDubla lista) {
	printf("Lista contine %d noduri:\n", lista.nrNoduri);
	Nod* p = lista.first;
		while (p) {
			afisareCarte(p->info);
			p = p->next;
		}
}

void afisareListaCartiDeLaSfarsit(ListaDubla lista) {
	printf("Lista contine %d noduri:\n", lista.nrNoduri);
	Nod* p = lista.last;
	while (p) {
		afisareCarte(p->info);
		p = p->prev;
	}
}


void adaugaCarteInLista(ListaDubla* lista, Carte carteNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = carteNoua;
	nodNou->next = NULL;
	nodNou->prev = lista->last;
	if (lista->last != NULL) {
		lista->last->next = nodNou;
	}
	else {
		lista->first = nodNou;
	}
	lista->last = nodNou;
	lista->nrNoduri++;
}

void adaugaLaInceputInLista(ListaDubla* lista, Carte carteNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = carteNoua;
	nodNou->next = lista->first;
	nodNou->prev = NULL;
	if (lista->first != NULL) {
		lista->first->prev = nodNou;
	}
	else {
		lista->last = nodNou;
	}
	lista->first = nodNou;
	lista->nrNoduri++;
}

ListaDubla citireLDCartiDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.nrNoduri = 0;
	lista.first = NULL;
	lista.last = NULL;

	if (!f) {

		return lista;
	}
	while (!feof(f)) 
	{
		adaugaCarteInLista(&lista, citireCarteDinFisier(f)); 
	}
	
	fclose(f);
	return lista;
}

void dezalocareLDCarti(ListaDubla* lista) {

	Nod* nod = lista->first;
	while (nod) 
	{
		Nod* aux = nod;
		nod = nod->next;
		if (aux->info.titlu) 
		{
			free(aux->info.titlu);
		}
		if (aux->info.autor)
		{
			free(aux->info.autor);
		}
		free(aux);
		lista->nrNoduri--;
	}
	lista->first = NULL;
	lista->last = NULL;
}

float calculeazaPretMediu(ListaDubla lista) {

	float pretTotal = 0;
	if (lista.first == NULL) {
		return 0;
	}else 
	{
		for (Nod* p = lista.first; p != NULL; p = p->next) 
		{
			pretTotal += p->info.pret;
		}
	}

	return pretTotal / lista.nrNoduri;
}

int main() {

	ListaDubla lista1 = citireLDCartiDinFisier("Carti.txt");
	afisareListaCartiDeLaInceput(lista1);
	printf("de la inceput: \n");

	printf("Pretul mediu al cartilor este %f\n", calculeazaPretMediu(lista1));
	

	return 0;
}