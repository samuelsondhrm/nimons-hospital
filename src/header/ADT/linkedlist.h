/* File: linkedlist.h */
/* Deklarasi ADT linked list*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../Boolean.h"

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Linked list structure (optional, for convenience)
typedef struct LinkedList {
    Node* head;
} LinkedList;

// Initialize linked list
void initList(LinkedList* list);

// Create a new node with given data
Node* createNode(int data);

// Insert a new node at the beginning
void insertAtHead(LinkedList* list, int data);

// Insert a new node at the end
void insertAtTail(LinkedList* list, int data);

// Delete first node with the given value; returns true if found and deleted
boolean deleteNode(LinkedList* list, int data);

// Search for a node with given value; returns pointer or NULL if not found
Node* searchNode(LinkedList* list, int data);

// Print the entire list
void printLinkedList(LinkedList* list);

// Free all nodes and clear the list
void freeList(LinkedList* list);

#endif
