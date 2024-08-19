#include <stdio.h>
int main(){
    int size;
    printf("Enter the size of the array: ");
    scanf("%d",&size);
    int *arr = (int*)malloc(size*sizeof(int));
    printf("the original address is %u\n", arr);
    int *ptr = arr;
    printf("Enter the elements of the array: ");
    for(int i=0;i<size;i++){
        scanf("%d",&arr[i]);
    }
    printf("The sum of the array are: ");
    int sum=0;
    for(int i=0;i<size;i++){
        sum+=arr[i];
    }
    printf("%d",sum);
    printf("\nEnter the new size of the array: ");
    scanf("%d",&size);
    int *arr1 = (int*)realloc(arr,size*sizeof(int));
    printf("the reallocated address is %u\n", arr1);
    printf("Enter the elements of the array: ");
    for(int i=0;i<size;i++){
        scanf("%d",&arr1[i]);
    }
    printf("The sum of the array are: ");   
    for(int i=0;i<size;i++){
        sum+=arr1[i];
    }
    printf("%d",sum);
    // printf("Printing the elements of the original array (using pointers): ");
    // for(int i=0;i<size;i++){
    //     printf("%d\n",ptr[i]);
    // }
    return 0;
}