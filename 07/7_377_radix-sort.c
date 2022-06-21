#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 101
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

typedef struct element{
    int key;
} element;

int digit(element, int, int);
int radixSort(element [], int[], int, const int, int);

void main(void){
    int i, n;
    element list[MAX_SIZE];
    int link[MAX_SIZE];

    printf("Enter the size of the list in the range from 1~100: ");
    scanf("%d", &n);
    
    if(n<1 || n>MAX_SIZE) {
        printf("The input value is invalid.\n");
        exit(-1);
    }

    printf("Unsorted array: \n");
    for(i=1; i<=n; i++){
        list[i].key = rand()%1000;
        printf("%d ", list[i].key);
    }
    printf("\n");
    
    // link[0]을 radixSort의 리턴값으로 설정
    link[0] = radixSort(list, link, 3, 10, n);
    
    // link 체인을 활용하여 list의 idx 설정
    printf("Sorted array: \n");
    for(i=link[0]; i!=0; i=link[i]){
        printf("%d ", list[i].key);
    }
    printf("\n");
}

// digit: r진수의의 i번째 digit 반환
int digit(element item, int i, int r){
    int t, result = item.key;
    for(t=1; t<i; t++) result = result/r;
    if(result>r) result = result%r;
    return result;
}

// radixSort: LSD 기수 정렬
// list: 리스트, link: 체인, d: 자릿수, r: r진수, n: 항목의 개수
int radixSort(element list[], int link[], int d, const int r, int n){
    int *front = malloc(r*sizeof(int));
    int *rear = malloc(r*sizeof(int));
    int i, bin, current, first, last;
    // 시작 체인의 초기화
    first = 1; link[n] = 0;
    for(i=1; i<n; i++) link[i] = i+1;
    // 1의 자리부터 자릿수만큼 반복해서 정렬
    for(i=1; i<=d; i++){
        // bin을 비어있도록 초기화
        for(bin=0; bin<r; bin++) front[bin] = 0;
        // queue에 삽입 (4_169_linked-queue.c)
        printf("\nd:%d ", i);
        for(current=first; current; current=link[current]){
            bin = digit(list[current], i, r); printf("%3d ", bin);
            if(front[bin]==0) front[bin] = current;
            else link[rear[bin]] = current;
            rear[bin] = current;
        }
        // 첫번째 비어있지 않은 bin의 first, last 설정
        for(bin=0; !front[bin]; bin++);
        first = front[bin]; last = rear[bin];
        // 나머지 bin을 이용해서 queue 이어주기
        for(bin++; bin<r; bin++){
            if(front[bin]) {
                link[last]=front[bin];
                last=rear[bin];
            }
        }
        link[last] = 0;
        printf("\nsort: ");
        for(int t=first; t!=0; t=link[t]){
            printf("%d ", list[t].key);
        }
        printf("\n\n");
    }
    // 첫 번째 위치 return
    return first;
}