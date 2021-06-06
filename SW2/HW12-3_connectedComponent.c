#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 10
#define TRUE 1
#define FALSE 0

typedef struct GraphNode{
    int vertex;
    struct GraphNode* link;
}GraphNode;

typedef struct Graph{
    int n; //정점의 개수
    GraphNode* adj_list[MAX_VERTICES];
}Graph;

int visited[MAX_VERTICES] = {0};

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
    u /= 10;
    v /= 10;
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


void dfs_list(Graph* g, int v){
    
    GraphNode* w;
    visited[v] = TRUE;
    printf("%d->", v*10);
    for (w = g->adj_list[v]; w; w = w->link)
        if (!visited[w->vertex])
            dfs_list(g, w->vertex);
}

int connected_component(Graph* g){
    
    int count = 0;
    for(int i=0; i<g->n; i++){
        if (!visited[i]){
            count++;
            dfs_list(g,i);
            printf("\n");
        }
    }
    return count;
}

int main(){
    
    Graph* g;
    g = (Graph*)malloc(sizeof(Graph));
    init(g);
    for (int i = 0; i<100; i+=10)
        insert_vertex(g, i);
    
    insert_edge(g, 30, 40);
    insert_edge(g, 40, 30);
    insert_edge(g, 40, 70);
    insert_edge(g, 70, 40);
    insert_edge(g, 70, 50);
    insert_edge(g, 50, 70);
    insert_edge(g, 50, 60);
    insert_edge(g, 60, 50);
    
    insert_edge(g, 10, 20);
    insert_edge(g, 20, 10);
    insert_edge(g, 20, 80);
    insert_edge(g, 80, 20);
    insert_edge(g, 80, 0);
    insert_edge(g, 0, 80);
    insert_edge(g, 0, 90);
    insert_edge(g, 90, 0);
    insert_edge(g, 90, 10);
    insert_edge(g, 10, 90);

    printf("\n연결성분 총 %d개\n",connected_component(g));
    free(g);
    return 0;
    
}
