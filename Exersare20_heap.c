#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
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

typedef struct Heap Heap;
struct Heap
{
	int lungime;
	int nrElemVizibile;
	Serial* vector;
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
	s.nrSezoane = atoi(strtok);
	aux = strtok(NULL, sep);
	s.numeSerial = (char*)malloc(strlen(aux) + 1);
	strcpy(s.numeSerial, aux);
	aux = strtok(NULL, sep);
	s.personaj = (char*)malloc(strlen(aux) + 1);
	strcpy(s.personaj, aux);
	aux = strtok(NULL, sep);
	s.rating = atof(aux);
	return s;
}

void afisareSerial(Serial serial)
{
	printf("Id: %d\n", serial.id);
	printf("Numar sezoane: %d\n", serial.nrSezoane);
	printf("Nume serial: %s\n", serial.numeSerial);
	printf("Personaj: %s\n", serial.personaj);
	printf("Rating: %.2f\n", serial.rating);
}

Heap initializareHeap(int lungime)
{
	Heap heap;
	heap.lungime = lungime;
	heap.nrElemVizibile = 0;
	heap.vector = (Serial*)malloc(sizeof(Serial) * lungime);
	return heap;
}

Heap filtrareHeap(Heap heap, int pozitieNod)
{
	int stanga = 2 * pozitieNod + 1;
	int dreapta = 2 * pozitieNod + 2;
	int pozMax = pozitieNod;
	if (stanga <heap.nrElemVizibile && heap.vector[stanga].rating > heap.vector[pozMax].rating)
	{
		pozMax = stanga;
	}
	if (dreapta < heap.nrElemVizibile && heap.vector[dreapta].rating > heap.vector[pozMax].rating)
	{
		pozMax = dreapta;
	}
	if (pozMax != pozitieNod)
	{
		Serial aux;
		aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozitieNod];
		heap.vector[pozitieNod] = aux;

		if (pozMax < (heap.nrElemVizibile - 2) / 2)
		{
			filtrareHeap(heap, pozMax);
		}
	}
}

Heap citireHeapDeSerialeDinFisier(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	Heap heap = initializareHeap(5);
	if (file)
	{
		while (!feof(file))
		{
			heap.vector[heap.nrElemVizibile++] = citireSerialDinFisier(file);
		}
	}

	for (int i = (heap.nrElemVizibile-2)/2; i >=0; i--)
	{
		filtrareHeap(heap, i);
	}

	fclose(file);
	return heap;
}

void afisareHeap(Heap heap)
{
	for (int i = 0; i < heap.nrElemVizibile; i++)
	{
		afisareSerial(heap.vector[i]);
	}
}

void afisareHeapAscuns(Heap heap)
{
	for (int i = heap.nrElemVizibile; i < heap.lungime; i++)
	{
		afisareSerial(heap.vector[i]);
	}
}

Serial extrageSerial(Heap* heap)
{
	Serial aux;
	aux.id = -1;
	if (heap->nrElemVizibile > 0)
	{
		heap->nrElemVizibile--;
		aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrElemVizibile];
		heap->vector[heap->nrElemVizibile] = aux;
		filtrareHeap(*heap, 0);
	}
	return aux;
}

void dezalocareHeap(Heap* heap)
{
	for (int i = 0; i < heap->lungime; i++)
	{
		free(heap->vector[i].numeSerial);
		free(heap->vector[i].personaj);
		free(heap->vector);
		heap->vector = NULL;
		heap->nrElemVizibile = 0;
		heap->lungime = 0;
	}
}

int main()
{ 
	Heap heap = citireHeapDeSerialeDinFisier("serialeHeap.txt");
	afisareHeap(heap);
	printf("Extragem elemente: \n");
	afisareSerial(extrageSerial(&heap));
	afisareSerial(extrageSerial(&heap));
	afisareSerial(extrageSerial(&heap));
	printf("Heap ascuns: \n");
	afisareHeapAscuns(heap);
	dezalocareHeap(&heap);
	printf("Heap-ul a fost dezalocat!!");
	return 0;
}