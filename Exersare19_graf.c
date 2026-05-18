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
	NodSecundar* info;
	NodSecundar* next;
};

Serial citireSerialDinFisier(FILE* file)
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Serial s;
	aux = strtok(sep, buffer);
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

////inserare muchie
//void inserareMuchie(NodPrincipal* listaPrincipala, int idStart, int idStop) {
//
//	if (listaPrincipala)
//	{
//		NodPrincipal* nodStart = cautaNodDupaID(listaPrincipala, idStart);
//		NodPrincipal* nodStop = cautaNodDupaID(listaPrincipala, idStart);
//		if (nodStart && nodStop)
//		{
//			inserareListaSecundaraLaInceput(&nodStart->vecini, nodStop);
//			inserareListaSecundaraLaInceput(&nodStop->vecini, nodStart);
//		}
//	}
//}
//

int main()
{

	return 0;
}