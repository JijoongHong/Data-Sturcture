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

void inorder_iter(TreeNode *root){ //LVR
    Stack s;
    init_stack(&s);
    
    while(1){
        for(;root; root = root->left) // 좌측 노드 모두 삽입
            push(&s, root);
        root = pop(&s); // 좌측 노드 꺼내어
        if (!root) break;
        printf("[%d]", root->data); // 출력
        root = root->right; // 출력 후 오른쪽 노드로
    }
}

void add_node_iter(TreeNode* root){
    int x, y;
    x = rand()%2 + 1;
    
    TreeNode* temp_root = root;
    y = rand()%2 + 10;
    
    while (temp_root){
        if (x == 1){
            if (temp_root->left == NULL){ // 왼쪽 노드가 없으면 삽입
                temp_root->left = new_node(y);
                break;
            }
            else{
                x = rand()%2 + 1; // 새로운 x 생성
                y = rand()%2 + 10; // 새로운 y 생성
                temp_root = root->left; // 좌측 노드를 루트 노드로 설정
            }
            
        }else{
            if (temp_root->right == NULL){ // 오른쪽 노드가 없으면 삽입
                temp_root->right = new_node(y);
                break;
            }
            else{
                x = rand()%2 + 1; // 새로운 x 생성
                y = rand()%2 + 10; // 새로운 y 생성
                temp_root = temp_root->right; // 우측 노드를 루트 노드로 설정
            }
        }
    }
}

void inorder(TreeNode *root){ // LVR
    if (root != NULL){
        inorder(root->left); // 좌측 노드 출력
        printf("[%d]", root->data); // 가운데 노드 출력
        inorder(root->right); // 우측 노드 출력
    }
}

void add_node(TreeNode* root){
    int x, y;
    x = rand()%2 + 1;
    y = rand()%2 + 10;
    
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

TreeNode* copy(TreeNode* orig){
    TreeNode* temp;
    if(orig){
        temp = new_node(orig->data);
        temp->left = copy(orig->left);
        temp->right = copy(orig->right);
        return temp;
    }
    return NULL;
}

TreeNode* copy_iter(TreeNode* orig){
    
    TreeNode *temp, *new_root, *temp_root;
    new_root = temp = new_node(orig->data);
    
    Stack s;
    init_stack(&s);
    push(&s, orig); // 루트 노드 삽입
    
    Stack new; // 결과 스택
    init_stack(&new);
    push(&new, temp); // 복사 루트 노드 삽입

    while(!is_empty(&new)){
        temp_root = pop(&s); // 원본 및 복사 노드 pop
        temp = pop(&new);

        if (temp_root->right != NULL){ // 원본에 오른쪽이 있으면
            temp->right = new_node(temp_root->right->data); // 복사본의 오른쪽에 복사
            push(&s, temp_root->right); // 원본 및 복사본 스택에 삽입
            push(&new, temp->right);
        }

        if(temp_root->left != NULL){ // 원본에 왼쪽이 있으면
            temp->left = new_node(temp_root->left->data); // 복사본의 왼쪽에 복사
            push(&s, temp_root->left); // 원본 및 복사본 스택에 삽입
            push(&new, temp->left);
        }
    }
    return new_root; // 복사본 루트 노드 주소 반환
}

int main(){
    
    srand((int)time(NULL));
    TreeNode* root = new_node(rand()%2 + 10);
    TreeNode* root_iter = new_node(rand()%2 + 10);
    
    for(int i = 0; i < SIZE - 1 ; i++){
        add_node(root);
        add_node_iter(root_iter);
    }
    
    TreeNode* copied = (TreeNode*)malloc(sizeof(TreeNode));
    copied = copy(root);
    
    TreeNode* copied_iter = (TreeNode*)malloc(sizeof(TreeNode));
    copied_iter = copy_iter(root_iter);
    
    printf("-----------------재귀 순회-----------------\n");
    inorder(root);
    printf("\n");
    inorder(copied);
    
    printf("\n\n-----------------비재귀 순회----------------\n");
    inorder(root_iter);
    printf("\n");
    inorder(copied_iter);
    printf("\n");
    
}
