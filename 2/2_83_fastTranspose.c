#include <stdio.h>
#define MAX_TERMS 101   // 최대 항의 갯수
#define MAX_COL 10      // 최대 열의 갯수

typedef struct{
    int col;    // 열
    int row;    // 행
    int value;  // 값
} term;
term a[MAX_TERMS];

void fastTranspose(term a[], term b[]){
    int i, j;
    int rowTerms[MAX_COL], startingPos[MAX_COL];
    int numCols = a[0].col, numRows = a[0].row, numTerms = a[0].value;
    b[0].row = numCols; b[0].col = numRows, b[0].value = numTerms;

    if(numTerms>0){
        // a 행렬의 열 개수만큼 0으로 초기화
        for(i=0; i<numCols; i++) rowTerms[i] = 0;

        // a 행렬의 열 인덱스를 기준으로, 해당 인덱스에 값이 존재하는 경우 1씩 증가
        for(i=0; i<numTerms; i++) rowTerms[a[i].col]++;

        // b 행렬에서 어떤 위치부터 값이 들어가야 할지 정하기
        startingPos[0] = 1;
        for(i=1; i<numCols; i++) startingPos[i] = startingPos[i-1] + rowTerms[i-1];

        // 정해진 위치에 a[1]부터 순서대로 전치하여 삽입
        for(i=1; i<=numTerms; i++){
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}