#include<stdio.h>
#define MAX 7
#define INF 123456789
#define FALSE -123456789

// 음의 가중치 허용하는 인접 행렬
int length[MAX][MAX] = {
    {0, 6, 5, 5, INF, INF, INF},
    {INF, 0, INF, INF, -1, INF, INF},
    {INF, -2, 0, INF, 1, INF, INF},
    {INF, INF, -2, 0, INF, -1, INF},
    {INF, INF, INF, INF, 0, INF, 3},
    {INF, INF, INF, INF, INF, 0, 3},
    {INF, INF, INF, INF, INF, INF, 0}
};
int dist[MAX];   // 정점의 최소거리
int prev[MAX];   // 간선의 존재유무
void bellmanford(int src, int n);

// bellmanford: 하나의 출발점에서 최단 경로 (음의 길이를 가지는 간선 비용)
void bellmanford(int src, int n){
    int u, v, k, i;
    // v부터 i까지 간선의 거리로 초기화
    for(u=0; u<n; u++){
        dist[u] = length[src][u];
        if(length[src][u] != INF) prev[u] = src;
        else prev[u] = FALSE;
    }
    dist[src] = 0; prev[src] = -1; k = 1;
    // 초기화된 dist 출력
    printf("k:%d| ", k);
    for(i=0; i<n; i++) dist[i]!=INF ? printf("%3d ", dist[i]) : printf("INF ");
    printf("\n");
    // 초기화된 prev 출력
    printf("k:%d| ", k);
    for(i=0; i<n; i++) prev[i]!=FALSE ? printf("%3d ", prev[i]) : printf("FAL ");
    printf("\n");
    // bellman-ford 알고리즘
    for(k=2; k<n; k++){
        int cnt = 0;
        for(u=0; u<n; u++){
            for(v=0; v<n; v++){
                if(dist[u]!=INF && dist[v] > dist[u]+length[u][v]){
                    dist[v] = dist[u]+length[u][v];
                    prev[v] = u;
                }
            }
        }
        // dist 출력
        printf("k:%d| ", k);
        for(i=0; i<n; i++) dist[i]!=INF ? printf("%3d ", dist[i]) : printf("INF ");
        printf("\n");
        // prev 출력
        printf("k:%d| ", k);
        for(i=0; i<n; i++) prev[i]!=FALSE ? printf("%3d ", prev[i]) : printf("FAL ");
        printf("\n");
    }
    // 음수 사이클의 유무 확인
    for(k=2; k<n; k++){
        for(u=0; u<n; u++){
            for(v=0; v<n; v++){
                if(dist[u]!=INF && dist[v] > dist[u]+length[u][v]){
                    printf("Graph contains negative weight cycle\n");
                    return;
                }
            }
        }
    }    
}

void main(){
    bellmanford(0, MAX);
}