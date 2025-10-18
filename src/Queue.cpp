#include "../include/Queue.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

// Fonction utilitaire pour créer un nouveau nœud
QNode* createQNode(int k) {
    QNode* temp = (QNode*)malloc(sizeof(QNode));
    if (temp == NULL) {
        cerr << "Erreur d'allocation mémoire pour le QNode." << endl;
        exit(EXIT_FAILURE);
    }
    temp->data = k;
    temp->next = NULL;
    return temp;
}

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        cerr << "Erreur d'allocation mémoire pour la Queue." << endl;
        exit(EXIT_FAILURE);
    }
    q->front = q->rear = NULL;
    return q;
}

/**
 * @brief Ajoute la clé k à la fin de la file (opération ENQUEUE). O(1)
 */
void enqueue(Queue* q, int k) {
    QNode* temp = createQNode(k);

    // Si la file est vide, le nouveau nœud devient à la fois front et rear
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    // Ajoute le nouveau nœud à la fin de la file et met à jour rear
    q->rear->next = temp;
    q->rear = temp;
}

/**
 * @brief Supprime et retourne l'élément de devant de la file (opération DEQUEUE). O(1)
 */
int dequeue(Queue* q) {
    if (q->front == NULL) {
        cerr << "  [Queue] La file est vide. DEQUEUE impossible." << endl;
        return -1; 
    }

    // Stocke la tête précédente et avance la tête d'un nœud
    QNode* temp = q->front;
    q->front = q->front->next;

    // Si front devient NULL, cela signifie que la file est vide, rear doit aussi être NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }

    int data = temp->data;
    free(temp);
    return data;
}

/**
 * @brief Retourne l'élément de devant sans le supprimer (opération PEEK). O(1)
 */
int peek(Queue* q) {
    if (q->front == NULL) {
        cerr << "  [Queue] La file est vide. PEEK impossible." << endl;
        return -1;
    }
    return q->front->data;
}

/**
 * @brief Vérifie si la file est vide. O(1)
 */
int isQueueEmpty(Queue* q) {
    return (q->front == NULL);
}

/**
 * @brief Affiche tous les éléments de la file. O(n)
 */
void printQueue(Queue* q) {
    cout << "  [Queue] Contenu (Front -> Rear): ";
    QNode* current = q->front;
    while (current != NULL) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
}

/**
 * @brief Libère la mémoire allouée à la file.
 */
void freeQueue(Queue* q) {
    if (q == NULL) return;
    
    QNode* current = q->front;
    QNode* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(q);
}
