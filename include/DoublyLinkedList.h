#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

// Définition du nœud
typedef struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

// Fonctions principales
void addElementD(DNode** headRef, int newData);
void deleteElementD(DNode** headRef, int key);
void printListD(DNode* node);
int searchElementD(DNode* head, int key);
void freeListD(DNode** headRef); // Fonction pour libérer la mémoire

#endif
