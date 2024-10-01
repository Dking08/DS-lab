#include <stdio.h>

void mergeArrays(int A[], int B[], int sizeA, int sizeB) {
    int i = sizeA - 1;
    int j = sizeB - sizeA - 1;
    int k = sizeB - 1;

    while (i >= 0 && j >= 0) {
        if (A[i] > B[j]) {
            B[k] = A[i];
            i--;
        } else {
            B[k] = B[j];
            j--;
        }
        k--;
    }

    while (i >= 0) {
        B[k] = A[i];
        i--;
        k--;
    }
}

int main() {
    int sizeA, sizeB;

    printf("Enter the size of aray A: ");
    scanf("%d", &sizeA);

    int A[sizeA];
    printf("Enter elements of sorted array A:\n");
    for (int i = 0; i < sizeA; i++) {
        scanf("%d", &A[i]);
    }

    printf("Enter the total size of array B ( including empy slots): ");
    scanf("%d", &sizeB);

    int B[sizeB];
    printf("Enter the filled elmennts of sorted array B:\n");
    for (int i = 0; i < sizeB - sizeA; i++) {
        scanf("%d", &B[i]);
    }

    mergeArrays(A, B, sizeA, sizeB);

    printf("Merged array B: ");
    for (int i = 0; i < sizeB; i++) {
        printf("%d ", B[i]);
    }

    return 0;
}