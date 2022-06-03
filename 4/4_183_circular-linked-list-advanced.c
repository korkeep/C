#include<stdio.h>

typedef struct listNode *listPointer;
struct listNode{
    char data;
    listPointer link;
};
listPointer avail;

// getNode: 가용 리스트에서 노드 제공
listPointer getNode(){
    listPointer node;
    if(avail){
        node = avail;
        avail = avail->link;
    }
    else MALLOC(node, sizeof(*node));
    return node;
}

// retNode: 가용 리스트에 노드를 반환
void retNode(listPointer node){
    node->link = avail;
    avail = node;
}

// cerase: ptr이 가리키는 원형 리스트 전체 제거
// cf. *ptr = 2중 포인터
void cerase(listPointer *ptr){
    listPointer temp;
    if(*ptr){
        temp = (*ptr)->link;
        (*ptr)->link = avail;
        avail = temp;
        *ptr = NULL;
    }
}

// insertFront: 원형 리스트의 앞에 삽입
// cf. *last = 2중 포인터
void insertFront(listPointer *last, listPointer node){
    if(!(*last)){
        *last = node;
        node->link = node;
    }
    else{
        node->link = (*last)->link;
        (*last)->link = node;
    }
}

// insertRear: 원형 리스트의 앞에 삽입
// cf. *last = 2중 포인터
void insertRear(listPointer *last, listPointer node){
    if(!(*last)){
        *last = node;
        node->link = node;
    }
    else{
        node->link = (*last)->link;
        (*last)->link = node;
        *last = node;  // 새로 생성된 노드가 last를 가리키도록
    }
}

// length: 원형 리스트의 길이 계산
int length(listPointer last){
    listPointer temp;
    int count = 0;
    if(last){
        temp = last;
        do{
            count++;
            temp = temp->link;
        } while(temp != last);
    }
    return count;
}