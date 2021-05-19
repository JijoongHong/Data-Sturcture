#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10

typedef struct TreeNode{
    int data;
    struct TreeNode *left, *right;
}TreeNode;

TreeNode* new_node(int y){
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->data = y;
    temp->left = temp->right = NULL;
    return temp;
}

int search(TreeNode *node, int target){ // 중복 탐지 함수
    
    if (node == NULL) return -1; // 재귀 탈출
    if (target == node->data) return 0; // 동일 데이터가 있으면 0 리턴
    else{                               // 없으면 좌측과 우측 탐색
        search(node->left, target);
        search(node->right, target);
    }
    return -1;
}

void add_node(TreeNode* root){
    int x, y;
    x = rand()%2 + 1;
    
    while (1){ // 중복값 확인
        y = rand()%2 + 11;
        if (search(root, y) == -1)
            break;
    }
    
    if (x == 1){ // 좌측 노드 삽입
        if (root->left == NULL)
            root->left = new_node(y); // 좌측 노드 없으면 삽입
        else
            add_node(root->left); // 존재하면 재귀 호출
        
    }else{
        if (root->right == NULL)
            root->right = new_node(y); // 우측 노드 없으면 삽입
        else
            add_node(root->right); // 존재하면 재귀 호출
    }
}


int main(){
    srand((int)time(NULL));

    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = rand()%100 + 1;
    root->left = root->right = NULL;

    for(int i = 0; i < SIZE - 1 ; i++){
        add_node(root);
    }
}
