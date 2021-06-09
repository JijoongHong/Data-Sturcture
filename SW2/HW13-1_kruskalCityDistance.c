#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10
#define INF 9999

struct City{
    char* data[10];
};

int parent[MAX_VERTICES];   //부모노드

void set_init(int n){       // 초기화
    for(int i = 0; i<n; i++)
        parent[i] = -1;
}

// curr가 속하는 집합 반환
int set_find(int curr){

    if (parent[curr] == -1)
        return curr; //루트
    while (parent[curr] != -1)
        curr = parent[curr];
    
    return curr;
}

// 두개의 원소가 속한 집합 합침
void set_union(int a, int b){
    int root1 = set_find(a); //노드 a의 루트
    int root2 = set_find(b); //노드 b의 루트
    if (root1 != root2)
        parent[root1] = root2; // 합침
}

struct Edge{ // 간선을 나타내는 구조체
    int start, end, weight;
};

typedef struct Graph{
    int n;
    struct Edge edges[2*MAX_VERTICES];
}Graph;

// 그래프 초기화
void init_graph(Graph* g){
    g->n = 0;
    for (int i = 0; i<2*MAX_VERTICES;i++){
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

// 간선 삽입
void insert_edge(Graph* g, int start, int end, int w){
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}

int compare(const void* a, const void* b){
    struct Edge* x = (struct Edge*) a;
    struct Edge* y = (struct Edge*) b;
    return (x->weight - y->weight);
}

void kruskal(Graph *g, int vnum, char** list){
    
    int edge_accepted = 0;
    int u_set, v_set;
    struct Edge e;
    
    set_init(g->n);
    qsort(g->edges, g->n, sizeof(struct Edge), compare);
    
    int i = 0;
    while (edge_accepted < vnum-1){
        
        e = g->edges[i];
        u_set = set_find(e.start);
        v_set = set_find(e.end);
        
        if(u_set != v_set){
            printf("(%s, %s): %d\n", list[e.start], list[e.end], e.weight);
            edge_accepted++;
            set_union(u_set, v_set);
        }
        i++;
    }
    
}

int main(){
    
    Graph* g;
    g = (Graph*)malloc(sizeof(Graph));
    init_graph(g);
    
    insert_edge(g, 0, 1, 29); // 서울-인천
    insert_edge(g, 0, 7, 123); // 서울-세종
    insert_edge(g, 0, 8, 34); // 서울-수원
    insert_edge(g, 0, 9, 74); // 서울-춘천
    insert_edge(g, 1, 2, 333); // 인천-부산
    insert_edge(g, 2, 3, 87); // 부산-대구
    insert_edge(g, 2, 5, 200); // 부산-대전
    insert_edge(g, 2, 6, 202); // 부산-광주
    insert_edge(g, 3, 4, 70); // 대구-울산
    insert_edge(g, 3, 5, 119); // 대구-대전
    insert_edge(g, 3, 9, 237); // 대구-춘천
    insert_edge(g, 4, 9, 292); // 울산-춘천
    insert_edge(g, 5, 7, 17); // 대전-세종
    insert_edge(g, 5, 8, 106); // 대전-수원
    insert_edge(g, 6, 7, 152); //광주-세종

    char* cities[10] = {"서울", "인천", "부산", "대구", "울산", "대전", "광주", "세종", "수원", "춘천"};
    
    
    kruskal(g, 10, cities);
    free(g);
    return 0;
    
    //서울 - 0, 인천 - 1, 부산 - 2, 대구 - 3, 울산 - 4, 대전 - 5, 광주 - 6, 세종 - 7, 수원 - 8, 춘천 - 9
}


