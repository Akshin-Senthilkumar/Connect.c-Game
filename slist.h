#ifndef slist_h
#define slist_h
#include <stdio.h>
#define NUM_COLS 7
// Define struct Node and struct LinkedList here
typedef struct Node {
    char board[6][7];
    struct Node* next;
} Node;



typedef struct LinkedList {
     Node* head; //Adds a head pointer to the linked list structure
     Node* tail;
} LinkedList;

void InitializeLinkedList(LinkedList* list);
void AddToLinkedList(LinkedList* list, char board[][NUM_COLS]);
void PrintLinkedList(LinkedList* list);
void FreeLinkedList(LinkedList* list); // Add declaration for cleaning up the linked list

#endif
 /* slist_h */