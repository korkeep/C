#include <stdio.h>
#include <math.h>
#define MAX_SIZE 101

void sort(int[], int);

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
    
    sort(list, n);
    
    printf("Sorted array: \n");
    for(i=0; i<n; i++){
        printf("%d ", list[i]);
    }
    printf("\n");
}

void sort(int list[], int n){
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