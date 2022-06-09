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

// search: 이원 탐색 트리의 순환적 탐색
// cf. 반환형이 element *, 함수 포인터와 개념이 다름
element *serach(treePointer tree, int k){
    if(!root) return NULL;
    if(k == root->data.key) return &(root->data);
    if(k < root->data.key) return search(root->leftChild, k);
    return search(root->rightChild, k);
}

// iterSearch: 이원 탐색 트리의 반복적 탐색
// cf. 반환형이 element *, 함수 포인터와 개념이 다름
element *iterSerach(treePointer tree, int k){
    while(tree){
        if(k == tree->data.key) return &(tree->data);
        if(k < tree->data.key) tree = tree->leftChild;
        else tree = tree->rightChild;
    }
    return NULL;
}