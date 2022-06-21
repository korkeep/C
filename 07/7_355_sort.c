#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX_SIZE 101

void selectionSort(int[], int);
void insertionSort(int[], int);
void bubbleSort(int[], int);

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
    
    bubbleSort(list, n);
    
    printf("Sorted array: \n");
    for(i=0; i<n; i++){
        printf("%d ", list[i]);
    }
    printf("\n");
}

// selectionSort: 선택 정렬 (전체 탐색 후 i에 들어가야 할 항목 선택)
void selectionSort(int list[], int n){
    int i, j, idx, temp;
    for(i=0; i<n-1; i++){
        idx = i;
        for(j=i+1; j<n; j++){
            if(list[j]<list[idx]) idx = j;
        }
        if(i != idx){
            temp = list[i];
            list[i] = list[idx];
            list[idx] = temp;
        }
    }
}

// insertionSort: 삽입 정렬 (왼쪽부터 i에 위치되어야 할 항목 삽입)
void insertionSort(int list[], int n){
    int i, j, key;
    for(i=1; i<n; i++){
        key = list[i];
        for(j=i-1; j>=0; j--){
            if(list[j]>key) list[j+1] = list[j];
            else break;
        }
        list[j+1] = key;
    }
}

// bubbleSort: 버블 정렬 (왼쪽부터 인접한 두 항목간 비교)
void bubbleSort(int list[], int n){
    int i, j, temp;
    for(i=0; i<n-1; i++){
        for(j=0; j<n-i-1; j++){
            if(list[j]>list[j+1]){
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
}