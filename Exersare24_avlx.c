#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Casa Casa;
struct Casa
{
	int id;
	int nrCamere;
	char* tip;
	float dimensiune;
	int pret;
};

typedef struct NodArbore NodArbore;
struct NodArbore
{
	NodArbore* stanga;
	NodArbore* dreapta;
	Casa info;
};

Casa citireCasaDinFisier(FILE* file)
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Casa c;
	aux = strtok(buffer, sep);
	c.id = atoi(aux);
	aux = strtok(NULL, sep);
	c.nrCamere = atoi(aux);
	aux = strtok(NULL, sep);
	c.tip = (char*)malloc(strlen(aux) + 1);
	strcpy(c.tip, aux);
	aux = strtok(NULL, sep);
	c.dimensiune = atof(aux);
	aux = strtok(NULL, sep);
	c.pret = atoi(aux);
	return c;
}

void afisareCasa(Casa casa)
{
	printf("Id: %d\n", casa.id);
	printf("Nr. camere: %d\n", casa.nrCamere);
	printf("Tip: %s\n", casa.tip);
	printf("Dimensiune: %.2f\n", casa.dimensiune);
	printf("Pret: %d\n", casa.pret);
}

int calculeazaInaltimeArbore(NodArbore* radacina)
{
	if (radacina==NULL)
	{
		return 0;
	}

	int dr = calculeazaInaltimeArbore(radacina->dreapta);
	int stg = calculeazaInaltimeArbore(radacina->stanga);
	return max(dr, stg) + 1;
}

void rotireStanga(NodArbore** radacina)
{
	NodArbore* aux = (*radacina)->dreapta;
	(*radacina)->dreapta = aux->stanga;
	aux->stanga = *radacina;
	*radacina = aux;
}

void rotireDreapta(NodArbore** radacina)
{
	NodArbore* aux = (*radacina)->stanga;
	(*radacina)->stanga = aux->dreapta;
	aux->dreapta = *radacina;
	*radacina = aux;
}

int verificareEchilibruArbore(NodArbore* radacina)
{
	return calculeazaInaltimeArbore(radacina->stanga) - calculeazaInaltimeArbore(radacina->dreapta);
}

void inserareCasaInArboreEchilibrat(NodArbore** radacina, Casa casaNoua)
{
	if (*radacina)
	{
		if ((*radacina)->info.id < casaNoua.id)
		{
			inserareCasaInArboreEchilibrat(&(*radacina)->dreapta, casaNoua);
		}

		if ((*radacina)->info.id > casaNoua.id)
		{
			inserareCasaInArboreEchilibrat(&(*radacina)->stanga, casaNoua);
		}

		int factorEchilibru = verificareEchilibruArbore(radacina);
		if (factorEchilibru == -2)
		{
			if (verificareEchilibruArbore((*radacina)->dreapta) == -1)
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
			if (verificareEchilibruArbore((*radacina)->stanga) == -1)
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
		nodNou->info = casaNoua;
		*radacina = nodNou;
	}
}

NodArbore* citireArboreDeCaseDinFisier(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	NodArbore* radacina;
	if (file)
	{
		while (!feof(file))
		{
			inserareCasaInArboreEchilibrat(&radacina, citireCasaDinFisier(file));
		}
	}
	fclose(file);
	return radacina;
}

void afisareCaseDinArbore(NodArbore* radacina)
{
	if (radacina)
	{
		afisareCasa(radacina->info);
		afisareCaseDinArbore(radacina->stanga);
		afisareCaseDinArbore(radacina->dreapta);
	}
}



int main()
{
	NodArbore* radacina = citireArboreDeCaseDinFisier("casa.txt");
	afisareCaseDinArbore(radacina);

	return 0;
}