#include <stdio.h>
#include <stdlib.h>

int main(){
    int m, n, choice;
    printf("Enter the dimension of the matrix [m n]: ");
    scanf("%d", &m);
    scanf("%d", &n);

    int *arr;
    arr = (int*)malloc(m * n * sizeof(int));

    printf("Enter the elements of the matrix: \n");
    for(int i = 0; i < m; i++){
        printf("Enter the elements of row %d: ", i+1);
        for(int j = 0; j < n; j++){
            scanf("%d", (arr + i * n + j));
        }
    }

    int NZcount = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if (*(arr + i * n + j) != 0)
                NZcount++;
        }
    }

    int *SparseMat = (int*)malloc(3 * NZcount * sizeof(int));
    int Addcount = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if (*(arr + i * n + j) != 0){
                *(SparseMat + 0 * NZcount + Addcount) = i;
                *(SparseMat + 1 * NZcount + Addcount) = j;
                *(SparseMat + 2 * NZcount + Addcount) = *(arr + i * n + j);
                Addcount++;
            }
        }
    }
        printf("\nSelect an option: \n");
        printf("1. Create and validate if matrix is sparse\n");
        printf("2. Display the matrix\n");
        printf("3. Convert the matrix into a compact sparse matrix\n");
        printf("4. Search an element in the sparse matrix\n");
        printf("5. Display neighboring elements of an index in the matrix\n");
        printf("6. Exit\n");
    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                if (NZcount >= m * n){
                    printf("Not a sparse matrix!\n");
                } else {
                    printf("The given matrix is sparse.\n");
                }
                break;
            }

            case 2: {
                printf("The matrix entered is: \n");
                for(int i = 0; i < m; i++){
                    for(int j = 0; j < n; j++){
                        printf("%d ", *(arr + i * n + j));
                    }
                    printf("\n");
                }
                break;
            }

            case 3: {
                printf("Printing Sparse Matrix:\n");
                printf("Row\tColumn\tValue\n");
                for(int i = 0; i < NZcount; i++){
                    printf("%d\t%d\t%d\n", *(SparseMat + i), *(SparseMat + NZcount + i), *(SparseMat + 2 * NZcount + i));
                }
                break;
            }

            case 4: {
                int SearchElem;
                printf("Enter element to search in matrix: ");
                scanf("%d", &SearchElem);
                int found = 0;
                for(int i = 0; i < NZcount; i++){
                    if(*(SparseMat + 2 * NZcount + i) == SearchElem){
                        printf("Found %d in row: %d and column: %d\n", *(SparseMat + 2 * NZcount + i), *(SparseMat + 0 * NZcount + i), *(SparseMat + 1 * NZcount + i));
                        found = 1;
                    }
                }
                if (!found) {
                    printf("Element %d not found in the sparse matrix.\n", SearchElem);
                }
                break;
            }

            case 5: {
                int Ni, Nj, neighborCount = 0;
                printf("Enter the index [i j]: ");
                scanf("%d", &Ni);
                scanf("%d", &Nj);
                printf("Neighbors in matrix:\n");
                
                for(int i=-1;i<=1;i++){
                    for(int j=-1;j<=1;j++){
                        if(Ni+i>=0 && Nj+j>=0 && Ni+i<m && Nj+j<n){
                            printf("%d ",*(arr+(Ni+i)*n+(Nj+j)));
                        }
                    }
                    printf("\n");
                }
                break;
            }

            case 6:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice! Please select a valid option.\n");
                break;
        }
    } while(choice != 6);

    free(arr);
    free(SparseMat);
    return 0;
}