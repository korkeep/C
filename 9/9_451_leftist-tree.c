#include <stdio.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

typedef struct{
    int key;
} element;

typedef struct leftist *leftistTree;
struct leftist{
    leftistTree leftChild;
    leftistTree rightChild;
    element data;
    int shortest;
};

// minMeld: 두 최소 좌향 트리의 합병
void minMeld(leftistTree *a, leftistTree *b){
    if(!*a) *a = *b;
    else if (*b) minUnion(a, b);
    *b = NULL;
}

// minUnion: 공백이 아닌 두 최소 좌향 트리의 합병
// cf. shortest(x) = 0 (외부 노드의 경우)
// cf. shortest(x) = 1+min(shortest(leftChild), shortest(rightChild))
// cf. leftistTree -> shortest(leftChild(x)) >= shortest(rightChild(x))
void minUnion(leftistTree *a, leftistTree *b){
    leftistTree temp;
    // a, b 중 최소값을 가진 트리를 a로 설정
    if((*a)->data.key > (*b)->data.key) SWAP(*a, *b, temp);
    // a의 rightChild가 없는 경우 rightChild에 b를 삽입
    if(!(*a)->rightChild) (*a)->rightChild = *b;
    else minUnion(&(*a)->rightChild, b);
    // a의 leftChild가 없는 경우 rightChild를 leftChild로 설정
    if(!(*a)->leftChild){
        (*a)->leftChild = (*a)->rightChild;
        (*a)->rightChild = NULL;
    }
    // shortest(l) < shortest(r)의 경우 SWAP
    else if((*a)->leftChild->shortest < (*a)->rightChild->shortest){
        SWAP((*a)->leftChild, (*a)->rightChild, temp);
    }
    // a의 shortest 재설정
    (*a)->shortest = (!(*a)->rightChild) ? 1 : (*a)->rightChild->shortest+1;
}