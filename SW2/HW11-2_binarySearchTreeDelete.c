#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#define SIZE 20

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

void inorder(TreeNode *root){ // LVR
    if (root != NULL){
        inorder(root->left); // 좌측 노드 출력
        printf("[%d]", root->data); // 가운데 노드 출력
        inorder(root->right); // 우측 노드 출력
    }
}

TreeNode* search(TreeNode *node, int key){
    
    if (node == NULL) return NULL;
    if (key == node->data) return node;
    else if(key<node->data)
        return search(node->left, key);
    else
        return search(node->right, key);
}


TreeNode* search_iter(TreeNode *node, int key){
    
    while(node != NULL){
        if (key == node->data) return node;
        else if (key < node->data)
            node = node->left;
        else
            node = node->right;
    }
    
    return NULL;
}

void add_node(TreeNode* root, int y){
    
    while (1){ // 중복 없는 y값 생성
        if (search(root, y) == NULL)
            break;
        else
            y = rand()%30 + 1;
    }
    
    if (y < root->data){ // 좌측 노드 삽입
        if (root->left == NULL)
            root->left = new_node(y); // 좌측 노드 없으면 삽입
        else
            add_node(root->left, y); // 존재하면 재귀 호출
        
    }else{
        if (root->right == NULL)
            root->right = new_node(y); // 우측 노드 없으면 삽입
        else
            add_node(root->right, y); // 존재하면 재귀 호출
    }
}

void add_node_iter(TreeNode* root){

    int y;
    TreeNode* temp_root = root;
    
    while (1){ // 중복 없는 y값 생성
        y = rand()%30 + 1;
        
        if (search_iter(root, y) == NULL)
            break;
    }
    
    while (temp_root){

        if (y < temp_root->data){
            if (temp_root->left == NULL){ // 왼쪽 노드가 없으면 삽입
                temp_root->left = new_node(y);
                break;
            }
            else{
                temp_root = temp_root->left;// 좌측 노드를 루트 노드로 설정
            }
            
        }else{
            if (temp_root->right == NULL){ // 오른쪽 노드가 없으면 삽입
                temp_root->right = new_node(y);
                break;
            }
            else{
                temp_root = temp_root->right;// 우측 노드를 루트 노드로 설정
            }
        }
    }
}


void delete_node(TreeNode **root, int key){
    
    TreeNode *p, *child, *succ, *succ_p, *t;
    // key를 갖는 노드 t탐색, p는 t의 부모노드
    p = NULL;
    t = *root;
    // key를 갖는 노드 t탐색
    printf("\n삭제할 데이터 : %d\n", key);
    
    while(t!=NULL && t->data != key){
        p = t;
        t = (key < t->data) ? t->left : t->right;
    }
    // 탐색이 종료된 시점에 t가 NULL이면 탐색 실패
    if (t == NULL){
        printf("삭제하고자 하는 값이 없습니다.\n");
        return;
    }
    
    // case1 : 단말노드인 경우
    if (t->left == NULL && t->right==NULL){
        if (p!=NULL){
            // 부모노드의 자식필드를 NULL로 만든다.
            if (p->left == t)
                p->left = NULL;
            else
                p->right = NULL;
        }else
            // 만약 부모노드가 NULL이면 삭제되는 노드가 루트
            *root = NULL;
    
    // case2 : 하나의 자식만 가지는 경우
    }else if (t->left == NULL || t->right==NULL){
        child = (t->left != NULL)? t->left:t->right;
        if (p!= NULL){
            if (p->left == t) // 부모를 자식과 연결
                p->left = child;
            else
                p->right = child;
        }else // 만약 부모노드가 NULL이면 삭제되는 노드가 루트
            *root = child;
        
    // case3 : 두개의 자식을 가지는 경우
    }else{
        // 오른쪽 서브트리에서 후계자를 찾는다
        succ_p = t;
        succ = t->right;
        // 후계자를 찾아 계속 왼쪽으로 이동한다.
        while(succ->left != NULL){
            succ_p = succ;
            succ = succ->left;
        }
        
        // 후속자의 부모와 자식 연결
        if (succ_p->left == succ)
            succ_p->left = succ->right;
        else
            succ_p->right = succ->right;
        // 후속자가 가진 키값을 현재 노드에 복사
        t->data = succ->data;
        // 원래의 후속자 삭제
        t = succ;
        
    }
    free(t);
}

int main(){
    srand((int)time(NULL));
    
    TreeNode* root = new_node(rand()%30 + 1);
    TreeNode* root2 = new_node(rand()%30 + 1);


    for(int i = 0; i < SIZE - 1 ; i++){
        add_node(root,rand()%30 + 1);
        add_node_iter(root2);
    }
    


    printf("\n재귀 : ");
    inorder(root);
    printf("\n비재귀 : ");
    inorder(root2);
    printf("\n");
    
    delete_node(&root, rand()%30 + 1);
    delete_node(&root2, rand()%30 + 1);
    
    printf("\n재귀 : ");
    inorder(root);
    printf("\n비재귀 : ");
    inorder(root2);
}
