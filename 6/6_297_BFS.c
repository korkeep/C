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
struct node{
    int vertex;
    nodePointer link;
};

nodePointer front, rear;
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

// addq: 연결 큐에서의 삽입 (뒤에서부터)
void addq(int item){
    nodePointer temp;
    MALLOC(temp, sizeof(*temp));
    
    temp->vertex = item;
    temp->link = NULL;

    if(front) rear->link = temp;
    else front = temp;
    rear = temp;
}

// deleteq: 연결 큐에서의 삭제 (앞에서부터)
int deleteq(){
    nodePointer temp = front;
    int item;

    if(!temp) return NULL;
    item = temp->vertex;
    front = temp->link;
    
    free(temp);
    return item;
}

// bfs: 그래프의 너비 우선 탐색
void bfs(int v){
    nodePointer w;
    front = rear = NULL;
    // visit 설정 & 출력
    printf("%3d ", v);
    visited[v] = TRUE;
    // 현재 정점 queue에 추가
    addq(v);
    while(front){
        // 현재 정점 queue에 삭제
        v = deleteq();
        // w = v에서 출발하는 리스트, visit 설정 & 출력
        for(w=graph[v]; w; w = w->link){
            if(!visited[w->vertex]){
                printf("%3d ", w->vertex);
                addq(w->vertex);
                visited[w->vertex] = TRUE;
            }
        }
    }
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

    bfs(0);

    return 0;
}