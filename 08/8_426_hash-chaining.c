#include<stdio.h>
#define MAX_SIZE 10

typedef struct element *tablePointer;
typedef struct element{
    int key;
} element;
tablePointer ht[MAX_SIZE];

typedef struct node *nodePointer;
typedef struct node{
    element data;
    nodePointer link;
} node;

// search: 체인 검색
element *search(int k){
    nodePointer current;
    int homeBucket = h(k);
    for(current=ht[homeBucket]; current; current=current->link){
        // Case 1. 버킷 ht[h(k)+j]%b에 값이 k인 키 쌍이 있는 경우
        if(current->data.key == k) return &current->data;
    }
    // Case 2. ht[h(k)+j]가 비어있는 경우, k는 테이블에 없음
    return NULL;
}