//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
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
////STACK
////Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
////putem reprezenta o stiva prin LSI, LDI sau vector
//
//typedef struct Nod Nod;
//struct Nod {
//	Masina masina;
//	Nod* next;
//};
//
//
//
//void pushStack(Nod** head, Masina masina) {
//	Nod* p = (Nod*)malloc(sizeof(Nod));
//	p->masina = masina;
//	p->next = (*head);
//	(*head) = p;
//}
//
//Masina popStack(Nod** head) {
//	//practic ce returnam
//	if ((*head) == NULL) {
//		Masina rezultat;
//		rezultat.id = -1;
//		return rezultat;
//	}
//	Masina rezultat = (*head)->masina;
//	Nod* temp = (*head)->next;
//	free(*head);
//	*head = temp;
//	return rezultat;
//}
//
////poate fi int sau char, functioneaza ca un bool, dar char ocupa mai putina memorie!
//char isEmptyStack(Nod* head) {
//	return head == NULL;
//
//}
//
//void* citireStackMasiniDinFisier(const char* numeFisier) {
//	FILE *file = fopen(numeFisier, "r");
//	if (!file) {
//		return NULL;
//	}
//	
//	Nod* head = NULL;
//	while (!feof(file)) {
//		Masina masina = citireMasinaDinFisier(file);
//		pushStack(&head, masina);
//	}
//	return head;
//	fclose(file);
//}
//
//void dezalocareStivaDeMasini(/*stiva*/) {
//	//sunt dezalocate toate masinile si stiva de elemente
//}
//
//int size(/*stiva*/) {
//	//returneaza numarul de elemente din stiva
//}
//
//typedef struct NodDublu NodDublu;
//struct NodDublu
//{
//	Masina info;
//	NodDublu* next;
//	NodDublu* prev;
//
//};
//
//typedef struct ListaDubla ListaDubla;
//struct ListaDubla 
//{
//	NodDublu* first;
//	NodDublu* last;
//};
////QUEUE
////lista dubla inlantuita (de facut si cu restul)
//void enqueue(ListaDubla* coada, Masina masina) {
//	NodDublu* nodNou = (NodDublu*)malloc(sizeof(NodDublu));
//	nodNou->info = masina;
//	nodNou->next = NULL;
//	nodNou->prev = coada->last;
//	if (coada->last) {
//		coada->last->next = nodNou;
//	}
//	else {
//		coada->first = nodNou;
//	}
//	coada->last = nodNou;
//}
//
//Masina dequeue(ListaDubla* coada) {
//	Masina rezultat;
//	rezultat.id = -1;
//	if (coada->first) {
//		rezultat = coada->first->info; //shallow copy si de asta dam free(temp) si nu separat pentru model si sofer
//		NodDublu* temp = coada->first;
//		coada->first = temp->next; 
//		free(temp);
//	}
//	return rezultat;
//}
//
//ListaDubla citireCoadaDeMasiniDinFisier(const char* numeFisier) {
//	ListaDubla coada;
//	coada.first = coada.last = NULL;
//	FILE* file = fopen(numeFisier, "r");
//	if (file) {
//		while (!feof(file)) {
//			enqueue(&coada, citireMasinaDinFisier(file));
//		}
//		fclose(file);
//	}
//	return coada;
//}
//
//void dezalocareCoadaDeMasini(/*coada*/) {
//	//sunt dezalocate toate masinile si coada de elemente
//}
//
//
////metode de procesare
//Masina getMasinaByID(Nod** stiva, int id) {
//	Masina rezultat;
//	if ((*stiva) == NULL) {
//		rezultat.id = -1;
//		return rezultat;
//	}
//
//	Nod* stivaNoua = NULL;
//
//	while ((*stiva)) {
//		Masina masinaNoua = popStack(stiva);
//		if (masinaNoua.id == id) {
//			rezultat = masinaNoua;
//			break; //cand ajunge la id-ul cautat
//		}
//		else {
//			pushStack(&stivaNoua, masinaNoua);
//		}
//		//pushStack(stivaNoua, popStack(&stiva));
//	}
//	//le parcurgem pe toate
//	while (stivaNoua) {
//		pushStack(stiva, popStack(&stivaNoua));
//	}
//
//	return rezultat;
//}
//
//float calculeazaPretTotal(/*stiva sau coada de masini*/);
//
//int main() {
//	Nod* stiva = citireStackMasiniDinFisier("Masini.txt");
//	afisareMasina(popStack(&stiva));
//	afisareMasina(popStack(&stiva));
//
//	afisareMasina(getMasinaByID(&stiva, 6));
//
//	printf("Coada\n");
//	ListaDubla coada = citireCoadaDeMasiniDinFisier("Masini.txt");
//	afisareMasina(dequeue(&coada));
//
//	return 0;
//}