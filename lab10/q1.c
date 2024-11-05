#include <stdio.h>

#define MAX 100

void displayMatrix(int adjMat[MAX][MAX], int vert) {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < vert; i++) {
        for (int j = 0; j < vert; j++) {
            printf("%d ", adjMat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int adjMat[MAX][MAX] = {0};
    int vert, edg, src, dest;

    printf("Enter number of vertices: ");
    scanf("%d", &vert);
    printf("Enter number of edges: ");
    scanf("%d", &edg);

    for (int i = 0; i < edg; i++) {
        printf("Enter edge %d (source destination): ", i + 1);
        scanf("%d %d", &src, &dest);

        adjMat[src][dest] = 1;
        adjMat[dest][src] = 1;
    }

    displayMatrix(adjMat, vert);
    return 0;
}