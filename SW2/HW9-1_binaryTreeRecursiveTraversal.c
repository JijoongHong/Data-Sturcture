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
        for(;root; root = root->left)
            push(&s, root);
        root = pop(&s);
        if (!root) break;
        printf("[%d]", root->data);
        root = root->right;
    }
}

void pre_order_iter(TreeNode *root){ //VLR
    
    Stack s;
    init_stack(&s);
    push(&s, root);
    
    while(1){
        root = pop(&s);
        if (!root) break;
        printf("[%d]", root->data);
        if(root->right != NULL)
            push(&s, root->right);
        if(root->left != NULL)
        push(&s, root->left);
    }
}

void post_order_iter(TreeNode *root){ //LRV
    
    Stack s, output;
    init_stack(&s);
    init_stack(&output);
    
    push(&s, root);
    
    while (!is_empty(&s)){
        root = pop(&s);
        push(&output, root);
        
        if (root->left != NULL){
            push(&s, root->left);
        }
        
        if (root->right != NULL){
            push(&s, root->right);
        }
    }
    
    while(!is_empty(&output)){
        printf("[%d]", pop(&output)->data);
    }
}

void inorder(TreeNode *root){
    if (root != NULL){
        inorder(root->left);
        printf("[%d]", root->data);
        inorder(root->right);
    }
}

void pre_order(TreeNode *root){
    if (root != NULL){
        printf("[%d]", root->data);
        pre_order(root->left);
        pre_order(root->right);
    }
}

void post_order(TreeNode *root){
    if (root != NULL){
        post_order(root->left);
        post_order(root->right);
        printf("[%d]", root->data);
    }
}

int search(TreeNode *node, int target){
    
    if (node == NULL) return -1;
    if (target == node->data) return 0;
    else{
        search(node->left, target);
        search(node->right, target);
    }
    return -1;
}

void add_node(TreeNode* root){
    int x, y;
    x = rand()%2 + 1;
    
    while (1){
        y = rand()%100 + 1;
        if (search(root, y) == -1)
            break;
    }
    
    if (x == 1){
        if (root->left == NULL)
            root->left = new_node(y);
        else
            add_node(root->left);
        
        
    }else{
        if (root->right == NULL)
            root->right = new_node(y);
        else
            add_node(root->right);
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
    
    printf("----------------------재귀 순회----------------------");
    printf("\n중위순회 : ");
    inorder(root);
    printf("\n전위순회 : ");
    pre_order(root);
    printf("\n후위순회 : ");
    post_order(root);
    printf("\n\n");
    
    printf("---------------------비재귀 순회---------------------");
    printf("\n중위순회 : ");
    inorder_iter(root);
    printf("\n전위순회 : ");
    pre_order_iter(root);
    printf("\n후위순회 : ");
    post_order_iter(root);
    printf("\n");
    
    //중위 : 18 99 92 97 90 27 55 50 97 49
    //전위 : 50 80 92 99 18 70 55 27 49 97
    //후위 : 18 99 70 92 27 55 80 97 49 50
    
    //                    50
    //                    /\
    //                   /  \
    //                  /    \
    //                 /      \
    //                /        \
    //               80        49
    //               /\        /
    //              /  \      /
    //             /    \    /
    //            92    55  97
    //           /\      /
    //          /  \    /
    //         99  70  27
    //        /
    //       18

}
