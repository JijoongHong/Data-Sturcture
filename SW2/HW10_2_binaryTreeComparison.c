#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10
#define TRUE 1
#define FALSE 0

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

void post_order_iter(TreeNode *root){ //LRV
    
    Stack s, output;
    init_stack(&s);
    init_stack(&output);
    
    push(&s, root); // 루트 노드 스택에 삽입
    
    while (!is_empty(&s)){
        root = pop(&s); // 루트 노드 꺼내어 output에 저장
        push(&output, root);
        
        if (root->left != NULL){ // 왼쪽 노드가 있으면 스택에 삽입 (output 스택에 나중에 넣기 위해 먼저 삽입)
            push(&s, root->left);
        }
        
        if (root->right != NULL){ // 오른쪽 노드가 있으면 스택에 삽입
            push(&s, root->right);
        } // output에 들어가는 순서 : V->R->L
    }
    
    while(!is_empty(&output)){
        printf("[%d]", pop(&output)->data); // output의 데이터 pop 시 LRV순으로 출력
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

void post_order(TreeNode *root){ // LRV
    if (root != NULL){
        post_order(root->left); // 좌측 노드 출력
        post_order(root->right); // 우측 노드 출력
        printf("[%d]", root->data); // 가운데 노드 출력
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

int equal(TreeNode* first, TreeNode* second){
    
    return (((!first && !second) || (first&&second&&(first->data == second->data)))
            && equal(first->left, second->left) && equal(first->right, second->right));
}


int equal_iter(TreeNode* first, TreeNode* second){
    
    Stack f;
    init_stack(&f);
    push(&f, first); // 루트 노드 삽입
    
    Stack s;
    init_stack(&s);
    push(&s, second); // 루트 노드 삽입
    
    while(!is_empty(&f) && !is_empty(&s)){
        first = pop(&f); // 루트 노드 꺼내어
        second = pop(&s);
        
        //printf("%d, %d\n", first->data, second->data);
        
        if (first->data != second->data)
            return 0;
        
        if(first->right != NULL)
            push(&f, first->right); // 오른쪽 노드가 있으면 삽입(pop시 left가 먼저 나오도록 right 먼저 삽입)
        
        if(second->right != NULL)
            push(&s, second->right); // 오른쪽 노드가 있으면 삽입(pop시 left가 먼저 나오도록 right 먼저 삽입)
        
        
        if(first->left != NULL)
            push(&f, first->left); // 왼쪽 노드가 있으면 삽입
        
        if(second->left != NULL)
            push(&s, second->left); // 왼쪽 노드가 있으면 삽입
        
    }
    
    if (!is_empty(&f) || !is_empty(&s))
        return 0;
    
    return 1;
}

int main(){
    
    srand((int)time(NULL));
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = rand()%2 + 10;
    root->left = root->right = NULL;

    TreeNode* root2 = (TreeNode*)malloc(sizeof(TreeNode));
    root2->data = rand()%2 + 10;
    root2->left = root2->right = NULL;
    
    TreeNode* root_iter = (TreeNode*)malloc(sizeof(TreeNode));
    root_iter->data = rand()%2 + 10;
    root_iter->left = root_iter->right = NULL;
    
    
    TreeNode* root_iter2 = (TreeNode*)malloc(sizeof(TreeNode));
    root_iter2->data = rand()%2 + 10;
    root_iter2->left = root_iter2->right = NULL;
    
    
    for(int i = 0; i < SIZE - 1 ; i++){
        add_node(root);
        add_node(root2);
        add_node_iter(root_iter);
        add_node_iter(root_iter2);
    }

    
    printf("-----------------재귀 순회-----------------\n");
    post_order(root);
    printf("\n");
    post_order(root2);
    printf("\n");
    if (equal(root, root2) == TRUE)
        printf("두 트리는 동일합니다.\n");
    else
        printf("두 트리는 동일하지 않습니다.\n");
    
    printf("\n\n-----------------비재귀 순회----------------\n");
    post_order_iter(root_iter);
    printf("\n");
    post_order_iter(root_iter2);
    printf("\n");
    if (equal_iter(root_iter, root_iter2) == TRUE)
        printf("두 트리는 동일합니다.\n");
    else
        printf("두 트리는 동일하지 않습니다.\n");
    
    
}
