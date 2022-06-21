#include<stdio.h>
#include<stdlib.h>

#define FALSE 0
#define TRUE 1

// P1. 각 노드의 원소는 오른쪽 형제에 있는 원소보다 작거나 같다.
// P2. 조부모의 왼쪽 자식에 있는 원소는 N에 있는 원소보다 작거나 같다.
// P3. 조부모의 오른쪽 자식에 있는 원소는 N에 있는 원소보다 크거나 같다.

// insert: 대칭 최소-최대 히프에서의 삽입
void insert(int h[], int last, int x){
    int currentNode, done, gp, lcgp, rcgp;
    currentNode = last++;
    // P1. curNode가 홀수번째고 조건 2. x < 왼쪽자식
    // lc를 curNode로 이동, curNode 1 감소
    if(last%2 == 1 && x<h[last-1]){
        h[last] = h[last-1]; currentNode--;
    }
    done = FALSE;
    while(!done && currentNode >= 4){   // 4: 조부모가 존재할 최소 필요 노드의 수
        gp = currentNode / 4; // 조부모
        lcgp = 2 * gp;        // 조부모의 왼쪽 자식
        rcgp = lcgp + 1;      // 조부모의 오른쪽 자식
        // P2. x < lcgp
        // lcgp를 curNode로 이동, curNode의 idx를 lcgp로 설정
        if(x<h[lcgp]){
            h[currentNode] = h[lcgp];
            currentNode = lcgp;
        }
        // P3. x > rcgp
        // rcgp를 curNode로 이동, curNode의 idx를 rcgp로 설정
        else if(x>h[rcgp]){
            h[currentNode] = h[rcgp];
            currentNode = rcgp;
        }
        // P1, P2, P3 만족
        else done = TRUE;
    }
    // curNode에 x 삽입
    h[currentNode] = x; 
}