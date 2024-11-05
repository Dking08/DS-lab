#include <stdio.h>

void Enqueue(int Queue[], int size, int item, int *rear, int *front);
int Dequeue(int Queue[], int Size, int *front, int *rear);
void traverse(int Queue[], int Size, int front, int rear);

int main(){
    int Size, front=-1, rear=-1;
    printf("Enter the size of the Queue: ");
    scanf("%d", &Size);
    int Queue[Size];
    int choice;
    
    printf("Enter 1 to Enqueue, 2 to Dequeue, 3 to traverse the Queue, 4 to exit: ");
    while(1){
        printf("Command: ");
        scanf("%d", &choice);
        if(choice == 1){
            int item;
            printf("Enter the item to enqueue: ");
            scanf("%d", &item);
            Enqueue(Queue, Size, item, &rear, &front);
        }
        else if(choice == 2){
            int index = Dequeue(Queue, Size, &front, &rear);
            if(index == -1){
                printf("Empty Queue\n");
                continue;
            }
            printf("Item dequeued: %d\n", Queue[index]);
        }
        else if(choice == 3){
            traverse(Queue, Size, front, rear);
        }
        else if(choice == 4){
            printf("Exiting\n");
            break;
        }
    }
    return 0;
}

void Enqueue(int Queue[], int size, int item, int *rear, int *front){
    if((*rear+1) % size == *front){
        printf("Queue Overflow\n");
        return;
    }
    if(*front == -1) *front = 0;
    *rear = (*rear+1) % size;
    Queue[*rear] = item;
}

int Dequeue(int Queue[], int Size, int *front, int *rear){
    if(*front == -1){
        printf("Queue Underflow\n");
        return -1;
    }
    int item = *front;
    if(*front == *rear){
        *front = -1;
        *rear = -1;
    } else {
        *front = (*front+1) % Size;
    }
    return item;
}

void traverse(int Queue[], int Size, int front, int rear){
    if(front == -1){
        printf("Empty Queue\n");
        return;
    }
    int i = front;
    while(i != rear){
        printf("%d ", Queue[i]);
        i = (i+1) % Size;
    }
    printf("%d\n", Queue[rear]);
    printf("Empty elements: %d\n", (Size - (rear - front + Size) % Size - 1));
}