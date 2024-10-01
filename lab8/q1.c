#include <stdio.h>

void Enqueue(int Queue[], int size, int item, int *rear);
int Dequeue(int Queue[], int Size, int *front, int *rear);
void traverse(int Queue[], int Size, int front, int rear);

int main(){
    int Size, front=-1, rear=-1;
    printf("Enter the size of the Queue: ");
    scanf("%d", &Size);
    int Queue[Size];
    int choice;
    
    while(1){
        printf("Enter 1 to Enqueue, 2 to Dequeue, 3 to traverse the Queue, 4 to exit: ");
        scanf("%d", &choice);
        if(choice == 1){
            int item;
            printf("Enter the item to enqueue: ");
            scanf("%d", &item);
            Enqueue(Queue, Size, item, &rear);
        }
        else if(choice == 2){
            int index = Dequeue(Queue, Size, &front, &rear);
            if(index == -1){
                printf("Empty Stack\n");
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

void Enqueue(int Queue[], int size, int item, int *rear){
    if(*rear+1 == size-1){
        printf("Queue Overflow");
        return;
    }
    Queue[++*rear] = item;
}

int Dequeue(int Queue[], int Size, int *front, int *rear){
    if(*front == *rear){
        printf("Queue Underflow");
        *front = -1;
        *rear = -1;
        return -1;
    }
    return ++*front;
}

void traverse(int Queue[], int Size, int front, int rear){
    if(front == rear){
        printf("Empty Queue\n");
        return;
    }
    for(int i = front+1; i <= rear; i++){
        printf("%d ", Queue[i]);
    }
    printf("\nEmpty elements: %d\n", Size - rear + front);
}