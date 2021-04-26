#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAX_QUEUE_SIZE 100

typedef char element;
typedef struct{
    element data[MAX_QUEUE_SIZE];
    int front, rear;
}Queue;

void error(char *message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_queue(Queue *q){
    q->front = q->rear = 0;
}

int is_empty(Queue *q){
    return (q->front == q->rear);
}

int is_full(Queue *q){
    return ((q->rear +1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(Queue* q, element item){
    
    if(is_full(q)) error("큐가 포화상태입니다.\n");
    q->rear = (q->rear+1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
    
}

element dequeue(Queue* q){
    
    if(is_empty(q)) error("큐가 공백상태입니다\n");
    q->front = (q->front+1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
    
}

int main(int argc, const char * argv[]) {
    int num;
    int index= 0, newtime = 0, oldtime = 0, dqIndex = 0, oldIndex =0, i =0;
    Queue queue;
    init_queue(&queue);
    element result[MAX_QUEUE_SIZE] = {NULL, };
    struct timeval start = {};
    struct timeval end = {};
    
    printf("system start!!!\n");
    do {
        gettimeofday(&start, NULL);
        printf(">>>");
        scanf("%d", &num);
        gettimeofday(&end, NULL);
        double time = end.tv_sec + end.tv_usec / 1000000 - start.tv_sec -start.tv_usec / 1000000;
        printf("%lf\n", time);
        oldtime = i;
        for(i=oldtime;i<(int)time+oldtime; i++){
            enqueue(&queue, i+65);
        }
        newtime = i;
        
        if(num == 0){
            // 상태 보기
            for(int j=oldtime;j<newtime;j++){
                printf("(SYSTEM) ENQUEUE(%c) F=%d R=%d\n", j+65, queue.front, j+1);
            }
           
        }
        
        else {
            for(int j=oldtime;j<newtime;j++){
                printf("(SYSTEM) ENQUEUE(%c)\n", j+65);
            }
            oldIndex = queue.front;
            for(dqIndex = oldIndex; dqIndex<oldIndex + num; dqIndex++){
                if(is_empty(&queue)){
                    printf("DELETEQUEUE() FAIL. QueueEmpty\n");
                    break;
                }
                printf("DEQUEUE() = %c, F=%d R=%d\n", queue.front+65, queue.front, queue.rear);
                result[index++] = dequeue(&queue);
            }
            result[index] = '\0';
            printf("RESULT = %s\n", result);
            result[0] = '\0';
            index=0;
        }
        
        //상태표시
        printf("QUEUE = ");
        if(is_empty(&queue)){
            printf("(0)\n");
        } else {
            for(int j=queue.front+1;j<queue.rear+1;j++){
                printf("%c", queue.data[j]);
            }
            printf("\n");
        }
    } while (1);
    return 0;
}
