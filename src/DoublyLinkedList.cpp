#include "../include/DoublyLinkedList.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

// Crée un nouveau nœud
DNode* createDNode(int data) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    if (newNode == NULL) {
        cerr << "Erreur d'allocation mémoire pour le DNode." << endl;
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

/**
 * @brief Ajoute un élément au début de la liste. O(1)
 */
void addElementD(DNode** headRef, int newData) {
    DNode* newNode = createDNode(newData);
    
    // Le nouveau nœud devient la tête
    newNode->next = *headRef;

    // Si la liste n'est pas vide, l'ancienne tête doit pointer vers le nouveau nœud
    if (*headRef != NULL) {
        (*headRef)->prev = newNode;
    }
    
    *headRef = newNode;
}

/**
 * @brief Supprime le premier élément dont la 'data' correspond à la 'key'. O(n)
 */
void deleteElementD(DNode** headRef, int key) {
    DNode* current = *headRef;

    // Recherche de la clé
    while (current != NULL && current->data != key) {
        current = current->next;
    }

    if (current == NULL) {
        cout << "  [DList] Élément " << key << " non trouvé." << endl;
        return;
    }

    // Cas 1: Le nœud à supprimer est la tête
    if (current->prev == NULL) {
        *headRef = current->next;
    } else {
        // Le nœud précédent doit ignorer le nœud actuel
        current->prev->next = current->next;
    }

    // Cas 2: Le nœud à supprimer n'est pas la queue
    if (current->next != NULL) {
        // Le nœud suivant doit pointer vers le nœud précédent
        current->next->prev = current->prev;
    }

    free(current);
    cout << "  [DList] Élément " << key << " supprimé." << endl;
}

/**
 * @brief Affiche tous les éléments de la liste. O(n)
 */
void printListD(DNode* node) {
    cout << "  [DList] Contenu: NULL <-> ";
    while (node != NULL) {
        cout << node->data << " <-> ";
        node = node->next;
    }
    cout << "NULL" << endl;
}

/**
 * @brief Recherche une clé dans la liste. Retourne 1 si trouvée, 0 sinon. O(n)
 */
int searchElementD(DNode* head, int key) {
    DNode* current = head;
    while (current != NULL) {
        if (current->data == key) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

/**
 * @brief Libère toute la mémoire allouée à la liste.
 */
void freeListD(DNode** headRef) {
    DNode* current = *headRef;
    DNode* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *headRef = NULL;
}
