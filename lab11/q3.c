#include <stdio.h>

void prntArr(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void bubSort(int *arr, int n) {
    int tmp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void bubSortAdapt(int *arr, int n) {
    int tmp, isSrted = 0;
    for (int i = 0; i < n - 1; i++) {
        isSrted = 1;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                isSrted = 0;
            }
        }
        if (isSrted) return;
    }
}

int main() {
    int arr[] = {1, 2, 5, 6, 12, 54, 625, 7, 23, 9, 987};
    int n = 11;
    prntArr(arr, n);
    bubSort(arr, n);
    prntArr(arr, n);
    return 0;
}