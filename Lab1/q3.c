#include <stdio.h>
int main(){
    
    int *p;
    int size;
    printf("Enter the size of the array: ");
    scanf("%d",&size);
    int arr[size];
    int (*ptr)[size];
    printf("Enter the elements: ");
    for(int i=0;i<size;i++){
        scanf("%d",&arr[i]);
    }
    p = arr;
    ptr = &arr;
    printf("The address are: %p, %p\n",p,ptr);
    printf("The first element: %d\n",*(*(ptr)+1));
    p++;
    ptr++;
    printf("The updated address are: %p, %p\n",p,ptr);
    // int arr2D[3][5] = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15}};
    // int (*ptr2D)[5];
    // ptr2D = &arr2D;
    // printf("%d\n",*(*(ptr2D+2)+3));
    return 0;
}