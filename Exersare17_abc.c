//#define _CRT_SECURE_NO_WARNINGS
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//
//typedef struct Seriale Seriale;
//struct Seriale
//{
//	int id; 
//	int nrSezoane;
//	char* numeSerial;
//	char* personaj;
//	float rating;
//};
//
//typedef struct Nod Nod;
//struct Nod
//{
//	Seriale info;
//	Nod* stanga;
//	Nod* dreapta;
//};
//
//Seriale citireSerialDinFisier(FILE* file)
//{
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Seriale s;
//	aux = strtok(buffer, sep);
//	s.id = atoi(aux);
//	s.nrSezoane = atoi(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	s.numeSerial = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(s.numeSerial, strlen(aux) + 1, aux);
//	aux = strtok(NULL, sep);
//	s.personaj = (char*)malloc(strlen(aux) + 1);
//	strcpy_s(s.personaj, strlen(aux) + 1, aux);
//	s.rating = atof(strtok(NULL, sep));
//	return s;
//}
//
//void afisareSerial(Seriale serial)
//{
//	printf("Id: %d\n", serial.id);
//	printf("Numar sezoane: %d\n", serial.nrSezoane);
//	printf("Nume serial: %s\n", serial.numeSerial);
//	printf("Personaj: %s\n", serial.personaj);
//	printf("Rating: %.2f\n", serial.rating);
//}
//
//void inserareSerialInArbore(Nod** radacina, Seriale serialNou)
//{
//	if (*radacina)
//	{
//		if ((*radacina)->info.id < serialNou.id)
//		{
//			inserareSerialInArbore(&(*radacina)->dreapta, serialNou);
//		}
//
//		if ((*radacina)->info.id > serialNou.id)
//		{
//			inserareSerialInArbore(&(*radacina)->stanga, serialNou);
//		}
//	}
//	else
//	{
//		Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//		nodNou->info = serialNou;
//		nodNou->stanga = NULL;
//		nodNou->dreapta = NULL;
//		*radacina = nodNou;
//	}
//}
//
//Nod* citireArboreDeSerialeDinFisier(const char* numeFisier)
//{
//	Nod* radacina = NULL;
//	FILE* file = fopen(numeFisier, "r");
//	while (!feof(file))
//	{
//		inserareSerialInArbore(&radacina, citireSerialDinFisier(file));
//	}
//	fclose(file);
//	return radacina;
//}
//
//void afisareSerialeDinArborePreordine(Nod* radacina)
//{
//	if (radacina)
//	{
//		afisareSerial(radacina->info);
//		afisareSerialeDinArborePreordine(radacina->stanga);
//		afisareSerialeDinArborePreordine(radacina->dreapta);
//	}
//}
//
//void afisareSerialeDinArboreInordine(Nod* radacina)
//{
//	if (radacina)
//	{
//		afisareSerialeDinArboreInordine(radacina->stanga);
//		afisareSerial(radacina->info);
//		afisareSerialeDinArboreInordine(radacina->dreapta);
//	}
//}
//
//void dezalocareArboreDeSeriale(Nod** radacina)
//{
//	if (*radacina)
//	{
//		dezalocareArboreDeSeriale(&(*radacina)->stanga);
//		dezalocareArboreDeSeriale(&(*radacina)->dreapta);
//		free((*radacina)->info.numeSerial);
//		free((*radacina)->info.personaj);
//		free((*radacina));
//		*radacina = NULL;
//	}
//}
//
//Seriale getSerialByID(Nod* radacina, int idCautat)
//{
//	if (radacina)
//	{
//		if (radacina->info.id == idCautat)
//		{
//			Seriale s = radacina->info;
//			s.numeSerial = (char*)malloc(strlen(radacina->info.numeSerial) + 1);
//			strcpy(s.numeSerial, radacina->info.numeSerial);
//			s.personaj = (char*)malloc(strlen(radacina->info.personaj) + 1);
//			strcpy(s.personaj, radacina->info.personaj);
//			return s;
//		}
//		if (radacina->info.id < idCautat)
//		{
//			return getSerialByID(radacina->dreapta, idCautat);
//		}
//		if (radacina->info.id > idCautat)
//		{
//			return getSerialByID(radacina->stanga, idCautat);
//		}
//	}
//	else
//	{
//		Seriale s;
//		s.id = -1;
//		return s;
//	}
//}
//
//int determinaNumarNoduri(Nod* radacina)
//{
//	if (radacina)
//	{
//		return determinaNumarNoduri(radacina->stanga) + determinaNumarNoduri(radacina->dreapta) + 1;
//	}
//	return 0;
//}
//
//int calculeazaInaltimeArbore(Nod* radacina)
//{
//	if (radacina)
//	{
//		int inaltimeStanga = calculeazaInaltimeArbore(radacina->stanga);
//		int inaltimeDreapta = calculeazaInaltimeArbore(radacina->dreapta);
//		return inaltimeStanga > inaltimeDreapta ? inaltimeStanga + 1 : inaltimeDreapta + 1;
//	}
//	return 0;
//}
//
//
//
//int main()
//{
//	printf("Sper ca merge!\n");
//	Nod* radacina = citireArboreDeSerialeDinFisier("seriale.txt");
//	if (radacina == NULL) {
//		printf("Eroare: Arborele este NULL. Verifica fisierul!\n");
//	}
//	else {
//		printf("Arborele a fost incarcat. Incepem afisarea:\n");
//		afisareSerialeDinArboreInordine(radacina);
//	}
//
//	afisareSerial(getSerialByID(radacina, 5));
//
//	printf("numar noduri: %d\n", determinaNumarNoduri(radacina));
//	printf("inaltime arbore: %d\n", calculeazaInaltimeArbore(radacina));
//
//	dezalocareArboreDeSeriale(&radacina);
//	printf("\nSfarsit program. Apasa o tasta...");
//
//	return 0;
//}