#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

void traverse(struct node* head);

int main() {
    int size;
    printf("Creating a doubly linked list\n");
    printf("Enter the size of the linked list: ");
    
    scanf("%d", &size);

    if (size <= 0) {
        printf("Invalid size. Exiting...\n");
        return 0;
    }

    struct node* head = malloc(sizeof(struct node));
    struct node* ptr = head;

    printf("Enter the data: ");
    scanf("%d", &head->data);
    head->next = head;
    head->prev = head;

    for (int i = 1; i < size; i++) {
        struct node* temp = malloc(sizeof(struct node));
        printf("Enter the data: ");
        scanf("%d", &temp->data);
        temp->next = head;
        temp->prev = ptr;
        ptr->next = temp;
        head->prev = temp;
        ptr = temp;
    }

    printf("The linked list is: \n");
    traverse(head);

    printf("After deleting last node: \n");
    ptr = head->prev;
    ptr->prev->next = head;
    head->prev = ptr->prev;

    free(ptr);
    traverse(head);

    return 0;
}

void traverse(struct node* head) {
    struct node* ptr = head;
    int index = 0;
    struct node* start = head;
    do {
        printf(" [%d] %d || %p --> %p\n", index, ptr->data, (void*)ptr, (void*)ptr->next);
        ptr = ptr->next;
        index++;
    } while (ptr != start);
}
