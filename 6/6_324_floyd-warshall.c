#include<stdio.h>
#define MAX 7
#define INF 123456789

int cost[MAX][MAX] = {
    {0, 29, INF, INF, INF, 10, INF},
    {29, 0, 16, INF, INF, INF, 15},
    {INF, 16, 0, 12, INF, INF, INF},
    {INF, INF, 12, 0, 22, INF, 18},
    {INF, INF, INF, 22, 0, 27, 25},
    {10, INF, INF, INF, 27, 0, INF},
    {INF, 15, INF, 18, 25, INF, 0}
};

int dist[MAX][MAX];

// printM: 2차원 행렬을 출력하는 함수
void printM(int matrix[][MAX]){
    int i, j, temp;
    for(i=0; i<MAX; i++){
        for(j=0; j<MAX; j++){
            temp = matrix[i][j];
            temp != INF ? printf("%3d ", temp) : printf("INF ");
        }
        printf("\n");
    }
}

// floyd: 모든 쌍의 최단 경로를 구하는 함수
void floyd(int n){
    int i, j, k;
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            dist[i][j] = cost[i][j];
    
    printf("iter 0\n");
    printM(dist);
    printf("\n");

    for(k=0; k<n; k++){
        printf("iter %d\n", k+1);
        for(i=0; i<n; i++){
            for(j=0; j<n; j++){
                if(dist[i][j]>dist[i][k]+dist[k][j])
                    dist[i][j] = dist[i][k]+dist[k][j];
                
            }
        }
        printM(dist);
        printf("\n");
    }
}

void main(){
    floyd(MAX);
}