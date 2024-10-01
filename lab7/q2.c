#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct node* Reverse(struct node* head); 
int main(){
    int size;
    int Sdata, loc;
    printf("Creating a linked list\n");
    printf("Enter the size of the linked list: ");
    struct node* head = malloc(sizeof(struct node));
    struct node* ptr = head;
    scanf("%d",&size);
    for(int i = 0; i<size; i++ ){
        struct node* temp = malloc(sizeof(struct node));
        printf("Enter the data: ");
        scanf("%d",&temp->data);
        ptr->next = temp;
        temp->next = NULL;
        ptr = temp;
    }
    ptr = head;
    printf("The linked list is: \n");
    while(ptr != NULL){
        printf("%d || %u\n",ptr->data, ptr->next);
        ptr = ptr->next;
    }
    int count=1;
    ptr=head->next;
    struct node* temp = head;
    //traverse(head);
    printf("Removing odd elements\n");
    while(ptr != NULL){
        if(ptr->data%2==1){
            // printf("%d at %d", ptr->data, ptr);
            temp->next = ptr->next;
            ptr = temp;
        }else{
            temp = ptr;
            ptr = ptr->next;
        }
    }
    traverse(head);
    return 0;
}

void traverse(struct node* head){
    struct node* ptr = head->next;
    int index=0;
    while(ptr != NULL){
        printf(" [%d] %d || %u --> %u\n",index,ptr->data, ptr, ptr->next);
        ptr = ptr->next;
        index++;
    }
}