//#define _CRT_SECURE_NO_WARNINGS 
//#include <string.h>
//#include <stdlib.h>
//#include <stdio.h>
//
//typedef struct Florarie Florarie;
//struct Florarie
//{
//	int id;
//	char* tip;
//	float pret;
//	int cantitate;
//};
//
//typedef struct Heap Heap;
//struct Heap
//{
//	int lungime;
//	int nrElementeVizibile;
//	Florarie* vector;
//};
//
//Florarie citireFlorarieDinFisier(FILE* file)
//{
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Florarie f;
//	aux = strtok(buffer, sep);
//	f.id = atoi(aux);
//	aux = strtok(NULL, sep);
//	f.tip = malloc(strlen(aux) + 1);
//	strcpy_s(f.tip, strlen(aux) + 1, aux);
//	f.pret = atof(strtok(NULL, sep));
//	f.cantitate = atoi(strtok(NULL, sep));
//	return f;
//}
//
//void afisareFloare(Florarie floare)
//{
//	printf("Id: %d\n", floare.id);
//	printf("Tip: %s\n", floare.tip);
//	printf("Pret: %.2f\n", floare.pret);
//	printf("Cantitate: %d\n", floare.cantitate);
//}
//
//Heap initializareHeap(int lungime)
//{
//	Heap heap;
//	heap.lungime = lungime;
//	heap.nrElementeVizibile = 0;
//	heap.vector = (Florarie*)malloc(sizeof(Florarie) * lungime);
//	return heap;
//}
//
//void filtreazaHeap(Heap heap, int pozitieNod)
//{
//	int stanga = 2 * pozitieNod + 1;
//	int dreapta = 2 * pozitieNod + 2;
//	int pozMax = pozitieNod;
//	if (stanga < heap.nrElementeVizibile && heap.vector[stanga].pret > heap.vector[pozMax].pret)
//	{
//		pozMax = stanga;
//	}
//
//	if (dreapta < heap.nrElementeVizibile && heap.vector[dreapta].pret > heap.vector[pozMax].pret)
//	{
//		pozMax = dreapta;
//	}
//
//	if (pozMax != pozitieNod)
//	{
//		Florarie aux;
//		aux = heap.vector[pozMax];
//		heap.vector[pozMax] = heap.vector[pozitieNod];
//		heap.vector[pozitieNod] = aux;
//		if (pozMax < (heap.nrElementeVizibile - 2) / 2)
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
//			heap.vector[heap.nrElementeVizibile++] = citireFlorarieDinFisier(file);
//		}
//	}
//
//	for (int i = (heap.nrElementeVizibile - 2) / 2; i > -0; i--)
//	{
//		filtreazaHeap(heap, i);
//	}
//	fclose(file);
//	return heap;
//}
//
//void afisareHeap(Heap heap)
//{
//	for (int i = 0; i < heap.nrElementeVizibile; i++)
//	{
//		afisareFloare(heap.vector[i]);
//	}
//}
//
//void afiseazaHeapAscuns(Heap heap)
//{
//	for (int i = heap.nrElementeVizibile; i < heap.lungime; i++)
//	{
//		afisareFloare(heap.vector[i]);
//	}
//}
//
//Florarie extragereFloare(Heap* heap)
//{
//	Florarie aux;
//	aux.id = -1;
//	if (heap->nrElementeVizibile > 0)
//	{
//		heap->nrElementeVizibile--;
//		aux = heap->vector[0];
//		heap->vector[0] = heap->vector[heap->nrElementeVizibile];
//		heap->vector[heap->nrElementeVizibile] = aux;
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
//		if (heap->vector[i].tip)
//			free(heap->vector[i].tip);
//	}	
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->nrElementeVizibile = 0;
//	heap->lungime = 0;
//}
//
//
//int main()
//{
//	Heap heap = citireHeapDeFloriDinFisier("Florarie.txt");
//	afisareHeap(heap);
//	printf("Extrage:\n");
//	afisareFloare(extragereFloare(&heap));
//	afisareFloare(extragereFloare(&heap));
//	afisareFloare(extragereFloare(&heap));
//	printf("Heap ascuns:\n");
//	afiseazaHeapAscuns(heap);
//	dezalocareHeap(&heap);
//
//	return 0;
//}