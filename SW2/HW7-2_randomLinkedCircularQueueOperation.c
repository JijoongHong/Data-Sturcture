#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int element;
int dq = 0, eq = 0, pass = 0;

typedef struct{
    element data;
    struct Node* link;
} Node;

typedef struct{
    int size;
    Node* front;
    Node* rear;
} ListType;

void error(char *message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

ListType* create(void){
    
    ListType *list = (ListType*)malloc(sizeof(ListType));
    list->size = 0;
    list->front = list->rear = NULL;
    return list;
    
}

void enqueue(ListType* list, int data){
    
    Node* new = (Node*)malloc(sizeof(Node));
    if (new == NULL) error("메모리 할당 에러");
    
    new->data = data;
    new->link = NULL;
    
    if (list->rear == NULL){ // 첫번째 노드 생성
        list->front = list->rear = new;
    }else{                   // 맨 뒤에 노드 추가
        list->rear->link = new; // 마지막 노드가 새로운 노드를 가리키도록 함
        list->rear = new; // rear가 새로운 노드를 가리키도록 함
    }
    list->size++;
    
}

void dequeue(ListType* list){
    if (list->front != NULL){ //삭제할 게 있으면
        Node* removed = list->front; // 맨 앞 노드 임시저장
        list->front = removed->link; // front가 맨 앞 노드가 가리키는 곳(2번째 노드)를 가리키도록 함
        if(list->front == NULL) list->rear = NULL; // 노드가 모두 삭제된 경우 rear 조정
        free(removed);
        list->size--;
        
    }else pass++; //삭제할 게 없으면
}

void print_queue(ListType* list){
    
    if (list->size != 0){ // 데이터가 남아 있는 경우
        Node* p = list->front;
        
        for(int i=0; i < list->size -1; i++){ // 하나씩 순회하며 출력
            printf("%d -> ", p->data);
            p = p->link;
        }
        printf("%d", list->rear->data);
        printf("\n");
    }

}

void print_log(ListType* list){
    
    Node* p = list->front;
    
    printf("----- log -----\n");
    
    for(int i=0; i < list->size; i++){
        if (p->data == -2) 
            printf("%d : dequeue\n", i+1);
        else
            printf("%d : enqueue(%d)\n", i+1, p->data);
        
         p = p->link;
    }
    printf("\nenqueue %d회", eq);
    printf("\ndequeue %d회", dq-pass);
    printf("\npass %d회\n", pass);
    printf("---------------\n");
}



int main(){
    ListType *queue, *log;
    queue = create();
    log = create();
    
    int mode = 0, random = 0;
    srand(time(NULL));
    
    for(int i = 0; i < 10; i++){
        
        mode = rand()%2 - 2;
        if (mode == -1){
            random = rand()%100 + 1;
            enqueue(queue, random);
            enqueue(log, random);
            eq++;
        }else{ //mode == -2
            dequeue(queue);
            enqueue(log, mode);
            dq++;
        }
    }
    
    print_log(log);
    print_queue(queue);
    
    
    free(queue);
    free(log);
    return 0;
    
}
