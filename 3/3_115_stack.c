#include <stdio.h>
#define MAX_STACK_SIZE 100

typedef struct{
    int key;
} element;
element stack[MAX_STACK_SIZE];
static int top = -1;

// push: stack에 원소 삽입
void push(element item){
    if(top>=MAX_STACK_SIZE-1) return stackFull();
    stack[++top] = item;
}

// pop: stack의 최상위 원소를 삭제하고 반환
element pop(){
    if(top==-1) return stackEmpty();
    return stack[top--];
}

void stackFull(){
    printf("Stack is full, cannot add element\n");
}

element stackEmpty(){
    element err; err.key = -1;
    printf("Stack is empty, cannot pop element\n");
    return err;
}