#include<stdio.h>
#define MAX_SIZE 10

typedef struct element *tablePointer;
typedef struct element{
    int key;
} element;
tablePointer ht[MAX_SIZE];

// search: 선형 조사법
element *serach(int k, int b){
    int homeBucket, currentBucket;
    homeBucket = h(k);
    for(currentBucket=homeBucket; ht[currentBucket] && ht[currentBucket]->key != k; ){
        currentBucket = (currentBucket+1) % b;
        // Case 3. 시작위치 ht[h(k)]로 돌아온 경우, 테이블은 만원이고 k는 테이블에 없음
        if(currentBucket==homeBucket) return NULL;
    }
    // Case 1. 버킷 ht[h(k)+j]%b에 값이 k인 키 쌍이 있는 경우
    if(ht[currentBucket]->key == k) return ht[currentBucket];
    // Case 2. ht[h(k)+j]가 비어있는 경우, k는 테이블에 없음
    return NULL;
}

void main(){}