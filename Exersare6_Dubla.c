#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Televizor Televizor;
struct Televizor
{
	char* producator;
	int greutate;
	float diagonala;
};

typedef struct Nod Nod;
struct Nod
{
	Nod* next;
	Nod* prev;
	Televizor info;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla
{
	Nod* first;
	Nod* last;
};

Televizor citireTelevizorDinFisier(FILE* file)
{
	char buffer[30];
	char* sep = ",\n";
	fgets(buffer, 30, file);
	char* aux;
	Televizor t1;
	aux = strtok(buffer, sep);
	t1.producator = malloc(strlen(aux) + 1);
	strcpy_s(t1.producator, strlen(aux) + 1, aux);
	t1.greutate = atoi(strtok(NULL, sep));
	t1.diagonala = atof(strtok(NULL, sep));

	return t1;
}

void afisareTelevizor(Televizor televizor)
{
	printf("Producator: %s\n", televizor.producator);
	printf("Greutate: %d\n", televizor.greutate);
	printf("Diagonala: %.2f\n", televizor.diagonala);
}

void afisareListaTelevizoareDeLaInceput(ListaDubla lista)
{
	Nod* p = lista.first;
	while (p)
	{
		afisareTelevizor(p->info);
		p = p->next;
	}
}

void afisareListaTelevizoareDeLaFinal(ListaDubla lista)
{
	Nod* p = lista.last;
	while (p)
	{
		afisareTelevizor(p->info);
		p=p->prev;
	}
}

void inserareTelevizor(ListaDubla* lista, Televizor televizorNou)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = televizorNou;
	nodNou->next = NULL;
	nodNou->prev = lista->last;
	if (lista->last != NULL)
	{
		lista->last->next = nodNou;
	}
	else
	{
		lista->first = nodNou;
	}
	lista->last = nodNou;
}

ListaDubla citireLDTelevizorDinFisier(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	if (!file)
	{
		return lista;
	}

	while (!feof(file))
	{
		inserareTelevizor(&lista, citireTelevizorDinFisier(file));
	}
	fclose(file);
	return lista;
}

void dezalocareLD(ListaDubla* lista)
{
	Nod* p = lista->first;
	while (p)
	{
		Nod* aux = p;
		p = p->next;
		if (aux->info.producator)
		{
			free(aux->info.producator);
		}
		free(aux);
	}
	lista->first = NULL;
	lista->last = NULL;
}

Televizor cautaTelevizorByProducator(ListaDubla lista, char* numeCautat)
{
	Nod* p = lista.first;
	while (p)
	{
		if (strcmp(p->info.producator, numeCautat) == 0)
		{
			return p->info;
		}
		p = p->next;
	}

	Televizor tvNull = { NULL, 0, 0.0f };
	return tvNull;
}

char* getProducatorByDiagonalaMinima(ListaDubla lista)
{
	if (lista.first == NULL)
		return NULL;
	Nod* p = lista.first;
	Nod* nodMin = p;
	float min = p->info.diagonala;

	while (p)
	{
		if (p->info.diagonala < min)
		{
			min = p->info.diagonala;
			nodMin = p;
		}
		p = p->next;
	}

	return nodMin->info.producator;
}

int main() 
{
	ListaDubla lista = citireLDTelevizorDinFisier("Televizoare.txt");
	printf("De la inceput:\n");
	afisareListaTelevizoareDeLaInceput(lista);

	Televizor t1;
	t1.producator = (char*)malloc(strlen("AncaTv") + 1);
	strcpy_s(t1.producator, strlen("AncaTv") + 1, "AncaTv");
	t1.greutate = 400;
	t1.diagonala = 11.2;
	inserareTelevizor(&lista, t1);
	printf("Afisare lista noua:\n");
	afisareListaTelevizoareDeLaFinal(lista);

	char* producatorCautat = "Samsung";
	Televizor tvGasit = cautaTelevizorByProducator(lista, producatorCautat);
	printf("Televizorul cautat este:\n");
	afisareTelevizor(tvGasit);

	char* producatorMin = getProducatorByDiagonalaMinima(lista);
	printf("Producatorul televizorului cu cea mai mica diagoanala este: %s\n", producatorMin);
	
	dezalocareLD(&lista);
	printf("Lista a fost stearsa!");

	return 0;
}