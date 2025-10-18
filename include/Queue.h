#ifndef QUEUE_H
#define QUEUE_H

// Définition du nœud (réutilisation de la structure de la liste chaînée)
typedef struct QNode {
    int data;
    struct QNode* next;
} QNode;

// Définition de la structure de File
typedef struct Queue {
    QNode *front; // Tête de la file (sortie)
    QNode *rear;  // Queue de la file (entrée)
} Queue;

// Fonctions principales
Queue* createQueue();
void enqueue(Queue* q, int k);
int dequeue(Queue* q);
int peek(Queue* q);
int isQueueEmpty(Queue* q);
void printQueue(Queue* q);
void freeQueue(Queue* q); // Fonction pour libérer la mémoire

#endif
