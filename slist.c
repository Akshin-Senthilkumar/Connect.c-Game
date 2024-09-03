#include <stdio.h>
#include <stdlib.h>
#include "slist.h"
#include <Windows.h>

#define NUM_ROWS 6
//Define the head as a global variable

void InitializeLinkedList(LinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
}

void AddToLinkedList(LinkedList* list, char board[][NUM_COLS]) {
    // Implementation to add the current board state to the linked list.
        Node* newNode = (Node*)malloc(sizeof(Node));

        if(newNode == NULL)
        {
            return;
        }
    // Copy the game board to the new node
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            newNode->board[i][j] = board[i][j];
        }
    }
    
    // Add the new node to the beginning of the linked list
    newNode->next =NULL;

    if (list->tail == NULL) 
    {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void FreeLinkedList(LinkedList* list)
{
    Node* current = list->head;
    
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp); // Free the memory of the current node
    }
    
    list->head = NULL;
    list->tail = NULL;
}

void PrintLinkedList(LinkedList* list) {
    Node* current = list->head;
    
    while (current != NULL) {
        // Print the contents of the current node
        for (int r = NUM_ROWS-1; r >= 0; r--) {
            for (int c = 0; c < NUM_COLS; c++) {
                printf("|%c", current->board[r][c]);
            }
            printf("|\n");
        }
        printf("\n"); // Add a line break between boards
        
        current = current->next;

        Sleep((unsigned int) 2000);
    }
}

// int main() {
//     return 0;
// }