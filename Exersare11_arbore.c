//#define _CRT_SECURE_WARNINGS
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//
//typedef struct Student Student;
//struct Student
//{
//	int id;
//	char* nume;
//	int varsta;
//	float medie;
//};
//
//typedef struct Nod Nod;
//struct Nod
//{
//	Nod* stanga;
//	Nod* dreapta;
//	Student info;
//};
//
//Student citireStudentDinFisier(FILE* file)
//{
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Student s;
//	aux = strtok(buffer, sep);
//	s.id = atoi(aux);
//	aux = strtok(NULL, sep);
//	s.nume = malloc(strlen(aux) + 1);
//	strcpy_s(s.nume, strlen(aux) + 1, aux);
//	s.varsta = atoi(strtok(NULL, sep));
//	s.medie = atof(strtok(NULL, sep));
//	return s;
//}
//
//void afisareStudent(Student student)
//{
//	printf("Id: %d\n", student.id);
//	printf("Nume: %s\n", student.nume);
//	printf("varsta: %d\n", student.varsta);
//	printf("medie: %.2f\n", student.medie);
//}
//
//void adaugaStudentInArbore(Nod** radacina, Student studentNou)
//{
//	if (*radacina)
//	{
//		if ((*radacina)->info.id < studentNou.id)
//		{
//			adaugaStudentInArbore(&(*radacina)->dreapta, studentNou);
//		}
//		if ((*radacina)->info.id > studentNou.id)
//		{
//			adaugaStudentInArbore(&(*radacina) -> stanga, studentNou);
//		}
//	}
//	else
//	{
//		Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//		nodNou->info = studentNou;
//		nodNou->stanga = NULL;
//		nodNou->dreapta = NULL;
//		*radacina = nodNou;
//	}
//}
//
//void* citireArboreDeStudentiDinFisier(const char* numeFisier)
//{
//	Nod* radacina = NULL;
//	FILE* file = fopen(numeFisier, "r");
//	while (!feof(file))
//	{
//		adaugaStudentInArbore(&radacina, citireStudentDinFisier(file));
//	}
//	fclose(file);
//	return radacina;
//}
//
//void afisarePreordine(Nod* radacina)
//{
//	if (radacina)
//	{
//		afisareStudent(radacina->info);
//		afisarePreordine(radacina->stanga);
//		afisarePreordine(radacina->dreapta);
//	}
//}
//
//void afisareInordine(Nod* radacina)
//{
//	if (radacina)
//	{
//		afisareInordine(radacina->stanga);
//		afisareStudent(radacina->info);
//		afisareInordine(radacina->dreapta);
//	}
//}
//
//void dezalocare(Nod** radacina)
//{
//	if (*radacina)
//	{
//		dezalocare(&(*radacina)->stanga);
//		dezalocare(&(*radacina)->dreapta);
//		free((*radacina)->info.nume);
//		free(*radacina);
//		*radacina = NULL;
//	}
//}
//
//Student getStudentById(Nod* radacina, int idCautat)
//{
//	if (radacina)
//	{
//		if (radacina->info.id == idCautat)
//		{
//			Student s = radacina->info;
//			s.nume = (char*)malloc(strlen(radacina->info.nume) + 1);
//			strcpy_s(s.nume, strlen(radacina->info.nume) + 1, radacina->info.nume);
//			return s;
//		}
//
//		if (radacina->info.id < idCautat)
//		{
//			return getStudentById(radacina->dreapta, idCautat);
//		}
//
//		if (radacina->info.id > idCautat)
//		{
//			return getStudentById(radacina->stanga, idCautat);
//		}
//	}
//	else {
//		Student s;
//		s.id = -1;
//		return s;
//	}
//}
//
//int main()
//{
//	Nod* radacina = citireArboreDeStudentiDinFisier("studenti.txt");
//	afisareInordine(radacina);
//
//	getStudentById(radacina, 1);
//
//	printf("dupa dezalocare:\n");
//	dezalocare(&radacina);
//	afisareInordine(radacina);
//	return 0;
//}