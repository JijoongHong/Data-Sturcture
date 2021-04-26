#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <ctype.h>
#define MAX_NUM 21 //20개 이상 입력큐에 들어온다면 오류
#define TRUE 1
#define FALSE 0


typedef char Data;

typedef struct Queue {
    Data queueArray[MAX_NUM];
    int front;
    int rear;
} queue;

void QueueInit(queue* pq){
    pq->front = 0;
    pq->rear = 0;
}

int isEmpty(queue* pq){
    if(pq->front == pq->rear){
        return TRUE;
    } else return FALSE;
}

int NextposIdx(int pos){
    if(pos == MAX_NUM - 1){
        return FALSE;
    } else {
        return pos+1;
    }
}

int isFull(queue* pq){
    return (pq->rear+1)%MAX_NUM == pq->front;
}

void enqueue(queue* pq,Data input){
    if(isFull(pq)){
        printf("ERROR");
        exit(-1);
    }
    pq->rear = (pq->rear+1) % MAX_NUM ;
    pq->queueArray[pq->rear] = input;
}

Data dequeue(queue* pq){
    if(isEmpty(pq)){
        printf("ERROR");
        exit(-1);
    }
    pq->front = (pq->front+1) % MAX_NUM;
    return pq->queueArray[pq->front];
}

int main(int argc, const char * argv[]) {
    int num;
    int index= 0, newtime = 0, oldtime = 0, dqIndex = 0, oldIndex =0, i =0;
    queue queue;
    QueueInit(&queue);
    Data result[MAX_NUM] = {NULL, };
    struct timeval start = {};
    struct timeval end = {};
    
    printf("system start!!!\n");
    do {
        gettimeofday(&start, NULL); //시간 start
        printf(">>>");
        scanf("%d", &num); //dequeue 할 양 = num
        gettimeofday(&end, NULL); //시간 end
        double time = end.tv_sec + end.tv_usec / 1000000 - start.tv_sec -start.tv_usec / 1000000;
        printf("%lf\n", time);
        oldtime = i; // 과거 시간
        for(i=oldtime;i<(int)time+oldtime; i++){ // 과거시간에서 과거시간 + 잰시간까지 반복
            enqueue(&queue, i%26 + 65);
        }
        newtime = i; // time+oldtime을 newtime으로 변경
        
        if(num == 0){
            // 상태 보기
            for(int j=oldtime;j<newtime;j++){ //과거시간부터 새로운시간까지 반복
                printf("(SYSTEM) ENQUEUE(%c) F=%d R=%d\n", j%26 + 65, queue.front, (j+1)%MAX_NUM);
            }
           
        }
        
        else { //0이 아닌숫자 입력시
            for(int j=oldtime;j<newtime;j++){
                printf("(SYSTEM) ENQUEUE(%c) F=%d R=%d\n", j%26 +65,  queue.front, (j+1)%21);
            }
            oldIndex = queue.front; //과거인덱스를 queue.front로 초기화
            for(dqIndex = oldIndex; dqIndex<oldIndex + num; dqIndex++){ //dequeue인덱스를 과거인덱스부터, 과거인덱스 + dequeue할 값 num 만큼 반복
                if(isEmpty(&queue)){ //queue가 비었다면
                    printf("DELETEQUEUE() FAIL. QueueEmpty\n");
                    break;
                }
                printf("DEQUEUE() = %c, F=%d R=%d\n", queue.queueArray[(queue.front+1)%21], (queue.front+1)%21, queue.rear);
                result[index++] = dequeue(&queue); //dequeue해서 result값에 넣어준다.
            }
            result[index] = '\0';
            printf("RESULT = %s\n", result); //result 출력
            result[0] = '\0'; //첫째값에 NULL값 넣어주면서 초기화
            index=0;
        }
        
        //상태표시
        printf("QUEUE = ");
        if(isEmpty(&queue)){
            printf("(0)\n");
        } else {
            int newI = queue.front+1;
            while(isalpha(queue.queueArray[newI%21])){
                printf("%c", queue.queueArray[newI% 21]);
                newI++;
                queue.queueArray[queue.rear+1] = '!'; //출력시에 isalpha를 검사하기때문에, 출력하면안되는 인덱스부터 숫자아닌값 넣어주기
            }
        }
            printf("\n");
        
    } while (1);
    return 0;
}
