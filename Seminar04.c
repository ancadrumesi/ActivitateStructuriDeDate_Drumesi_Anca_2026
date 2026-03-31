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
//	Nod* next; //adresa urmatorului nod
//};
//
////creare structura pentru un nod dintr-o lista simplu inlantuita
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
//	m1.pret= atof(strtok(NULL, sep));
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
//void afisareListaMasini(Nod* cap) {
//	while (cap != NULL)
//	{
//		afisareMasina(cap->info);
//		cap = cap->next;
//	}
//	//afiseaza toate elemente de tip masina din lista simplu inlantuita
//	//prin apelarea functiei afisareMasina()
//}
//
//void adaugaMasinaInLista(Nod**cap, Masina masinaNoua) {//** daca lista e goala modificam si capul listei
//
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = masinaNoua;
//	nodNou->next = NULL;
//	if ((*cap) == NULL)
//	{
//		(*cap) = nodNou;
//	}
//	else 
//	{
//		Nod* aux = (*cap);
//		while (aux->next!= NULL) //ne oprim la un pas anterior 
//		{
//			aux = aux->next;
//		}
//		aux->next = nodNou;
//	}
//	//adauga la final in lista primita o noua masina pe care o primim ca parametru
//}
//
//void adaugaLaInceputInLista(Nod**cap, Masina masinaNoua) {
//
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = masinaNoua;
//	nodNou->next = *cap;
//	*cap = nodNou;
//
//	//adauga la inceputul listei o noua masina pe care o primim ca parametru
//}
//
//Nod* citireListaMasiniDinFisier(const char* numeFisier) {
//
//	FILE* file = fopen(numeFisier, "r");
//	if (file)
//	{
//		Nod* cap = NULL;
//		while (!feof(file))
//		{
//			adaugaMasinaInLista(&cap, citireMasinaDinFisier(file));
//		}
//		fclose(file);
//		return cap;
//	}
//	return NULL;
//
//	//void* pointer la void e un pointer generic, stramosul lui template din poo, deci ori void* ori Nod*, face ce trebuie la compilare
//
//
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//}
//
//void dezalocareListaMasini(Nod** cap) {
//	while (*cap)
//	{
//		Nod* p = *cap;
//		(*cap) = p-> next;
//		//p e nodul de sters
//		if (p->info.numeSofer)
//		{
//			free(p->info.numeSofer);
//		}
//		if (p->info.model)
//		{
//			free(p->info.model);
//		}
//		free(p); //stergem fiecare nod
//	}
//	//sunt dezalocate toate masinile si lista de elemente
//}
//
//float calculeazaPretMediu(Nod*cap) {
//
//	float suma = 0;
//	int contor = 0;
//	while (cap)
//	{
//		suma += cap->info.pret;
//		contor++;
//		cap = cap->next; //SA NU UITAM SA TRECEM LA URMATORUL NOD!!
//	}
//	if (contor > 0)
//	{
//		return suma / contor;
//	}
//	return 0;
//}
//
//void stergeMasiniDinSeria(Nod** cap, char serieCautata) {
//	
//	while ((*cap) && (*cap)->info.serie == serieCautata)
//	{
//		Nod* temp = *cap;
//		(*cap) = temp->next;
//
//		if (temp->info.numeSofer)
//		{
//			free(temp->info.numeSofer);
//		}
//		if (temp->info.model)
//		{
//			free(temp->info.model);
//		}
//		free(temp);
//	}
//
//	Nod* p = *cap;
//
//	while(p)
//	{
//		while (p->next && p->info.serie != serieCautata)
//		{
//			p = p->next;
//		}
//
//		if (p->next)
//		{
//			Nod* temp = p->next;
//			p->next = temp->next;
//
//			if (temp->info.model)
//			{
//				free(temp->info.model);
//			}
//			if (temp->info.numeSofer)
//			{
//				free(temp->info.numeSofer);
//			}
//			free(temp);
//		}
//		else
//		{
//			p = p->next;
//		}
//	}
//
//	//sterge toate masinile din lista care au seria primita ca parametru.
//	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
//}
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* cap, const char* numeSofer) {
//
//	float pretTotal = 0;
//
//	Nod* aux = cap; //sa nu pierdem adresa capului 
//
//	while (aux != NULL) {
//
//		//compara sirurile si returneaza 0 daca sunt identice
//		if (strcmp(aux->info.numeSofer, numeSofer) == 0) {
//			pretTotal += aux->info.pret;
//		}
//		aux = aux->next;
//	}
//	return pretTotal;
//}
//
//int main() {
//	
//	Nod* cap = NULL;
//	cap = citireListaMasiniDinFisier("masini.txt");
//	afisareListaMasini(cap);
//	//printf("lista dupa dezalocare\n");
//	//dezalocareListaMasini(&cap); 
//	//afisareListaMasini(cap);
//
//	float valoare = 0;
//	valoare = calculeazaPretMediu(cap);
//	printf("Pret mediu: %.2f\n", valoare);
//	printf("Stergem masinile cu seria A: \n");
//	stergeMasiniDinSeria(&cap, 'A');
//	printf("Dupa stergerea seriei A\n");
//	afisareListaMasini(cap);
//
//	const char* sofer = "Ionescu";
//	float pretTotal = calculeazaPretulMasinilorUnuiSofer(cap, sofer);
//
//	printf("Pretul total al masinilor soferului %s este: %.2f\n", sofer, pretTotal);
//
//	return 0;
//}