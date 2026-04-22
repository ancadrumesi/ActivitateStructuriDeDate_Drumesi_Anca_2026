#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Florarie Florarie;
struct Florarie
{
	char* denumire;
	float pret;
	int stoc;
};

typedef struct Nod Nod;
struct Nod
{
	Nod* next; 
	Nod* prev;
	Florarie info;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla
{
	Nod* first;
	Nod* last;
};

Florarie citireFloareDinFisier(FILE* file)
{
	char buffer[100];
	char* sep = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Florarie f1;
	aux = strtok(buffer, sep);
	f1.denumire = malloc(strlen(aux) + 1);
	strcpy_s(f1.denumire, strlen(aux) + 1, aux);
	f1.pret = atof(strtok(NULL, sep));
	f1.stoc = atoi(strtok(NULL, sep));
	return f1;
}

void afisareFlorarie(Florarie florarie)
{
	printf("Floare: %s\n", florarie.denumire);
	printf("Pret: %.2f\n", florarie.pret);
	printf("Stoc: %d\n", florarie.stoc);
}

void parcurgereListaDeLaFinal(ListaDubla lista)
{
	Nod* p = lista.last;
	while (p)
	{
		afisareFlorarie(p->info);
		p = p->prev;
	}
}

void inserareFloare(ListaDubla* lista, Florarie floareNoua)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = floareNoua;
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

ListaDubla citireLDDinFisier(const char* numeFisier)
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
		inserareFloare(&lista, citireFloareDinFisier(file));
	}
	fclose(file);
	return lista;
}

void dezalocareLista(ListaDubla* lista)
{
	Nod* p = lista->first;
	while (p)
	{
		Nod* aux = p;
		p = p->next;
		if (aux->info.denumire)
		{
			free(aux->info.denumire);
		}
		free(aux);
	}

	lista->first = NULL;
	lista->last = NULL;
}

int stocTotal(ListaDubla lista, const char* denumireCautata)
{
	int total = 0;
	Nod* p = lista.first;
	while (p)
	{
		if (strcmp(p->info.denumire, denumireCautata) == 0)
		{
			total += p->info.stoc;
		}
		p = p->next;
	}
	return total;
}

int main()
{
	ListaDubla lista = citireLDDinFisier("Florarie.txt");
	printf("Lista florarie:\n");
	parcurgereListaDeLaFinal(lista);

	char* denumireCautata = "Bujor";
	printf("Stocul total pentru floarea de tipul: %s este: %d\n", denumireCautata, stocTotal(lista, denumireCautata));
	

	dezalocareLista(&lista);
	printf("Lista a fost stearsa!");

	return 0;
}