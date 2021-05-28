#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define SIZE 100

typedef struct TreeNode{
    char data;
    struct TreeNode *left, *right;
}TreeNode;

TreeNode* new_node(int y){
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->data = y;
    temp->left = temp->right = NULL;
    return temp;
}

typedef struct Stack{
    char data[SIZE];
    int top;
}Stack;

void init_stack(Stack *s){
    s->top = -1;
}

int is_empty(Stack *s){
    return (s->top == -1);
}

void push(Stack *s, char p){
    if (s->top < SIZE-1)
        s->data[++s->top] = p;
}

char pop(Stack *s){
    if (is_empty(s)){
        
        printf("스택 공백 에러\n");
        exit(1);
        
    }else return s->data[(s->top)--];
}

char peek(Stack *s){
    if (is_empty(s)){
        
        printf("스택 공백 에러\n");
        exit(1);
        
    }else return s->data[s->top];
}

typedef struct NodeStack{
    TreeNode* stack[SIZE];
    int top;
}NodeStack;

void n_init_stack(NodeStack *s){
    s->top = -1;
}

int n_is_empty(NodeStack *s){
    return (s->top == -1);
}

void n_push(NodeStack *s, TreeNode *p){
    if (s->top < SIZE-1)
        s->stack[++s->top] = p;
}

TreeNode* n_pop(NodeStack *s){
    TreeNode *p = NULL;
    if(!n_is_empty(s))
        p = s->stack[s->top--];
    return p;
}

TreeNode* n_peek(NodeStack *s){
    TreeNode *p = NULL;
    if(!n_is_empty(s))
        p = s->stack[s->top];
    return p;
}


void post_order(TreeNode *root){ // LRV
    if (root != NULL){
        post_order(root->left); // 좌측 노드 출력
        post_order(root->right); // 우측 노드 출력
        if (isdigit(root->data+'0') !=0){
            printf("[%c]", root->data + '0'); // 가운데 숫자 노드 출력
        }
        else{
            printf("[%c]", root->data); // 가운데 연산자 노드 출력
        }
    }
}

TreeNode* init_tree(char* exp, int len){
    
    NodeStack s;
    n_init_stack(&s);
    TreeNode* temp;
    
    for (int i = 0; i<len; i++){
        if (isdigit(exp[i]) !=0){
            n_push(&s, new_node(exp[i]-'0'));
        }
        else{
            
            temp = new_node(exp[i]);
            temp->right = n_pop(&s);
            temp->left = n_pop(&s);
            n_push(&s, temp);
        }
    }
    return n_pop(&s);
}

int get_priority(char ch){
    
    switch (ch) {
        case '*': case '/':
            return 0;
            
        case '+': case '-':
            return 1;
    }
    
    return -1;
}


TreeNode* postfix(char* math_exp, int len){
    
    Stack s;
    init_stack(&s);
    char* post_exp = (char*)malloc(sizeof(char)*len);
    int priority, j=0;

    for (int i = 0; i < len; i++){
        priority = get_priority(math_exp[i]);
        
        if (priority == -1){ // 숫자인 경우
            post_exp[j++] = math_exp[i];
            
        }else{ // 연산자인 경우
            while(!is_empty(&s) && (get_priority(peek(&s)) <= get_priority(math_exp[i])))
                post_exp[j++] = pop(&s);
            push(&s, math_exp[i]);
        }
    }
            
    while(!is_empty(&s)) //남은 항목 저장
        post_exp[j++] = pop(&s);

    return init_tree(post_exp, len);
                
}

int evaluate(TreeNode* root){
    
    if (root == NULL) return 0;
    
    if (root->left == NULL && root->right == NULL)
        return root->data;
    
    else{
        int op1 = evaluate(root->left);
        int op2 = evaluate(root->right);
        switch (root->data) {
            case '+':
                return op1 + op2;
            case '-':
                return op1 - op2;
            case '*':
                return op1 * op2;
            case '/':
                return op1 / op2;
        }
    }
    return 0;
}


int main(){

    char math_exp[100];
    int len;
    printf("수식을 입력하세요 : ");
    // 8/4-5+2*3-1*5
    scanf(" %[^\n]", math_exp);
    len = strlen(math_exp);
    TreeNode* root = postfix(math_exp, len);
    printf("\n후위순회: ");
    post_order(root);
    printf("\n연산결과: %d\n", evaluate(root));
    
                
}
