#include "../include/LinkedList.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

// Create a nex node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        cerr << "Erreur d'allocation mémoire pour le nœud." << endl;
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/**
 * @brief Ad an element on the begin of the list. O(1)
 */
void addElement(Node** headRef, int newData) {
    Node* newNode = createNode(newData);
    newNode->next = *headRef; 
    *headRef = newNode;       // Head become new node
}

/**
 * @brief Erase the first element with data = key. O(n)
 */
void deleteElement(Node** headRef, int key) {
    Node *temp = *headRef, *prev = NULL;

    // Case 1: Head have the key
    if (temp != NULL && temp->data == key) {
        *headRef = temp->next; // Change the head
        free(temp);            // free old node
        cout << "  [List] Élément " << key << " supprimé." << endl;
        return;
    }

    // Case 2: Search the key
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // Case 3: key not found
    if (temp == NULL) {
        cout << "  [List] Élément " << key << " non trouvé." << endl;
        return;
    }

    // Case 4: key found (temp is the node to be erased)
    prev->next = temp->next;
    free(temp);
    cout << "  [List] Élément " << key << " supprimé." << endl;
}

/**
 * @brief See all the elements of the list. O(n)
 */
void printList(Node* node) {
    cout << "  [List] Contenu: ";
    while (node != NULL) {
        cout << node->data << " -> ";
        node = node->next;
    }
    cout << "NULL" << endl;
}

/**
 * @brief Search a key on the list. Return 1 if found, else 0. O(n)
 */
int searchElement(Node* head, int key) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == key) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

/**
 * @brief Free all the list memory
 */
void freeList(Node** headRef) {
    Node* current = *headRef;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *headRef = NULL; 
}
