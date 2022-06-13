#include<stdio.h>

#define TRUE 1
#define FALSE 0
#define MAX 100
#define HEAP_FULL(n) (n == MAX-1)
#define HEAP_EMPTY(n) (!n)
#define MALLOC(p,s) \
    if(!((p)=malloc(s))) { \
        printf("Insufficient memory"); \
        exit(-1); \
    }

// union, find 집합
int parent[MAX];    // 각 정점의 부모 노드
int num[MAX];       // 각 집합의 크기

// sinit: parent, num 초기화
void sinit(){
    int i;
    for(i=0; i<MAX; i++){
        parent[i] = -1;
        num[i] = 1;
    }
}

// sfind: 정점이 속하는 집합을 반환
int sfind(int v){
    int i, root;
    // 루트노드까지 반복
    for(i = v; parent[i] >= 0; i = parent[i]);
    // 루트(마지막 i) 정보를 저장
    root = i;
    // v의 조상 노드가 root를 향하도록 설정
    for(i = v; parent[i] >= 0; i = parent[i])
        parent[i] = root;
    // 루트 반환
    return root;
}

// sunion: 더 큰 집합을 기준으로 합치기
void sunion(int s1, int s2){
    if(num[s1] < num[s2]){
        parent[s1] = s2;
        num[s2] += num[s1];
    }
    else{
        parent[s2] = s1;
        num[s1] += num[s2];
    }
}

typedef struct element{
    int key;        // 가중치
    int u;          // 정점1
    int v;          // 정점2
} element;

typedef struct heap *heapPointer;
typedef struct heap{
    int size;
    element heap[MAX];
} heap;

// push: 최소 히프에 삽입 (shift-up)
void push(heapPointer h, element item){
    // h->size = 현재 힙에 있는 최대 인덱스의 개수
    int i = ++(h->size);
    if(HEAP_FULL(h->size)){
        printf("The heap is full.\n");
        return;
    }
    // shift-up: 상향식으로 부모 노드와 비교하는 과정
    // i가 루트가 아니고 item의 key가 i의 부모의 키보다 작은 경우
    while((i!=1) && item.key < h->heap[i/2].key){
        // 현재 노드를 새 부모 노드로 설정
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    // 현재 인덱스 위치에 item을 삽입
    h->heap[i] = item;
}

// pop: 최소 히프에서의 삭제
element pop(heapPointer h){
    int parent, child;
    element item, temp;
    if(HEAP_EMPTY(h->size)){
        printf("The heap is empty.\n");
        return;
    }
    item = h->heap[1];           // item = 가장 큰 값
    temp = h->heap[(h->size)--]; // temp = 마지막 원소
    parent = 1; child = parent*2;
    // 마지막 원소가 들어가야 할 자리 찾는 과정
    while(child <= h->size){
        // child와 같은 level에 노드가 있고, L-R중 R이 작은 경우 child를 R로 변경
        if(child < h->size && (h->heap[child].key > h->heap[child+1].key)) child++;
        // 마지막 원소 값이 child보다 작은 경우, 해당 자리에 temp가 들어가야 하므로 break
        if(temp.key <= h->heap[child].key) break;
        // 위에서 아래로 한 단계 내려가는 과정
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2; 
    }
    // 마지막 원소 값을 parent 자리에 삽입
    h->heap[parent] = temp;
    return item;
}

// insert: 초기화 과정에서 히프의 노드를 삽입하는 함수
void insert(heapPointer h, int u, int v, int weight){
    element e;
    e.u = u;
    e.v = v;
    e.key = weight;
    push(h, e);
}

// kruskal: Kruskal 알고리즘
void kruskal(heapPointer h, int n){
    element e;
    int edge_accepted = 0; // 현재까지 선택된 간선의 수
    int uset, vset;        // 정점 u와 정점 v의 집합 번호

    while(edge_accepted < (n-1)) {  // 간선의 수 = n-1
        e = pop(h);
        uset = sfind(e.u);
        vset = sfind(e.v);

        if(uset != vset){  // 다른 집합에 속할 시 최소경로가 되므로 출력
            printf("(%d, %d) %d \n", e.u, e.v, e.key);
            edge_accepted++;
            sunion(uset, vset);
        }
    }
}

void main(){
    heapPointer h;
    MALLOC(h, sizeof(*h));
    
    sinit();

    h->size = 0;
    insert(h, 0, 1, 29);
    insert(h, 1, 2, 16);
    insert(h, 2, 3, 12);
    insert(h, 3, 4, 22);
    insert(h, 4, 5, 27);
    insert(h, 5, 0, 10);
    insert(h, 6, 1, 15);
    insert(h, 6, 3, 18);
    insert(h, 6, 4, 25);

    kruskal(h, 7);
}