#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

void deletePreviousOfLast(struct node* head);
void traverse(struct node* head);

int main() {
    int size;
    printf("Creating a linked list\n");
    printf("Enter the size of the linked list: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Invalid size\n");
        return 1;
    }

    struct node* head = malloc(sizeof(struct node));
    struct node* ptr = head;

    printf("Enter the data: ");
    scanf("%d", &head->data);
    head->next = NULL;

    for (int i = 1; i < size; i++) {
        struct node* temp = malloc(sizeof(struct node));
        printf("Enter the data: ");
        scanf("%d", &temp->data);
        temp->next = NULL;
        ptr->next = temp;
        ptr = temp;
    }

    printf("Before deletion: \n");
    traverse(head);

    deletePreviousOfLast(head);

    printf("After deletion: \n");
    traverse(head);

    return 0;
}

void deletePreviousOfLast(struct node* head) {
    struct node* ptr = head;
    struct node* prev = NULL;

    if (head == NULL || head->next == NULL || head->next->next == NULL) {
        return;
    }

    while (ptr->next->next != NULL) {
        prev = ptr;
        ptr = ptr->next;
    }

    prev->next = ptr->next;
    free(ptr);
}

void traverse(struct node* head) {
    struct node* ptr = head;
    if (head == NULL) return;
    while (ptr != NULL) {
        printf("%d --> ", ptr->data);
        ptr = ptr->next;
    }
    printf("NULL\n");
}
