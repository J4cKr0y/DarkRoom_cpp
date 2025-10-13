#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// node def
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// main functions
void addElement(Node** headRef, int newData);
void deleteElement(Node** headRef, int key);
void printList(Node* node);
int searchElement(Node* head, int key);
void freeList(Node** headRef); 

#endif
