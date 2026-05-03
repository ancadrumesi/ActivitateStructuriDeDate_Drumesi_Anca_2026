#define _CRT_SECURE_WARNINGS
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

typedef struct Nod Nod;
struct Nod
{
	Nod* stanga;
	Nod* dreapta;
	Student info;
};

int main()
{
	return 0;
}