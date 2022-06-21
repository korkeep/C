#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct element{
    int key;
} element;

typedef struct treeNode *treePointer;
typedef struct treeNode{
    treePointer leftChild;
    treePointer rightChild;
    element data;
    short int bf;
} treeNode;

// leftRotation: LL / LR 변환
void leftRotation(treePointer *parent, int *unbalanced){
    treePointer grandChild, child;
    child = (*parent)->leftChild;
    // LL Rotation: p.526 메모 참고
    if(child->bf == 1){
        (*parent)->leftChild = child->rightChild;
        child->rightChild = *parent;
        (*parent)->bf = 0;
        (*parent) = child;      // child가 parent가 되었음
    }
    // LR Roataion: p.526 메모 참고
    else{
        grandChild = child->rightChild;
        child->rightChild = grandChild->leftChild;
        grandChild->leftChild = child;
        (*parent)->leftChild = grandChild->rightChild;
        grandChild->rightChild = *parent;
        switch(grandChild->bf){
            case 1: (*parent)->bf = -1; child->bf = 0; break;
            case 0: (*parent)->bf = 0; child->bf = 0; break;
            case -1: (*parent)->bf = 0; child->bf = 1;
        }
        *parent = grandChild;   // gc가 parent가 되었음
    }
    // 새로운 parent의 bf 초기화, balance 상태 업데이트
    (*parent)->bf = 0;
    *unbalanced = FALSE;
}

// rightRotation: RR / RL 변환
void rightRotation(treePointer *parent, int *unbalanced){
    treePointer grandChild, child;
    child = (*parent)->rightChild;
    // RR Rotation: p.526 메모 참고
    if(child->bf == -1){
        (*parent)->rightChild = child->leftChild;
        child->leftChild = *parent;
        (*parent)->bf = 0;
        (*parent) = child;      // child가 parent가 되었음
    }
    // RL Roataion: p.526 메모 참고
    else{
        grandChild = child->leftChild;
        child->leftChild = grandChild->rightChild;
        grandChild->rightChild = child;
        (*parent)->rightChild = grandChild->leftChild;
        grandChild->leftChild = *parent;
        switch(grandChild->bf){
            case -1: (*parent)->bf = 1; child->bf = 0; break;
            case 0: (*parent)->bf = 0; child->bf = 0; break;
            case 1: (*parent)->bf = 0; child->bf = -1;
        }
        *parent = grandChild;   // gc가 parent가 되었음
    }
    // 새로운 parent의 bf 초기화, balance 상태 업데이트
    (*parent)->bf = 0;
    *unbalanced = FALSE;
}

// avlInsert: AVL 트리에서의 삽입
void avlInsert(treePointer *parent, element x, int *unbalanced){
    // 첫 원소의 경우 삽입
    if(!*parent){
        *unbalanced = TRUE;
        *parent = malloc(sizeof(treeNode));
        (*parent)->leftChild = (*parent)->rightChild = NULL;
        (*parent)->bf = 0;
        (*parent)->data = x;
    }
    // 왼쪽 원소로 들어가는 경우
    else if(x.key < (*parent)->data.key){
        avlInsert(&(*parent)->leftChild, x, unbalanced);
        if(*unbalanced){
            // p.525 메모 참고
            switch((*parent)->bf){
                case -1: (*parent)->bf = 0; *unbalanced = FALSE; break;
                case 0: (*parent)->bf = 1; break;
                case 1: leftRotation(parent, unbalanced);
            }
        }
    }
    // 오른쪽 원소로 들어가는 경우
    else if(x.key > (*parent)->data.key){
        avlInsert(&(*parent)->rightChild, x, unbalanced);
        if(*unbalanced){
            // p.525 메모 참고
            switch((*parent)->bf){
                case 1: (*parent)->bf = 0; *unbalanced = FALSE; break;
                case 0: (*parent)->bf = -1; break;
                case -1: rightRotation(parent, unbalanced);
            }
        }
    }
    // 이미 존재하는 키인 경우
    else{
        *unbalanced = FALSE;
        printf("The key is already in the tree\n");
    }
}

// inorder: 중위 순회
void inorder(treePointer ptr){
    if(ptr){
        inorder(ptr->leftChild);
        printf("%d ", ptr->data);
        inorder(ptr->rightChild);
    }
}

// preorder: 전위 순회
void preorder(treePointer ptr){
    if(ptr){
        printf("%d ", ptr->data);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

// postorder: 후위 순회
void postorder(treePointer ptr){
    if(ptr){
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%d ", ptr->data);
    }
}

void main(){
    int unbalanced;
    element temp;
    treePointer avl = NULL;

    for(int i=1; i<=7; i++){
        temp.key = i;
        avlInsert(&avl, temp, &unbalanced);
    }

    printf("Inorder: "); inorder(avl); printf("\n");
    printf("Preorder: "); preorder(avl); printf("\n");
    printf("Postorder: "); postorder(avl); printf("\n");

}