#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
	Televizor info;
};

Televizor citireTelevizorDinFisier(FILE* file)
{
	char buffer[50];
	char* sep = ",\n";
	fgets(buffer, 50, file);
	Televizor t1; 
	char* aux = strtok(buffer, sep);
	t1.producator = (char*)malloc(strlen(aux) + 1);
	strcpy_s(t1.producator, strlen(aux) + 1, aux);
	t1.greutate = atoi(strtok(NULL, sep));
	t1.diagonala = atof(strtok(NULL, sep));
	return t1;
}

void afisareTelevizor(Televizor tv)
{
	printf("Producator: %s\n", tv.producator);
	printf("Greutate: %d\n", tv.greutate);
	printf("Diagonala: %.2f\n", tv.diagonala);
}

void parcurgereLS(Nod* head)
{
	while (head)
	{
		afisareTelevizor(head->info);
		head = head->next;
	}
}

void inserareTelevizor(Nod** head, Televizor tvNou)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = tvNou;
	nodNou->next = 0;
	if (*head == NULL)
	{
		(*head) = nodNou;
	}
	else
	{
		Nod* aux = (*head);
		while (aux != NULL)
		{
			aux = aux->next;
		}

		aux->next = nodNou;
	}
}

void inserareLaInceput(Nod** head, Televizor tvNou)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = tvNou;
	nodNou->next = *head;
	*head = nodNou;
}

Nod* citireLSDinFisier(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	if(file)
	{
		Nod* head = NULL;
		while (!feof(file))
		{
			inserareLaInceput(&head, citireTelevizorDinFisier(file));
		}
		fclose(file);
		return head;
	}

	return NULL;
}

void dezalocare(Nod** head)
{
	while (*head)
	{
		Nod* aux = *head;
		*head = aux->next;
		if (aux->info.producator)
		{
			free(aux->info.producator);
		}
		free(aux);
	}
}


int main() 
{
	Nod* head = citireLSDinFisier("Televizoare.txt");
	printf("Lista initiala este:\n");
	parcurgereLS(head);

	Televizor t1; 
	t1.producator = (char*)malloc(strlen("Samsung") + 1);
	strcpy_s(t1.producator, strlen("Samsung") + 1, "Samsung");
	t1.greutate = 100;
	t1.diagonala = 14.00;
	inserareLaInceput(&head, t1);
	printf("Noua lista este:\n");
	parcurgereLS(head);

	dezalocare(&head);
	printf("Lista a fost stearsa!\n");

	return 0;
}