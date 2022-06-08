#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct threadedTree *threadedPointer;
struct threadedTree{
    char data;
    short int leftThread;
    short int rightThread;
    threadedPointer leftChild;
    threadedPointer rightChild;
};

// insucc: 중위 후속자(inorder-successor)의 탐색
threadedPointer insucc(threadedPointer tree){
    threadedPointer temp;
    temp = tree->rightChild;    // temp를 tree의 오른쪽 자식으로 초기화
    if(!tree->rightThread)      // tree에서 R 노드가 존재하는 경우
        while(!temp->leftChild) // temp에서 L 노드가 존재하는 경우 끝까지 이동
            temp = temp->leftChild; // leftChild 방향으로 temp 이동
    return temp;
}

// tinorder: 스레드 이진 트리에서의 중위 순회, stack 없이 순회 가능
void tinorder(threadedPointer tree){
    threadedPointer temp = tree;    // tree가 head 역할을 수행함
    while(1){
        temp = insucc(tree);    // 중위 후속자를 temp로 지정
        if(temp==tree) break;   // 중위 후속자가 tree이면 종료
        printf("%c ", temp->data);
    }
}

// insertRight: 스레드 이진 트리에서의 오른쪽 삽입
void insertRight(threadedPointer s, threadedPointer r){
    threadedPointer temp;
    // 새로 삽입되는 노드 r의 설정
    r->rightChild = s->rightChild;
    r->rightThread = s->rightThread;
    r->leftChild = s;
    r->leftThread = TRUE;
    // 기존 s의 연결을 r로 변경
    s->rightChild = r;
    r->rightThread = FALSE;
    // r에서 R 노드가 존재하는 경우
    // r의 후속자의 leftChild를 r과 연결
    if(!r->rightThread){
        temp = insucc(r);
        temp->leftChild = r;
    }
}