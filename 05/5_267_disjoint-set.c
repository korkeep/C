#include<stdio.h>
#define MAX_SIZE 100

int parent[MAX_SIZE];
int count[MAX_SIZE];

// weightUnion: 가중 규칙을 사용하는 union 함수
// parent[i] = -count[i], parent[j] = -count[j]
void weightUnion(int i, int j){
    int temp = parent[i] + parent[j];
    // j의 노드 수가 많은 경우
    if(parent[i] > parent[j]){
        parent[i] = j;
        parent[j] = temp;
    }
    // i의 노드 수가 많은 경우
    else{
        parent[j] = i;
        parent[i] = temp;
    }
}

// collapsingFind: 붕괴 규칙을 이용하여 root로 가는 모든 노드를 붕괴
// cf. 붕괴규칙: j가 i에서 루트로 가는 경로에 있으며, parent[j]를 root[i]로 지정
int collapsingFind(int i){
    int root, trail, lead;
    // 가장 높은 위치의 root를 찾아옴
    for(root = i; parent[root] >= 0; root = parent[root]);
    // 붕괴 규칙을 적용하여 i로부터 root로 가는 모든 노드를 붕괴시킴
    for(trail = i; trail != root; trail = lead){
        lead = parent[trail];
        parent[trail] = root;
    }
    return root;
}
