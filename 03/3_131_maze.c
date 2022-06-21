#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define COL 6
#define ROW 8

typedef struct{
    short int row; // 행
    short int col; // 열
    short int dir; // 방향: 북-동-남-서
} element;

element stack[MAX_STACK_SIZE];
static int top = -1;

typedef struct{
    short int vert;
    short int horiz;
} offsets;

// 방향: 북(0)-동(1)-남(2)-서(3)
const offsets move[4] = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}
};

// 미로: 0은 움직일 수 있는 경로
static int maze[ROW+1][COL+1] = {
    {-1, -1, -1, -1, -1, -1, -1},
    {-1, 0, 0, 0, 0, 0, 1},
    {-1, 1, 1, 1, 1, 0, 0},
    {-1, 0, 1, 1, 0, 1, 0},
    {-1, 0, 1, 0, 0, 0, 0},
    {-1, 1, 1, 1, 0, 1, 1},
    {-1, 1, 0, 0, 0, 1, 0},
    {-1, 1, 1, 0, 1, 1, 0},
    {-1, 1, 0, 0, 0, 0, 0}
};

// 방문 체크: 방문한 곳을 1로 표기
static int mark[ROW+1][COL+1];

// push: stack에 원소 삽입
void push(element item){
    if(top>=MAX_STACK_SIZE-1) return stackFull();
    stack[++top] = item;
}

// pop: stack의 최상위 원소를 삭제하고 반환
element pop(){
    if(top==-1) stackEmpty();
    return stack[top--];
}

void stackFull(){
    printf("Stack is full, cannot add element\n");
}

void stackEmpty(){
    printf("Stack is empty, cannot pop element\n");
    exit(-1);
}

void path(){
    int i, found = 0;
    int row, col, nextRow, nextCol, dir;
    element pos;

    // 입구 세팅
    mark[1][1]=1; top=0;
    stack[0].row=1; stack[0].col=1; stack[0].dir=1;

    // 미로 찾기
    while(top>-1 && !found){
        pos = pop(&top); // 움직일 수 있는 방향이 존재하지 않는다면 pop
        row = pos.row; col = pos.col; dir = pos.dir;
        // dir 방향으로 이동
        while(dir<4 && !found){
            // 다음 움직일 방향 설정
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz; 
            // 출구 발견
            if(nextRow == ROW && nextCol == COL) found=1;
            // 경로이면서 방문하지 않은 지점
            else if(!maze[nextRow][nextCol] && !mark[nextRow][nextCol]){
                mark[nextRow][nextCol] = 1;
                pos.row = row; pos.col = col, pos.dir = ++dir;
                push(pos); // 다른 방향으로 움직일 수 있으므로 이전 위치 push
                row = nextRow; col = nextCol; dir = 0;
            }
            // 이전에 방문했기 때문에 방향만 전환
            else ++dir;
        }
    }

    // 경로 출력
    if(found){
        printf("The path is: \n");
        printf("(row col) \n");
        for(i=0; i<=top; i++){
            printf("(%d%4d) ", stack[i].row, stack[i].col);
            if((i+1)%5==0) printf("\n");
        }
        printf("(%d%4d) ", row, col);
        if((++i)%5==0) printf("\n");
        printf("(%d%4d) ", ROW, COL);
        if((++i)%5==0) printf("\n");
    }

    else
        printf("The maze does not have a path\n");
}

int main(){
    path();
    return 0;
}