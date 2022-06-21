#include<stdio.h>
#define TRUE 1
#define FALSE 0
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

int found[MAX]; // 정점의 선택여부
int dist[MAX];  // 정점의 최소거리

void dijkstra(int v, int n);
int choose(int n);

// dijkstra: 하나의 출발점에서 최단 경로 (음이 아닌 간선 비용)
void dijkstra(int v, int n){
    int i, u, w;
    // v부터 i까지 간선의 거리로 초기화
    for(i=0; i<n; i++) dist[i] = cost[v][i];
    found[v] = TRUE;
    dist[v] = 0;
    
    for(i=0; i<n-2; i++){
        u = choose(n);  // 최저비용 간선의 선택
        found[u] = TRUE;
        // 더 작은 경로 발견된 경우 비용 업데이트
        for(w=0; w<n; w++){
            if(!found[w] && (dist[u]+cost[u][w] < dist[w]))
                dist[w] = dist[u]+cost[u][w];
        }
    }
}

// choose: 최저비용 간선의 선택
int choose(int n){
    int i, min, minpos;
    min = INF;
    minpos = -1;
    // i 인덱스에서 found = FALSE 이고, dist가 최소인 경우
    for(i=0; i<n; i++){
        if(dist[i]<min && !found[i]){
            min = dist[i];
            minpos = i;
        }
    }
    // 최저비용 간선의 인덱스 반환
    return minpos;
}

void main(){
    int i;
    for(i=0; i<MAX; i++) found[i] = FALSE;

    dijkstra(0, MAX);

    for(i=0; i<MAX; i++) printf("%3d ", dist[i]);
}