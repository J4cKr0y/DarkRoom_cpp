#ifndef MAXHEAP_H
#define MAXHEAP_H

// Définition de la structure de Tas
typedef struct MaxHeap {
    int* arr;
    int size;
    int capacity;
} MaxHeap;

// Fonctions principales
MaxHeap* createMaxHeap(int capacity);
void insertElement(MaxHeap* heap, int element);
int extractMax(MaxHeap* heap);
void heapify(MaxHeap* heap, int index);
void printHeap(MaxHeap* heap);
void freeHeap(MaxHeap* heap); // Fonction pour libérer la mémoire

#endif
