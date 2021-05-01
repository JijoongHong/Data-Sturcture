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
    
    if (list->rear == NULL){
        list->front = list->rear = new;
    }else{
        list->rear->link = new;
        list->rear = new;
    }
    list->size++;
    
}

void dequeue(ListType* list){
    if (list->front != NULL){
        Node* removed = list->front;
        list->front = removed->link;
        if(list->front == NULL) list->rear = NULL;
        free(removed);
        list->size--;
        
    }else pass++;
}

void print_queue(ListType* list){
    
    if (list->size != 0){
        Node* p = list->front;
        
        for(int i=0; i < list->size -1; i++){
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
        }else{
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
