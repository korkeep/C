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

typedef struct stack *stackPointer;
typedef struct stack{
    int w;
    int u;
    stackPointer link;
} stack;

nodePointer graph[NODES];
stackPointer top;
short int visited[NODES];
short int dfn[NODES];
short int low[NODES];
int num;

// gpush: i번째 연결 스택에서의 삽입
void gpush(int i, int item){
    nodePointer temp;
    MALLOC(temp, sizeof(*temp));

    temp->vertex = item;
    temp->link = graph[i];
    graph[i] = temp;
}

// push: 연결 스택에서의 삽입
void push(int u, int w){
    stackPointer temp;
    MALLOC(temp, sizeof(*temp));

    temp->u = u;
    temp->w = w;
    temp->link = top;
    top = temp;
}

// pop: i번째 연결 스택에서의 삭제
void pop(int *u, int *w){
    stackPointer temp = top;
    
    if(!temp) return NULL;
    *w = temp->w;
    *u = temp->u;
    top = temp->link;
    
    free(temp);
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

// bicon: 그래프의 이중결합 요소
// dfn(u) = 정점의 깊이 우선 탐색 순서
// low(u) = min{c1->dfn(u), c2->min{low(w)|w는 u의 child}, c3->min{dfn(w)|(u, w)는 back-edge}}
void bicon(int u, int v){   // u가 자식, v가 부모인 경우에서 dfs 수행
    nodePointer ptr;
    int w, x, y;
    dfn[u] = low[u] = num++;
    for(ptr = graph[u]; ptr; ptr=ptr->link){
        w = ptr->vertex;
        // 간선을 처음 만났을 때 stack에 보관
        if(v!=w && dfn[w]<dfn[u]){
            // stack에 u, w 삽입
            push(u, w);
            // u에 연결된 정점 중 방문되지 않은 w
            if(dfn[w] < 0){
                bicon(w, u); // 재귀 호출, 깊이 우선으로 dfn 계산
                low[u] = MIN(low[u], low[w]); // c1, c2의 비교
                // 새로운 단절점이 발견되는 경우 (low[w] >= dfn[u])
                if(low[w]>=dfn[u]){
                    printf("\nNew biconnected component: ");
                    do{
                        pop(&x, &y);  // stack에 push했던 간선 pop
                        printf(" <%d, %d>", x, y);
                    } while(!((x==u) && (y==w))); // 현재 u, w와 같아질 때까지 반복
                }
            }
            // u에 연결된 정점 중 방문된 w
            else if(w != v) // back-edge = 연결되었지만, 부모-자식 관계가 아닌 경우
                low[u] = MIN(low[u], dfn[w]); // c1 & c2, c3의 비교
        }
    }
}

int main(){
    
    // cf. push 함수가 스택이므로 역순으로 삽입
    gpush(0, 1);
    gpush(1, 3); gpush(1, 2); gpush(1, 0);
    gpush(2, 4), gpush(2, 1);
    gpush(3, 5); gpush(3, 4); gpush(3, 1);
    gpush(4, 3); gpush(4, 2);
    gpush(5, 7); gpush(5, 6); gpush(5, 3);
    gpush(6, 7); gpush(6, 5);
    gpush(7, 9); gpush(7, 8); gpush(7, 6); gpush(7, 5);
    gpush(8, 7);
    gpush(9, 7);

    printf("\n   dfs: ");
    dfs(3);

    init();
    bicon(3, -1);

    return 0;
}