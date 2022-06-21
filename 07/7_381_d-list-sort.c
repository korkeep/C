#include<stdio.h>
#include<stdlib.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

typedef struct element{
    int key;
} element;

// d_listSort: 이중 연결 리스트를 이용한 레코드 재배치
void d_listSort(element list[], int linka[], int linkb[], int n, int first){
    int i, current, prev = 0;
    element tempe; int tempi;
    // linka의 chain을 doubly linked list로 변경
    for(current=first; current; current=linka[current]){
        linkb[current] = prev;
        prev = current;
    }
    for(i=1; i<n; i++){
        if(first != i){
            // i를 가리키는 앞-뒤 포인터를 first의 자리로 옮김
            if(linka[i]) linkb[linka[i]] = first;
            linka[linkb[i]] = first;
            // i와 first의 값, 앞-뒤 포인터 SWAP
            SWAP(list[first], list[i], tempe);
            SWAP(linka[first], linka[i], tempi);
            SWAP(linkb[first], linkb[i], tempi);
        }
        // 다음 first 값 설정
        first = linka[i];
    }
}