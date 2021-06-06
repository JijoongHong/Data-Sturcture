#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10
#define MAX_NUM 10

typedef int element;

typedef struct{
    element data[MAX_NUM];
    int top;
}Stack;

void init_stack(Stack *s){
    s->top = -1;
}

int is_empty(Stack *s){
    return (s-> top == -1);
}

int is_full(Stack *s){
    return (s-> top == MAX_NUM);
}

void push(Stack *s, element item){
    if (is_full(s)){
        fprintf(stderr, "스택포화에러\n");
        exit(1);
    }
    s->top++;
    s->data[s->top] = item;
    
}

element pop(Stack *s){
    if (is_empty(s)){
        fprintf(stderr, "스택공백에러\n");
        exit(1);
    }else return s->data[(s->top)--];
    
}


typedef struct {
    element data[MAX_NUM];
    int front;
    int rear;
}Queue;

void error(char* message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_queue(Queue *q){
    q->front = 0;
    q->rear = 0;
}

int is_q_empty(Queue *q){
    return (q->front == q->rear);
}

int is_q_full(Queue *q){
    return ((q->rear+1)%MAX_NUM == q->front);
}

void enqueue(Queue *q, element item){
    
    if(is_q_full(q)){
        error("큐가 포화상태입니다.");
    }
    q->rear = (q->rear + 1) % MAX_NUM;
    q->data[q->rear] = item;
}

element dequeue(Queue *q){
    
    if(is_q_empty(q)){
        error("큐가 공백상태입니다.");
    }
    q->front = (q->front + 1) % MAX_NUM;
    return q->data[q->front];
}


typedef struct Graph{
    int n; //정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
}Graph;

int visited[MAX_VERTICES];

// 그래프 초기화
void init(Graph* g){
    
    int r, c;
    g->n = 0;
    for (r=0; r<MAX_VERTICES; r++)
        for(c=0; c<MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}

// 정점 삽입
void insert_vertex(Graph* g, int v){
    
    if((g->n)+1 > MAX_VERTICES){
        fprintf(stderr, "그래프: 정점 개수 초과");
        return;
    }
    g->n++;
}

// 간선 삽입
void insert_edge(Graph* g, int start, int end){
    
    if (start >= g->n || end >= g->n){
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
    
}

// 깊이 우선 탐색
void dfs_mat(Graph* g, int v){
    int w;
    visited[v] = TRUE;
    printf("%d->", v);
    for(w=0; w < g->n; w++)
        if (g->adj_mat[v][w] && !visited[w])
            dfs_mat(g, w);
}

void dfs_mat_iter(Graph* g, int v){
    
    for (int i = 0; i<MAX_VERTICES; i++){
        visited[i] = 0;
    }
    
    Stack s;
    init_stack(&s);
    push(&s, v);
    while(!is_empty(&s)){
        v = pop(&s);
        printf("%d->", v);
        visited[v] = TRUE;
        for(int w=0; w < g->n; w++)
            if (g->adj_mat[v][w] && !visited[w]){
                push(&s, w);
                visited[w] = TRUE;
            }
    }
}


// 너비 우선 탐색 
void bfs_mat(Graph* g, int v){
    
    for (int i = 0; i<MAX_VERTICES; i++){
        visited[i] = 0;
    }
    
    int w;
    Queue q;
    init_queue(&q);
    visited[v] = TRUE;
    printf("%d->", v);
    enqueue(&q, v);
    while(!is_q_empty(&q)){
        v = dequeue(&q);
        for (w=0; w<g->n; w++)
            if (g->adj_mat[v][w] && !visited[w]){
                visited[w] = TRUE;
                printf("%d->", w);
                enqueue(&q, w);
            }
    }
}

int main(){
    
    Graph* g;
    g = (Graph*)malloc(sizeof(Graph));
    init(g);
    for (int i = 0; i<10; i++)
        insert_vertex(g, i);
    
    insert_edge(g, 3, 4);
    insert_edge(g, 4, 3);
    insert_edge(g, 4, 7);
    insert_edge(g, 7, 4);
    insert_edge(g, 7, 5);
    insert_edge(g, 5, 7);
    insert_edge(g, 5, 6);
    insert_edge(g, 6, 5);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 8);
    insert_edge(g, 8, 2);
    insert_edge(g, 8, 0);
    insert_edge(g, 0, 8);
    insert_edge(g, 0, 9);
    insert_edge(g, 9, 0);
    insert_edge(g, 9, 1);
    insert_edge(g, 1, 9);
    insert_edge(g, 0, 6);
    insert_edge(g, 6, 0);
    
    printf("재귀 DFS : ");
    dfs_mat(g, 0);
    printf("\n비재귀 DFS : ");
    dfs_mat_iter(g,0);
    printf("\nBFS : ");
    bfs_mat(g, 0);
    printf("\n");
    free(g);
    return 0;
    
}

