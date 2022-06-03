#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) \
    if(!((p)=malloc(s))) { \
        printf("Insufficient memory\n"); \
        exit(-1); \
    }
#define COMPARE(x,y) ((x)<(y) ? -1 : ((x)==(y)) ? 0 : 1)

typedef struct polyNode *polyPointer;
struct polyNode{
    float coef; // 계수
    int expon;  // 지수
    polyPointer link;
};
polyPointer avail;

// getNode: 가용 리스트에서 노드 제공
polyPointer getNode(){
    polyPointer node;
    if(avail){
        node = avail;
        avail = avail->link;
    }
    else MALLOC(node, sizeof(*node));
    return node;
}

// retNode: 가용 리스트에 노드를 반환
void retNode(polyPointer node){
    node->link = avail;
    avail = node;
}

// cerase: ptr이 가리키는 원형 리스트 전체 제거
// cf. *ptr = 2중 포인터
void cerase(polyPointer *ptr){
    polyPointer temp;
    if(*ptr){
        temp = (*ptr)->link;
        (*ptr)->link = avail;
        avail = temp;
        *ptr = NULL;
    }
}