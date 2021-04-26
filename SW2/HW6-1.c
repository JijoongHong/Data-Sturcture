#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_NUM 21

typedef int element;
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

int is_empty(Queue *q){
    return (q->front == q->rear);
}

int is_full(Queue *q){
    return ((q->rear+1)%MAX_NUM == q->front);
}

void enqueue(Queue *q, element item){
    
    if(is_full(q)){
        error("큐가 포화상태입니다.");
    }
    q->rear = (q->rear + 1) % MAX_NUM;
    q->data[q->rear] = item;
}

element dequeue(Queue *q){
    
    if(is_empty(q)){
        error("큐가 공백상태입니다.");
    }
    q->front = (q->front + 1) % MAX_NUM;
    return q->data[q->front];
}

element peek(Queue *q){
    
    if(is_empty(q)){
        error("큐가 공백상태입니다.");
    }
    return q->data[(q->front + 1) % MAX_NUM];
    
}

void print_queue_from_front(Queue *q){
    
    if(!is_empty(q)){
        
        int i = q->front;
        
        printf("From front: \n|");
        do{
            i = (i+1) % MAX_NUM;
            printf(" %d |", q->data[i]);
            if (i == q->rear) break;
            
        }while (i != q->front);
        
    }
    printf("\n");
}


void print_queue_from_rear(Queue *q){
    
    if(!is_empty(q)){
        
        int i = q->rear + 1;
        printf("From rear: \n|");
        do{
            i = (i-1) % MAX_NUM;
            printf(" %d |", q->data[i]);
            if (i == q->front + 1) break;
            
        }while (i != q->front);
        
    }
    printf("\n");

}

int main(){
    
    Queue q;
    init_queue(&q);
    
    int mode = 0, random = 0, add = 0, del = 0, pass = 0;
    srand(time(NULL));
    
    for(int i = 0; i < 30; i++){
        
        mode = rand()%2 + 1;
        printf("mode : %d\n", mode);
        if (mode == 1){
            random = rand()%100 + 1;
            printf("random : %d\n", random);
            enqueue(&q, random);
            add++;
        
        }else{
            if (is_empty(&q)){
                pass++;
                printf("nothing to delete\n");
                printf("\n");
                continue;
            }
            else dequeue(&q); del++;
        }
        
        
    }
    
    print_queue_from_front(&q);
    printf("\n");
    print_queue_from_rear(&q);
    
    printf("\nAdded : %d, Deleted : %d, Passed : %d\n", add, del, pass);
    
    return 0;
    
}
