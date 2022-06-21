#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) \
    if(!((p)=malloc(s))) { \
        printf("Insufficient memory\n"); \
        exit(-1); \
    }
#define COMPARE(x,y) ((x)<(y) ? -1 : ((x)==(y)) ? 0 : 1)

typedef struct polyNode *polyPointer;
struct polyNode{
    float coef; // 계수
    int expon;  // 지수
    polyPointer link;
};
polyPointer a, b;

// attatch: 리스트의 끝에 노드를 첨가
// cf. *rear = 2중 포인터
void attatch(float coef, int expon, polyPointer *rear){
    polyPointer temp;
    MALLOC(temp, sizeof(*temp));
    temp->coef = coef;
    temp->expon = expon;
    (*rear)->link = temp;
    *rear = temp;
}

// erase: 전체 노드의 제거
// cf. *ptr = 2중 포인터
void erase(polyPointer *ptr){
    polyPointer temp;
    while(*ptr){
        temp = *ptr;
        *ptr = (*ptr)->link;
        free(temp);
    }
}

// padd: 두 다항식을 더하는 함수
polyPointer padd(polyPointer a, polyPointer b){
    polyPointer c, rear, temp;
    int sum;
    MALLOC(rear, sizeof(*rear));
    c = rear;

    while(a && b){
        switch(COMPARE(a->expon, b->expon)){
            case -1:    // b가 큰 경우
                attatch(b->coef, b->expon, &rear);
                b = b->link;
                break;
            case 0:     // a, b가 같은 경우
                sum = a->coef + b->coef;
                if(sum) attatch(sum, a->expon, &rear);
                a = a->link; b = b->link; break;
            case 1:     // a가 큰 경우
                attatch(a->coef, a->expon, &rear);
                a = a->link;
        }
    }

    // a, b 리스트의 나머지를 복사
    for(; a; a = a->link) attatch(a->coef, a->expon, &rear);
    for(; b; b = b->link) attatch(b->coef, b->expon, &rear);
    rear->link = NULL;

    // 초기 노드 삭제
    temp = c; c = c->link; free(temp);
    
    // 첫 연결 노드 반환
    return c;
}