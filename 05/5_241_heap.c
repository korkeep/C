#include<stdio.h>

#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct element{
    int key;
} element;
element heap[MAX_ELEMENTS];
int n = 0;

// push: 최대 히프에 삽입 (shift-up)
void push(element item, int *n){
    int i;
    if(HEAP_FULL(*n)){
        printf("The heap is full.\n");
        exit(-1);
    }
    // n = 현재 힙에 있는 최대 인덱스의 개수
    i = ++(*n);
    // i가 root가 아닐 때, key값이 부모보다 크면 재설정
    while((i!=1) && (item.key>heap[i/2].key)){
        heap[i] = heap[i/2];    // 자식의 값을 부모와 교체
        i /= 2;                 // idx를 바뀐 위치로 이동
    }
    heap[i] = item;     // 재설정된 i의 자리에 item 삽입
}

// pop: 최대 히프에서의 삭제
element pop(int *n){
    int parent, child;
    element item, temp;
    if(HEAP_EMPTY(*n)){
        printf("The heap is empty.\n");
        exit(-1);
    }
    item = heap[1];         // item = 가장 큰 값
    temp = heap[(*n)--];    // temp = 마지막 원소
    parent = 1; child = parent*2;
    // 마지막 원소가 들어가야 할 자리 찾는 과정
    while(child <= *n){
        // child와 같은 level에 노드가 있고, L-R중 R이 큰 경우 child를 R로 변경
        if(child < *n && (heap[child].key < heap[child+1].key)) child++;
        // 마지막 원소 값이 child보다 큰 경우, 해당 자리에 temp가 들어가야 하므로 break
        if(temp.key >= heap[child].key) break;
        // 위에서 아래로 한 단계 내려가는 과정
        heap[parent] = heap[child];
        parent = child;
        child *= 2; 
    }
    // 마지막 원소 값을 parent 자리에 삽입
    heap[parent] = temp;
    return item;
}