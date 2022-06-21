#include<stdio.h>
#define SIZE 15
#define MALLOC(p,s) \
    if(!((p)=malloc(s))) { \
        printf("Insufficient memory"); \
        exit(-1); \
    }

typedef struct node *treePointer;
struct node{
    int data;
    treePointer leftChild, rightChild;
};

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

int main(){
    treePointer temp;
    treePointer tree[SIZE+1];

    for(int i=1; i<=SIZE; i++){
        MALLOC(temp, sizeof(*temp));
        temp->leftChild = NULL;
        temp->rightChild = NULL;
        tree[i] = temp;
    }

    for(int i=1; i<=SIZE; i++){
        tree[i]->data = i;        
        if(i<=SIZE/2){
            tree[i]->leftChild = tree[i*2];
            tree[i]->rightChild = tree[i*2+1];
        }
    }

    inorder(tree[1]); printf("\n");
    preorder(tree[1]); printf("\n");
    postorder(tree[1]); printf("\n");
    
    return 0;
}