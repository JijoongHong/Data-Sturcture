#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_NUM 21

typedef int element;

typedef struct ListNode{
    element data;
    struct ListNode* next;
    struct ListNode* prev;
}ListNode;

typedef struct List{
    ListNode* head;
    ListNode* tail;
}List;

ListNode* new_node(element data){
    
    ListNode *new = (ListNode*)malloc(sizeof(ListNode));
    new->data = data;
    new->prev = new->next = NULL;
    
    return new;
}

void init(List* list){
    list->head = new_node(0); // 더미노드 생성
    list->tail = new_node(0);
    list->head->next = list->tail; // tail과 head 연결
    list->tail->prev = list->head;
}


int is_empty(List* list){
    return (list->head->next == list->tail && list->tail->prev == list->head); //플래그 주어서 공백안써도 됨
}

void enqueue(List* list, ListNode* next_node, element data){
    
    ListNode* new = new_node(data);
    new->prev = next_node->prev; //새로운 노드의 이전을 다음 노드가 가리키던 곳으로 설정
                                 //마지막에 추가되는 경우 새로운 노드의 이전을 원래 마지막 노드로 설정
    new->next = next_node; // 새로운 노드의 다음을 다음 노드로 설정
                           // 마지막에 추가되는 경우 새로운 노드의 다음을 tail로 설정
    next_node->prev->next = new; // 추가되는 곳 이전(다음 노드의 이전)이 새로운 노드를 가리키도록 함
                                 // 마지막에 추가되는 경우 원래 마지막 노드가 새로운 노드를 가리키도록 함
    next_node->prev = new; // 다음 노드의 이전을 새로운 노드로 설정
                           // tail의 이전을 새로운 노드로 설정
    
}

element dequeue(List* list, ListNode* removed){
    int temp = removed->data;
    removed->prev->next = removed->next; // 이전 노드의 다음을 삭제할 노드의 다음으로 설정
    removed->next->prev = removed->prev; // 다음 노드의 이전을 삭제할 노드의 이전으로 설정
    free(removed);
    return temp;
}

void print_from_front(List* list){
    printf("\nFrom front to rear\n");
    ListNode* p = list->head->next;
    printf("| ");
    while (p != list->tail){
        printf("%d | ", p->data);
        
        p = p->next;
    }
    printf("\n");
}

void print_from_rear(List* list){
    printf("\nFrom rear to front\n");
    ListNode* p = list->tail->prev;
    printf("| ");
    while (p != list->head){
        printf("%d | ", p->data);
        
        p = p->prev;
    }
    printf("\n\n");
}


int main(){
    
    List d;
    init(&d);
    
    int mode = 0, random = 0, add = 0, del = 0, pass = 0;
    srand(time(NULL));
    
    printf("----------------log----------------\n");
    
    for(int i = 0; i < 30; i++){
        
        mode = rand()%4 + 1;
        
        if (mode == 1){
            random = rand()%100 + 1;
            printf("Front add(%d)\n", random);
            enqueue(&d, d.head->next, random);
            add++;
        
        }else if (mode == 2){
            if (is_empty(&d)) {
                pass++;
                printf("Front delete(nothing to delete)\n");
                continue;
                
            }else{
                random = dequeue(&d, d.head->next);
                printf("Front delete(%d)\n", random);
                del++;
            }
            
        }else if (mode == 3){
            random = rand()%100 + 1;
            printf("Rear add(%d)\n", random);
            enqueue(&d, d.tail,random);
            add++;
            
        }else{
            if (is_empty(&d)) {
                pass++;
                printf("Rear delete(nothing to delete)\n");
                continue;
                
            }
            else {
                random = dequeue(&d, d.tail->prev);
                printf("Rear delete(%d)\n", random);
                del++;
            }
        }
    }
    
    printf("\nAdded : %d, Deleted : %d, Passed : %d\n", add, del, pass);
    printf("-------------------------------------\n");
    
    print_from_front(&d);
    print_from_rear(&d);

    return 0;

}
