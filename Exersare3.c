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
	char buffer[150];
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

void afisareListaCartiDeLaInceput(ListaDubla LD)
{
	printf("Lista contine %d noduri:\n", LD.nrNoduri);
	Nod* p = LD.first;
	while (p)
	{
		afisareCarte(p->info);
		p = p->next;
	}
}

void afisareListaDeLaSfarsit(ListaDubla LD)
{
	printf("Lista contine %d noduri:\n", LD.nrNoduri);
	Nod* p = LD.last;
	while (p)
	{
		afisareCarte(p->info);
		p = p->prev;
	}
}

void inserareCarteInListaLaFinal(ListaDubla* LD, Carte carteNoua)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = carteNoua;
	nodNou->next = NULL;
	nodNou->prev = LD->last;
	if (LD->last != NULL)
	{
		LD->last->next = nodNou;
	}
	else
	{
		LD->first = nodNou;
	}
	LD->last = nodNou;
	LD->nrNoduri++;
}

void inserareCarteInListaLaInceput(ListaDubla* LD, Carte carteNoua)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = carteNoua;
	nodNou->prev = NULL;
	nodNou->next = LD->first;
	if (LD->first != NULL)
	{
		LD->first->prev = nodNou;
	}
	else
	{
		LD->last = nodNou;
	}
	LD->first = nodNou;
	LD->nrNoduri++;
}

ListaDubla citireLDCartiDinFisier(const char* numeFisier)
{
	FILE* f = fopen(numeFisier, "r");
	ListaDubla LD;
	LD.nrNoduri = 0;
	LD.first = NULL;
	LD.last = NULL;

	if (!f)
	{
		return LD;
	}

	while (!feof(f))
	{
		inserareCarteInListaLaInceput(&LD, citireCarteDinFisier(f));
	}
	fclose(f);
	return LD;
}

void dezalocareLDCarti(ListaDubla* LD)
{
	Nod* nod = LD->first;
	while (nod)
	{
		Nod* aux = nod;
		nod = nod->next;
		if (aux->info.titlu)
		{
			free(aux->info.titlu);
		}
		if (aux->info.numeAutor)
		{
			free(aux->info.numeAutor);
		}
		free(aux);
		LD->nrNoduri--;
	}
	LD->first = NULL;
	LD->last = NULL;
}

void stergeCarteDupaID(ListaDubla* LD, int id)
{
	if (LD->first)
	{
		Nod* p;
		for (p = LD->first; p != NULL && p->info.id != id; p = p->next); //parcurgem lista
		if (!p)
			return;
		else
		{
			if (p->prev = NULL)
			{
				Nod* aux = p;
				if (p->next)
				{
					p->next->prev = NULL;
				}
				else
				{
					LD->first = NULL;
				}
				LD->first = p->next;
				free(p->info.titlu);
				free(p->info.numeAutor);
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
					LD->last = p->prev;
				}
				free(p->info.titlu);
				free(p->info.numeAutor);
				free(p);
			}
			LD->nrNoduri--;
		}
	}
}

float calculeazaPretMediu(ListaDubla LD)
{
	float pretTotal = 0;
	if(LD.first == NULL)
	{
		return 0;
	}
	else 
	{
		Nod* p = LD.first;
		while (p)
		{
			pretTotal += p->info.pret;
		}
	}
	return pretTotal/LD.nrNoduri;
}

char* getNumeAutorCarteScumpa(ListaDubla LD)
{
	if (LD.first == NULL)
		return NULL;
	Nod* p = LD.first;
	Nod* nodMaxim = p;
	double pretMaxim = p->info.pret;
	while (p != NULL)
	{
		if (p->info.pret > pretMaxim)
		{
			pretMaxim = p->info.pret;
			nodMaxim = p;
		}
		p = p->next;
	}
	return nodMaxim->info.numeAutor;
}

int main()
{
	ListaDubla lista = citireLDCartiDinFisier("Carti.txt");
	printf("De la inceput:\n");
	afisareListaCartiDeLaInceput(lista);

	Carte carteNoua;
	carteNoua.id = 11; 
	carteNoua.an = 1989;
	carteNoua.titlu = (char*)malloc(strlen("Revolutie") + 1);
	strcpy_s(carteNoua.titlu, strlen("Revolutie") + 1, "Revolutie");
	carteNoua.numeAutor = (char*)malloc(strlen("Florin Dragomir") + 1);
	strcpy_s(carteNoua.numeAutor, strlen("Florin Dragomir") + 1, "Florin Dragomir");
	carteNoua.pret = 199.99;
	carteNoua.serie = 'A';
	inserareCarteInListaLaFinal(&lista, carteNoua);

	printf("Afisare noua lista:\n");
	afisareListaDeLaSfarsit(lista);

	int id = 8;
	stergeCarteDupaID(&lista, id);
	printf("Lista dupa stergerea cartii cu id-ul %d:\n", afisareListaCartiDeLaInceput);

	printf("Pretul mediu al cartilor este:\n");
	float pretTotal = 0;
	calculeazaPretMediu(lista);
	
	dezalocareLDCarti(&lista);

	return 0;
}