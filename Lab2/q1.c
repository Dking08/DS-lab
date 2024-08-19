#include <stdio.h>
#include <stdlib.h>
int main(){
    int m,n;
    printf("Enter the dimension of the matrix [m n]: ");
    scanf("%d",&m);
    scanf("%d",&n);
    int *arr;
    arr = (int*)malloc(m*n*sizeof(int));
    printf("Enter the elements of the matrix: \n");
    for(int i=0;i<m;i++){
        printf("Enter the elements of row %d: ",i+1);
        for(int j=0;j<n;j++){
            scanf("%d",(arr+i*n+j));
        }
    }
    printf("The matrix entered is: \n");
    int NZcount=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%d ",*(arr+i*n+j));
            if (*(arr+i*n+j)!=0)
                NZcount++;
        }
        printf("\n");
    }
    if (NZcount>=m*n){
        printf("Not a sparse matrix!");
        return 0;
    }else{printf("The given matrix is sparse in format:\nRow\tData\nColoumn\nData \n");}
    int *SparseMat = (int*)malloc(3*NZcount*sizeof(int));
    int Addcount=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if (*(arr+i*n+j)!=0){
                *(SparseMat+0*NZcount+Addcount)=i;
                *(SparseMat+1*NZcount+Addcount)=j;
                *(SparseMat+2*NZcount+Addcount)=*(arr+i*n+j);
                Addcount++;
            }
        }
    }
    printf("Printing Sprase Matrix:\n");
    for(int i=0;i<3;i++){
        for(int j=0;j<NZcount;j++){
            printf("%d ",*(SparseMat+i*NZcount+j));
        }
        printf("\n");
    }
    printf("Enter element to search in matrix: ");
    int SearchElem=0;
    scanf("%d",&SearchElem);
    for(int i=0;i<NZcount;i++){
        if(*(SparseMat+2*NZcount+i)== SearchElem){
            printf("Found %d in row: %d and coloumn: %d\n",*(SparseMat+2*NZcount+i),*(SparseMat+0*NZcount+i),*(SparseMat+1*NZcount+i));
        }
    }
    printf("Finding neighbour:\n Enter the index [i j]: ");
    int Ni,Nj;
    scanf("%d",&Ni);
    scanf("%d",&Nj);
    printf("Neighbour:\n");
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if(Ni+i>=0 && Nj+j>=0 && Ni+i<m && Nj+j<n){
                printf("%d ",*(arr+(Ni+i)*n+(Nj+j)));
            }
        }
        printf("\n");
    }
    return 0;
}