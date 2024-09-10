#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

struct node* Reverse(struct node* head);
int CFLAG = 0; // Circular flag

void traverse(struct node* head);
void insert(struct node** head, int loc, int size);
void Search(struct node* head, int data);
void Update(struct node* head, int data, int Newdata);
void DeleteNode(struct node** head, int loc, int size);
void CreateCircular(struct node** head);

int main() {
    int size;
    int Sdata, loc;
    printf("Creating a doubly linked list\n");
    printf("Enter the size of the linked list: ");
    
    struct node* head = malloc(sizeof(struct node));
    struct node* ptr = head;
    scanf("%d", &size);

    if (size <= 0) {
        printf("Invalid size. Exiting...\n");
        return 0;
    }

    for (int i = 0; i < size; i++) {
        struct node* temp = malloc(sizeof(struct node));
        printf("Enter the data: ");
        scanf("%d", &temp->data);
        ptr->next = temp;
        temp->prev = ptr;
        temp->next = NULL;
        ptr = temp;
    }
    
    ptr = head->next; // Adjusting to the first actual node
    free(head); // Free the initial dummy node
    head = ptr;
    
    printf("The linked list is: \n");
    traverse(head);
    
    int count = 0;
        printf("Select the choice: \n");
        printf("0: Traverse list\n");
        printf("1: Insert Node at the beginning\n");
        printf("2: Insert Node at the end\n");
        printf("3: Insert Node at the given position\n");
        printf("4: Search an element\n");
        printf("5: Update an element\n");
        printf("6: Delete node at beginning\n");
        printf("7: Delete node at specific position\n");
        printf("8: Delete node at the end\n");
        printf("9: Reverse the List\n");
        printf("10: Create Circular\n");
        printf("11: Exit\n");
    while (count != 11) {
        printf("Enter your choice: ");
        scanf("%d", &count);

        switch (count) {
            case 0:
                traverse(head);
                break;
            case 1:
                printf("Inserting at beginning\n");
                insert(&head, 0, size);
                size++;
                break;
            case 2:
                printf("Inserting at end\n");
                insert(&head, size, size);
                size++;
                break;
            case 3:
                printf("Inserting at specific location\n");
                printf("Enter location: ");
                scanf("%d", &loc);
                insert(&head, loc, size);
                size++;
                break;
            case 4:
                printf("Enter the data to be searched: ");
                scanf("%d", &Sdata);
                Search(head, Sdata);
                break;
            case 5:
                printf("Enter the data to be updated: ");
                int NewData;
                scanf("%d", &Sdata);
                printf("Enter updated value: ");
                scanf("%d", &NewData);
                Update(head, Sdata, NewData);
                break;
            case 6:
                printf("Deleting at beginning\n");
                DeleteNode(&head, 0, size);
                size--;
                break;
            case 7:
                printf("Deleting at specific location\n");
                printf("Enter location: ");
                scanf("%d", &loc);
                DeleteNode(&head, loc, size);
                size--;
                break;
            case 8:
                printf("Deleting at end\n");
                DeleteNode(&head, size - 1, size);
                size--;
                break;
            case 9:
                printf("Reversing List...\n");
                head = Reverse(head);
                traverse(head);
                break;
            case 10:
                CreateCircular(&head);
                printf("List converted to circular.\n");
                break;
            case 11:
                printf("Exiting\n");
                break;
            default:
                printf("Entered input not recognized!\n");
                break;
        }
    }
    return 0;
}

void traverse(struct node* head) {
    struct node* ptr = head;
    int index = 0;
    
    if (CFLAG == 0) {
        // Non-circular traversal
        while (ptr != NULL) {
            printf(" [%d] %d || %p <-- %p --> %p\n", index, ptr->data, (void*)ptr->prev, (void*)ptr, (void*)ptr->next);
            ptr = ptr->next;
            index++;
        }
    } else {
        // Circular traversal
        if (ptr != NULL) {
            struct node* start = head;
            do {
                printf(" [%d] %d || %p <-- %p --> %p\n", index, ptr->data, (void*)ptr->prev, (void*)ptr, (void*)ptr->next);
                ptr = ptr->next;
                index++;
            } while (ptr != start);
        }
    }
}

void insert(struct node** head, int loc, int size) {
    if (loc > size) {
        printf("Invalid location!\n");
        return;
    }

    struct node* temp = malloc(sizeof(struct node));
    printf("Enter the data: ");
    scanf("%d", &temp->data);
    
    if (loc == 0) { // Insertion at the beginning
        if (*head == NULL) {
            temp->next = temp->prev = temp;
            *head = temp;
        } else {
            struct node* last = (*head)->prev;
            temp->next = *head;
            temp->prev = last;
            last->next = (*head)->prev = temp;
            *head = temp;
        }
        if (!CFLAG) {
            (*head)->prev = NULL;
        }
    } else {
        struct node* ptr = *head;
        for (int i = 0; i < loc - 1; i++) {
            ptr = ptr->next;
        }
        temp->next = ptr->next;
        temp->prev = ptr;
        ptr->next = temp;
        if (temp->next) {
            temp->next->prev = temp;
        }
        if (CFLAG && temp->next == NULL) {
            temp->next = *head;
            (*head)->prev = temp;
        }
    }
}

void Search(struct node* head, int data) {
    struct node* ptr = head;
    int found = 0;
    
    if (CFLAG == 0) {
        while (ptr != NULL) {
            if (ptr->data == data) {
                printf("Found at %p\n", (void*)ptr);
                found = 1;
                break;
            }
            ptr = ptr->next;
        }
    } else {
        struct node* start = head;
        do {
            if (ptr->data == data) {
                printf("Found at %p\n", (void*)ptr);
                found = 1;
                break;
            }
            ptr = ptr->next;
        } while (ptr != start);
    }
    
    if (!found) {
        printf("Element not found!\n");
    }
}

void Update(struct node* head, int data, int Newdata) {
    struct node* ptr = head;
    int found = 0;
    
    if (CFLAG == 0) {
        while (ptr != NULL) {
            if (ptr->data == data) {
                printf("Found at %p\n", (void*)ptr);
                ptr->data = Newdata;
                found = 1;
                break;
            }
            ptr = ptr->next;
        }
    } else {
        struct node* start = head;
        do {
            if (ptr->data == data) {
                printf("Found at %p\n", (void*)ptr);
                ptr->data = Newdata;
                found = 1;
                break;
            }
            ptr = ptr->next;
        } while (ptr != start);
    }
    
    if (!found) {
        printf("Element not found!\n");
    }
}

void DeleteNode(struct node** head, int loc, int size) {
    if (loc >= size || *head == NULL) {
        printf("Invalid location!\n");
        return;
    }

    struct node* ptr = *head;
    if (loc == 0) { // Delete head
        if (CFLAG) {
            struct node* last = (*head)->prev;
            *head = (*head)->next;
            last->next = *head;
            (*head)->prev = last;
        } else {
            *head = ptr->next;
            if (*head) (*head)->prev = NULL;
        }
        free(ptr);
    } else {
        for (int i = 0; i < loc; i++) {
            ptr = ptr->next;
        }
        if (ptr->prev) ptr->prev->next = ptr->next;
        if (ptr->next) ptr->next->prev = ptr->prev;
        free(ptr);
    }
}

struct node* Reverse(struct node* head) {
    struct node* ptr = head;
    struct node* prev = NULL;
    struct node* start = head;

    do {
        struct node* temp = ptr->next;
        ptr->next = prev;
        prev = ptr;
        ptr->prev = ptr->next;
        ptr = temp;
    } while (CFLAG && ptr != start || !CFLAG && ptr != NULL);

    if (CFLAG) {
        head->next = prev;
        prev->prev = head;
    }
    
    return prev;
}

void CreateCircular(struct node** head) {
    if (CFLAG == 0 && *head != NULL) {
        struct node* ptr = *head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = *head;
        (*head)->prev = ptr;
        CFLAG = 1;
        printf("List has been made circular.\n");
    } else {
        printf("List is already circular or empty.\n");
    }
}
