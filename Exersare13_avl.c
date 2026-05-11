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

void rotireDreapta(NodArbore** radacina)
{
	NodArbore* aux = (*radacina)->stanga;
	(*radacina)->stanga = aux -> dreapta;
	aux->dreapta = (*radacina);
	(*radacina) = aux;
}

int verificareEchilibru(NodArbore* radacina)
{
	return calculeazaInaltimeArbore(radacina->stanga) - calculeazaInaltimeArbore(radacina->dreapta);
}

void adaugaStudentInArboreEchilibrat(NodArbore** radacina, Student studentNou)
{
	if ((*radacina) != NULL)
	{
		if (studentNou.id > (*radacina)->info.id)
		{
			adaugaStudentInArboreEchilibrat(&(*radacina)->dreapta, studentNou);
		}
		else
		{
			adaugaStudentInArboreEchilibrat(&(*radacina)->stanga, studentNou);
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
		nodNou->info = studentNou;
		(*radacina) = nodNou;
	}
}

NodArbore* citireArboreDeStudentiDinFisier(const char* numeFisier)
{
	NodArbore* radacina = NULL;
	FILE* file = fopen(numeFisier, "r");
	if (file)
	{
		while (!feof(file))
		{
			adaugaStudentInArboreEchilibrat(&radacina, citireStudentDinFisier(file));
		}
	}
	fclose(file);
	return radacina;
}

void afisareStudentiDinArbore(NodArbore* radacina)
{
	if (radacina)
	{
		afisareStudent(radacina->info);
		afisareStudentiDinArbore(radacina->stanga);
		afisareStudentiDinArbore(radacina->dreapta);
	}
}

void dezalocareArboreDeStudenti(NodArbore** radacina)
{
	if (*radacina)
	{
		dezalocareArboreDeStudenti(&(*radacina)->stanga);
		dezalocareArboreDeStudenti(&(*radacina)->dreapta);
		free((*radacina)->info.nume);
		*radacina = NULL;
	}
}

Student getStudentById(NodArbore* radacina, int idCautat)
{
	if (radacina)
	{
		if (radacina->info.id == idCautat)
		{
			Student s = radacina->info;
			s.nume = (char*)malloc(strlen(radacina->info.nume) + 1);
			strcpy(s.nume, radacina->info.nume);
			return s;
		}

		if (radacina->info.id < idCautat)
		{
			return getStudentById(radacina->dreapta, idCautat);
		}

		if (radacina->info.id > idCautat)
		{
			return getStudentById(radacina->stanga, idCautat);
		}
	}
	else
	{
		Student s;
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

float calculeazaMedieTotala(NodArbore* radacina)
{
	if (radacina)
	{
		return (calculeazaMedieTotala(radacina->stanga) + calculeazaMedieTotala(radacina->dreapta) + radacina->info.medie)/determinaNumarNoduri(radacina);
	}

}

int main()
{
	NodArbore* radacina = citireArboreDeStudentiDinFisier("studenti.txt");
	afisareStudentiDinArbore(radacina);
	dezalocareArboreDeStudenti(&radacina);

	printf("Studentul cu id-ul %d este: ", getStudentById(radacina, 1));
	printf("Numarul de noduri din arbore este: ", determinaNumarNoduri(radacina));
	printf("Media totala a studentilor este: ", calculeazaMedieTotala(radacina));

	return 0;

}