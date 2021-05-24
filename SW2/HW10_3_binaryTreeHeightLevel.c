#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <math.h>
#define SIZE 10
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

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

void level_order(TreeNode *node){
    
    Queue q;
    init_queue(&q);
    
    if (node == NULL) return;
    
    enqueue(&q, node); // 큐에 루트 노드 삽입
    while(!is_empty(&q)){
        node = dequeue(&q); // dequeue 후 출력
        printf("[%d]", node->data);
        if (node->left)
            enqueue(&q, node->left); // 좌측 노드가 있으면 삽입
        if (node->right)
            enqueue(&q, node->right); // 우측 노드가 있으면 삽입
    }
}

void add_node(TreeNode* root){
    int x, y;
    x = rand()%2 + 1;
    y = rand()%100 + 1;
    
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

int get_node_count(TreeNode* node){
    
    int count = 0;
    if (node != NULL)
        count = 1 + get_node_count(node->left) + get_node_count(node->right);
    
    return count;
}


int get_height(TreeNode* node){
    int height = 0;
    if (node != NULL)
        height = 1 + MAX(get_height(node->left), get_height(node->right));
    
    return height;
}

int get_height_iter(TreeNode* node){
    int num = pow(2,get_node_count(node)); // 최악의 경우
    int depth = 0; // 깊이
    int max_depth = 0; // 최대 깊이
    
    while(num!=0){
        TreeNode* temp_root = node;
        int temp = num;
        depth = 0;
        int idx=0;
        int path[10] = {0};
        for (int i = 0; temp!=0; i++){ // 2진수 변환하여 0 or 1로 구성된 path 지정, 총 노드 갯수에 미치지 않으면 앞에 0 패딩
            path[9-i] = temp%2;
            temp = temp/2;
        }
        
        while(temp_root != NULL){
            if (path[idx++]==0){ // 0이면 왼쪽으로 이동
                temp_root = temp_root->left; // depth 1 증가
                depth++;
            }else{
                temp_root = temp_root->right; // 1이면 오른쪽으로 이동
                depth++; // depth 1 증가
            }
        }// 노드가 끝나면 중단
        
        if (depth > max_depth) // 현재까지 최고 깊이보다 depth가 크면
            max_depth = depth; // 변경
        
        num--; // 기준 숫자 변경
        
    }
    return max_depth;
}

void get_node_count_per_level(TreeNode* node){
    
    int count[10] = {0};
    if (node!=NULL)
        count[0] = 1;
    int level = 0, checked = 0;
    TreeNode* temp_root = node;
    Queue q;
    init_queue(&q);
    enqueue(&q, temp_root);
    
    while(!is_empty(&q)){
        int max_siblings = 1;
        temp_root = dequeue(&q);
        
        if (temp_root->left != NULL){ // 왼쪽에 있으면
            count[++level]++; // 해당 레벨의 갯수 1 증가
            level--; // 기존 레벨 회귀
            enqueue(&q, temp_root->left); // 왼쪽 삽입
        }
        
        checked++; // 왼쪽에 있는지 없는지 확인한 횟수
        
        if (temp_root->right != NULL){ // 오른쪽에 있으면
            count[++level]++; // 해당 레벨의 갯수 1 증가
            level--; // 기존 레벨 회귀
            enqueue(&q, temp_root->right); // 오른쪽 삽입
        }
        
        checked++; // 왼쪽에 있는지 없는지 확인
        max_siblings = pow(2, level); // 레벨 당 최대 노드 갯수
        
        if (max_siblings <= checked){ // 최대 노드 갯수 이상이면 레벨 1 증가 
            checked = 0;
            level++;
        }

    }
    
    for (int i = 0; i < get_height(node); i++)
        
        printf("레벨%d: %d\n", i+1, count[i]);
    
}

int main(){
    srand((int)time(NULL));
    TreeNode* root = new_node(rand()%100 + 1);

    for(int i = 0; i < SIZE - 1 ; i++){
        add_node(root);
    }
    
    printf("높이(재귀) : ");
    int height = get_height(root);
    printf("%d\n", height);
    
    printf("높이(비재귀) : ");
    int height2 = get_height_iter(root);
    printf("%d\n", height2);
    
    get_node_count_per_level(root);
    printf("\n");
    
    return 0;
    
}


/*
 int get_node_count(TreeNode* node){
     
     int count = 0;
     if (node != NULL)
         count = 1 + get_node_count(node->left) + get_node_count(node->right);
     
     return count;
 }
 
 int get_leaf_count(TreeNode* node){
     int i = 0;
     int counts[10] = {-1};
     int count = 0;
     int level = get_height(node);
     if (node != NULL){
         if (node->left == NULL && node->right == NULL)
             return 1;
         else{
             int a = get_leaf_count(node->left);
             int b = get_leaf_count(node->right);

         }

     }

     
     return count;
     
 }
 
 
 */
