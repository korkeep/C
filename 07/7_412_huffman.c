#include<stdio.h>

typedef struct treeNode *treePointer;
typedef struct treeNode{
    int weight;
    treePointer leftChild;
    treePointer rightChild;
} treeNode;

// huffman: 최소 가중치 외부 경로 길이를 가진 이진 트리 찾기
void huffman(treePointer heap[], int n){
    int i;
    treePointer tree;
    // 최소 heap의 생성
    initialize(heap, n);
    // huffman-tree 구축 과정
    for(i=1; i<n; i++){
        tree = malloc(sizeof(*tree));
        tree->leftChild = pop(&n);
        tree->rightChild = pop(&n);
        tree->weight = tree->leftChild->weight + tree->rightChild->weight;
        push(tree, &n);
    }
}