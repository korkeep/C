#include<stdio.h>

typedef struct element{
    int key;
} element;

// tableSort: 테이블 정렬 (list[t[1]]-list[t[n]])
void tableSort(element list[], int n, int t[]){
    int i, current, next;
    element temp;
    for(i=1; i<n; i++){
        // 비당연사이클의 경우 진입
        if(t[i]!=i){
            temp = list[i]; current = i;
            do{
                next = t[current];  // next를 다음 위치로 설정
                list[current] = list[next]; // list[next] 삽입
                t[current] = current;  // t[cur] 값을 정리
                current = next; // 다음 값 설정
            } while(t[current]!=i);
            // 마지막 값 설정
            list[current] = temp;
            t[current]= current;
        }
    }
}