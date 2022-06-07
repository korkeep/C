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

typedef struct queue *queuePointer;
struct queue{
    treePointer data;
    queuePointer link;
};
queuePointer front = NULL;
queuePointer rear = NULL;

// push: 연결 큐에서의 삽입 (뒤에서부터)
void push(treePointer item){
    queuePointer temp;
    MALLOC(temp, sizeof(*temp));

    temp->data = item;
    temp->link = NULL;
    
    if(front) rear->link = temp;
    else front = temp;
    rear = temp;
}

// pop: 연결 큐에서의 삭제 (앞에서부터)
treePointer pop(){
    queuePointer temp = front;
    treePointer item;

    if(!temp) return NULL;
    item = temp->data;
    front = temp->link;

    free(temp);
    return item;
}

void levelOrder(treePointer ptr){
    if(!ptr) return;
    push(ptr);
    while(1){
        ptr = pop();
        if(ptr){
            printf("%d ", ptr->data);
            if(ptr->leftChild) push(ptr->leftChild);
            if(ptr->rightChild) push(ptr->rightChild);
        }
        else break;
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

    levelOrder(tree[1]); printf("\n");

    return 0;
}