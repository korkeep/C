#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 101
#define HEAP_FULL(n) (n == MAX_SIZE-1)
#define HEAP_EMPTY(n) (!n)
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

typedef struct element{
    int key;
} element;

void adjust(element [], int, int);
void heapSort(element [], int);

void main(void){
    int i, n;
    element heap[MAX_SIZE];
    
    printf("Enter the size of the list in the range from 1~100: ");
    scanf("%d", &n);
    
    if(n<1 || n>MAX_SIZE) {
        printf("The input value is invalid.\n");
        exit(-1);
    }

    printf("Unsorted array: \n");
    for(i=1; i<=n; i++){
        heap[i].key = rand()%100;
        printf("%d ", heap[i].key);
    }
    printf("\n");
    
    heapSort(heap, n);
    
    printf("Sorted array: \n");
    for(i=1; i<=n; i++){
        printf("%d ", heap[i].key);
    }
    printf("\n");
}

// adjust: 최대 히프의 조정 (shift-down)
void adjust(element list[], int root, int n){
    int child, rootkey;
    element temp;
    temp = list[root];
    rootkey = list[root].key;
    child = 2*root;
    // 최대 히프로 맞춰주는 과정
    while(child<=n){
        // child 값 중 더 큰 값을 child로 설정
        if((child<n) && list[child].key<list[child+1].key) child++;
        // Case 1. root > child -> break
        if(rootkey > list[child].key) break;
        // Case 2. root <= child -> SWAP, child*2 이후 진행
        else {list[child/2] = list[child]; child *= 2;}
    }
    // 현재 root를 조정된 자리에 삽입
    list[child/2] = temp;
}

// heapSort: 히프 정렬
void heapSort(element list[], int n){
    int i, j;
    element temp;
    // 최대 히프 생성
    for(i=n/2; i>0; i--) adjust(list, i, n);
    // 첫 원소와 끝 원소를 교환
    // 최대 히프 생성의 반복을 통해 정렬
    for(i=n-1; i>0; i--){
        SWAP(list[1], list[i+1], temp);
        adjust(list, 1, i);
    }   
}