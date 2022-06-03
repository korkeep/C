#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100
#define COMPARE(x,y) ((x)<(y) ? -1 : ((x)==(y)) ? 0 : 1)

typedef struct {
    float coef; // 계수
    int expon;  // 지수
} polynomial;

polynomial terms[MAX_TERMS];
int avail = 0;

// 새로운 항을 첨가하는 함수
void attatch(float coef, int expon){
    if(avail >= MAX_TERMS){
        printf("Polynomial has too many terms.\n");
        exit(-1);
    }

    terms[avail].coef = coef;
    terms[avail].expon = expon;
    avail++;
}

// 두 다항식을 더하는 함수
void padd(int startA, int finishA, int startB, int finishB, int *startR, int *finishR){
    *startR = avail;
    
    // A(x)와 B(x)를 더하여 R(x)를 생성
    while(startA<=finishA && startB<=finishB){
        switch(COMPARE(terms[startA].expon, terms[startB].expon)){
            case -1: 
                attatch(terms[startB].coef, terms[startB].expon);
                startB++;
                break;
            case 0:
                attatch(terms[startA].coef + terms[startB].coef, terms[startA].expon);
                startA++; startB++;
                break;
            case 1:
                attatch(terms[startA].coef, terms[startA].expon);
                startA++;
        }
    }

    // 비교문에서 계산되지 않은 나머지 항 추가
    for(; startA<=finishA; startA++) attatch(terms[startA].coef, terms[startA].expon);
    for(; startB<=finishB; startB++) attatch(terms[startB].coef, terms[startB].expon);

    *finishR = avail-1;
}

int main(){
    int startR, finishR;

    // A(x)
    attatch(2, 100);
    attatch(1, 0);
    
    // B(x)
    attatch(1, 4);
    attatch(10, 3);
    attatch(3, 2);
    attatch(1, 0);

    // R(x)
    padd(0, 1, 2, 5, &startR, &finishR);
    for(int i=startR; i<=finishR; i++){
        printf("%f, %d\n", terms[i].coef, terms[i].expon);
    }

    return 0;
}