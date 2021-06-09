#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 10
#define MAX_NUM 10
#define TRUE 1
#define FALSE 0

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

typedef struct GraphNode{
    int vertex;
    struct GraphNode* link;
}GraphNode;

typedef struct Graph{
    int n; //정점의 개수
    GraphNode* adj_list[MAX_VERTICES];
}Graph;

int visited[MAX_VERTICES];

//그래프 초기화
void init(Graph *g){
    int v;
    g->n = 0;
    for(v=0; v<MAX_VERTICES; v++)
        g->adj_list[v] = NULL;
}

// 정점 삽입 연산
void insert_vertex(Graph* g, int v){
    
    if((g->n)+1 > MAX_VERTICES){
        fprintf(stderr, "그래프: 정점 개수 초과");
        return;
    }
    g->n++;
}

// 간선 삽입 연산, v를 u의 인접 리스트에 삽입
void insert_edge(Graph* g, int u, int v){
    
    GraphNode* node;
    if (u >= g->n || v >= g->n){
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

int topo_sort(Graph* g, char** list){
    
    int i;
    Stack s;
    init_stack(&s);
    GraphNode* node;
    
    int* in_degree = (int*)malloc(g->n*sizeof(int));
    for (i=0; i< g->n; i++)
        in_degree[i] = 0;
    for (i=0; i< g->n; i++){
        node = g->adj_list[i];
        while(node != NULL){
            in_degree[node->vertex]++;
            node = node->link;
        }
    }
    
    for (i=0; i< g->n; i++)
        if (in_degree[i] == 0)
            push(&s, i);
    
    while(!is_empty(&s)){
        int w;
        w = pop(&s);
        printf("%s -> ", list[w]);
        node = g->adj_list[w];
        while (node != NULL) {
            int u = node->vertex;
            in_degree[u]--;
            if (in_degree[u] == 0)
                push(&s, u);
            node = node->link;
        }
    }
    
    free(in_degree);
    printf("\n");
    return (i == g->n);
}

int main(){
    
    Graph g;
    init(&g);
    char* courses[10] = {"정보통신기술I", "정보통신기술II", "SW프로그래밍I", "SW프로그래밍II", "보안통계학", "보안데이터분석", "소프트웨어보안", "알고리즘", "머신러닝", "인공지능과 보안"};

    for (int i = 0; i<10; i++)
        insert_vertex(&g, i);
    
    insert_edge(&g, 0, 1);
    insert_edge(&g, 1, 3);
    insert_edge(&g, 2, 3);
    insert_edge(&g, 2, 5);
    insert_edge(&g, 3, 6);
    insert_edge(&g, 3, 7);
    insert_edge(&g, 4, 5);
    insert_edge(&g, 5, 8);
    insert_edge(&g, 7, 8);
    insert_edge(&g, 6, 9);
    insert_edge(&g, 8, 9);

    topo_sort(&g, courses);
    return 0;
    
}
