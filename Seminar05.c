#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod {
	Masina info;
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

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasiniDeLaInceput(ListaDubla lista) {
	printf("Lista contine %d noduri:\n", lista.nrNoduri);
	Nod* p = lista.first;
		while (p) {
			afisareMasina(p->info);
			p = p->next;
		}
}

void afisareListaMasiniDeLaSfarsit(ListaDubla lista) {
	printf("Lista contine %d noduri:\n", lista.nrNoduri);
	Nod* p = lista.last;
	while (p) {
		afisareMasina(p->info);
		p = p->prev;
	}
}


void adaugaMasinaInLista(ListaDubla* lista, Masina masinaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua;
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

void adaugaLaInceputInLista(ListaDubla* lista, Masina masinaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua; //shallow copy ca sa nu stergem 
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

ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
//o stocam pe stack deci nu ii alocam memorie deci dam return asa cum e!
	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;

	if (!f) {

		return lista;
	}
	while (!feof(f)) 
	{
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f)); //shallow copy
	}
	
	fclose(f);
	return lista;
}

void dezalocareLDMasini(ListaDubla* lista) {

	Nod* nod = lista->first;
	while (nod) 
	{
		Nod* aux = nod;
		nod = nod->prev;
		if (aux->info.model) 
		{
			free(aux->info.model);
		}
		if (aux->info.numeSofer)
		{
			free(aux->info.numeSofer);
		}
		free(aux);
		lista->nrNoduri--;
	}
	lista->first = NULL;
	lista->last = NULL;
}

float calculeazaPretMediu(ListaDubla lista) {
	//parcurgem lista si facem suma preturilor 

	float pretTotal = 0;
	if (lista.first == NULL) {
		return 0;
	}else 
	{
		/*Nod* p = lista.first;
		while (p) 
		{
			pretTotal += p->info.pret;
		}*/
		for (Nod* p = lista.first; p != NULL; p = p->next) 
		{
			pretTotal += p->info.pret;
		}
	}

	return pretTotal / lista.nrNoduri;
}

void stergeMasinaDupaID(ListaDubla* lista, int id) {
	//modificam si numarul de noduri orice ar fi deci transmitem prin adresa *
	//modificam legaturile

	if (lista->first) 
	{
		Nod* p;
		for (p = lista->first; p != NULL && p->info.id != id; p = p->next); //facem parcurgerea
		if (!p) return;
		else
		{
			if (p->prev == NULL)
			{
				Nod* aux = p;
				if (p->next)
				{
					p->next->prev = NULL;
				}else
				{
					lista->last = NULL;
				}
				lista->first = p->next;
				free(p->info.model);
				free(p->info.numeSofer);
				free(p);
			}
			else
			{
				p->prev->next = p->next;
				if (p->next)
				{
					p->next->prev = p->prev;
				}
				else 
				{
					lista->last = p->prev;
				}
				free(p->info.model);
				free(p->info.numeSofer);
				free(p);
			}
			lista->nrNoduri--;
		}
	}


	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	return NULL;
}

int main() {

	ListaDubla listaMea = citireLDMasiniDinFisier("Masini.txt");
	afisareListaMasiniDeLaInceput(listaMea);
	printf("de la inceput: \n");

	printf("Pretul mediu al masinilor este %f\n", calculeazaPretMediu(listaMea));
	stergeMasinaDupaID(&listaMea, );
	afisareListaMasiniDeLaInceput(listaMea);
	

	return 0;
}