#include <stdio.h>
#include <stdlib.h>
#include "../../header/Boolean.h"
#include "../../header/ADT/linkedlist.h"

void initList(LinkedList* list) {
    list->head = NULL;
}

Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory failure\n");
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtHead(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    newNode->next = list->head;
    list->head = newNode;
}

void insertAtTail(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    Node* temp = list->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

boolean deleteNode(LinkedList* list, int data) {
    if (list->head == NULL) return false;
    Node* current = list->head;
    Node* prev = NULL;
    if (current->data == data) {
        list->head = current->next;
        free(current);
        return true;
    }
    while (current != NULL && current->data != data) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) return false;
    prev->next = current->next;
    free(current);
    return true;
}

Node* searchNode(LinkedList* list, int data) {
    Node* current = list->head;
    while (current != NULL) {
        if (current->data == data)
            return current;
        current = current->next;
    }
    return NULL;
}

void printList(LinkedList* list) {
    Node* current = list->head;
    printf("List: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}
