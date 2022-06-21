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

typedef struct node *nodePointer;
typedef struct node{
    int vertex;
    nodePointer link;
} node;

nodePointer graph[NODES];
short int visited[NODES];

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

int main(){
    
    // cf. push 함수가 스택이므로 역순으로 삽입
    push(0, 2); push(0, 1);
    push(1, 4); push(1, 3); push(1, 0);
    push(2, 6), push(2, 5); push(2, 0);
    push(3, 7); push(3, 1);
    push(4, 7); push(4, 1);
    push(5, 7); push(5, 2);
    push(6, 7); push(6, 2);
    push(7, 6); push(7, 5); push(7, 4); push(7, 3);

    dfs(0);

    return 0;
}