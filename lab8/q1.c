#include <stdio.h>

void Enqueue(int Queue[], int size, int item, int *rear, int *front);
int Dequeue(int Queue[], int size, int *front, int *rear);
void traverse(int Queue[], int size, int front, int rear);

int main(){
    int size, front=-1, rear=-1;
    printf("Enter the size of the Queue: ");
    scanf("%d", &size);
    int Queue[size];
    int choice;
    
    printf("Enter 1 to Enqueue, 2 to Dequeue, 3 to traverse the Queue, 4 to exit: ");
    while(1){
        printf("Command: ");
        scanf("%d", &choice);
        if(choice == 1){
            int item;
            printf("Enter the item to enqueue: ");
            scanf("%d", &item);
            Enqueue(Queue, size, item, &rear, &front);
        }
        else if(choice == 2){
            int index = Dequeue(Queue, size, &front, &rear);
            if(index == -1){
                printf("Queue is empty\n");
                continue;
            }
            printf("Item dequeued: %d\n", Queue[index]);
        }
        else if(choice == 3){
            traverse(Queue, size, front, rear);
        }
        else if(choice == 4){
            printf("Exiting\n");
            break;
        }
    }
    return 0;
}

void Enqueue(int Queue[], int size, int item, int *rear, int *front){
    if(*rear == size - 1){  // Queue is full
        printf("Queue Overflow\n");
        return;
    }
    if(*front == -1) *front = 0;  // First element being added
    Queue[++*rear] = item;
}

int Dequeue(int Queue[], int size, int *front, int *rear){
    if(*front == -1 || *front > *rear){  // Queue is empty
        printf("Queue Underflow\n");
        *front = -1;
        *rear = -1;
        return -1;
    }
    return (*front)++;
}

void traverse(int Queue[], int size, int front, int rear){
    if(front == -1 || front > rear){
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for(int i = front; i <= rear; i++){
        printf("%d ", Queue[i]);
    }
    printf("\n");
    printf("Empty slots: %d\n", size - (rear - front + 1));
}