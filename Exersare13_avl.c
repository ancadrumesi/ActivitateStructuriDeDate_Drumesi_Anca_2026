#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Student Student;
struct Student
{
	int id;
	char* nume;
	int varsta;
	float medie;
};

typedef struct NodArbore NodArbore;
struct NodArbore
{
	Student info;
	NodArbore* stanga;
	NodArbore* dreapta;
};

Student citireStudentDinFisier(FILE* file)
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Student s1;
	aux = strtok(buffer, sep);
	s1.id = atoi(aux);
	s1.nume = malloc(strlen(aux) + 1);
	strcpy_s(s1.nume, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	s1.varsta = atoi(aux);
	s1.medie = atof(strtok(NULL, sep));
	return s1;
}

void afisareStudent(Student student)
{
	printf("Id: %d\n", student.id);
	printf("Nume: %s\n", student.nume);
	printf("Varsta: %d\n", student.varsta);
	printf("Medie: %.2f\n", student.medie);
}

int calculeazaInaltimeArbore(NodArbore* radacina)
{
	if (radacina == NULL)
	{
		return 0;
	}

	int dreapta = calculeazaInaltimeArbore(radacina->dreapta);
	int stanga = calculeazaInaltimeArbore(radacina->stanga);
	return 1 + max(dreapta, stanga);
}

void rotireStanga(NodArbore** radacina)
{
	NodArbore* aux = (*radacina)->dreapta;
	(*radacina)->dreapta = aux->stanga;
	aux->stanga = (*radacina);
	(*radacina) = aux;
}



int main()
{



	return 0;

}