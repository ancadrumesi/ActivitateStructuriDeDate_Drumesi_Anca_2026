#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StructuraCarte Carte;
struct StructuraCarte
{
	int id;
	int an;
	float pret;
	char* titlu;
	char* numeAutor; 
	unsigned char serie;
};

Carte citireCarteDinFisier(FILE* file)
{
	char buffer[150];
	char* sep = ",\n";
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
	printf("Pret: %.2f\n", carte.pret);
	printf("Titlu: %s\n", carte.titlu);
	printf("Autor: %s\n", carte.numeAutor);
	printf("Serie: %c\n", carte.serie);
}

typedef struct Nod Nod;
struct Nod
{
	Nod* next; //folosim lista simpla
	Carte info;
};

void pushStack(Nod** head, Carte carte)
{
	Nod* p = (Nod*)malloc(sizeof(Nod));
	p->info = carte;
	p->next = (*head);
	(*head) = p;
}

Carte popStack(Nod** head)
{
	Carte rezultat;
	if ((*head) == NULL)
	{
		rezultat.id = -1;
		return rezultat;
	}
	rezultat = (*head)->info;
	Nod* temp = (*head)->next;
	free(*head);
	*head = temp;
	return rezultat;
}

char isEmptyStack(Nod* head)
{
	return head == NULL;
}

void* citireStackCartiDinFisier(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	if (!file)
	{
		return NULL;
	}

	Nod* head = NULL;
	while (!feof(file))
	{
		Carte carte = citireCarteDinFisier(file);
		pushStack(&head, carte);
	}
	fclose(file);
	return head;
}

void dezalocareStivaDeCarti(Nod** head)
{
	while (*head)
	{
		Nod* p = *head;
		(*head) = (*head)->next;
		if (p->info.titlu)
		{
			free(p->info.titlu);
		}
		if (p->info.numeAutor)
		{
			free(p->info.numeAutor);
		}
		free(p);
	}
}

Carte getCarteByID(Nod** head, int idCautat)
{
	Carte rezultat;
	if ((*head) == NULL)
	{
		rezultat.id = -1;
		return rezultat;
	}

	Nod* stivaNoua = NULL;
	while ((*head))
	{
		Carte carte = popStack(head);
		if (carte.id == idCautat)
		{
			rezultat = carte;
			pushStack(&stivaNoua, carte);
			break;
		}
		else
		{
			pushStack(&stivaNoua, carte);
		}
	}
	while (stivaNoua)
	{
		pushStack(head, popStack(&stivaNoua));
	}
	return rezultat;
}

float calculeazaPretTotal(Nod** head)
{
	float suma = 0;
	Nod* stivaAux = NULL;

	//ggolim stiva si adunam preturile si le punem in stiva noua 
	while ((*head) != NULL)
	{
		Carte carte = popStack(head);
		suma += carte.pret;
		pushStack(&stivaAux, carte);
	}

	//reconstruim stiva originala
	while (stivaAux != NULL)
	{
		pushStack(head, popStack(&stivaAux));
	}

	return suma;
}

Carte getCarteByTitlu(Nod** head, char* titluCautat)
{
	Carte rezultat;
	if ((*head) == NULL)
	{
		rezultat.id = -1;
		return rezultat;
	}

	Nod* stivaNoua = NULL;
	while ((*head))
	{
		Carte carte = popStack(head);

		if (strcmp(carte.titlu, titluCautat)==0)
		{
			rezultat = carte;
			pushStack(&stivaNoua, carte);
			break;
		}
		else
		{
			pushStack(&stivaNoua, carte);
		}
	}

	while (stivaNoua)
	{
		pushStack(head, popStack(&stivaNoua));
	}
	return rezultat;
}

int size(Nod* head)
{
	int contor = 0;
	Nod* p = head;
	while (p)
	{
		contor++;
		p = p->next;
	}
	return contor;
}

int main()
{
	Nod* stiva = citireStackCartiDinFisier("Carti.txt");
	printf("Marimea stivei initiale este %d\n", size(stiva));

	float total = calculeazaPretTotal(&stiva);
	printf("Pret total carti din stiva este %.2f\n", total);


	int idCautat = 3;
	Carte carteByID = getCarteByID(&stiva, idCautat);
	if (carteByID.id != -1)
	{
		printf("Cartea gasita este:\n");
		afisareCarte(carteByID);
	}


	char* titluCautat = "Invitatie la vals";
	Carte carteByTitlu = getCarteByTitlu(&stiva, titluCautat);
	if (carteByTitlu.id != -1)
	{
		printf("Cartea cautata dupa titlu este:\n");
		afisareCarte(carteByTitlu);
	}

	afisareCarte(popStack(&stiva));
	afisareCarte(popStack(&stiva));
	
	//extragere 
	printf("Extragem ultimul element din stiva:\n");
	Carte ultimaCarte = popStack(&stiva);
	afisareCarte(ultimaCarte);
	free(ultimaCarte.titlu);
	free(ultimaCarte.numeAutor);

	printf("Stiva are acum %d elemente:\n", size(stiva));

	dezalocareStivaDeCarti(&stiva);

	return 0;
}