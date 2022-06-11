#include<stdio.h>
#include<stdlib.h>

#define FALSE 0
#define TRUE 1
#define NODES 100
#define MALLOC(p,s) \
    if(!((p)=malloc(s))) { \
        printf("Insufficient memory"); \
        exit(-1); \
    }
#define MIN(x,y) ((x)<(y) ? (x):(y))

typedef struct node *nodePointer;
typedef struct node{
    int vertex;
    nodePointer link;
} node;

nodePointer graph[NODES];
short int visited[NODES];
short int dfn[NODES];
short int low[NODES];
int num;

// push: i번째 연결 스택에서의 삽입
void push(int i, int item){
    nodePointer temp;
    MALLOC(temp, sizeof(*temp));

    temp->vertex = item;
    temp->link = graph[i];
    graph[i] = temp;
}

// dfs: 깊이 우선 탐색
void dfs(int v){
    nodePointer w;
    // 첫 노드 visit 설정 & 출력
    visited[v] = TRUE;
    printf("%3d ", v);
    // v부터 시작해서 link로 연결된 정점의 재귀 호출
    for(w = graph[v]; w; w = w->link)
        if(!visited[w->vertex]) dfs(w->vertex);
}

// init: dfn, low의 초기화
void init(){
    int i;
    for(i=0; i<NODES; i++){
        visited[i] = FALSE;
        dfn[i] = low[i] = -1;
    }
    num = 0;
}

// dfnlow: dfn, low의 결정
// dfn(u) = 정점의 깊이 우선 탐색 순서
// low(u) = min{c1->dfn(u), c2->min{low(w)|w는 u의 child}, c3->min{dfn(w)|(u, w)는 back-edge}}
void dfnlow(int u, int v){  // u가 자식, v가 부모인 경우에서 dfs 수행
    nodePointer ptr;
    int w;
    dfn[u] = low[u] = num++;
    for(ptr = graph[u]; ptr; ptr=ptr->link){
        w = ptr->vertex;
        // u에 연결된 정점 중 방문되지 않은 w
        if(dfn[w] < 0){
            dfnlow(w, u); // 재귀 호출, 깊이 우선으로 dfn 계산
            low[u] = MIN(low[u], low[w]); // c1, c2의 비교
        }
        // u에 연결된 정점 중 방문된 w
        else if(w != v) // back-edge = 연결되었지만, 부모-자식 관계가 아닌 경우
            low[u] = MIN(low[u], dfn[w]); // c1 & c2, c3의 비교
    }
}

int main(){
    
    // cf. push 함수가 스택이므로 역순으로 삽입
    push(0, 1);
    push(1, 3); push(1, 2); push(1, 0);
    push(2, 4), push(2, 1);
    push(3, 5); push(3, 4); push(3, 1);
    push(4, 3); push(4, 2);
    push(5, 7); push(5, 6); push(5, 3);
    push(6, 7); push(6, 5);
    push(7, 9); push(7, 8); push(7, 6); push(7, 5);
    push(8, 7);
    push(9, 7);

    printf("\n   dfs: ");
    dfs(3);

    init();
    dfnlow(3, -1);

    printf("\nvertex: ");
    for(int i=0; i<10; i++) printf("%3d ", i);
    printf("\n   dfn: ");
    for(int i=0; i<10; i++) printf("%3d ", dfn[i]);
    printf("\n   low: ");
    for(int i=0; i<10; i++) printf("%3d ", low[i]);

    return 0;
}