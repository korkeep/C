#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
    if(!((p) = malloc(s))) { \
        printf("Insufficient memeory"); \
        exit(-1); \
    }
#define INIT_QUEUE_SIZE 1

typedef struct{
    int key;
} element;

element *queue;
static int rear = -1;   // 뒤
static int front = -1;  // 앞
static int capacity = INIT_QUEUE_SIZE;  // 원소 수

// push: queue의 후방에 원소 삽입
void push(element item){
    rear = (rear+1) % capacity;
    if(front == rear) queueFull(); // queueFull에서 크기 확장됨
    queue[rear] = item;
}

// pop: queue의 전방 원소를 삭제하고 반환 
element pop(){
    if(front == rear) queueEmpty();
    front = (front+1) % INIT_QUEUE_SIZE;
    return queue[front];
}

// queueFull: queue의 크기를 확장
void queueFull(){
    // newQueue에 기존 용량의 2배 크기의 메모리 할당 
    element *newQueue;
    MALLOC(newQueue, 2*capacity*sizeof(*queue));
    // queue의 데이터를 newQueue로 옮기는 과정
    int start = (front+1) % capacity;  // start: 시작 원소 위치
    // case 1. start = 0 -> front = capacity-1
    // case 2. start = 1 -> front = 0
    // c1, c2 모두 idx 조절할 필요 없이 쭉 복사 가능
    if(start<2)
        copy(queue+start, queue+start+capacity-1, newQueue);
    // case 3.
    else{
        copy(queue+start, queue+capacity, newQueue);  // start 지점부터 마지막 인덱스까지 복사
        copy(queue, queue+rear+1, newQueue+capacity-start); // 0부터 start 직전 지점까지 복사
    }
    // 본래 queue를 newQueue로 설정
    front = 2*capacity-1;  // 마지막 인덱스에 위치
    rear = capacity-2;  // [0]부터 삽입되었으므로 -2
    capacity *= 2;
    free(queue);
    queue = newQueue;
}

void queueEmpty(){
    printf("Queue is empty, cannot pop element\n");
    exit(-1);
}