#include <stdio.h>

void insSort(int ar[], int n) {
    for (int i = 1; i < n; i++) {
        int ky = ar[i];
        int j = i - 1;

        while (j >= 0 && ar[j] > ky) {
            ar[j + 1] = ar[j];
            j--;
        }
        ar[j + 1] = ky;
    }
}

void printArr(int ar[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", ar[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter num of elements: ");
    scanf("%d", &n);

    int ar[n];

    printf("Enter %d elems:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &ar[i]);
    }

    insSort(ar, n);

    printf("Sorted array: ");
    printArr(ar, n);

    return 0;
}