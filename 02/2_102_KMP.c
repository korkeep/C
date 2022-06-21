#include <stdio.h>
#include <string.h>
#define MAX_STRING_SIZE 100
#define MAX_PATTERN_SIZE 100
int pmatch();
void fail();
int failure[MAX_PATTERN_SIZE];
char string[MAX_STRING_SIZE];
char pat[MAX_PATTERN_SIZE];

// 실패함수: 패턴 매칭에 실패하기 직전, 접두-접미어가 일치한 최대 길이
void fail(char *pat){
    int i, j;
    int n = strlen(pat);
    
    failure[0] = -1;
    for(j=1; j<n; j++){
        // i = 접두-접미어가 일치한 최대 길이에서 접두어의 마지막 인덱스
        i = failure[j-1];
        
        // 인덱스 j를 포함했을 때 부분 매치가 발생하는지 검사
        // 부분 매치가 발생하지 않을 때마다 i = failure[i]로 설정
        while(pat[j]!=pat[i+1] && (i>=0))
            i = failure[i];
        
        // 접두-접미어의 부분 매치가 발생하는 경우 failure[j]=i+1으로 설정
        if(pat[j]==pat[i+1])
            failure[j] = i+1;
        
        // 접두-접미어가 완전히 일치하지 않는 경우 -1로 설정
        else
            failure[j] = -1;
    }
}

int KMP(char *string, char *pat){
    int i = 0, j = 0;
    int lenS = strlen(string);
    int lenP = strlen(pat);

    while(i<lenS && j<lenP){
        // 값이 일치하는 경우: 타겟, 패턴 1만큼 이동
        if(string[i]==pat[j]) {i++; j++;}

        // 패턴의 인덱스가 0이고, 값이 일치하지 않는 경우: 타겟 1만큼 이동
        else if(j==0) i++;
        
        // 값이 일치하지 않는 경우: 패턴을 건너뛸 수 있는 길이만큼 이동
        else j = failure[j-1]+1;
    }

    // i-lenP: 패턴이 발견된 경우 패턴의 시작 위치
    return ((j==lenP) ? (i-lenP) : -1);
}

int main(){
    char string[] = "ababdababc";
    char pattern[] = "ababc";
    
    fail(pattern);    
    printf("%d\n", KMP(string, pattern));
    
    return 0;
}