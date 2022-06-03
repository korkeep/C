#include<stdio.h>
#include<stdlib.h>
#define MALLOC(p,s) \
    if(!((p)=malloc(s))) { \
        printf("Insufficient memory\n"); \
        exit(-1); \
    }
#define QUEUES 10  // 큐 자료구조의 수

typedef struct{
    int key;
} element;

typedef struct queue *queuePointer;
struct queue{
    element data;
    queuePointer link;
};
queuePointer front[QUEUES], rear[QUEUES];

// push: i번째 연결 큐에서의 삽입 (뒤에서부터)
void push(int i, element item){
    queuePointer temp;
    MALLOC(temp, sizeof(*temp));
    
    temp->data = item;
    temp->link = NULL;

    if(front[i]) rear[i]->link = temp;
    else front[i] = temp;
    rear[i] = temp;
}

// pop: i번째 연결 큐에서의 삭제 (앞에서부터)
element pop(int i){
    queuePointer temp = front[i];
    element item;

    if(!temp) queueEmpty();
    item = temp->data;
    front[i] = temp->link;
    
    free(temp);
    return item;
}

void queueEmpty(){
    printf("Queue is empty, cannot pop element\n");
    exit(-1);
}