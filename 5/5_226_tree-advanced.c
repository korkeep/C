#include<stdio.h>
#include<stdlib.h>
#define SIZE 15
#define MALLOC(p,s) \
    if(!((p)=malloc(s))) { \
        printf("Insufficient memory"); \
        exit(-1); \
    }

typedef struct node *treePointer;
struct node{
    int data;
    treePointer leftChild, rightChild;
};

// copy: 이진 트리의 복사
treePointer copy(treePointer origin){
    treePointer temp;
    if(origin){
        MALLOC(temp, sizeof(*temp));
        temp->leftChild = copy(origin->leftChild);
        temp->rightChild = copy(origin->rightChild);
        temp->data = origin->data;
        return temp;
    }
    return NULL;
}

// equal: 이진 트리의 동일성 검사
int equal(treePointer first, treePointer second){
    return (!first && !second) ||       // Case 1. leaf인 노드
            (first && second &&         // Case 2. leaf가 아닌 노드
                (first->data==second->data) &&
                equal(first->leftChild, second->leftChild) &&
                equal(first->rightChild, second->rightChild));
}