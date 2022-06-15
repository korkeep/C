#include<stdio.h>
#include<stdlib.h>
#define MAXN 7
#define MAXE 10
#define INF 123456789
#define MALLOC(p,s) \
    if(!((p)=malloc(s))) { \
        printf("Insufficient memory"); \
        exit(-1); \
    }

typedef struct edge *edgePtr;
typedef struct edge{
    int src;    // 시작 지접
    int dest;   // 종료 지점
    int weight; // 가중치
}edge;

typedef struct graph *graphPtr;
typedef struct graph{
    int V;      // 정점의 수
    int E;      // 간선의 수
    edge *edge; // 간선
} graph;

// bellmanford: 하나의 출발점에서 최단 경로 (음의 길이를 가지는 간선 비용)
void bellmanford(graphPtr g, int src){
    int i, j, k;
    int V = g->V;
    int E = g->E;
    
    int *dist;
    MALLOC(dist, sizeof(int)*V);
    for(i=0; i<V; i++) dist[i] = INF;
    dist[src] = 0;

    for(i=1; i<=V-1; i++){
        for(j=0; j<E; j++){
            int u = g->edge[j].src;
            int v = g->edge[j].dest;
            int weight = g->edge[j].weight;
            // case 1. 정점 u가 무한대가 아닌 경우
            // case 2. "시작점까지 최단거리 + 가중치 < 도착점의 가중치"인 경우
            if(dist[u]!=INF && dist[u]+weight < dist[v]) dist[v] = dist[u]+weight;
            printf("u:%2d, v:%2d ->", u, v);
            for(k=0; k<g->V; k++) dist[k] != INF ? printf("%3d ", dist[k]) : printf("INF ");
            printf("\n");
        }
    }

    // 음의 가중치에 의해 무한히 최단 경로가 작아지는 케이스 추출
    for(i=0; i<E; i++){
        int u = g->edge[i].src; 
        int v = g->edge[i].dest;
        int weight = g->edge[i].weight;        
        if(dist[u] != INF && dist[u]+weight < dist[v]){
            printf("Graph contains negative weight cycle\n");
            break;
        }
    }
}

void main(){
    int src = 0;
    edgePtr e; MALLOC(e, sizeof(*e)*MAXE);
    graphPtr g; MALLOC(g, sizeof(*g));
    g->V = MAXN; g->E = MAXE; g->edge = e;

    g->edge[0].src = 0; g->edge[0].dest = 1; g->edge[0].weight = 6;
    g->edge[1].src = 0; g->edge[1].dest = 2; g->edge[1].weight = 5;
    g->edge[2].src = 0; g->edge[2].dest = 3; g->edge[2].weight = 5;
    g->edge[3].src = 2; g->edge[3].dest = 1; g->edge[3].weight = -2;
    g->edge[4].src = 3; g->edge[4].dest = 2; g->edge[4].weight = -2;
    g->edge[5].src = 1; g->edge[5].dest = 4; g->edge[5].weight = -1;
    g->edge[6].src = 2; g->edge[6].dest = 4; g->edge[6].weight = 1;
    g->edge[7].src = 3; g->edge[7].dest = 5; g->edge[7].weight = -1;
    g->edge[8].src = 4; g->edge[8].dest = 6; g->edge[8].weight = 3;
    g->edge[9].src = 5; g->edge[9].dest = 6; g->edge[9].weight = 3;

    bellmanford(g, src);
}