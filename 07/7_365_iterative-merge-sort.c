#include<stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX_SIZE 101
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

void merge(int[], int[], int, int, int);
void mergePass(int[], int[], int, int);
void mergeSort(int[], int);

void main(void){
    int i, n;
    int list[MAX_SIZE];
    
    printf("Enter the size of the list in the range from 1~100: ");
    scanf("%d", &n);
    
    if(n<1 || n>MAX_SIZE) {
        printf("The input value is invalid.\n");
        exit(-1);
    }

    printf("Unsorted array: \n");
    for(i=0; i<n; i++){
        list[i] = rand()%100;
        printf("%d ", list[i]);
    }
    printf("\n");
    
    mergeSort(list, n);
    
    printf("Sorted array: \n");
    for(i=0; i<n; i++){
        printf("%d ", list[i]);
    }
    printf("\n");
}

// merge: 정렬된 두 리스트의 합병
// initList[i:m] + initList[m+1:n] -> mergedList[i:n]
void merge(int initList[], int mergedList[], int i, int m, int n){
    int j, k, t;
    j = m+1; k = i;
    // i->m or j->n에 도달할 때까지 합병
    while(i<=m && j<=n){
        if(initList[i] <= initList[j]) mergedList[k++] = initList[i++];
        else mergedList[k++] = initList[j++];
    }
    // i를 끝까지 진행하지 못한 경우
    if(i>m)
        for(t=j; t<=n; t++) mergedList[k++] = initList[t];
    // j를 끝까지 진행하지 못한 경우
    else
        for(t=i; t<=m; t++) mergedList[k++] = initList[t];
}

// mergePass: 합병 패스
void mergePass(int initList[], int mergedList[], int n, int s){
    int i, j;
    // initList[i:i+s-1] + initList[i+s, i+2*s-1]
    for(i=0; i<=n-2*s+1; i+=2*s)
        merge(initList, mergedList, i, i+s-1, i+2*s-1);
    // 마지막 합병 원소들에 대한 merge
    if(i+s-1<n)
        merge(initList, mergedList, i, i+s-1, n);
    // 남은 합병 원소가 s보다 작은 경우
    // 이미 정렬되어 있으므로 그대로 붙여줌
    else
        for(j=i; j<=n; j++) mergedList[j] = initList[j];
}

// mergeSort: 반복적 합병 정렬
void mergeSort(int list[], int n){
    int segsize=1;
    int extra[MAX_SIZE];

    while(segsize<n){
        // 원래 List를 임시 List에 merge, segsize 2배
        mergePass(list, extra, n, segsize);
        segsize *= 2;
        // 임시 List를 원래 List에 merge, segsize 2배
        mergePass(extra, list, n, segsize);
        segsize *= 2;
    }
}