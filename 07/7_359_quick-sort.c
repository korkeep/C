#include<stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX_SIZE 101
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

void quickSort(int[], int, int);

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
    
    quickSort(list, 0, n-1);
    
    printf("Sorted array: \n");
    for(i=0; i<n; i++){
        printf("%d ", list[i]);
    }
    printf("\n");
}

// quickSort: 퀵 정렬, left-right 범위의 인덱스를 정렬함
void quickSort(int list[], int left, int right){
    int i, j, pivot, temp;
    if(left<right){
        i = left; j = right+1;
        pivot = list[left]; // 첫 번째 값을 pivot으로 선택
        do{
            do i++; while (list[i] < pivot); // 왼쪽->오른쪽 방향, pivot보다 작은 경우 진행
            do j--; while (list[j] > pivot); // 오른쪽->왼쪽 방향, pivot보다 큰 경우 진행
            if(i < j) SWAP(list[i], list[j], temp); // list[i] <-> list[j]
        } while(i < j);
        // list[left] <-> list[j]
        SWAP(list[left], list[j], temp);
        // 정해진 값 기준으로 재귀적으로 sort 진행
        quickSort(list, left, j-1);
        quickSort(list, j+1, right);
    }
}
