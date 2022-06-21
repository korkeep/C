#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct node *nodePointer;
typedef struct node{
    int vertex; // 노드 번호
    nodePointer link;
} node;
typedef struct hdnodes{
    int count;  // 진입 차수, 스택 번호로 활용됨
    nodePointer link;
} hdnodes;
hdnodes graph[MAX];

// topSort: 위상 정렬
void topSort(int n){
    int i, j, k, top;
    nodePointer ptr;
    // 시작 노드의 설정
    top = -1;
    for(i=0; i<n; i++){
        if(!graph[i].count){
            graph[i].count = top;
            top = i;
        }
    }
    // 시작 노드에서부터 이어짐
    for(i=0; i<n; i++){
        if(top == -1){
            printf("Network has a cycle.\n");
            exit(-1);
        }
        else{
            // 정점 출력
            j = top;
            top = graph[top].count;
            printf("v%d, ", j);
            // graph[j]에서부터 출발하는 리스트
            for(ptr = graph[j].link; ptr; ptr = ptr->link){
                // 정점의 삭제
                k = ptr->vertex;
                graph[k].count--;
                // 새로운 시작 노드 설정
                if(!graph[k].count){
                    graph[k].count = top;
                    top = k;
                }
            }
        }
    }
}

// init: AOV 그래프의 초기화
void init(){
    int i;
    for(i=0; i<MAX; i++){
        graph[i].count = 0;
        graph[i].link = NULL;
    }
}

// add: AOV 그래프에 node 할당
void add(int src, int dest){
    node* newNode = (node*)malloc(sizeof(node));
    node* temp = graph[src].link;
    
    newNode->vertex = dest;
    newNode->link = NULL;
    graph[dest].count++;

    if(temp == NULL)
        graph[src].link = newNode;
    else{
        while(temp->link != NULL) temp = temp->link;
        temp->link = newNode;
    }
}

void main() {
    init();
    
    add(0, 1); add(0, 2); add(0, 3);
    add(1, 4);
    add(2, 4); add(2, 5);
    add(3, 4); add(3, 5);
    
    topSort(6);
}