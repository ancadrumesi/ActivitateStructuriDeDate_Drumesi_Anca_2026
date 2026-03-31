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
//void afisareMasina(Masina masina) {
//	printf("id masina: %d\n", masina.id);
//	printf("nr usi: %d\n", masina.nrUsi);
//	printf("pret masina: %.2f\n", masina.pret);
//	printf("modelul: %s\n", masina.model);
//	printf("sofer: %s\n", masina.numeSofer);
//	printf("sofer: %c\n\n", masina.serie);
//
//}
//
//void afisareVectorMasini(Masina* masini, int nrMasini) {
//	for (int i = 0; i < nrMasini; i++) {
//		afisareMasina(masini[i]);
//	}
//}
//
//void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
//	Masina* temp = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1)); //prioritizam adunareaa yay
//	for (int i = 0; i < *nrMasini; i++) {
//		
//		temp[i] = (*masini)[i]; //pointer la pointer si deferentiem pentru a accesa
//	}
//	temp[*nrMasini] = masinaNoua;
//	free(*masini);
//	//am facut shallow copy
//	(*masini) = temp;
//	(*nrMasini)++;
//
//	//adauga in vectorul primit o noua masina pe care o primim ca parametru
//	//ATENTIE - se modifica numarul de masini din vector;
//}
//
//Masina citireMasinaFisier(FILE* file) {
//
//	//avem stream deja pentru ca avem pointer la file
//	//buffer alocare statica pe stiva si functia va face dezalocare la final
//	Masina masina;
//	char buffer[50];
//	char delimitator[3] = ",\n";
//	fgets(buffer, 50, file);
//
//	
//	masina.id = atoi(strtok(buffer, delimitator));
//	masina.nrUsi = atoi(strtok(NULL, delimitator));
//	masina.pret = (float)atof(strtok(NULL, delimitator));
//
//	char* aux = strtok(NULL, delimitator);
//	masina.model = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
//	strcpy(masina.model, aux);
//
//	aux = strtok(NULL, delimitator);
//	masina.numeSofer = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
//	strcpy(masina.numeSofer, aux);
//
//	masina.serie = (strtok(NULL, delimitator))[0];
//
//	return masina;
//
//	//functia citeste o masina dintr-un strceam deja deschis
//	//masina citita este returnata;
//}
//
//Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
//
//	FILE* file;
//	file = fopen(numeFisier, "r"); //read 
//	Masina* masini = NULL;
//	*nrMasiniCitite = 0;
//	while (!feof(file)) {
//		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file)); //ii dam adresa ca isi ia el pointer e deja *
//		//e incrementat deja in functie
//	}
//	//EOF = e un flag, care atunci cand ajungem la sfarsitul fisierului si folosim feof ca sa verificam
//	fclose(file);
//	return masini;
//
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaFisier()
//	//numarul de masini este determinat prin numarul de citiri din fisier
//	//ATENTIE - la final inchidem fisierul/stream-ul
//}
//
//void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
//
//	for (int i = 0; i < (*nrMasini); i++) {
//		free((*vector)[i].model);
//		free((*vector)[i].numeSofer);
//	}
//
//	free(*vector);
//	*vector = NULL;
//	(*nrMasini) = 0;
//	//este dezalocat intreg vectorul de masini, parcurgem vectorul de masini si la fiecare dezalocam model si numesofer
//}
//
//int main() {
//
//	int nrMasini = 10;
//	Masina* masini = NULL;
//	masini = citireVectorMasiniFisier("Masini.txt", &nrMasini);
//	afisareVectorMasini(masini, nrMasini);
//
//	return 0;
//}
//
////-> deferentiere si deplasare 
////(*vector) deferentiere si accesare