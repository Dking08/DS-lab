#include <stdio.h>
int main(){
    int size;
    printf("Enter the size of the array: ");
    scanf("%d",&size);
    int *arr = (int*)malloc(size*sizeof(int));
    // printf("the original address is %u\n", arr);
    int *ptr = arr; 
    printf("Enter the elements of the array: ");
    for(int i=0;i<size;i++){
        scanf("%d",(ptr+i));
    }
    printf("The non-even of the array are: ");
    for(int i=1;i<size;i+=2){
        if(arr[i]%2!=0){
            printf("%d\n",*(ptr+i));
        }
    }
    // printf("\n Enter the new size of the array: ");
    // scanf("%d",&size);
    // int *arr1 = (int*)realloc(arr,size*sizeof(int));
    // printf("the reallocated address is %u\n", arr1);
    // printf("Enter the elements of the array: ");
    // for(int i=0;i<size;i++){
    //     scanf("%d",&arr1[i]);
    // }
    // printf("The non-even of the array are:\n");
    // for(int i=1;i<size;i+=2){
    //     if(arr1[i]%2!=0){
    //         printf("%d\n",*(arr1+i));
    //     }
    // }
    return 0;
}