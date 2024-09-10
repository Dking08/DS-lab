#include <stdio.h>

void push(int *arr, int *head, int data, int size);
int pop(int *arr, int *head);
void printStack(int *arr, int size, int head);

int main() {
    int size;
    printf("Enter the size of the stack: ");
    scanf("%d", &size);
    
    int stack[size], tempStack[size];
    int head = -1, headT = -1;
    
    printf("Enter the data to fill in stack:\n");
    for (int i = 0; i < size; i++) {
        int data;
        printf("Enter data: ");
        scanf("%d", &data);
        push(stack, &head, data, size);
    }
    
    printf("Original stack:\n");
    printStack(stack, size, head);
    
    while (head >= 0) {
        int temp = pop(stack, &head);
        
        while (headT >= 0 && tempStack[headT] > temp) {
            push(stack, &head, pop(tempStack, &headT), size);
        }
        
        push(tempStack, &headT, temp, size);
    }

    printf("Ascending sorted stack:\n");
    printStack(tempStack, size, headT);
    
    while (headT >= 0) {
        push(stack, &head, pop(tempStack, &headT), size);
    }
    
    printf("Descending sorted stack:\n");
    printStack(stack, size, head);
    
    return 0;
}

void push(int *arr, int *head, int data, int size) {
    if (*head >= size - 1) {
        printf("Stack overflow \n");
        return;
    }
    *head = *head + 1;
    arr[*head] = data;
}

int pop(int *arr, int *head) {
    if (*head < 0) {
        printf("Stack underflow \n");
        return -1;
    }
    int data = arr[*head];
    *head = *head - 1;
    return data;
}

void printStack(int *arr, int size, int head) {
    for (int i = 0; i <= head; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}