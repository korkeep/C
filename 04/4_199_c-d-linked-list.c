#include<stdio.h>
#include<stdlib.h>

typedef struct node *nodePointer;
struct node{
    nodePointer llink;
    char data;
    nodePointer rlink;
};

// dinsert: 이중 원형 연결 리스트에 삽입
void dinsert(nodePointer node, nodePointer newnode){
    newnode->llink = node;
    newnode->rlink = node->rlink;
    node->rlink = newnode;
    node->rlink->llink = newnode;
}

// ddelete: 이중 원형 연결 리스트에서의 삭제
void ddelete(nodePointer node, nodePointer deleted){
    if(node==deleted)
        printf("Deletion of head is not permitted.\n");
    else{
        deleted->llink->rlink = deleted->rlink;
        deleted->rlink->llink = deleted->llink;
        free(deleted);
    }
}