#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Serial Serial;
struct Serial
{
	int id;
	int nrSezoane;
	char* numeSerial;
	char* personaj;
	float rating;
};

typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct NodPrincipal
{
	Serial info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

typedef struct NodSecundar
{
	NodPrincipal* info;
	NodSecundar* next;
};

Serial citireSerialDinFisier(FILE* file)
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Serial s;
	aux = strtok(buffer, sep);
	s.id = atoi(aux);
	s.nrSezoane = atoi(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	s.numeSerial = (char*)malloc(strlen(aux) + 1);
	strcpy_s(s.numeSerial, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	s.personaj = (char*)malloc(strlen(aux) + 1);
	strcpy_s(s.personaj, strlen(aux) + 1, aux);
	s.rating = atof(strtok(NULL, sep));
	return s;
}

void afisareSerial(Serial serial)
{
	printf("Id: %d\n", serial.id);
	printf("Numar sezoane: %d\n", serial.nrSezoane);
	printf("Nume serial: %s\n", serial.numeSerial);
	printf("Personaj: %s\n", serial.personaj);
	printf("Rating: %.2f\n", serial.rating);
}

void inserareListaPrincipalaLaFinal(NodPrincipal** graf, Serial serialNou)
{
	NodPrincipal* nodNou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nodNou->info = serialNou;
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
	}else
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
			inserareListaSecundaraLaFinal(&nodStart->vecini, nodStop);
			inserareListaSecundaraLaFinal(&nodStop->vecini, nodStart);
		}
	}
}

NodPrincipal* citireNoduriSerialeDinFisier(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	NodPrincipal* listaPrincipala = NULL;
	if (file)
	{
		while (!feof(file))
		{
			inserareListaPrincipalaLaFinal(&(listaPrincipala), citireSerialDinFisier(file));
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

void dezalocare(NodPrincipal** graf)
{
	while (*graf)
	{
		NodPrincipal* p = *graf;
		NodSecundar* s = p->vecini;
		while (s)
		{
			NodSecundar* auxS = p->vecini;
			s = s->next;
			free(auxS);
		}
		free(p->info.numeSerial);
		free(p->info.personaj);
		*graf = p->next;
		free(p);
	}
}

int main()
{
	NodPrincipal* graf = citireNoduriSerialeDinFisier("seriale.txt");
	citireMuchiiDinFisier(graf, "muchii.txt");

	if (graf) printf("Graful a fost incarcat cu succes!\n");

	dezalocare(&graf);
	printf("Memoria a fost eliberata.\n");
	return 0;

	return 0;
}