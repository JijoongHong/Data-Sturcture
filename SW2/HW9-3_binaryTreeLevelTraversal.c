#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
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

typedef TreeNode* element;
typedef struct Queue{
    element data[SIZE];
    int front, rear;
}Queue;

void error(char* message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_queue(Queue *q){
    q->front = 0;
    q->rear = 0;
}

int is_empty(Queue *q){
    return (q->front == q->rear);
}

int is_full(Queue *q){
    return ((q->rear+1) % SIZE == q->front);
}

void enqueue(Queue *q, element item){
    
    if(is_full(q)){
        error("큐가 포화상태입니다.");
    }
    q->rear = (q->rear + 1) % SIZE;
    q->data[q->rear] = item;
}

element dequeue(Queue *q){
    
    if(is_empty(q)){
        error("큐가 공백상태입니다.");
    }
    q->front = (q->front + 1) % SIZE;
    return q->data[q->front];
}

void level_order(TreeNode *ptr){
    
    Queue q;
    init_queue(&q);
    
    if (ptr == NULL) return;
    
    enqueue(&q, ptr);
    while(!is_empty(&q)){
        ptr = dequeue(&q);
        printf("[%d]", ptr->data);
        if (ptr->left)
            enqueue(&q, ptr->left);
        if (ptr->right)
            enqueue(&q, ptr->right);
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
    
    printf("레벨순회 : ");
    level_order(root);
    printf("\n");
    
}
