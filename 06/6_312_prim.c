#include<stdio.h>
#define TRUE 1
#define FALSE 0
#define MAX 7
#define INF 123456789

int weight[MAX][MAX] = {
    {0, 29, INF, INF, INF, 10, INF},
    {29, 0, 16, INF, INF, INF, 15},
    {INF, 16, 0, 12, INF, INF, INF},
    {INF, INF, 12, 0, 22, INF, 18},
    {INF, INF, INF, 22, 0, 27, 25},
    {10, INF, INF, INF, 27, 0, INF},
    {INF, 15, INF, 18, 25, INF, 0}
};

int selected[MAX];  // 정점의 선택여부
int dist[MAX];      // 정점의 최소거리

// find: 최소 dist[v]를 갖는 정점을 반환
int find(int n){
    int v, i;

    // 아직 선택되지 않은 정점을 v에 저장
    for(i=0; i<n; i++){
        if(selected[i] == FALSE) {v = i; break;}
    }
    // 선택되지 않은 정점을 순회하며 최소거리 정점을 찾음
    for(i=0; i<n; i++){
        if(selected[i] == FALSE && (dist[i] < dist[v])) v = i;
    }

    return v;
}

// prim: Prim 알고리즘
void prim(int s, int n){
    int i, u, v;
    dist[s] = 0; // 시작 노드를 0으로 설정

    for(i=0; i<n; i++){
        // 최소 dist를 갖는 정점의 반환
        u = find(n); selected[u] = TRUE;
        // Spanning Tree가 아닌 경우 예외처리
        if(dist[u] == INF) return;
        // 방문한 정점을 출력
        printf("%d ", u);
        // 기존의 거리보다 짧은 경우가 발견된 경우
        for(v=0; v<n; v++){
            if(weight[u][v] != INF){
                // 새롭게 발견된 짧은 거리로 업데이트
                if(selected[v] == FALSE && weight[u][v] < dist[v])
                    dist[v] = weight[u][v];
            }
        }
    }    
}

void main(){
    int i;
    for(i=0; i<MAX; i++){
        dist[i] = INF;
        selected[i] = FALSE;
    }

    prim(0, MAX);
}