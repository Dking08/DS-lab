#include <stdio.h>

void push(int *arr, int *head, int data);
int pop(int *arr, int *head);

int main(){

    int size;
    printf("Enter the size of the stack: ");
    scanf("%d", &size);
    int stack[size], tempStack[size];
    int head=size-1,headT=0;
    printf("Enter the data to fill in stack: \n");
    for(int i=0; i<size; i++){
        printf("Enter data: ");
        scanf("%d", &stack[i]);
        tempStack[i]=-1;
    }
    printf("Stack formed\n");
    for(int j=0;j<size;j++){
        printf("%d -->",stack[j]);
    }
    int count=0;
    while(count!=10){
        printf("Index:::%d<---->[%d]\n", head, headT);
        printf("Stack--->>%d<---->[%d]\n", stack[head], tempStack[headT-1?0:headT>0]);
        // headT = headT-1?0:headT>0;
        if(stack[head]>tempStack[headT-1?0:headT>0]){
            push(tempStack, &headT, stack[head]);
            pop(stack,&head);
            for(int j=0;j<size;j++){
                printf("[%d] --> [%d]",stack[j], tempStack[j]);
    }
        }
        else if(stack[head]<=tempStack[headT-1?0:headT>0]){
            int value = pop(stack, &head);
            while(value<tempStack[headT-1?0:headT>0]){
                printf("%d %d",value, tempStack[headT-1?0:headT>0]);
                headT--;
                // int theValue = ;
                push(stack, &head, pop(tempStack, &headT));
            }
            
            for(int j=0;j<size;j++){
                printf("[%d] --> [%d]",stack[j], tempStack[j]);
    }
        }
        count++;
    }

    printf("\nSorted formed\n");
    for(int j=0;j<size;j++){
        printf("%d -->",stack[j]);
    }

}

void push(int *arr, int *head, int data){
    arr[*head] = data;


    *head = *head+1;
}

int pop(int *arr, int *head){
    *head = *head-1;
    return arr[*head+1];
}