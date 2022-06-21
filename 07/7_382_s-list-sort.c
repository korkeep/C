#include<stdio.h>
#include<stdlib.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

typedef struct element{
    int key;
} element;

// s_listSort: 하나의 링크 필드만 사용하는 레코드 재배치
void s_listSort(element list[], int link[], int n, int first){
    int i;
    element temp;
    for(i=1; i<n; i++){
        // p.384, first=4로 시작함
        while(first<i) first = link[first];
        // p.384, first=8로 설정됨
        int q = link[first];
        // i와 first의 값, 포인터 SWAP
        if(first!=i){
            SWAP(list[i], list[first], temp);
            link[first] = link[i];
            link[i] = first;
        }
        // 다음 first 값을 q로 지정
        first = q;
    }
}