#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAX_STACK_SIZE 10
#define TRUE 1
#define FALSE 0

typedef struct book_info
{
    char book_name[20];
    char author[20];
    int price;
    char date[8];
    
}book_info;

// -------- Stack Area -------- //

typedef book_info* element;

typedef struct{
    element *data;
    int top;
    int capacity;
} Stack;


void init_stack(Stack *s){
    s->top = -1;
    s->capacity = 1;
    s->data = (element*)malloc(s->capacity * sizeof(element));
}

int is_full(Stack *s){
    
    return (s->top == (s->capacity - 1));
}

void push(Stack *s, element item){
    
    if(is_full(s)){
        
        s->capacity *= 2;
        s->data = (element*)realloc(s->data, s->capacity * sizeof(element));

    }
    (s->top)++;
    s->data[(s->top)] = item;
    
}

int is_empty(Stack *s){
    return (s->top == -1);
}

element pop(Stack *s){
    
    if (is_empty(s)){
        
        printf("스택 공백 에러\n");
        exit(1);
        
    }else return s->data[(s->top)--];
    
}

element peek(Stack *s){
    
    if (is_empty(s)){
        
        printf("스택 공백 에러\n");
        exit(1);
        
    }else return s->data[s->top];
}

// -------- End of Stack Area -------- //

int classify_book(char name[]){
    
    int status=0;
    char* keyword[4] = {"IS", "CS", "MS", "EEE"};
    
    for (int i = 0; i < 4; i++){
        if (strstr(name, keyword[i]) != NULL){
            status = i+1;
            break;
        }
    }

    return status;
}

void store_book(Stack *s, book_info* bi){

    Stack temp;
    init_stack(&temp);
    
    if (is_empty(s)){
        push(s, bi);
        printf("log: %s(%s) has pushed to stack\n", bi->book_name, bi->author);
    }
    else {
        if ((strcmp(peek(s)->author, bi->author) > 0)){
            int i = 0;
            while (strcmp(peek(s)->author, bi->author) > 0){
                push(&temp, pop(s)); // 옮김
                printf("log: %s(%s) in stack has moved to temp stack\n", temp.data[i]->book_name, temp.data[i]->author);
                i++;
                if (s->top == -1) break;
            }
            push(s, bi);
            printf("log: %s(%s) has pushed to stack\n", bi->book_name, bi->author);//끼워넣기
            
            int j = 0;
            while (temp.top > -1){
                printf("log: %s(%s) in temp has moved to stack\n", temp.data[i]->book_name, temp.data[j]->author);
                push(s, pop(&temp)); // 다시채움
                j++;
            }
            
        }else{
            push(s, bi); //맨 위에 추가
             printf("log: %s(%s) has pushed to stack\n", bi->book_name, bi->author);
        }
    }
}


int is_exist(Stack *overlapped, element item){
    
    Stack temp;
    init_stack(&temp);
    
    for (int i=0; i<overlapped->top; i++){
        if (strcmp(peek(overlapped)->author, item->author) == 0){ //중복발견
            
            if (is_empty(&temp)) return TRUE; //맨 위에서 중복 발견
            else{
                while (temp.top > -1){
                    push(overlapped, pop(&temp)); // 다시 채움
                    
                return TRUE;
                }
            }

        }else {
            if (is_empty(overlapped)){ //끝까지 다 확인
                while (temp.top > -1) push(overlapped, pop(&temp));
                break;
            }else {
                push(&temp, pop(overlapped));
            }
        }
    }
    
    return FALSE;
}


int find_author(Stack *is, Stack *cs, Stack *ms, Stack *eee, int len_is, int len_cs, int len_ms, int len_eee){
     
    Stack overlapped;
    init_stack(&overlapped);
    int flag = 0;//찾으면 중단
    
    //IS 분야에서 cs, ms, eee 분야의 중복 저자를 찾고, 찾으면 중단(이후의 중복은 고려하지 않음)
    for(int i=0; i<len_is; i++){
        for(int j=0; j<len_cs; j++){
            
            if (strcmp(is->data[i]->author, cs->data[j]->author) == 0){
                if (!is_exist(&overlapped, cs->data[j])) push(&overlapped, cs->data[j]);
                flag = 1;
                break;
            }
        }
        
        if(flag == 1){
            flag = 0;
            continue;
            }
            
        for(int k=0; k<len_ms; k++){
            
            if (strcmp(is->data[i]->author, ms->data[k]->author) == 0){
                if (!is_exist(&overlapped, ms->data[k])) push(&overlapped, ms->data[k]);
                flag = 1;
                break;
            }
        }
        
        if(flag == 1){
            flag = 0;
            continue;
            }
        
        for(int l=0; l<len_eee; l++){
            
            if (strcmp(is->data[i]->author, eee->data[l]->author) == 0){
                if (!is_exist(&overlapped, eee->data[l]))push(&overlapped, eee->data[l]);
                break;
            }
        }
    }// end of IS
        
    //CS 분야에서 ms, eee 분야의 중복 저자를 찾고, 찾으면 중단(이후의 중복은 고려하지 않음)
    for(int i=0; i<len_cs; i++){
        for(int j=0; j<len_ms; j++){
            
            if (strcmp(cs->data[i]->author, ms->data[j]->author) == 0){
                if (!is_exist(&overlapped, ms->data[j])) push(&overlapped, ms->data[j]);
                flag = 1;
                break;
            }
        }
        
        if(flag == 1){
            flag = 0;
            continue;
            }
            
        for(int k=0; k<len_eee; k++){
            
            if (strcmp(cs->data[i]->author, eee->data[k]->author) == 0){
                if (!is_exist(&overlapped, eee->data[k])) push(&overlapped, eee->data[k]);
                flag = 1;
                break;
            }
        }
        
        if(flag == 1){
            flag = 0;
            continue;
            }
    }// end of CS
    
    //MS 분야에서 eee 분야의 중복 저자를 찾고, 찾으면 중단(이후의 중복은 고려하지 않음)
    for(int i=0; i<len_ms; i++){
        for(int j=0; j<len_eee; j++){
            
            if (strcmp(ms->data[i]->author, eee->data[j]->author) == 0){
                if (!is_exist(&overlapped, eee->data[j]))push(&overlapped, eee->data[j]);
                break;
            }
        }
    }// end of MS
    
    return overlapped.top + 1;
}
            

int main(){
    
    book_info bi[10];
    
    int grp;
    int len_is = 0, len_cs = 0, len_ms = 0, len_eee = 0, num_of_author=0;
    
    Stack is, cs, ms, eee;
    init_stack(&is);
    init_stack(&cs);
    init_stack(&ms);
    init_stack(&eee);
    
    for (int i=0; i<5; i++){
        
        printf("---------------------------------------\n");
        
        printf("책이름을 입력하세요 : ");
        scanf(" %[^\n]", bi[i].book_name);

        printf("저자이름을 입력하세요 : ");
        scanf(" %s", bi[i].author);

        printf("가격을 입력하세요 : ");
        scanf(" %d", &bi[i].price);

        printf("출판년월을 입력하세요. 예시(2020/12) : ");
        scanf(" %s", bi[i].date);
        
        printf("---------------------------------------\n");

        grp = classify_book(bi[i].book_name);
        
        if (grp == 1) {
            store_book(&is, &bi[i]);
            len_is++;
        }
        else if (grp == 2 ) {
            store_book(&cs, &bi[i]);
            len_cs++;
        }else if (grp == 3) {
            store_book(&ms, &bi[i]);
            len_ms++;
        }else {
            store_book(&eee, &bi[i]);
            len_eee++;
        }
    }
    

    num_of_author = find_author(&is, &cs, &ms, &eee, len_is, len_cs, len_ms, len_eee);
    printf("\n중복된 저자 수 : %d\n", num_of_author);
    return 0;
}


