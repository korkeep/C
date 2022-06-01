#include <stdio.h>
#include <string.h>

// 패턴의 마지막 문자부터 검사하는 패턴 매칭
int nfind(char *string, char *pat){
    int i, j, start = 0;
    int lastS = strlen(string)-1;
    int lastP = strlen(pat)-1;
    int endmatch = lastP;

    for(i=0; endmatch<=lastS; endmatch++, start++){
        if(string[endmatch]==pat[lastP])
            for(j=0, i=start; j<lastP && string[i]==pat[j]; i++, j++);
        if(j==lastP) return start;
    }

    return -1;
}

int main(){
    char string[] = "ababbaabaa";
    char pattern[] = "aab";
    
    printf("%d", nfind(string, pattern));
    
    return 0;
}