#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Artist Artist;
struct Artist
{
	int id;
	char* nume;
	int nrAlbume;
	float medieAscultatori;
};

typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct NodPrincipal
{
	NodPrincipal* next;
	Artist info;
	NodSecundar* vecini;
};

struct NodSecundar
{
	NodSecundar* next;
	NodPrincipal* info;
};

Artist citireArtistDinFisier(FILE* file)
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Artist a;
	aux = strtok(buffer, sep);
	a.id = atoi(aux);
	aux = strtok(NULL, sep);
	a.nume = (char*)malloc(strlen(aux) + 1);
	strcpy(a.nume, aux);
	aux = strtok(NULL, sep);
	a.nrAlbume = atoi(aux);
	aux = strtok(NULL, sep);
	a.medieAscultatori = atof(aux);
	return a;
}

void afisareArtist(Artist artist)
{
	printf("Id: %d\n", artist.id);
	printf("Nume: %s\n", artist.nume);
	printf("Numar albume: %d\n", artist.nrAlbume);
	printf("Medie ascultatori: %.2f\n", artist.medieAscultatori);
}

void inserareListaPrincipala(NodPrincipal** graf, Artist artistNou)
{
	NodPrincipal* nodNou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nodNou->info = artistNou;
	nodNou->next = NULL;
	nodNou->vecini = NULL;

	if (*graf)
	{
		NodPrincipal* aux = *graf;
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

void inserareListaSecundara(NodSecundar** listaS, NodPrincipal* info)
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

NodPrincipal* cautaNodDupaIdInListaPrincipala(NodPrincipal* listaP, int idCautat)
{
	if (listaP)
	{
		while ((listaP) && listaP->info.id != idCautat)
		{
			listaP = listaP->next;
		}
		return listaP;
	}
}

void inserareMuchie(NodPrincipal* listaP, int idStart, int idStop)
{
	if (listaP)
	{
		NodPrincipal* nodStart = cautaNodDupaIdInListaPrincipala(listaP, idStart);
		NodPrincipal* nodStop = cautaNodDupaIdInListaPrincipala(listaP, idStop);
		if (nodStart && nodStop)
		{
			inserareListaSecundara(&nodStart->vecini, nodStop);
			inserareListaSecundara(&nodStop->vecini, nodStart);
		}
	}
}

NodPrincipal* citireGrafDeArtistiDinFisier(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	NodPrincipal* listaP = NULL;
	if (file)
	{
		while (!feof(file))
		{
			inserareListaPrincipala(&listaP, citireArtistDinFisier(file));
		}
	}
	fclose(file);
	return listaP;
}

void citireMuchiiDinFisier(NodPrincipal* listaP, const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	int idStart;
	int idStop;
	while (!feof(file))
	{
		fscanf(file, "%d %d", &idStart, &idStop);
		inserareMuchie(listaP, idStart, idStop);
	}
	fclose(file);
}

void afisareLista(NodPrincipal* graf, int id)
{
	NodPrincipal* nod = cautaNodDupaIdInListaPrincipala(graf, id);
	NodSecundar* cap = nod->vecini;
	while (cap)
	{
		afisareArtist(cap->info->info);
		cap = cap->next;
	}
}

void dezalocare(NodPrincipal** graf)
{
	while (*graf)
	{
		NodPrincipal* p = *graf;
		NodSecundar* s = p->vecini;
		while (s)
		{
			NodSecundar* auxS = s;
			s = s->next;
			free(auxS);
		}
		free(p->info.nume);
		*graf = p->next;
		free(p);
	}
}

int main()
{
	NodPrincipal* graf = citireGrafDeArtistiDinFisier("artisti.txt");
	citireMuchiiDinFisier(graf, "muchii.txt");
	afisareLista(graf, 6);
	dezalocare(&graf);
	printf("Dezalocare cu succes!");
	return 0;
}