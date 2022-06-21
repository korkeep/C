#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

typedef enum {not, and, or, true, false} logical;
typedef struct node *treePointer;
struct node{
    logical data;
    short int value;
    treePointer leftChild;
    treePointer rightChild;
};

// postOrderEval: 후위 순회를 이용한 연산 함수
void postOrderEval(treePointer node){
    if(node){
        postOrderEval(node->leftChild);
        postOrderEval(node->rightChild);
        switch(node->data){
            case not:
                node->value = !node->rightChild->value;  // not의 경우 오른쪽 자식만 가짐
                break;
            case and:
                node->value = node->rightChild->value && node->leftChild->value;
                break;
            case or:
                node->value = node->rightChild->value && node->leftChild->value;
                break;
            case true:
                node->value = TRUE;
                break;
            case false:
                node->value = FALSE;
        }
    }
}