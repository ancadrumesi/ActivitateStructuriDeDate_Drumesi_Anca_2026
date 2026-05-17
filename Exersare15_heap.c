//#define _CRT_SECURE_NO_WARNINGS 
//#include <stdio.h>
//#include <stdlib.h>
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
//typedef struct Heap Heap;
//struct Heap
//{
//	int lungime;
//	int nrElemVizibile;
//	Student* vector;
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
//	printf("Varsta: %d\n", student.varsta);
//	printf("Medie: %.2f\n", student.medie);
//}
//
//
//Heap initializareHeap(int lungime)
//{
//	Heap heap;
//	heap.lungime = lungime;
//	heap.nrElemVizibile = 0;
//	heap.vector = (Student*)malloc(sizeof(Student) * lungime);
//	return heap;
//}
//
//void filtreazaHeap(Heap heap, int pozitieNod)
//{
//	int stanga = 2 * pozitieNod + 1;
//	int dreapta = 2 * pozitieNod + 2;
//	int pozMax = pozitieNod;
//	if (stanga < heap.nrElemVizibile && heap.vector[stanga].medie > heap.vector[pozMax].medie)
//	{
//		pozMax = stanga;
//	}
//
//	if (dreapta < heap.nrElemVizibile && heap.vector[dreapta].medie > heap.vector[pozMax].medie)
//	{
//		pozMax = dreapta;
//	}
//
//	if (pozMax != pozitieNod)
//	{
//		Student aux;
//		aux = heap.vector[pozMax];
//		heap.vector[pozMax] = heap.vector[pozitieNod];
//		heap.vector[pozitieNod] = aux;
//		if (pozMax < (heap.nrElemVizibile - 2) / 2)
//		{
//			filtreazaHeap(heap, pozMax);
//		}
//	}
//}
//
//Heap citireHeapDeFloriDinFisier(const char* numeFisier)
//{
//	FILE* file = fopen(numeFisier, "r");
//	Heap heap = initializareHeap(10);
//	if (file)
//	{
//		while (!feof(file))
//		{
//			heap.vector[heap.nrElemVizibile++] = citireStudentDinFisier(file);
//		}
//	}
//
//	for (int i = (heap.nrElemVizibile - 2) / 2; i > -0; i--)
//	{
//		filtreazaHeap(heap, i);
//	}
//	fclose(file);
//	return heap;
//}
//
//
//void afisareHeap(Heap heap)
//{
//	for (int i = 0; i < heap.nrElemVizibile; i++)
//	{
//		afisareStudent(heap.vector[i]);
//	}
//}
//
//void afiseazaHeapAscuns(Heap heap)
//{
//	for (int i = heap.nrElemVizibile; i < heap.lungime; i++)
//	{
//		afisareStudeent(heap.vector[i]);
//	}
//}
//
//Student extragereStudent(Heap* heap)
//{
//	Student aux;
//	aux.id = -1;
//	if (heap->nrElemVizibile > 0)
//	{
//		heap->nrElemVizibile--;
//		aux = heap->vector[0];
//		heap->vector[0] = heap->vector[heap->nrElemVizibile];
//		heap->vector[heap->nrElemVizibile] = aux;
//		filtreazaHeap(*heap, 0);
//	}
//
//	return aux;
//}
//
//void dezalocareHeap(Heap* heap)
//{
//	for (int i = 0; i < heap->lungime; i++)
//	{
//		if (heap->vector[i].nume)
//			free(heap->vector[i].nume);
//	}
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->nrElemVizibile = 0;
//	heap->lungime = 0;
//}
//
//int main()
//{
//	Heap heap = citireHeapDeFloriDinFisier("studenti.txt");
//	afisareHeap(heap);
//	printf("Extrage:\n");
//	afisareStudent(extragereStudent(&heap));
//	afisareStudent(extragereStudent(&heap));
//	afisareStudent(extragereStudent(&heap));
//	printf("Heap ascuns:\n");
//	afiseazaHeapAscuns(heap);
//	dezalocareHeap(&heap);
//
//	return 0;
//}