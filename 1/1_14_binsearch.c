#include <stdio.h>
#define COMPARE(x,y) ((x)>(y) ? -1 : ((x)==(y)) ? 0 : 1)

// 반복을 이용
int binsearch_1(int list[], int target, int left, int right){
    int mid;
    while(left <= right){
        mid = (left+right)/2;
        switch (COMPARE(list[mid], target)){
            case -1: left = mid+1; break;
            case 0: return mid;
            case 1: right = mid-1;
        }
    }
    return -1;
}

// 재귀를 이용
int binsearch_2(int list[], int target, int left, int right){
    int mid = (left+right)/2;
    if(left<=right){
        switch(COMPARE(list[mid], target)){
            case -1: binsearch_2(list, target, mid+1, right); break;
            case 0: return mid;
            case 1: binsearch_2(list, target, left, mid-1);
        }
    }
    return -1;
}