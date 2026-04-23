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
	Florarie info;
	Nod* next;
};

Florarie citireFlorarieDinFisier(FILE* file)
{
	char buffer[50];
	char* sep = ",\n";
	fgets(buffer, 50, file);
	Florarie f1;
	char* aux = strtok(buffer, sep);
	f1.denumire = (char*)malloc(strlen(aux) + 1);
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

void afisareLS(Nod* head)
{
	while (head != NULL)
	{
		afisareFlorarie(head->info);
		head = head->next;
	}
}

void inserareFloare(Nod** head, Florarie floareNoua)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = floareNoua;
	nodNou->next = NULL;
	if ((*head) == NULL)
	{
		(*head) = nodNou;
	}
	else
	{
		Nod* aux = (*head);
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = nodNou;
	}
}

void inserareLaInceput(Nod** head, Florarie floareNoua)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = floareNoua;
	nodNou->next = *head;
	*head = nodNou;
}

Nod* citireLSDinFisier(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	if (file)
	{
		Nod* head = NULL;
		while (!feof(file))
		{
			inserareFloare(&head, citireFlorarieDinFisier(file));
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
		if (aux->info.denumire)
		{
			free(aux->info.denumire);
		}
		free(aux);
	}
}

int main()
{
	Nod* head = citireLSDinFisier("Florarie.txt");
	printf("Lista:\n");
	afisareLS(head);

	Florarie f1;
	f1.denumire = (char*)malloc(strlen("Zambila") + 1);
	strcpy_s(f1.denumire, strlen("Zambila") + 1, "Zambila");
	f1.pret = 12.30;
	f1.stoc = 3;
	inserareFloare(&head, f1);
	printf("lista actualizata:\n");
	afisareLS(head);

	dezalocare(&head);
	printf("Lista a fost stearsa!");


	return 0;
}