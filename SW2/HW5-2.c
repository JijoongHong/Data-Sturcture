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

void cal_postfix(char* math_exp, int len){
    
    int term1, term2, i=0, num=0;;
    Stack s;
    init_stack(&s);
    
    while(i != len){
        if (math_exp[i] != '*' && math_exp[i] != '/' && math_exp[i] != '+' && math_exp[i] != '-' ){
            
            if(math_exp[i] == ' '){
                i++;
                while (math_exp[i] != ','){
                    num = num * 10 + math_exp[i++] - '0';
                }
                push(&s, num);
                i++;
                
            }else push(&s, math_exp[i++]-'0');
            
            
        }else{
            
            term1 = pop(&s);
            //printf("term1 : %d\n", term1);
            term2 = pop(&s);
            //printf("term2 : %d\n", term2);
            switch (math_exp[i++]) {
                    
                case '*':
                    //printf("operation : %c\n", math_exp[i-1]);
                    push(&s, term2 * term1);
                    //printf("result : %d\n", peek(&s));
                    break;
                    
                case '/':
                    //printf("operation : %c\n", math_exp[i-1]);
                    push(&s, term2 / term1);
                    //printf("result : %d\n", peek(&s));
                    break;
                    
                case '+':
                    //printf("operation : %c\n", math_exp[i-1]);
                    push(&s, term2 + term1);
                    //printf("result : %d\n", peek(&s));
                    break;
                    
                case '-':
                    //printf("operation : %c\n", math_exp[i-1]);
                    push(&s, term2 - term1);
                    //printf("result : %d\n", peek(&s));
                    break;

            }
            //printf("----------------\n");
                
        }
    }
    
    printf("= %d\n", pop(&s));
    free(s.data);
}


int get_priority(char ch){
    
    switch (ch) {
        case '[': case ']':
            return 0;
        
        case '{': case '}':
            return 1;
            
        case '(': case ')':
            return 2;
            
        case '*': case '/':
            return 3;
            
        case '+': case '-':
            return 4;
    }
    
    return -1;
}

void postfix(char* math_exp, int len){
    
    Stack s;
    init_stack(&s);
    char* post_exp = (char*)malloc(sizeof(char)*len*2);
    int priority, i, j=0, prev, post, brace_count=0, tens_count=0;
    char ch;

    //[3*{6+10/(2+3)}]
    //36 10,23+/+*
    
    for (i = 0; i < len; i++){
        priority = get_priority(math_exp[i]);
        if (priority == 0 || priority == 1 || priority == 2) brace_count++;
        post = get_priority(math_exp[i+1]);
        prev = get_priority(math_exp[i-1]);
        if (priority == -1){
            
            if(post == -1 && math_exp[i+1] != '\0'){ //2자리수 이상일 때 앞자리
                post_exp[j] = ' ';
                j++;
                post_exp[j] = math_exp[i];
                j++;
                
            }else{
                if(prev == -1 && math_exp[i-1] != '\0'){ //2자리수 이상일 때 뒷자리
                    post_exp[j] = math_exp[i];
                    j++;
                    post_exp[j] = ',';
                    j++;
                    tens_count++;
                    
                }else{
                    post_exp[j] = math_exp[i];
                    j++;
                }
            }
            
        }else{
            if (is_empty(&s) || priority == 0 || priority == 1 || priority == 2) { //비었거나 괄호-> 우선순위해놓고 의미가 없지않나?
                push(&s, math_exp[i]);
            }
            else{
                if (get_priority(peek(&s)) < priority && get_priority(peek(&s)) != 0 && get_priority(peek(&s)) != 1
                    && get_priority(peek(&s)) != 2){ //우선순위 낮으면 연산자 옮기기
                    while (get_priority(peek(&s)) < priority && get_priority(peek(&s)) != 0 && get_priority(peek(&s)) != 1
                    && get_priority(peek(&s)) != 2){
                        post_exp[j] = pop(&s);
                        j++;
                    }
                    push(&s, math_exp[i]);
                    
                }else if(get_priority(peek(&s)) < priority && (peek(&s) == ')' || peek(&s) == '}'|| peek(&s) == ']')){
                    while (peek(&s) != '(' || peek(&s) != '{' || peek(&s) != '['){ //괄호 속 연산자 옮기기
                        ch = pop(&s);
                        if ((ch != '(' && ch != ')') || (ch != '{' && ch != '}') || (ch != '[' && ch != ']')){
                            post_exp[j] = ch;
                            j++;
                        }
                    }
                    push(&s, math_exp[i]);
                    
                }else{
                    push(&s, math_exp[i]); //우선순위 높을 때
                }
                
            }
            
        }
    }
            
    while(!is_empty(&s)){
        ch = pop(&s);
        if ((ch != '(' && ch != ')') && (ch != '{' && ch != '}') && (ch != '[' && ch != ']')){
            post_exp[j] = ch;
            j++;
        }
    }
    printf("후위수식: ");
    for (int i = 0; i<len; i++)
        if(post_exp[i] != ' ' && post_exp[i] != ',') printf("%c", post_exp[i]);
    
    printf("\n");
    cal_postfix(post_exp, len-(brace_count)+(2*tens_count));
    free(post_exp);
    free(s.data);
    
}


int check_exp(char* math_exp, int len){
    
    Stack s;
    init_stack(&s);
    
    int index = -1;
    char front, ch;
    
    for (int i = 0; i<len; i++){
        ch = math_exp[i];
        switch(ch){
            case '+': case '-': case '/': case '*':
                switch (math_exp[i+1]) {
                     case '+': case '-': case '%': case '*': case '^':
                        index = i+1;
                        return index;
                }
        }
    }
    
    
    for (int i = 0; i<len; i++){
        ch = math_exp[i];
        
        switch(ch){
            case '(' : case '{' : case '[' :
                push(&s, math_exp[i]);
                break;
        
            case ')': case ']': case '}':
                if (is_empty(&s)) {
                    index = -2;
                    break;}
                else {
                    front = pop(&s);
                    if ((front == '(' && ch != ')') ||  (front == '[' && ch != ']') ||  (front == '{' && ch != '}')) //괄호 우선순위 없음
                        index = -2;
                        break;
                }
        }
    }
    
    if (!is_empty(&s)){
        index = -2;
        return index;
    }
    
    free(s.data);
    return index;
    
}

int main(){
    
    char math_exp[100];
    int index, len;
    printf("수식을 입력하세요 : ");
    scanf(" %[^\n]", math_exp);
    
    len = strlen(math_exp);
    index = check_exp(math_exp, len);

    if (index == -2){
        printf("괄호에 오류가 있습니다.\n");
        exit(1);
        
    }else if (index != -1){
        for (int i = 0; i < len; i++){
            printf("%c", math_exp[i]);
        }
        printf("\n");
        
        for (int i = 0; i < index; i++){
            printf(" ");
        }
        printf("^이 위치에 오류가 있습니다.\n");
        exit(1);
        
    }else postfix(math_exp, len);
    
    return 0;
}

