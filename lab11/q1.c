#include <stdio.h>

void printArr(int* A, int n){
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void selSort(int* A, int n){
    int indxOfMin, tmp;
    printf("Runing selection sort...\n");
    for (int i = 0; i < n-1; i++) {
        indxOfMin = i;
        for (int j = i+1; j < n; j++) {
            if(A[j] < A[indxOfMin]){
                indxOfMin = j;
            }
        }
        tmp = A[i];
        A[i] = A[indxOfMin];
        A[indxOfMin] = tmp;
    }
}

int main(){
    int A[] = {3, 5, 2, 13, 12};
    int n = 5;
    printArr(A, n);
    selSort(A, n);
    printArr(A, n);

    return 0;
}