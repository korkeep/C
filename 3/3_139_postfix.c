#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100

char *expr;
char stack[MAX_STACK_SIZE];
static int top = -1;

// push: stack에 원소 삽입
void push(char item){
    if(top>=MAX_STACK_SIZE-1) return stackFull();
    stack[++top] = item;
}

// pop: stack의 최상위 원소를 삭제하고 반환
char pop(){
    if(top==-1) stackEmpty();
    return stack[top--];
}

void stackFull(){
    printf("Stack is full, cannot add element\n");
    exit(-1);
}

void stackEmpty(){
    printf("Stack is empty, cannot pop element\n");
    // exit(-1);
}

// precedence: 우선순위 열거 타입
typedef enum {
    lparen, rparen, plus, minus, multiply, divide, mod, eos, operand
} precedence;

// isp: in-stack precedence, icp: incoming precedence
// isp, icp로 구분한 이유는 왼쪽 괄호 '(', 오른쪽 괄호')' 처리를 위함
int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

// getToken: 스트링으로부터 토큰을 가져오는 함수
precedence getToken(char *symbol, int *n){
    *symbol = expr[(*n)++];
    switch(*symbol){
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '/': return divide;
        case '*': return multiply;
        case '%': return mod;
        case ' ': return eos;
        default: return operand;
    }
}

// printToken: 토큰으로부터 스트링을 리턴하는 함수
void printToken(precedence token){
    switch(token){
        case lparen: printf("("); return;
        case rparen: printf(")"); return;
        case plus: printf("+"); return;
        case minus: printf("-"); return;
        case divide: printf("/"); return;
        case multiply: printf("*"); return;
        case mod: printf("%"); return;
        default: return;
    }
}

// eval: 후위 표기식을 계산하는 함수
int eval(){
    precedence token;
    char symbol;
    int cnt = 0;
    int op1, op2;
    top = -1;

    // 스트링을 읽으며 후위 표기식을 계산하는 과정
    token = getToken(&symbol, &cnt);
    while(token != eos){
        // break 조건
        if(strlen(expr) < cnt) break;
        // case 1. 피연산자의 경우 스택에 삽입
        if(token == operand) push(symbol-'0');
        // case 2. 연산자의 경우 연산 결과를 스택에 삽입
        else{
            op2 = pop();
            op1 = pop();
            switch(token){
                case plus: push(op1+op2); break;
                case minus: push(op1-op2); break;
                case multiply: push(op1*op2); break;
                case divide: push(op1/op2); break;
                case mod: push(op1%op2);
            }
        }
        token = getToken(&symbol, &cnt);        
    }

    // 최종 연산 결과를 반환
    return pop();
}

// postfix: 중위 표기를 후위 표기로 변환하는 함수
void postfix(){
    char symbol;
    precedence token;
    int cnt = 0;
    top = 0; stack[0] = eos; // eos를 스택에 삽입

    // 스트링을 읽으며 중위 표기식을 후위 표기식으로 변환
    token = getToken(&symbol, &cnt);
    while(token != eos){        
        // break 조건
        if(strlen(expr) < cnt) break;
        // case 1. 피연산자의 경우 그대로 출력
        if(token == operand) printf("%c", symbol);
        // case 2. 오른쪽 괄호인 경우 (괄호 끝나는 부분)
        else if(token == rparen){
            // 스택의 토큰을 제거하며 출력
            while(stack[top] != lparen) printToken(pop());
            // 왼쪽 괄호 제거
            pop();
        }
        // case 3. 오른쪽 괄호가 아닌 연산자인 경우
        // cf. 스택 속 연산자의 왼쪽 괄호 우선순위: 0 (의미 없음)
        // cf. 스택에 들어오는 연산자의 왼쪽 괄호 우선순위: 20 (최고 우선순위)
        else{
            // 스택 속 연산자가 들어오는 연산자보다 우선순위가 높은 경우 pop
            while(isp[stack[top]] >= icp[token]) printToken(pop());
            // 들어오는 연산자 스택에 push
            push(token);
        }
        token = getToken(&symbol, &cnt);
    }

    // 스택에 남은 연산자
    while((token=pop()) != eos) printToken(token);
    printf("\n");
}

int main(){
    expr = "6/2-(3+4)*2+17";
    postfix();

    expr = "62/34+2*-17+";
    printf("%d", eval());

    return 0;
}