#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//diferenta de 2 ne arata ca avem dezechilibru 
//-2 factor de echilibru
//stanga - dreapta 
//rotim la stanga si schimbam radacina cu nodul din dreapta (daca avem dezechilibru la dreapta)
//trebuie sa vedem daca gradul e negativ sau pozitiv si asa ne dam seama unde sa facem rotirea 
//uneori facem dubla rotire cand gradul celui din mijloc e negativ si se schimba semnul 
//echilibrarea se face la momentul inserarii 
//trebuie sa facem verificarea de dezechilibru in fiecare nod de la nodul inserat catre radacina
//multimea {0, -1, 1} unde ai diferentele dintre inaltimea stanga - inaltimea dreapta 

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

typedef struct NodArbore NodArbore;
struct NodArbore
{
	NodArbore* stanga; 
	NodArbore* dreapta; 
	Masina info;
};

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

int calculeazaInaltimeArbore(NodArbore* radacina) {

	if (radacina == NULL)
	{
		return 0;
	}

	int dr = calculeazaInaltimeArbore(radacina->dreapta);
	int stg = calculeazaInaltimeArbore(radacina->stanga);
	return 1+ max(dr, stg);
}

void rotireStanga(NodArbore** radacina)
{
	NodArbore* aux = (*radacina)->dreapta;
	(*radacina)->dreapta = aux->stanga;
	aux->stanga = (*radacina);
	(*radacina) = aux;
}

void rotireDreapta(NodArbore** radacina)
{
	NodArbore* aux = (*radacina)->stanga;
	(*radacina)->stanga = aux->dreapta;
	aux->dreapta = (*radacina);
	(*radacina) = aux;
}

int verificareEchilibru(NodArbore* radacina)
{
	return calculeazaInaltimeArbore(radacina->stanga) - calculeazaInaltimeArbore(radacina->dreapta);
}

void adaugaMasinaInArboreEchilibrat(NodArbore** radacina, Masina masinaNoua) {

	if ((*radacina) != NULL)
	{
		if (masinaNoua.id > (*radacina)->info.id)
		{
			adaugaMasinaInArboreEchilibrat(&(*radacina)->dreapta, masinaNoua);
		}
		else
		{
			adaugaMasinaInArboreEchilibrat(&(*radacina)->stanga, masinaNoua);
		}


		//verificare echilibru
		int factorEchilibru = verificareEchilibru(*radacina);
		if (factorEchilibru == -2)
		{
			//dezechilibru in dreapta
			if (verificareEchilibru((*radacina)->dreapta) == -1)
			{
				rotireStanga(&(*radacina));
			}
			else
			{
				rotireDreapta(&(*radacina)->dreapta);
				rotireStanga(&(*radacina));
			}
		}

		if (factorEchilibru == 2)
		{
			//dezechilibru in stanga 
			if (verificareEchilibru((*radacina)->stanga) == -1)
			{
				rotireStanga(&(*radacina)->stanga);
			}
			rotireDreapta(&(*radacina));
		}
	}
	else
	{
		NodArbore* nodNou = (NodArbore*)malloc(sizeof(NodArbore));
		nodNou->stanga = NULL;
		nodNou->dreapta = NULL;
		nodNou->info = masinaNoua;
		(*radacina) = nodNou;
	}
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte principiile de arbore binar de cautare ECHILIBRAT
	//dupa o anumita cheie pe care o decideti - poate fi ID
}

NodArbore* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	NodArbore* radacina = NULL;
	FILE* file = fopen(numeFisier, "r");
	if (file)
	{
		while(!feof(file)) 
		{
			adaugaMasinaInArboreEchilibrat(&radacina, citireMasinaDinFisier(file));
		}
	}
	fclose(file);
	return radacina;
}

void afisareMasiniDinArbore(NodArbore* radacina) {

	if (radacina)
	{
		afisareMasina(radacina->info);
		afisareMasiniDinArbore(radacina->stanga);
		afisareMasiniDinArbore(radacina->dreapta);
	}
}

void dezalocareArboreDeMasini(NodArbore** radacina) {
	if (*radacina)
	{
		dezalocareArboreDeMasini(&(*radacina)->stanga);
		dezalocareArboreDeMasini(&(*radacina)->dreapta);
		free((*radacina)->info.numeSofer);
		free((*radacina)->info.model);
		free(*radacina);
		*radacina = NULL;
	}
	//sunt dezalocate toate masinile si arborele de elemente
}

//Preluati urmatoarele functii din laboratorul precedent.
//Acestea ar trebuie sa functioneze pe noul arbore echilibrat.

Masina getMasinaByID(/*arborele de masini*/int id);

int determinaNumarNoduri(/*arborele de masini*/);

float calculeazaPretTotal(/*arbore de masini*/);

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer);

int main() {

	NodArbore* radacina = citireArboreDeMasiniDinFisier("Masini.txt");
	afisareMasiniDinArbore(radacina);
	dezalocareArboreDeMasini(&radacina);

	return 0;
}