#include <stdio.h>
#include <string.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

void perm(char *list, int i, int n){
    int j, temp;

    if(i==n){
        for(j=0; j<=n; j++) printf("%c", list[j]);
        printf("  ");
    }
    
    else{
        for(j=i; j<=n; j++){
            SWAP(list[i], list[j], temp);
            perm(list, i+1, n);
            SWAP(list[i], list[j], temp);
        }
    }
}

int main(){
    // char 포인터의 경우 .bss에 선언되어 Stack에 할당됨, Read만 가능
    // char 배열의 경우 첫 번째 문자부터 순서대로 Stack에 할당됨, Read/Write 가능
    char yuna[] = "yuna";
    perm(yuna, 0, 3);
    return 0;
}