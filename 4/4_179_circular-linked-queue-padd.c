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
polyPointer avail;

// getNode: 가용 리스트에서 노드 제공
polyPointer getNode(){
    polyPointer node;
    if(avail){
        node = avail;
        avail = avail->link;
    }
    else MALLOC(node, sizeof(*node));
    return node;
}

// retNode: 가용 리스트에 노드를 반환
void retNode(polyPointer node){
    node->link = avail;
    avail = node;
}

// cerase: ptr이 가리키는 원형 리스트 전체 제거
// cf. *ptr = 2중 포인터
void cerase(polyPointer *ptr){
    polyPointer temp;
    if(*ptr){
        temp = (*ptr)->link;
        (*ptr)->link = avail;
        avail = temp;
        *ptr = NULL;
    }
}

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

// cpadd: 헤더 노드를 가진 원형 리스트로 표현된 두 다항식의 덧셈
polyPointer cpadd(polyPointer a, polyPointer b){
    // Result의 헤더노드 설정
    polyPointer r, rearR;
    r = getNode();
    r->expon = -1; rearR = r;

    polyPointer startA = a;   // startA: a의 헤더노드
    a = a->link; b = b->link; // a, b의 헤더노드 건너뛰기
    int sum, done=0;

    do{
        switch(COMPARE(a->expon, b->expon)){
            case -1:    // case 1. b가 큰 경우
                attatch(b->coef, b->expon, &rearR);
                b = b->link;
                break;
            case 0:     // case 2. a, b가 같은 경우
                if(startA == a) done = 1; // 둘 다 헤더노드인 경우 종료
                sum = a->coef + b->coef;
                if(sum) attatch(sum, a->expon, &rearR);
                a = a->link; b = b->link; break;
            case 1:     // case 3. a가 큰 경우
                attatch(a->coef, a->expon, &rearR);
                a = a->link;
        }
    } while(!done);     // cf. circular 형식은 헤더노드 expon = -1이 존재하므로, c1, c3에서 나머지 돌아갈 수 있음

    // circular queue 특성
    rearR->link = r;
    return r;
}