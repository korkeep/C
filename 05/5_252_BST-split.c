#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) \
    if(!((p)=malloc(s))) { \
        printf("Insufficient memory"); \
        exit(-1); \
    }

typedef struct node *treePointer;
struct node{
    element data;
    treePointer leftChild, rightChild;
};
typedef struct element{
    int key;
    int item;
} element;
treePointer root;

// split: 이원 탐색 트리의 분할 (small, mid, big)
void split(treePointer *theTree, int k, treePointer *small, element *mid, treePointer *big){
    if(!theTree){
        *small = *big = NULL;
        (*mid).key = -1;
        return;
    }
    
    treePointer sHead, bHead, s, b, curNode;
    MALLOC(sHead, sizeof(*sHead));  // small 트리의 헤더
    MALLOC(bHead, sizeof(*bHead));  // big 트리의 헤더
    
    curNode = *theTree; 
    while(curNode){
        // big 트리에 삽입
        if(k < curNode->data.key){
            b->leftChild = curNode;
            b = curNode;
            curNode = curNode->leftChild;
        }
        // small 트리에 삽입
        else if(k > curNode->data.key){
            s->rightChild = curNode;
            s = curNode;
            curNode = curNode->rightChild;
        }
        // split 연산 수행
        else{
            s->rightChild = curNode->leftChild;
            b->leftChild = curNode->rightChild;
            *small = sHead->rightChild; free(sHead);
            *big = bHead->leftChild; free(bHead);
            (*mid).item = curNode->data.item;
            (*mid).key = curNode->data.key;
            free(curNode);
            return;
        }
    }

    // k를 트리에서 찾을 수 없는 경우
    s->rightChild = b->leftChild = NULL;
    *small = sHead->rightChild; free(sHead);
    *big = bHead->leftChild; free(bHead);
    (*mid).key = -1;
    return;
}