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

typedef struct Stack{
    TreeNode *stack[SIZE];
    int top;
}Stack;

void init_stack(Stack *s){
    s->top = -1;
}

int is_empty(Stack *s){
    return (s->top == -1);
}

void push(Stack *s, TreeNode *p){
    if (s->top < SIZE-1)
        s->stack[++s->top] = p;
}

TreeNode* pop(Stack *s){
    TreeNode *p = NULL;
    if(!is_empty(s))
        p = s->stack[s->top--];
    return p;
}

TreeNode* peek(Stack *s){
    TreeNode *p = NULL;
    if(!is_empty(s))
        p = s->stack[s->top];
    return p;
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


int main(){
    srand((int)time(NULL));
    
    TreeNode* root = new_node(rand()%30 + 1);
    TreeNode* root2 = new_node(rand()%30 + 1);


    for(int i = 0; i < SIZE - 1 ; i++){
        add_node(root,rand()%30 + 1
                 );
        add_node_iter(root2);
    }

    printf("----------------------재귀 순회----------------------");
    printf("\n재귀 : ");
    inorder(root);
    printf("\n비재귀 : ");
    inorder(root2);
}
