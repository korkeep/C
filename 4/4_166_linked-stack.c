#include<stdio.h>
#include<stdlib.h>
#define MALLOC(p,s) \
    if(!((p)=malloc(s))) { \
        printf("Insufficient memory"); \
        exit(-1); \
    }
#define STACKS 10   // 스택 자료구조의 수

typedef struct{
    int key;
} element;

typedef struct stack *stackPointer;
struct stack{
    element data;
    stackPointer link;
};
stackPointer top[STACKS];

// push: i번째 연결 스택에서의 삽입
void push(int i, element item){
    stackPointer temp;
    MALLOC(temp, sizeof(*temp));

    temp->data = item;
    temp->link = top[i];
    top[i] = temp;
}

// pop: i번째 연결 스택에서의 삭제
element pop(int i){
    stackPointer temp = top[i];
    element item;
    
    if(!temp) stackEmpty();
    item = temp->data;
    top[i] = temp->link;
    
    free(temp);
    return item;
}

void stackEmpty(){
    printf("Stack is empty, cannot pop element\n");
    exit(-1);
}