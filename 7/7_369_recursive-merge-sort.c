#include<stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX_SIZE 101
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

int merge(int[], int[], int, int);
int rmergeSort(int[], int[], int, int);

void main(void){
    int i, n;
    int list[MAX_SIZE];
    int link[MAX_SIZE];

    printf("Enter the size of the list in the range from 1~100: ");
    scanf("%d", &n);
    
    if(n<1 || n>MAX_SIZE) {
        printf("The input value is invalid.\n");
        exit(-1);
    }

    printf("Unsorted array: \n");
    for(i=1; i<=n; i++){
        list[i] = rand()%100;
        link[i] = 0;
        printf("%d ", list[i]);
    }
    printf("\n");
    
    // link[0]을 rmergeSort의 리턴값으로 설정
    link[0] = rmergeSort(list, link, 1, n);
    
    // link 체인을 활용하여 list의 idx 설정
    printf("Sorted array: \n");
    for(i=link[0]; i!=0; i=link[i]){
        printf("%d ", list[i]);
    }
    printf("\n");
}

// merge: 정렬된 체인의 합병
int merge(int list[], int link[], int start1, int start2){
    int last1, last2, lastResult = 0;
    for(last1 = start1, last2 = start2; last1 && last2; ){
        if(list[last1] <= list[last2]){
            link[lastResult] = last1; // link[lastResult]의 위치를 last1의 크기로 set
            lastResult = last1;       // lastResult의 값을 last1으로 set
            last1 = link[last1];      // last1의 값을 link[last1]으로 set (이어주는 과정을 위함)
        }
        else{
            link[lastResult] = last2; // link[lastResult]의 위치를 last1의 크기로 set
            lastResult = last2;       // lastResult의 값을 last2로 set
            last2 = link[last2];      // last2의 값을 link[last2]로 set (이어주는 과정을 위함)
        }
    }
    // 이어주는 과정
    if(last1==0) link[lastResult] = last2;
    else link[lastResult] = last1;
    // link의 첫 원소 return
    return link[0];
}

// rmergeSort: 재귀적 합병 정렬
int rmergeSort(int list[], int link[], int left, int right){
    // 재귀의 종료 조건
    if(left>=right) return left;
    // mid를 기준으로 왼쪽, 오른쪽 인덱스 재귀 분할
    int mid = (left+right)/2;
    return merge(list, link,
                    rmergeSort(list, link, left, mid),
                    rmergeSort(list, link, mid+1, right));
}