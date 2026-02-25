#include<stdio.h>
#include<malloc.h>

struct Telefon {
	int id;
	int RAM;
	char* producator;
	float pret;
	char serie;
};
struct Telefon initializare(int id, int RAM, char* producator, float pret, char serie) {
	struct Telefon t;
	t.id = id;
	t.RAM = RAM;
	t.producator = (char*)malloc((strlen(producator) + 1) * sizeof(char));
	strcpy(t.producator, producator);
	t.pret = pret;
	t.serie = serie;
	return t;
}

struct Telefon copiazaTelefon(struct Telefon t) {
	struct Telefon telefon = initializare(t.id, t.RAM, t.producator, t.pret, t.serie);
	return telefon;
}

void afisare(struct Telefon t) {
	printf("Id: %d\nRAM: %d\nProducator: %s\nPret: %f\nSerie: %c\n\n", t.id, t.RAM, t.producator, t.pret, t.serie);
}

void afisareVector(struct  Telefon* vector, int nrElemente) {
	//afisarea elementelor din vector apeland functia afisare
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
	}
}

struct  Telefon* copiazaPrimeleNElemente(struct  Telefon* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	if (nrElementeCopiate > nrElemente) {
		nrElementeCopiate = nrElemente;
	}
		struct Telefon* vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);
		for (int i = 0; i < nrElementeCopiate; i++) {
				vectorNou[i] = copiazaTelefon(vector[i]);
		}
		return vectorNou;
	
}

void dezalocare(struct  Telefon** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++) {
		free((*vector)[i].producator);
		(*vector)[i].producator = NULL;
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaTelefoaneScumpe(struct  Telefon* vector, char nrElemente, float pretMinim, struct Telefon** vectorNou, int* dimensiune) {
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].pret >= pretMinim) {
			(*dimensiune)++;
		}
	}

	*vectorNou = malloc(*dimensiune * sizeof(struct Telefon));
	for (int i = 0, j=0; i<nrElemente; i++) {
		if (vector[i].pret >= pretMinim) {
			i += 1;
			(*vectorNou)[j] = copiazaTelefon(vector[i]);
			j += 1;
		}
	}

	//OPERATORRUL INDEX = DEPLASARE SI REFERENTIERE 
}

struct  Telefon getPrimulElementConditionat(struct  Telefon* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat. 
	//functie care face o cautare in telefoane in functie de producator, folosim strcmp 
	struct  Telefon s;
	s.id = 1;

	return s;
}
	


int main() {

	struct Telefon telefon;
	telefon = initializare(1, 256, "Apple", 3100, 'A');
	
	int nrTelefoane = 3;
	struct Telefon* telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrTelefoane);
	telefoane[0] = initializare(1, 256, "Apple", 3200, 'A');
	telefoane[1] = initializare(2, 256, "Samsung", 2500, 'S');
	telefoane[2] = telefon;
	afisareVector(telefoane, nrTelefoane);
	int nrTelefoaneCopiate = 2;
	struct Telefon* telefoaneCopiate = copiazaPrimeleNElemente(telefoane, nrTelefoane, nrTelefoaneCopiate);
	printf("Vector telefoane copiate: \n");
	afisareVector(telefoaneCopiate, nrTelefoaneCopiate);
	dezalocare(&nrTelefoaneCopiate, &nrTelefoaneCopiate);
	printf("Dupa dezalocare: \n");
	afisareVector(telefoane, nrTelefoane);
	struct Telefon* vectorNou;
	int dimensiune;
	copiazaTelefoaneScumpe(telefoane, nrTelefoane, 2700, &vectorNou, &dimensiune);
	printf("Telefoane scumpe:\n");
	afisareVector(vectorNou, dimensiune);

	return 0;
}