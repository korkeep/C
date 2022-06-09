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

// modifiedSearch: insert에서 k, i가 삽입되어야 하는 부모 노드
// cf. 반환형이 treePointer *, 함수 포인터와 개념이 다름
treePointer *modifiedSerach(treePointer tree, int k){
    treePointer temp;
    if(!tree) return NULL;  // 트리가 공백인 경우
    while(tree){
        if(k == tree->data.key) return NULL; // k가 존재하는 경우
        if(k < tree->data.key) {temp = tree; tree = tree->leftChild;}
        else {temp = tree; tree = tree->rightChild;}
    }
    return temp; // 마지막으로 검사한 노드의 포인터
}

// insert: 이원 탐색 트리에 삽입
void insert(treePointer *node, int k, int i){
    treePointer ptr;
    treePointer temp = modifiedSerach(*node, k);
    if(temp || !(*node)){
        MALLOC(ptr, sizeof(*ptr));
        ptr->data.key = k;
        ptr->data.item = i;
        ptr->leftChild = ptr->rightChild = NULL;
        // 트리 중간에 삽입되는 경우
        if(*node){
            if(k < temp->data.key) temp->leftChild = ptr;
            else temp->rightChild = ptr;
        }
        // root에 삽입되는 경우
        else{
            *node = ptr;
        }
    }
}