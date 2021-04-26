#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_NUM 20

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
    d->front = MAX_NUM/2;
    d->rear =  MAX_NUM/2;
}

int is_empty(Deque *d){
    return (d->front == d->rear);
}

int is_full_front(Deque *d){
    return (d->front == 0);
}

int is_full_rear(Deque *d){
    return (d->rear + 1 == MAX_NUM);
}

void add_rear(Deque *d, element item){
    
    if(is_full_rear(d)){
        error("큐의 뒷부분이 포화상태입니다.");
    }

    d->data[++(d->rear)] = item;
}

void add_front(Deque *d, element item){
    
    if(is_full_front(d)){
        error("큐의 앞부분이 포화상태입니다.");
    }
    d->data[(d->front)--] = item;
    
}

element delete_front(Deque *d){
    
    if(is_empty(d)){
        error("큐가 공백상태입니다.");
    }
    return d->data[++(d->front)];
}

element delete_rear(Deque *d){
    
    if(is_empty(d)){
        error("큐가 공백상태입니다.");
    }
    
    int prev = d->rear;
    d->rear = d->rear - 1;
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

void print_queue_from_front(Deque *d){
    
    if(!is_empty(d)){
        
        int i = d->front+1;
        
        printf("From front: \n|");
        do{
            printf(" %d |", d->data[i++]);
            if (i == d->rear+1) break;
            
        }while (i != d->front);
        printf("\n");
    }else printf("From rear: \n| |");
    
}


void print_queue_from_rear(Deque *d){
    
    if(!is_empty(d)){
        
        int i = (d->rear);
        printf("From rear: \n|");
        do{
            printf(" %d |", d->data[i--]);
            if (i== d->front) break;
            
        }while (i != d->front);
        printf("\n");
    }else printf("From rear: \n| |");
    
}

int main(){
    
    Deque d;
    init_deque(&d);
    
    int mode = 0, random = 0, add = 0, del = 0, pass = 0;
    srand((int)time(NULL));
    
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
                pass++;
                printf("nothing to delete\n");printf("\n");
                continue;}
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
                pass++;printf("nothing to delete\n");
                printf("\n");
                continue;}
            else {
                delete_rear(&d);
                del++;
            }
        }
        
        printf("\n");
    }
    
    print_queue_from_front(&d);
    printf("\n");
    print_queue_from_rear(&d);
    
    printf("\nAdded : %d, Deleted : %d, Passed : %d\n", add, del, pass);
    
    return 0;
    
}
