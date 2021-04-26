#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
typedef char element;

typedef struct{
    element* data;
    int top;
    int capacity;
}Stack;

void init_stack(Stack *s){
    s->top = -1;
    s->capacity = 1;
    s->data = (element*)malloc(s->capacity * sizeof(element));
}

int is_empty(Stack *s){
    
    return (s-> top == -1);
    
}

int is_full(Stack *s){
    
    return (s-> top == (s->capacity-1));
}

void push(Stack *s, element item){
    
    if (is_full(s)){
        s->capacity *= 2;
        s->data = (element*)realloc(s->data, s->capacity * sizeof(element));
    }
    
    s->top++;
    s->data[s->top] = item;
    
}

element pop(Stack *s){
    
    if (is_empty(s)){
        fprintf(stderr, "스택공백에러\n");
        exit(1);
    }else return s->data[(s->top)--];
    
}

element peek(Stack *s){
    
    if (is_empty(s)){
        fprintf(stderr, "스택공백에러\n");
        exit(1);
    }else return s->data[s->top];
    
}

typedef struct{
    int* data;
    int top;
    int capacity;
}Stack_int;

void init_stack_int(Stack_int *i){
    i->top = -1;
    i->capacity = 1;
    i->data = (int*)malloc(i->capacity * sizeof(int));
}

int is_empty_int(Stack_int *i){
    
    return (i-> top == -1);
    
}

int is_full_int(Stack_int *i){
    
    return (i-> top == (i->capacity-1));
}

void push_int(Stack_int *i, int item){
    
    if (is_full(i)){
        i->capacity *= 2;
        i->data = (int*)realloc(i->data, i->capacity * sizeof(int));
    }
    
    i->top++;
    i->data[i->top] = item;
    
}

int pop_int(Stack_int *i){
    
    if (is_empty(i)){
        fprintf(stderr, "스택공백에러\n");
        exit(1);
    }else return i->data[(i->top)--];
    
}

int peek_int(Stack_int *i){
    
    if (is_empty(i)){
        fprintf(stderr, "스택공백에러\n");
        exit(1);
    }else return i->data[i->top];
    
}


void cal_postfix(char* math_exp, int len){
    
    int result, term1, term2;
    Stack_int s;
    init_stack_int(&s);
    int num= 0;
    int i=0, j=0;
    char temp[4];
    // 2+(3*4^2-12)
    // 2342^*\012\0-+
    // 2342^* 12 -+
    //char* ptr = strtok(math_exp, " ");
    
    
    while(i != len){
        if (math_exp[i] != '(' && math_exp[i] != ')' && math_exp[i] != '^' && math_exp[i] != '*' && math_exp[i] != '%' &&
            math_exp[i] != '+' && math_exp[i] != '-' ){
            
            if(math_exp[i] == ' '){
                i++;
                //printf("?\n");
                while (math_exp[i] != ','){
                    //num = num * 10 + math_exp[i++] - '0';
                    temp[j++] = math_exp[i++];
                    printf("!!!!! %d(i) / %c<-%c\n", i, temp[j], math_exp[i]);
                    
                }
                push_int(&s, atoi(temp));
                i++;
                //printf("%d\n", peek(&s));
                    //printf("%d\n", peek(&s));
                
                
            }else push_int(&s, atoi(&math_exp[i++]));
            
            
        }else{
            
            term1 = pop_int(&s);
            printf("term1 : %d\n", term1);
            term2 = pop_int(&s);
            printf("term2 : %d\n", term2);
            switch (math_exp[i++]) {
                case '^':
                    printf("operation : %c\n", math_exp[i-1]);
                    j=term2;
                    for(int i=0; i<term1;i++) j = j*term2;
                    push_int(&s, j);
                    printf("result : %d\n", peek_int(&s));
                    break;
                    
                case '*':
                    printf("operation : %c\n", math_exp[i-1]);
                    push_int(&s, term2 * term1);
                    printf("result : %d\n", peek_int(&s));
                    break;
                    
                case '%':
                    printf("operation : %c\n", math_exp[i-1]);
                    push_int(&s, term2 % term1);
                    printf("result : %d\n", peek_int(&s));
                    break;
                    
                case '+':
                    printf("operation : %c\n", math_exp[i-1]);
                    push_int(&s, term2 + term1);
                    printf("result : %d\n", peek_int(&s));
                    break;
                    
                case '-':
                    printf("operation : %c\n", math_exp[i-1]);
                    push_int(&s, term2 -term1);
                    printf("result : %d\n", peek_int(&s));
                    break;

            }
            printf("----------------\n");
                
        }
    }
    
    result = pop_int(&s);
    
    printf("=%d\n", result);
}

/*
void cal_postfix(char* math_exp, int len){
    
    int result, term1, term2;
    Stack s;
    init_stack(&s);
    char temp[4];
    int i, j=0;
    
    for (i = 0; i < len; i++){
        if (math_exp[i] != '(' && math_exp[i] != ')' && math_exp[i] != '^' && math_exp[i] != '*' && math_exp[i] != '%' &&
            math_exp[i] != '+' && math_exp[i] != '-' ){
            
            if(math_exp[i] == ' '){
                while (math_exp[i] != '(' && math_exp[i] != ')' && math_exp[i] != '^' && math_exp[i] != '*' && math_exp[i] != '%' &&
                       math_exp[i] != '+' && math_exp[i] != '-' ){
                    temp[j++] = math_exp[i++];
                    printf("!!!!! %d(i) / %c<-%c\n", i, temp[j], math_exp[i]);
                    
                    push(&s, atoi(temp));
                    printf("%d\n", atoi(temp));
                    printf("%d\n", peek(&s));
                }
                
            }else push(&s, math_exp[i] - '0');
            
            
        }else{
            
            term1 = pop(&s);
            term2 = pop(&s);
            switch (math_exp[i]) {
                case '^':
                    push(&s, pow(term2, term1));
                    break;
                    
                case '*':
                    push(&s, term2 * term1);
                    break;
                    
                case '%':
                    push(&s, term2 % term1);
                    break;
                    
                case '+':
                    push(&s, term2 + term1);
                    break;
                    
                case '-':
                    push(&s, term2 -term1);
                    break;

            }
                
        }
    }
    
    result = pop(&s);
    
    printf("=%d\n", result);
}
*/


int get_priority(char ch){
    
    switch (ch) {
        case '(': case ')':
            return 0;
            
        case '^':
            return 1;
            
        case '*': case '%':
            return 2;
            
        case '+': case '-':
            return 3;
    }
    
    return -1;
}

void postfix(char* math_exp, int len){
    
    Stack s;
    init_stack(&s);
    char* post_exp = (char*)malloc(sizeof(char)*len*2);
    int priority, i, j=0;
    char ch;
    //2+(3*4^2-12)
    //2342^*12-+
    //+(*^-
    // 1순위 ( )
    // 2순위 ^
    // 3순위 * %
    // 4순위 + -
    //2+(3*4)^2-12
    //234*2^12-+
    //+(*)^
    
    for (i = 0; i < len; i++){
        
        if (math_exp[i] != '(' && math_exp[i] != ')' && math_exp[i] != '^' && math_exp[i] != '*' && math_exp[i] != '%' &&
            math_exp[i] != '+' && math_exp[i] != '-' ){
            
            if(math_exp[i+1] != '(' && math_exp[i+1] != ')' && math_exp[i+1] != '^' && math_exp[i+1] != '*' && math_exp[i+1] != '%' &&
               math_exp[i+1] != '+' && math_exp[i+1] != '-' && math_exp[i+1] != '\0'){
                
                printf("!!\n");
                post_exp[j] = ' ';
                j++;
                post_exp[j] = math_exp[i];
                j++;

                
            }else{
                if(math_exp[i-1] != '(' && math_exp[i-1] != ')' && math_exp[i-1] != '^' && math_exp[i-1] != '*' && math_exp[i-1] != '%' &&
                   math_exp[i-1] != '+' && math_exp[i-1] != '-' && math_exp[i-1] != '\0'){
                    post_exp[j] = math_exp[i];
                    j++;
                    post_exp[j] = ',';
                    j++;
                    
                    
                }else{
                    post_exp[j] = math_exp[i];
                    j++;
                    
                }

            }
            
        }else{
            
            priority = get_priority(math_exp[i]);
            if (is_empty(&s) || priority == 0) {
                push(&s, math_exp[i]);
                printf("push %c\n", math_exp[i]);
            }
            else{
                if (get_priority(peek(&s)) < priority && peek(&s) != '(' && peek(&s) != ')'){ //우선순위 낮으면
                    while (get_priority(peek(&s)) < priority && peek(&s) != '(' && peek(&s) != ')'){
                        post_exp[j] = pop(&s);
                        printf("pop %c\n", post_exp[j]);
                        j++;
                    }
                    push(&s, math_exp[i]);
                }else if(get_priority(peek(&s)) < priority && peek(&s) == ')'){
                    printf("? %c\n", math_exp[i]);
                    while (peek(&s) != '('){
                        ch = pop(&s);
                        printf("!pop %c\n", ch);
                        if (ch != '(' && ch != ')') {
                            post_exp[j] = ch;
                            j++;
                        }
                        
                    }
                    push(&s, math_exp[i]);
                    printf("push %c\n", math_exp[i]);
                    
                }else{
                    push(&s, math_exp[i]);
                    printf("push %c\n", math_exp[i]);
                }
                
                //2+(3*4)^2-12
                //234
                //+(*)^
                
            }
            
        }
    }
            
    
    while(!is_empty(&s)){
        ch = pop(&s);
        if (ch != '(' && ch != ')') {
            post_exp[j] = ch;
            j++;
        }
    }
    
    for (int i = 0; i<len; i++)
        printf("%c", post_exp[i]);
    
    printf("\n");
    cal_postfix(post_exp, len);
                
        
}
    
    
    
    


int check_exp(char* math_exp, int len){
    
    Stack s;
    init_stack(&s);
    
    int index = -1;
    char front;
    
    for (int i = 0; i<len; i++){
        switch(math_exp[i]){
            case '+': case '-': case '%': case '*': case '^':
                switch (math_exp[i+1]) {
                     case '+': case '-': case '%': case '*': case '^':
                        index = i+1;
                        return index;
                }
            }
    }
    
    
    for (int i = 0; i<len; i++){
        switch(math_exp[i]){
            case '(' :
                push(&s, math_exp[i]);
                break;
        
            case ')' :
                if (is_empty(&s)){
                    index = 0;
                    return index;
      
                }else {
                    front = pop(&s);
                    if (front == '(') break;
                }
            }
    }
    
    if (!is_empty(&s)) {
        index = len;
        return index;
    }
        
    return index;
    
}

int main(){
    
    char math_exp[100];
    int index, len, result;
    printf("수식을 입력하세요 : ");
    scanf(" %[^\n]", math_exp);
    
    len = strlen(math_exp);
    index = check_exp(math_exp, len);
    //printf("%d\n", index);
    if (index != -1){
        for (int i = 0; i < len; i++){
            printf("%c", math_exp[i]);
        }
        printf("\n");
        
        for (int i = 0; i < index; i++){
            printf(" ");
        }
        printf("^이 위치에 오류가 있습니다.\n");
        exit(1);
    }else{
    
        postfix(math_exp, len);
        //result = cal_postfix(math_exp, len);
        //printf("%d", result);
          
    }
    
    
    return 0;
}

