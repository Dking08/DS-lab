#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* rear = NULL;

void Enqueue(struct node** head, int item) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = item;
    temp->next = NULL;

    if (*head == NULL) {
        *head = temp;
        rear = temp;
    } else {
        rear->next = temp;
        rear = temp;
        rear->next = NULL;
    }
}

int Dequeue(struct node** head) {
    if (*head == NULL) {
        return -1;
    }
    
    // printf("[[[[[%u]]]]]",head);
    struct node* temp = *head;
    int dequeuedData = temp->data;
    *head = (*head)->next;
    // printf("[[[[[%u]]]]]",head);
    free(temp);
    return dequeuedData;
}

void traverse(struct node* head) {
    if (head == NULL) {
        printf("Queue is empty\n");
        return;
    }
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    printf("Circular Queue Operations\n");
    struct node* head = NULL;
    int choice;

    while (1) {
        printf("Enter 1 to Enqueue, 2 to Dequeue, 3 to traverse the Qeue, 4 to exit: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            int item;
            printf("Enter the item to enqueue: ");
            scanf("%d", &item);
            Enqueue(&head, item);
        } else if (choice == 2) {
            int dequeuedItem = Dequeue(&head);
            if (dequeuedItem == -1) {
                printf("Queue is empty\n");
            } else {
                printf("Item dequeued: %d\n", dequeuedItem);
            }
        } else if (choice == 3) {
            traverse(head);
        } else if (choice == 4) {
            printf("Exiting\n");
            break;
        } else {
            printf("Invalid choice, try again.\n");
        }
    }
    return 0;
}