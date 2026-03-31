//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraCarte {
//	int id;
//	int anPublicatie;
//	char* titlu;
//	char* autor;
//	float pret;
//	char gen;
//};
//typedef struct StructuraCarte Carte;
//
//typedef struct Nod Nod;
//struct Nod{
//
//	Carte info;
//	Nod* next;
//};
//
//Carte citireCarteDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Carte c1;
//	aux = strtok(buffer, sep);
//	c1.id = atoi(aux);
//	c1.anPublicatie = atoi(strtok(NULL, sep));
//	c1.pret = atoi(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	c1.titlu = malloc(strlen(aux) + 1);
//	strcpy_s(c1.titlu, strlen(aux) + 1, aux);
//	aux = strtok(NULL, sep);
//	c1.autor = malloc(strlen(aux) + 1);
//	strcpy_s(c1.autor, strlen(aux) + 1, aux);
//	c1.gen = *strtok(NULL, sep);
//	return c1;
//}
//
//void afisareCarte(Carte carte) {
//	printf("Id: %d\n", carte.id);
//	printf("An publicatie: %d\n", carte.anPublicatie);
//	printf("Titlu: %s\n", carte.titlu);
//	printf("Autor: %s\n", carte.autor);
//	printf("Pret carte: %.2f\n", carte.pret);
//	printf("Gen: %c\n\n", carte.gen);
//}
//
//void afisareListaCarti(Nod* cap) {
//	while (cap != NULL) {
//		afisareCarte(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaCarteInLista(Nod** cap, Carte carteNoua) {
//
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = carteNoua;
//	nodNou->next = NULL;
//	if ((*cap) == NULL) {
//		(*cap) = nodNou;
//	}
//	else 
//	{
//		Nod* aux = (*cap);
//
//		while ((aux->next) != NULL) 
//		{
//			aux = aux->next;
//		}
//
//		aux->next = nodNou;
//	}
//}
//
//void adaugaCarteLaInceputDeLista(Nod** cap, Carte carteNoua) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = carteNoua;
//	nodNou->next = *cap;
//	*cap = nodNou;
//}
//
//int main() {
//	Nod* cap = NULL;
//
//	cap = citireCarteDinFisier("Carti.txt");
//
//}