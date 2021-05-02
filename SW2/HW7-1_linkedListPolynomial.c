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
    
    if (list->tail == NULL){ // 첫번째 노드 생성
        list->head = list->tail = new;
    }else{ // 마지막에 추가
        list->tail->link = new;
        list->tail = new;
    }
    list->size++;
    
}

void insert(ListType* list, Node* pre, int coef, int expon){
    
    Node* new = (Node*)malloc(sizeof(Node));
    new->coef = coef;
    new->expon = expon;
    
    if(pre == NULL){ // 맨 앞에 추가하는 경우
        new->link = list->head; // 새 노드가 맨 앞 노드를 가리키도록 함
        list->head = new; // head가 새 노드를 가리키도록 함
    }else{ // 노드 사이에 추가하는 경우
        new->link = pre->link; // 새 노드가 추가될 곳 다음(이전 노드가 가리키던 곳)을 가리키도록 함
        pre->link = new; // 이전 노드가 새 노드를 가리키도록 함
    }
    
    list->size++;
}


void poly_add(ListType* list1, ListType* list2, ListType* list3){
    
    Node* a = list1->head;
    Node* b = list2->head;
    int sum;
    
    while(a && b){
        
        if (a->expon == b->expon){ // 지수가 같으면
            sum = a->coef + b->coef; // 계수를 더하여
            if (sum != 0) insert_last(list3, sum, a->expon); // 연결리스트 삽입
            a = a->link; // 다음
            b = b->link; // 노드
            
        }else if(a->expon > b->expon){ //지수가 다르면 더 큰 차수의 항을 삽입
            insert_last(list3, a->coef, a->expon);
            a = a->link;
            
        }else{
            insert_last(list3, b->coef, b->expon);
            b = b->link;
        }
    }
    
    
    for (; a != NULL; a = a->link) // 비교연산 후 남은 항들을 삽입
        insert_last(list3, a->coef, a->expon);
    
    for (; b != NULL; b = b->link)
        insert_last(list3, b->coef, b->expon);
}

multiply is_exist(ListType* list, int expon){
    // 중복값 검사 및 인덱스 지정
    multiply state;
    Node* a = list->head; // 탐색할 현재 노드
    Node* pre = list->head; // 탐색한 이전 노드
    int target = expon;
    
    while (a) {
        // 중복되는 차수를 찾았을 때
        if (target == a->expon){
            state.idx = a; // 게수를 더해줄 노드
            state.flag = 0;
            return state;
        }
            
        if (target > a->expon){
            // 해당 차수는 존재하지 않고 차수 사이에 끼워넣어야 할 경우
            state.idx = pre; // 삽입하기 이전 노드
            state.flag = 1;
            return state;
        }
        
        pre = a;
        a = a->link;
    }

    // 해당 차수는 존재하지 않고 맨 뒤에 추가해야하는 경우
    state.idx = pre; // 삽입하기 이전 노드(마지막 노드), while문이 끝나기 직전에 pre=a 시행했으므로
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

            if (i>=1){ // 두번째 곱 이후로 항의 위치 지정
                state = is_exist(list4, tempexpon); // 이미 해당 차수의 항이 있는지 확인
                
                switch (state.flag) {
                    case 0: // 해당 차수의 항이 존재
                        state.idx->coef += tempcoef; // 계수를 해당 항에 더해줌
                        break;
                        
                    case 1:
                        insert(list4, state.idx, tempcoef, tempexpon); // 중간에 끼워넣음
                        break;
                        
                    case 2:
                        insert_last(list4, tempcoef, tempexpon); // 마지막에 추가
                        break;
                        
                }
            }else{ // 첫번째 곱은 마지막에 추가
                insert_last(list4, tempcoef, tempexpon);
            }
            
            b = b->link;
        }
        a = a->link; // 첫번째 식의 다음 노드로
        b = list2->head; // 두번째 식의 처음으로
    }
    
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


int main(){
    
    char a_input[50], b_input[50];
    int flag = 0;
    ListType *list1, *list2, *list3, *list4;
    
    list1 = create(); // 식 1
    list2 = create(); // 식 2
    list3 = create(); // 덧셈식
    list4 = create(); // 곱셈식
    
    printf("수식 1을 입력하세요 : ");
    scanf(" %[^\n]", a_input); // 공백 포함 입력
    
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
