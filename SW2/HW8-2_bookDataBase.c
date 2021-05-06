#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct book_info
{
    char book_name[20];
    char author[20];
    int price;
    char date[8];
}book_info;

typedef book_info* element;

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
    element dummy = NULL;
    list->head = new_node(dummy); // 더미노드 생성
    list->tail = new_node(dummy);
    list->head->next = list->tail; // tail과 head 연결
    list->tail->prev = list->head;
}

void insert(List* list, ListNode* next_node, element data){
    
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

void delete(List* list, ListNode* removed){
    
    removed->prev->next = removed->next; // 이전 노드의 다음을 삭제할 노드의 다음으로 설정
    removed->next->prev = removed->prev; // 다음 노드의 이전을 삭제할 노드의 이전으로 설정
    free(removed);
    
}

void print_from_front(List* list){
    printf("\n오름차순 정렬\n");
    ListNode* p = list->head->next;
    while (p != list->tail){
        printf("도서명: %s | ", p->data->book_name);
        printf("저자 : %s | ", p->data->author);
        printf("가격 : %d | ", p->data->price);
        printf("출판일 : %s |", p->data->date);
        printf("\n");
        
        p = p->next;
    }
}

void print_from_rear(List* list){
    printf("\n내림차순 정렬\n");
    ListNode* p = list->tail->prev;
    while (p != list->head){
        printf("도서명: %s | ", p->data->book_name);
        printf("저자 : %s | ", p->data->author);
        printf("가격 : %d | ", p->data->price);
        printf("출판일 : %s |", p->data->date);
        printf("\n");
        
        p = p->prev;
    }
}


int classify_book(char date[]){
    
    int status;

    char temp[5];
    for(int i = 0; i < 4; i++){
        temp[i] = date[i];
    }
    temp[4] = '\0';

    if (atoi(temp)>2000){
        status = 1;
    }
    else status = 0;
    
    return status;
}

int get_year(char* date){
    
    char new_date[7];
    int len = strlen(date);
    int j = 0;
    
    for (int i=0; i<len; i++){
        if (isdigit(date[i])){
            new_date[j] = date[i];
            j++;
        }
    }
    int temp = atoi(new_date);
    
    return temp;
    
}

ListNode* where_to_insert(List* group, char* date){
    
    int new_data;
    new_data = get_year(date);
    ListNode* p = group->head->next;
    
    while (p != group->tail){
        
        if (get_year(p->data->date) > new_data){
            break;
        }
        p = p->next;
    }
    
    return p;
}


void store_book(List* group, element bi){
    
    ListNode* next = where_to_insert(group, bi->date);
    insert(group, next, bi);
    
}

List* merge_group(List* group_a, List* group_b){
    
    ListNode* a = group_a->head->next;
    ListNode* b = group_b->head->next;
    
    while (1){
        if (get_year(a->data->date) > get_year(b->data->date)){
            insert(group_a, a, b->data);
            b = b->next;
        }else
            a = a->next;
        
        if(a == group_a->tail || b == group_b->tail)
            break;
    }
    
    if (b != group_b->tail){
        group_a->tail->prev->next = b;
        group_b->head->next->prev = group_a->tail->prev;
        group_a->tail = group_b->tail;
        return group_a;
    }
    
    if (a != group_a->tail){
        group_b->tail->prev->next = a;
        group_a->head->next->prev = group_b->tail->prev;
        group_b->tail = group_a->tail;
        return group_b;
    }
    
    return group_a;
}

int main(){

    List group_a;
    List group_b;
    init(&group_a);
    init(&group_b);
    
    int grp;
    book_info bi[10];
    
    for (int i=0; i<10; i++){
        
        printf("------------------------------------\n");
        printf("책이름을 입력하세요 : ");
        scanf("%s", bi[i].book_name);
        printf("저자이름을 입력하세요 : ");
        scanf("%s", bi[i].author);
        printf("가격을 입력하세요 : ");
        scanf("%d", &bi[i].price);
        printf("출판년월을 입력하세요. 예시(2020/12) : ");
        scanf("%s", bi[i].date);
        printf("------------------------------------\n");

        grp = classify_book(bi[i].date);

        if (grp == 0)
            store_book(&group_a,&bi[i]);
        else
            store_book(&group_b,&bi[i]);
    }
    
    List* merged = merge_group(&group_a, &group_b);
    print_from_front(merged);
    print_from_rear(merged);

    return 0;
}

