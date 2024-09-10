#include <stdio.h>
#include <stdlib.h>
int main(){

    int m,n;
    int EVENFLAG=0;
    printf("Enter the dimension of the matrix [m n]: ");
    scanf("%d",&m);
    scanf("%d",&n);

    int *arr = (int *) malloc((sizeof(int)*m*n));
    printf("Filling data:\n");
    for(int i=0;i<m;i++){
        printf("Enter the row (%d): ",i);
            for(int j=0;j<n;j++){
                // printf("Enter element [%d,%d]: ",i,j);
                scanf("%d", arr + (n*i+ j));
        }
    }

    printf("The matrix is:\n");
    for(int i=0;i<m;i++){
        printf("[ ");
        for(int j=0;j<n;j++){
            printf("%d ", *(arr+(n*i+j)));
            if(*(arr+(n*i+j))%2==0) EVENFLAG=1;
        }
        printf("]\n");
    }

    if(EVENFLAG==0) {
        printf("No EVEN in the matrix.\n");
        printf("Exiting...\n"); 
        return(0);
    }
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            int p=i, q=j;
            if(*(arr+(n*i+j))%2==1){
                while(*(arr+(n*p+q))%2==1){
                    q = (q+1)%n;
                    if (p == m-1 && q == 0){ p = 0; q=0;}
                    else if (q == 0) p++;
                }
                *(arr+(n*i+j)) = *(arr+(n*p+q));
            }
        }
    }


    printf("The modified matrix is:\n");
    for(int i=0;i<m;i++){
        printf("[ ");
        for(int j=0;j<n;j++){
            printf("%d ", *(arr+(n*i+j)));
        }
        printf("]\n");
    }
    
}