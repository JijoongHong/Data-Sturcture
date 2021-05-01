#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int coef;
    int expon;
    struct Node* link;
} Node;

typedef struct{
    int size;
    Node* head;
    Node* tail;
} ListType;

typedef struct {
    Node* idx;
    int flag;
} multiply;

void error(char *message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

ListType* create(void){
    
    ListType *list = (ListType*)malloc(sizeof(ListType));
    list->size = 0;
    list->head = list->tail = NULL;
    return list;
    
}

void insert_last(ListType* list, int coef, int expon){
    
    Node* new = (Node*)malloc(sizeof(Node));
    if (new == NULL) error("메모리 할당 에러");
    new->coef = coef;
    new->expon = expon;
    new->link = NULL;
    
    if (list->tail == NULL){
        list->head = list->tail = new;
    }else{
        list->tail->link = new;
        list->tail = new;
    }
    list->size++;
    
}

void insert(ListType* list, Node* pre, int coef, int expon){
    
    Node* new = (Node*)malloc(sizeof(Node));
    new->coef = coef;
    new->expon = expon;
    
    if(pre == NULL){
        new->link = list->head;
        list->head = new;
    }else{
        new->link = pre->link;
        pre->link = new;
    }
    
    list->size++;
}


void poly_add(ListType* list1, ListType* list2, ListType* list3){
    
    Node* a = list1->head;
    Node* b = list2->head;
    int sum;
    
    while(a && b){
        
        if (a->expon == b->expon){
            sum = a->coef + b->coef;
            if (sum != 0) insert_last(list3, sum, a->expon);
            a = a->link;
            b = b->link;
            
        }else if(a->expon > b->expon){
            insert_last(list3, a->coef, a->expon);
            a = a->link;
            
        }else{
            insert_last(list3, b->coef, b->expon);
            b = b->link;
        }
    }
    
    
    for (; a != NULL; a = a->link)
        insert_last(list3, a->coef, a->expon);
    
    for (; b != NULL; b = b->link)
        insert_last(list3, b->coef, b->expon);
}

void print_poly(ListType* list){
    
    Node* p = list->head;
    
    for(int i=0; i < list->size -1; i++){
        printf("%d^%d + ", p->coef, p->expon);
        p = p->link;
    }
    printf("%d^%d", list->tail->coef, list->tail->expon);
    printf("\n");
}


multiply is_exist(ListType* list, int expon){
    // 중복값 검사 및 인덱스 지정
    multiply state;
    Node* a = list->head;
    Node* pre = list->head;
    int target = expon;
    
    while (a) {
        // 중복되는 차수를 찾았을 때
        if (target == a->expon){
            state.idx = a;
            state.flag = 0;
            return state;
        }
            
        if (target > a->expon){
            // 차수 사이에 끼워넣어야 할 경우
            state.idx = pre;
            state.flag = 1;
            return state;
        }
        
        pre = a;
        a = a->link;
    }

    //맨 뒤에 추가해야하는 경우
    state.idx = pre;
    state.flag = 2;
    return state;

}

void poly_mul(ListType* list1, ListType* list2, ListType* list4){
    
    
    Node* a = list1->head;
    Node* b = list2->head;
    
    int tempcoef;
    int tempexpon;
    multiply state;
    
    for (int i = 0 ; i < list1->size; i++){
        for (int j = 0; j< list2->size; j++){

            tempcoef = a->coef * b->coef;
            tempexpon = a->expon + b->expon;

            if (i>=1){
                state = is_exist(list4, tempexpon);
                
                switch (state.flag) {
                    case 0:
                        state.idx->coef += tempcoef;
                        break;
                        
                    case 1:
                        insert(list4, state.idx, tempcoef, tempexpon);
                        break;
                        
                    case 2:
                        insert_last(list4, tempcoef, tempexpon);
                        break;
                        
                }
            }else{
                insert_last(list4, tempcoef, tempexpon);
            }
            
            b = b->link;
        }
        a = a->link;
        b = list2->head;
    }
    
}
    

int main(){
    
    char a_input[50], b_input[50];
    int flag = 0;
    ListType *list1, *list2, *list3, *list4;
    
    list1 = create();
    list2 = create();
    list3 = create();
    list4 = create();
    
    printf("수식 1을 입력하세요 : ");
    scanf(" %[^\n]", a_input);
    
    char *temp = strtok(a_input, " ");
    int coef, expon;
    
    while (temp != NULL){
        
        if (flag == 0){
            coef = atoi(temp);
            flag = 1;
        }else{
            expon = atoi(temp);
            flag = 0;
            insert_last(list1, coef, expon);
        }
        temp = strtok(NULL, " ");
    }
    
    printf("수식 2를 입력하세요 : ");
    scanf(" %[^\n]", b_input);

    temp = strtok(b_input, " ");
    while (temp != NULL){
        
        if (flag == 0){
            coef = atoi(temp);
            flag = 1;
        }else{
            expon = atoi(temp);
            flag = 0;
            insert_last(list2, coef, expon);
        }
        temp = strtok(NULL, " ");
    }
    
    printf("\n첫번째 다항식 : ");
    print_poly(list1);
    printf("두번째 다항식 : ");
    print_poly(list2);
    printf("\n---------------------------\n");
    printf("다항식 덧셈 : ");
    poly_add(list1, list2, list3);
    print_poly(list3);
    printf("다항식 곱셈 : ");
    poly_mul(list1, list2, list4);
    print_poly(list4);
    
    free(list1);
    free(list2);
    free(list3);
    free(list4);
    
    return 0;
}
