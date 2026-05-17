//#define _CRT_SECURE_NO_WARNINGS 
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//
//typedef struct Florarie Florarie;
//struct Florarie
//{
//	int id;
//	char* denumire;
//	float pret;
//	int stoc;
//};
//
//typedef struct Nod Nod;
//struct Nod
//{
//	Nod* stanga;
//	Nod* dreapta;
//	Florarie info;
//};
//
//Florarie citireFloareDinFisier(FILE* file)
//{
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Florarie f1;
//	aux = strtok(buffer, sep);
//	f1.id = atoi(aux);
//	aux = strtok(NULL, sep);
//	f1.denumire = malloc(strlen(aux) + 1);
//	strcpy_s(f1.denumire, strlen(aux) + 1, aux);
//	f1.pret = atof(strtok(NULL, sep));
//	f1.stoc = atoi(strtok(NULL, sep));
//	return f1;
//}
//
//void afisareFlorarie(Florarie florarie)
//{
//	printf("Id: %d\n", florarie.id);
//	printf("Floare: %s\n", florarie.denumire);
//	printf("Pret: %.2f\n", florarie.pret);
//	printf("Stoc: %d\n", florarie.stoc);
//}
//
//void adaugaFloareInArbore(Nod** radacina, Florarie floareNoua)
//{
//	if (*radacina)
//	{
//		if ((*radacina)->info.id < floareNoua.id)
//		{
//			adaugaFloareInArbore(&(*radacina)->dreapta, floareNoua);
//		}
//
//		if ((*radacina)->info.id > floareNoua.id)
//		{
//			adaugaFloareInArbore(&(*radacina)->stanga, floareNoua);
//		}
//	}
//	else
//	{
//		Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//		nodNou->info = floareNoua;
//		nodNou->stanga = NULL;
//		nodNou->dreapta = NULL;
//		*radacina = nodNou;
//	}
//}
//
//void* citireArboreDeMasiniDinFisier(const char* numeFisier)
//{
//	Nod* radacina = NULL;
//	FILE* file = fopen(numeFisier, "r");
//	while (!feof(file))
//	{
//		adaugaFloareInArbore(&radacina, citireFloareDinFisier(file));
//	}
//	fclose(file);
//	return radacina;
//}
//
//void afisareFloriDinArborePreordine(Nod* radacina)
//{
//	if (radacina)
//	{
//		afisareFlorarie(radacina->info);
//		afisareFloriDinArborePreordine(radacina->stanga);
//		afisareFloriDinArborePreordine(radacina->dreapta);
//	}
//}
//
//void afisareFloriDinArboreInordine(Nod* radacina)
//{
//	if (radacina)
//	{
//		afisareFloriDinArboreInordine(radacina->stanga);
//		afisareFlorarie(radacina->info);
//		afisareFloriDinArboreInordine(radacina->dreapta);
//	}
//}
//
//void dezalocareArbore(Nod** radacina)
//{
//	if (*radacina) 
//	{
//		dezalocareArbore(&(*radacina)->stanga);
//		dezalocareArbore(&(*radacina)->dreapta);
//		free((*radacina)->info.denumire);
//		free(*radacina);
//		*radacina = NULL;
//	}
//}
//
//Florarie getFloareById(Nod* radacina, int idCautat)
//{
//	if (radacina)
//	{
//		if (radacina->info.id == idCautat)
//		{
//			Florarie f = radacina->info;
//			f.denumire = (char*)malloc(strlen(radacina->info.denumire) + 1);
//			strcpy_s(f.denumire, strlen(radacina->info.denumire) + 1, radacina->info.denumire);
//			return f;
//		}
//
//		if (radacina->info.id < idCautat)
//		{
//			return getFloareById(radacina->dreapta, idCautat);
//		}
//		if (radacina->info.id > idCautat)
//		{
//			return getFloareById(radacina->stanga, idCautat);
//		}
//	}
//	else
//	{
//		Florarie f;
//		f.id = -1;
//		return f;
//	}
//}
//
//int determinaNumarNoduri(Nod* radacina)
//{
//	if (radacina)
//	{
//		return determinaNumarNoduri(radacina->stanga) + determinaNumarNoduri(radacina->dreapta) + 1;
//	}
//
//	return 0;
//}
//
//int calculeazaInaltimeArbore(Nod* radacina)
//{
//	//inaltimea maxima a arborelui e data de lungimea dintre radacina si cel mai indepartat nod frunza
//	if (radacina)
//	{
//		int inaltimeStg = calculeazaInaltimeArbore(radacina->stanga);
//		int inaltimeDrpt = calculeazaInaltimeArbore(radacina->dreapta);
//		return inaltimeStg > inaltimeDrpt ? inaltimeStg + 1 : inaltimeDrpt + 1;
//	}
//
//	return 0;
//}
//
//float calculeazaPretTotal(Nod* radacina)
//{
//	if (radacina)
//	{
//		return calculeazaPretTotal(radacina->stanga) + calculeazaPretTotal(radacina->dreapta) + radacina->info.pret;
//	}
//
//	return 0;
//}
//
//float calculeazaPretulBujorilor(Nod* radacina, const char* denumire)
//{
//	if (radacina)
//	{
//		float suma = calculeazaPretulBujorilor(radacina->stanga, denumire) + calculeazaPretulBujorilor(radacina->dreapta, denumire);
//		if (strcmp(radacina->info.denumire, denumire) == 0)
//		{
//			return suma + radacina->info.pret;
//		}
//		else
//		{
//			return suma;
//		}
//	}
//	else
//	{
//		return 0;
//	}
//
//	return 0;
//}
//
//int main()
//{
//	Nod* radacina = citireArboreDeMasiniDinFisier("florarie_arbore.txt");
//	afisareFloriDinArboreInordine(radacina);
//	afisareFlorarie(getFloareById(radacina, 1));
//	printf("Numar noduri in arbore: %d\n", determinaNumarNoduri(radacina));
//	printf("Inaltimea arborelui este: %d\n", calculeazaInaltimeArbore(radacina));
//	printf("Pretul total al florilor din florarie este: %.2f\n", calculeazaPretTotal(radacina));
//	printf("Pret total al florilor de tip Bujor este: %.2f\n", calculeazaPretulBujorilor(radacina, "Bujor"));
//
//	dezalocareArbore(&radacina);
//	printf("dupa dezalocare\n");
//	afisareFloriDinArboreInordine(radacina);
//
//	return 0;
//}