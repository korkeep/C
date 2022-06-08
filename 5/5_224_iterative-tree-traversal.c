#include<stdio.h>
#include<stdlib.h>
#define SIZE 15
#define MALLOC(p,s) \
    if(!((p)=malloc(s))) { \
        printf("Insufficient memory"); \
        exit(-1); \
    }

typedef struct node *treePointer;
struct node{
    int data;
    treePointer leftChild, rightChild;
};

typedef struct stack *stackPointer;
struct stack{
    treePointer data;
    stackPointer link;
};
stackPointer top = NULL;

// push: 연결 스택에서의 삽입
void push(treePointer item){
    stackPointer temp;
    MALLOC(temp, sizeof(*temp));

    temp->data = item;
    temp->link = top;
    top = temp;
}

// pop: 연결 스택에서의 삭제
treePointer pop(){
    treePointer item;
    stackPointer temp = top;
    if(!temp) return NULL;
    item = temp->data;
    top = temp->link;
    free(temp);
    return item;
}

// iterInorder: 반복적 중위 순회
void iterInorder(treePointer ptr){
    while(1){
        // ptr의 왼쪽 방향으로 이동, stack에 push
        while(ptr){
            push(ptr);
            ptr = ptr->leftChild;
        }
        // pop 결과를 ptr에 저장, 출력
        ptr = pop();
        if(!ptr) break;
        printf("%d ", ptr->data);
        // ptr의 오른쪽 자식으로 이동
        ptr = ptr->rightChild;
    }
}

int main(){
    treePointer temp;
    treePointer tree[SIZE+1];

    for(int i=1; i<=SIZE; i++){
        MALLOC(temp, sizeof(*temp));
        temp->leftChild = NULL;
        temp->rightChild = NULL;
        tree[i] = temp;
    }

    for(int i=1; i<=SIZE; i++){
        tree[i]->data = i;        
        if(i<=SIZE/2){
            tree[i]->leftChild = tree[i*2];
            tree[i]->rightChild = tree[i*2+1];
        }
    }

    iterInorder(tree[1]); printf("\n");

    return 0;
}