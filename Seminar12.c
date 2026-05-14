#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

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

//1. 
// structuri necesare
//dorim stocarea unui graf intr-o lista de liste
//astfel avem nod ListaPrincipala si NodListaSecundara

typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct NodPrincipal
{
	Masina info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar
{
	NodSecundar* next;
	NodPrincipal* info; //adresa care ne duce la informatia din nodul principal
};

//2.
//functii de inserare in liste
//si in principala si in secundara

void inserareListaPrincipalaLaFinal(NodPrincipal** graf, Masina masinaNoua)
{
	NodPrincipal* nodNou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nodNou->info = masinaNoua;
	nodNou->next = NULL;
	nodNou->vecini = NULL;

	if (*graf)
	{
		NodPrincipal* aux = *graf; //inceputul listei 
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

void inserareListaSecundaraLaInceput(NodSecundar** listaS, NodPrincipal* info)
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

//3.
//functie de cautarea in lista principala dupa ID
void* cautaNodDupaID(NodPrincipal* listaPrincipala, int id) 
{
	if (listaPrincipala)
	{
		while ((listaPrincipala)&&listaPrincipala->info.id != id)
		{
			listaPrincipala = listaPrincipala->next;
		}
		return listaPrincipala;
	}
}

//4.
//inserare muchie
void inserareMuchie(NodPrincipal* listaPrincipala, int idStart, int idStop) {

	if (listaPrincipala)
	{
		NodPrincipal* nodStart = cautaNodDupaID(listaPrincipala, idStart);
		NodPrincipal* nodStop = cautaNodDupaID(listaPrincipala, idStart);
		if (nodStart && nodStop)
		{
			inserareListaSecundaraLaInceput(&nodStart->vecini, nodStop);
			inserareListaSecundaraLaInceput(&nodStop->vecini, nodStart);
		}
	}
}


NodPrincipal* citireNoduriMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	NodPrincipal* listaPrincipala = NULL;
	if (file)
	{
		while (!feof(file))
		{
			inserareListaPrincipalaLaFinal(&(listaPrincipala), citireMasinaDinFisier(file));
		}
	}
	fclose(file);
	return listaPrincipala;
}

void citireMuchiiDinFisier(NodPrincipal* listaPrincipala, const char* numeFisier) {

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

void dezalocareNoduriGraf(void* listaPrincipala) {
	//sunt dezalocate toate masinile din graf 
	//si toate nodurile celor doua liste
}

int main() {

	NodPrincipal* graf = citireNoduriMasiniDinFisier("Masini.txt");
	citireMuchiiDinFisier(graf, "muchii.txt");

	return 0;
}