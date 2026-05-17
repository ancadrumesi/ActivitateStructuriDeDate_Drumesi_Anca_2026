//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//typedef struct Nod Nod;
//struct Nod
//{
//	Masina info;
//	struct Nod* stanga;
//	struct Nod* dreapta;
//	int gradEchilibru;
//};
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//
//void rotireStanga(Nod** arbore)
//{
//	Nod* aux = (*arbore)->dreapta;
//	(*arbore)->dreapta = aux->stanga;
//	aux->stanga = (*arbore);
//	(*arbore) = aux;
//	(*arbore)->gradEchilibru--;
//}
//
//void rotireDreapta(Nod** arbore)
//{
//	Nod* aux = (*arbore)->stanga;
//	(*arbore)->stanga = aux->dreapta;
//	aux->dreapta = (*arbore);
//	(*arbore) = aux;
//	(*arbore)->gradEchilibru++;
//}
//
//
//
//void adaugaMasinaInArboreEchilibrat(Nod** radacina, Masina masinaNoua) {
//	//adauga o noua masina pe care o primim ca parametru in arbore,
//	//astfel incat sa respecte principiile de arbore binar de cautare ECHILIBRAT
//	//dupa o anumita cheie pe care o decideti - poate fi ID
//	if ((*radacina) != NULL) {
//		if ((*radacina)->info.id > masinaNoua.id) {
//			adaugaMasinaInArboreEchilibrat(&((*radacina)->stanga), masinaNoua);
//			(*radacina)->gradEchilibru++;
//		}
//		else {
//			adaugaMasinaInArboreEchilibrat(&((*radacina)->dreapta), masinaNoua);
//			(*radacina)->gradEchilibru--;
//		}
//		if ((*radacina)->gradEchilibru == 2) {
//			//avem dezechilibru in stanga
//			if ((*radacina)->stanga->gradEchilibru == 1) {
//				//rotire la dreapta
//				rotireDreapta(radacina);
//			}
//			else
//			{
//				rotireStanga(&((*radacina)->stanga));
//				rotireDreapta(radacina);
//			}
//		}
//		if ((*radacina)->gradEchilibru == -2)
//		{
//			//rotire la stanga
//			if ((*radacina)->dreapta->gradEchilibru == 1)
//			{
//				rotireDreapta(&((*radacina)->dreapta));
//			}
//			rotireStanga(radacina);
//		}
//	}
//
//	else
//	{
//		Nod* radacinaNoua = malloc(sizeof(radacina));
//		radacinaNoua->info = masinaNoua;
//		radacinaNoua->dreapta = NULL;
//		radacinaNoua->stanga = NULL;
//		radacinaNoua->gradEchilibru = 0;
//		(*radacina) = radacinaNoua;
//	}
//}
//
//Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* f = fopen(numeFisier, "r");
//	Nod* arbore = NULL;
//	while (!feof(f))
//	{
//		Masina m = citireMasinaDinFisier(f);
//		adaugaMasinaInArboreEchilibrat(&arbore, m);
//	}
//	fclose(f);
//	return arbore;
//}
//
//void afisarePreOrdine(Nod* arbore)
//{
//	if (arbore)
//	{
//
//		afisareMasina(arbore->info);
//
//		afisarePreOrdine(arbore->stanga);
//		afisarePreOrdine(arbore->dreapta);
//	}
//}
//
//void afisareMasiniDinArbore(/*arbore de masini*/) {
//	//afiseaza toate elemente de tip masina din arborele creat
//	//prin apelarea functiei afisareMasina()
//	//parcurgerea arborelui poate fi realizata in TREI moduri
//	//folositi toate cele TREI moduri de parcurgere
//}
//
//void dezalocareArboreDeMasini(/*arbore de masini*/) {
//	//sunt dezalocate toate masinile si arborele de elemente
//}
//
////Preluati urmatoarele functii din laboratorul precedent.
////Acestea ar trebuie sa functioneze pe noul arbore echilibrat.
//
//Masina getMasinaByID(/*arborele de masini*/int id);
//
//int determinaNumarNoduri(/*arborele de masini*/);
//
//float calculeazaPretTotal(/*arbore de masini*/);
//
//float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer);
//
//int main() {
//
//	Nod* arbore = citireArboreDeMasiniDinFisier("Masini.txt");
//	afisarePreOrdine(arbore);
//	return 0;
//}