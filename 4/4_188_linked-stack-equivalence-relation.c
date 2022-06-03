#include<stdio.h>
#include<stdlib.h>
#define MALLOC(p,s) \
    if(!((p)=malloc(s))) { \
        printf("Insufficient memory\n"); \
        exit(-1); \
    }
#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1

typedef struct node *nodePointer;
struct node{
    int data;
    nodePointer link;
};

int main(){
    short int out[MAX_SIZE];
    nodePointer seq[MAX_SIZE];
    nodePointer x, y, top;
    int i, j, n;

    // Step 0: 초기화
    printf("Enter the size below %d: ", MAX_SIZE);
    scanf("%d", &n);  // cf. scanf 인자는 주소값, & 연산자 필요
    for(i=0; i<n; i++){
        out[i] = TRUE;
        seq[i] = NULL;
    }

    // Step 1: 동치 쌍들의 입력
    printf("Enter a pair of numbers (-1, -1 to quit): ");
    scanf("%d%d", &i, &j);  // cf. 배열의 경우 이름은 주소값이기 때문에 이름만 들어가도 됨
    while(i >= 0){
        MALLOC(x, sizeof(*x));
        x->data = j; x->link = seq[i]; seq[i] = x;
        MALLOC(x, sizeof(*x));
        x->data = i; x->link = seq[j]; seq[j] = x;
        scanf("%d%d", &i, &j);
    }

    // Step 2: 동치 부류들의 출력
    for(i=0; i<n; i++){
        // 아직 출력되지 않은 부류
        if(out[i]){
            // 부류를 출력된 것으로 설정
            printf("\nNew class: %5d", i);
            out[i] = FALSE;
            // 스택 초기화
            x = seq[i]; top = NULL;
            // 나머지 부류 찾기
            while(TRUE){
                // seq[x]에서 시작
                while(x){
                    j = x->data;
                    if(out[j]){
                        printf("%5d", j);
                        out[j] = FALSE; // 부류를 출력된 것으로 설정
                        
                        y = x->link;    // y를 x의 다음 항목으로 설정
                        x->link = top;  // y를 top으로 설정
                        top = x;        // top을 x로 설정 (다음 항목으로 이동 단계를 위함)
                        x = y;          // y가 새로운 x가 됨
                    }
                    else
                        x = x->link;    // x가 이미 출력된 경우 항목 이동
                }
                // 항목이 더 없을 시 break
                if(!top) break;
                // 다음 항목으로 이동
                x = seq[top->data];
                top = top->link; 
            }
        }
    }

    return 0;
}