#include "../include/MaxHeap.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm> // Pour std::swap

using namespace std;

// Fonction utilitaire pour obtenir l'index du parent
int parent(int i) { return (i - 1) / 2; }

// Fonction utilitaire pour obtenir l'index des enfants
int leftChild(int i) { return (2 * i + 1); }
int rightChild(int i) { return (2 * i + 2); }

MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    if (heap == NULL) {
        cerr << "Erreur d'allocation mémoire pour le Tas." << endl;
        exit(EXIT_FAILURE);
    }
    heap->size = 0;
    heap->capacity = capacity;
    heap->arr = (int*)malloc(capacity * sizeof(int));
    if (heap->arr == NULL) {
        cerr << "Erreur d'allocation mémoire pour le tableau du Tas." << endl;
        free(heap);
        exit(EXIT_FAILURE);
    }
    return heap;
}

/**
 * @brief Rétablit la propriété de Max-Heap à partir de l'index donné. O(log n)
 */
void heapify(MaxHeap* heap, int i) {
    int l = leftChild(i);
    int r = rightChild(i);
    int largest = i;

    // Trouve le plus grand parmi le parent, l'enfant gauche et l'enfant droit
    if (l < heap->size && heap->arr[l] > heap->arr[largest]) {
        largest = l;
    }
    if (r < heap->size && heap->arr[r] > heap->arr[largest]) {
        largest = r;
    }

    // Si le plus grand n'est pas le parent, échange et continue l'opération heapify
    if (largest != i) {
        swap(heap->arr[i], heap->arr[largest]);
        heapify(heap, largest);
    }
}

/**
 * @brief Insère un élément dans le tas. O(log n)
 */
void insertElement(MaxHeap* heap, int element) {
    if (heap->size == heap->capacity) {
        cout << "  [Heap] Capacité maximale atteinte, insertion échouée." << endl;
        return;
    }

    // 1. Insérer le nouvel élément à la fin
    heap->size++;
    int i = heap->size - 1;
    heap->arr[i] = element;

    // 2. Rééquilibrer l'arbre en remontant (Heapify Up)
    while (i != 0 && heap->arr[parent(i)] < heap->arr[i]) {
        swap(heap->arr[i], heap->arr[parent(i)]);
        i = parent(i);
    }
}

/**
 * @brief Extrait la racine (le plus grand élément) du tas. O(log n)
 */
int extractMax(MaxHeap* heap) {
    if (heap->size <= 0) {
        return -1; // -1 ou lance une exception
    }
    if (heap->size == 1) {
        heap->size--;
        return heap->arr[0];
    }

    // 1. Stocker la racine (max)
    int root = heap->arr[0];

    // 2. Remplacer la racine par le dernier élément
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    // 3. Rééquilibrer l'arbre en descendant (Heapify Down)
    heapify(heap, 0);

    return root;
}

/**
 * @brief Affiche les éléments du tableau du tas (pas l'arbre lui-même).
 */
void printHeap(MaxHeap* heap) {
    cout << "  [Heap] Contenu: ";
    for (int i = 0; i < heap->size; i++) {
        cout << heap->arr[i] << (i == heap->size - 1 ? "" : ", ");
    }
    cout << endl;
}

/**
 * @brief Libère la mémoire allouée au tas.
 */
void freeHeap(MaxHeap* heap) {
    if (heap != NULL) {
        free(heap->arr);
        free(heap);
    }
}
