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

// erase: 전체 노드의 제거
// cf. *ptr = 2중 포인터
void erase(listPointer *ptr){
    listPointer temp;
    while(*ptr){
        temp = *ptr;
        *ptr = (*ptr)->link;
        free(temp);
    }
}

// invert: 단순 연결 리스트를 역순으로 만드는 함수
listPointer invert(listPointer lead){
    listPointer middle, trail;
    middle = NULL;
    while(lead){
        trail = middle;
        middle = lead;
        lead = lead->link;
        middle->link = trail;
    }
    return middle;
}

// concatenate: 단순 연결 리스트의 연결
listPointer concatenate(listPointer ptr1, listPointer ptr2){
    listPointer temp;
    if(!ptr1) return ptr2;
    if(!ptr2) return ptr1;
    for(temp=ptr1; temp->link; temp=temp->link); 
    temp->link = ptr2;
}