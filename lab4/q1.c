#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
    struct node *prev;
};

struct node* Reverse(struct node* head); 
int CFLAG=0;
int main(){
    int size;
    int Sdata, loc;
    printf("Creating a doubly link list\n");
    printf("Enter the size of the linked list: ");
    struct node* head = malloc(sizeof(struct node));
    struct node* ptr = head;
    scanf("%d",&size);
    for(int i = 0; i<size; i++ ){
        struct node* temp = malloc(sizeof(struct node));
        printf("Enter the data: ");
        scanf("%d",&temp->data);
        ptr->next = temp;
        temp->prev = ptr;
        temp->next = NULL;
        ptr = temp;
    }
    ptr = head;
    printf("The linked list is: \n");
    while(ptr != NULL){
        printf("[ %u || %d || %u ]\n",ptr->prev,ptr->data, ptr->next);
        ptr = ptr->next;
    }
    int count =0;
    while(count != 10){
        printf("Select the choice: \n0: Traverse list\n1: Insert Node at the beginning\n2: Insert Node at the end\n3: Insert Node at the given position\n4: Search an element\n5: Update an element\n6: Delete node at begining\n7: Delete node at specific position\n8: Delete node at the end\n9: Reverse the List\n10: Create Circular\n11: Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&count);
        switch(count){
            case 0:
                traverse(head);
            break;
            case 1:
                printf("Inserting at begining\n");
                insert(head, 0, size);
                size++;
            break;
            case 2:
                printf("Inserting at end\n");
                insert(head, size, size);
                size++;
            break;
            case 3:
                printf("Inserting at specific location\n");
                printf("Enter location: ");
                scanf("%d",&loc);
                insert(head, loc, size);
                size++;
            break;
            case 4:
                printf("Enter the data to be searched: ");
                scanf("%d",&Sdata);
                Search(head, Sdata);
            break;
            case 5:
                printf("Enter the data to be updated: ");
                int NewData;
                scanf("%d",&Sdata);
                printf("Enter updated value: ");
                scanf("%d",&NewData);
                Update(head, Sdata, NewData);
            break;
            case 6:
                printf("Deleting at begining\n");
                DeleteNode(head, 0, size);
                size--;
            break;
            case 7:
                printf("Deleting at specific location\n");
                printf("Enter location: ");
                scanf("%d",&loc);
                DeleteNode(head, loc, size);
                size--;
            break;
            case 8:
                printf("Deleting at begining\n");
                DeleteNode(head, size, size);
                size--;
            break;
            case 9:
                printf("Reversed List:\nDone\n");
                head = Reverse(head);
                traverse(head);
            break;
            case 10:
                printf("Exiting");
            break;
            default:
                printf("Entered input not recognised!");
                break;
        }
    }
    return 0;
}

void traverse(struct node* head){
    struct node* ptr = head;
    int index=0;
    while(ptr != NULL){
        printf(" [%d] %d || %u <-- %u --> %u\n",index,ptr->data,ptr->prev, ptr, ptr->next);
        ptr = ptr->next;
        index++;
    }
}
void insert(struct node* head, int loc, int size)
{
                if(loc > size){
                    printf("Invalid location!");
                    return NULL;
                }
                struct node* temp = malloc(sizeof(struct node));
                printf("Enter the data: ");
                scanf("%d",&temp->data);
                struct node* ptr = head;
                for(int i = 0; i<loc; i++){
                    ptr = ptr->next;
                }
                temp->prev = ptr;
                temp->next = ptr->next;
                ptr->next = temp;
}
void Search(struct node* head, int data){
    struct node* ptr = head;
    while(ptr != NULL){
        if(ptr->data == data){
            printf("Found at %u",ptr->next);
        }
        ptr = ptr->next;
    }
}

void Update(struct node* head, int data, int Newdata){
    struct node* ptr = head;
    while(ptr != NULL){
        if(ptr->data == data){
            printf("Found at %u",ptr->next);
            ptr->data=Newdata;
        }
        ptr = ptr->next;
    }
}

void DeleteNode(struct node* head, int loc, int size){
    if (loc>size){
        return NULL;
    }
    struct node* ptr = head;
    for(int i=0;i<loc;i++){
        ptr = ptr->next;
    }
    struct node* target = ptr->next;
    ptr->next->prev = ptr;
    ptr->next = ptr->next->next;
    free(target);
}

struct node* Reverse(struct node* head){
    struct node* ptr = head;
    struct node* prev = NULL;
    while(ptr != NULL){
        struct node* temp = ptr->next;
        // printf("%d\n",ptr->data);
        ptr->next = prev;
        ptr->prev = ptr->next;
        prev = ptr;
        ptr = temp;
    }
    return prev;
}

void CreateCircular(struct node* head){
    if (CFLAG==0){
        struct node* targetHead = head;
        struct node* ptr = head;
        while(ptr->next != NULL){
            ptr = ptr->next;
        }
        ptr->next = head;
        targetHead->prev = ptr;
        CFLAG=1;
    }
}

// struct node* Reverse(struct node* head){
//     struct node* ptr = head;
//     if (ptr == NULL || ptr->next == NULL){
//         return ptr;
//     }
//     struct node* rest = Reverse(ptr->next);
//     ptr->next->next = ptr;
//     ptr->next = NULL;
//     return rest;
// }