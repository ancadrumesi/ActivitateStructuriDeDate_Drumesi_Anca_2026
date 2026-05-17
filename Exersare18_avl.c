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

typedef struct NodArbore NodArbore;
struct NodArbore
{
	Serial info;
	NodArbore* stanga;
	NodArbore* dreapta;
};

Serial citireSerialDinFisier(FILE* file)
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Serial s;
	aux = strtok(buffer, sep);
	s.id = atoi(aux);
	aux = strtok(NULL, sep);
	s.nrSezoane = atoi(aux);
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
	printf("Nr sezoane: %d\n", serial.nrSezoane);
	printf("Nume serial: %s\n", serial.numeSerial);
	printf("Personaj: %s\n", serial.personaj);
	printf("Rating: %.2f\n", serial.rating);
}

int calculeazaInaltimeArbore(NodArbore* radacina)
{
	if (radacina == NULL)
	{
		return 0;
	}
	int inaltimeDreapta = calculeazaInaltimeArbore(radacina->dreapta);
	int inaltimeStanga = calculeazaInaltimeArbore(radacina->stanga);
	return 1 + max(inaltimeDreapta, inaltimeStanga);
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

void adaugaSerialInArboreEchilibrat(NodArbore** radacina, Serial serialNou)
{
	if ((*radacina) != NULL)
	{
		if ((*radacina)->info.id < serialNou.id)
		{
			adaugaSerialInArboreEchilibrat(&(*radacina)->dreapta, serialNou);
		}
		else
		{
			adaugaSerialInArboreEchilibrat(&(*radacina)->stanga, serialNou);
		}

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
		nodNou->info = serialNou;
		(*radacina) = nodNou;
	}
}

NodArbore* citireArboreDeSerialeDinFisier(const char* numeFisier)
{
	NodArbore* radacina = NULL;
	FILE* file = fopen(numeFisier, "r");
	if (file)
	{
		while (!feof(file))
		{
			adaugaSerialInArboreEchilibrat(&radacina, citireSerialDinFisier(file));
		}
	}
	fclose(file);
	return radacina;
}

void afisareSerialeDinArbore(NodArbore* radacina)
{
	if (radacina)
	{
		afisareSerial(radacina->info);
		afisareSerialeDinArbore(radacina->stanga);
		afisareSerialeDinArbore(radacina->dreapta);
	}
}

void dezalocare(NodArbore** radacina)
{
	if (*radacina)
	{
		dezalocare(&(*radacina)->stanga);
		dezalocare(&(*radacina)->dreapta);
		free((*radacina)->info.numeSerial);
		free((*radacina)->info.personaj);
		*radacina = NULL;
	}
}

Serial getSerialById(NodArbore* radacina, int idCautat)
{
	if (radacina)
	{
		if (radacina->info.id == idCautat)
		{
			Serial s = radacina->info;
			s.numeSerial = (char*)malloc(strlen(radacina->info.numeSerial) + 1);
			strcpy(s.numeSerial, radacina->info.numeSerial);
			return s;
		}
		if (radacina->info.id < idCautat)
		{
			return getSerialById(radacina->dreapta, idCautat);
		}
		if (radacina->info.id > idCautat)
		{
			return getSerialById(radacina->stanga, idCautat);
		}
	}
	else
	{
		Serial s;
		s.id = -1;
		return s;
	}
}

int determinaNumarNoduri(NodArbore* radacina)
{
	if (radacina)
	{
		return determinaNumarNoduri(radacina->stanga) + determinaNumarNoduri(radacina->dreapta) + 1;
	}
	return 0;
}

float calculeazaRatingTotal(NodArbore* radacina)
{
	if (radacina)
	{
		return calculeazaRatingTotal(radacina->stanga) + calculeazaRatingTotal(radacina->dreapta) + (radacina->info.rating) / determinaNumarNoduri(radacina);
	}
}

int main()
{
	NodArbore* radacina = citireArboreDeSerialeDinFisier("seriale.txt");
	afisareSerialeDinArbore(radacina);
	printf("Serialul cu id-ul %d este: ", getSerialById(radacina, 5));
	printf("Numarul de noduri din arbore este: ", determinaNumarNoduri(radacina));
	printf("Rating total pentru seriale: ", calculeazaRatingTotal(radacina));
	dezalocare(&radacina);

	return 0;
}