#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Student Student;
struct Student
{
	int id;
	char* nume; 
	int varsta;
	float medie;
};

typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;
struct NodPrincipal
{
	Student info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar
{
	NodSecundar* next;
	NodPrincipal* info;
};

Student citireStudentDinFisier(FILE* file)
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Student s;
	aux = strtok(buffer, sep);
	s.id = atoi(aux);
	aux = strtok(NULL, sep);
	s.nume = malloc(strlen(aux) + 1);
	strcpy_s(s.nume, strlen(aux) + 1, aux);
	s.varsta = atoi(strtok(NULL, sep));
	s.medie = atof(strtok(NULL, sep));
	return s;
}

void afisareStudent(Student student)
{
	printf("Id: %d\n", student.id);
	printf("Nume: %s\n", student.nume);
	printf("Varsta: %d\n", student.varsta);
	printf("Medie: %.2f\n", student.medie);
}

void inserareListaPrincipalaLaFinal(NodPrincipal** graf, Student studentNou)
{
	NodPrincipal* nodNou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nodNou->info = studentNou;
	nodNou->next = NULL;
	nodNou->vecini = NULL;
	if (*graf)
	{
		NodPrincipal* aux = *graf;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nodNou;
	}
	else
	{
		*graf = nodNou;
	}
}

void inserareListaSecundaraLaFinal(NodSecundar** listaS, NodPrincipal* info)
{
	NodSecundar* nodNou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nodNou->info = info;
	nodNou->next = NULL;
	if (*listaS)
	{
		NodSecundar* aux = *listaS;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nodNou;
	}
	else
	{
		*listaS = nodNou;
	}
}

NodPrincipal* cautaNodDupaId(NodPrincipal* listaPrincipala, int idCautat)
{
	if (listaPrincipala)
	{
		while ((listaPrincipala) && listaPrincipala->info.id != idCautat)
		{
			listaPrincipala = listaPrincipala->next;
		}
		return listaPrincipala;
	}
}

void inserareMuchie(NodPrincipal* listaPrincipala, int idStart, int idStop)
{
	if (listaPrincipala)
	{
		NodPrincipal* nodStart = cautaNodDupaId(listaPrincipala, idStart);
		NodPrincipal* nodStop = cautaNodDupaId(listaPrincipala, idStop);
		if (nodStart && nodStop)
		{
			inserareListaSecundaraLaInceput(&nodStart->vecini, nodStop);
			inserareListaSecundaraLaInceput(&nodStop->vecini, nodStart);
		}
	}
}

NodPrincipal* citireNoduriStudentDinFisier(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	NodPrincipal* listaPrincipala = NULL;
	if (file)
	{
		while (!feof(file))
		{
			inserareListaPrincipalaLaFinal(&listaPrincipala, citireStudentDinFisier(file));
		}
	}
	fclose(file);
	return listaPrincipala;
}

void citireMuchiiDinFisier(NodPrincipal* listaPrincipala, const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	int idStart;
	int idStop;
	while (!feof(file))
	{
		fscanf(file, "%d %d", &idStart, &idStop);
		inserareMuchie(listaPrincipala, idStart, idStop);
	}
	fclose(file);
}


void afisareLista(NodPrincipal* graf, int id)
{
	NodPrincipal* nod = cautaNodDupaId(graf, id);
	NodSecundar* cap = nod->vecini;
	while (cap)
	{
		afisareStudent(cap->info->info);
		cap = cap->next;
	}
}

void dezalocareNoduriGraf(NodPrincipal** graf) {

	NodPrincipal* aux = *graf;
	while (aux != NULL)
	{
		NodSecundar* s = aux->vecini;
		while (s != NULL)
		{
			NodSecundar* auxS = s;
			s = s->next;
			free(auxS);
		}
		if (aux->info.nume)
		{
			free(aux->info.nume);
		}

		NodPrincipal* auxP = aux;
		aux = aux->next;
		free(auxP);
	}
	*graf = NULL;
}


int main()
{
	NodPrincipal* graf = citireNoduriStudentDinFisier("studenti.txt");
	citireMuchiiDinFisier(graf, "muchii.txt");

	afisareLista(graf, 10);

	return 0;
}