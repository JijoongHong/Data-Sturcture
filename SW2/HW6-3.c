#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_NUM 21

typedef int element;
typedef struct {
    element data[MAX_NUM];
    int front;
    int rear;
}Deque;

void error(char* message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_deque(Deque *d){
    d->front = 0;
    d->rear = 0;
}

int is_empty(Deque *d){
    return (d->front == d->rear); //플래그 주어서 공백안써도 됨
}

int is_full(Deque *d){
    return ((d->rear + 1) % MAX_NUM == d->front); //원형덱은 프론트 감소시켜도 됨
}

void add_rear(Deque *d, element item){
    
    if(is_full(d)){
        error("큐가 포화상태입니다.");
    }
    d->rear = (d->rear + 1) % MAX_NUM;
    d->data[d->rear] = item;
}

void add_front(Deque *d, element item){
    
    if(is_full(d)){
        error("큐가 포화상태입니다.");
    }
    d->data[d->front] = item;
    d->front = (d->front + MAX_NUM - 1) % MAX_NUM;
    printf("add front %d\n", d->front);
    
}

element delete_front(Deque *d){
    
    if(is_empty(d)){
        error("큐가 공백상태입니다.");
    }
    d->front = d->front + 1;
    return d->data[d->front];
}

element delete_rear(Deque *d){
    
    if(is_empty(d)){
        error("큐가 공백상태입니다.");
    }
    
    int prev = d->rear;
    d->rear = (d->rear - 1 + MAX_NUM) % MAX_NUM;
    return d->data[prev];
}

element get_front(Deque *d){
    
    if(is_empty(d)){
        error("큐가 공백상태입니다.");
    }
    return d->data[d->front];
    
}

element get_rear(Deque *d){
    
    if(is_empty(d)){
        error("큐가 공백상태입니다.");
    }
    return d->data[d->rear];
    
}

void print_deque_from_front(Deque *d){
    
    if(!is_empty(d)){
        
        int i = d->front;
        
        printf("From front: \n|");
        do{
            i = (i+1) % MAX_NUM;
            printf(" %d |", d->data[i]);
            if (i == d->rear) break;
            
        }while (i != d->front);
        printf("\n");
    }else printf("From rear: \n| |");
    
}


void print_deque_from_rear(Deque *d){
    
    if(!is_empty(d)){
        
        int i = d->rear + 1;
        printf("From rear: \n|");
        do{
            i = (i-1) % MAX_NUM;
            printf(" %d |", d->data[i]);
            if (i == d->front + 1) break;
            
        }while (i != d->front);
        printf("\n");
    }else printf("From rear: \n| |");
    

}


int main(){
    
    Deque d;
    init_deque(&d);
    
    int mode = 0, random = 0, add = 0, del = 0, pass = 0;
    srand(time(NULL));
    
    for(int i = 0; i < 30; i++){
        
        mode = rand()%4 + 1;
        printf("mode : %d\n", mode);
        
        if (mode == 1){
            random = rand()%100 + 1;
            printf("random : %d\n", random);
            add_front(&d, random);
            add++;
        
        }else if (mode == 2){
            if (is_empty(&d)) {
                pass++;printf("nothing to delete\n");printf("\n"); continue;}
            else{
                delete_front(&d);
                del++;
            }
            
        }else if (mode == 3){
            random = rand()%100 + 1;
            printf("random : %d\n", random);
            add_rear(&d, random);
            add++;
            
        }else{
            if (is_empty(&d)) {
                pass++;printf("nothing to delete\n");printf("\n"); continue;}
            else {
                delete_rear(&d);
                del++;
            }
        }
        
        printf("\n");
    }
    
    print_deque_from_front(&d);
    printf("\n");
    print_deque_from_rear(&d);
    
    printf("\nAdded : %d, Deleted : %d, Passed : %d\n", add, del, pass);
    
    return 0;
    
}
