#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
typedef char element;

typedef struct StackNode{
    element data;
    struct StackNode* link;
}StackNode;


typedef struct Stack{
    StackNode* top;
}Stack;

void init_stack(Stack *s){
    s->top = NULL;
}

int is_empty(Stack *s){
    return (s->top == NULL);
}

void push(Stack *s, element item){
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
}

element pop(Stack *s){
    if (is_empty(s)){
        fprintf(stderr, "스택공백에러\n");
        exit(1);
    }else{
        StackNode *temp = s->top;
        element data = temp->data;
        s->top = s->top->link;
        free(temp);
        return data;
    }
}

element peek(Stack *s){
    if (is_empty(s)){
        fprintf(stderr, "스택공백에러\n");
        exit(1);
    }else{
        return s->top->data;
    }
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
            term2 = pop(&s);
            switch (math_exp[i++]) {
                    
                case '*':
                    push(&s, term2 * term1);
                    break;
                    
                case '/':
                    push(&s, term2 / term1);
                    break;
                    
                case '+':
                    push(&s, term2 + term1);
                    break;
                    
                case '-':
                    push(&s, term2 - term1);
                    break;
            }
        }
    }
    printf("= %d\n", pop(&s));
}


int get_priority(char ch){
    
    switch (ch) {
        case '[': case ']': case '{': case '}': case '(': case ')':
            return 0;
        
        case '*': case '/':
            return 1;
            
        case '+': case '-':
            return 2;
    }
    
    return -1;
}

void postfix(char* math_exp, int len){
    
    Stack s;
    init_stack(&s);
    char* post_exp = (char*)malloc(sizeof(char)*len*2);
    int priority, i, j=0, prev, post, brace_count=0, tens_count=0;
    char ch;
    
    //[3*(14+6)]
    //3 14,6+*
    //[3*{6+10/(2+3)}]
    //36 10,23+/+*
    
    for (i = 0; i < len; i++){
        priority = get_priority(math_exp[i]);
        
        if (priority == 0) brace_count++;
        
        post = get_priority(math_exp[i+1]);
        prev = get_priority(math_exp[i-1]);
        
        if (priority == -1){ // 숫자인 경우
            
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
            
        }else{ // 연산자인 경우
            if (is_empty(&s) || priority == 0) { //스택이 비었거나 괄호이면 바로 저장
                push(&s, math_exp[i]);
            }
            else{
                if (get_priority(peek(&s)) < priority && get_priority(peek(&s)) != 0){ //괄호가 아니고, 우선순위 낮으면 연산자 옮기기
                    while (get_priority(peek(&s)) < priority){
                        post_exp[j] = pop(&s);
                        j++;
                    }
                    push(&s, math_exp[i]);
                    
                }else if(get_priority(peek(&s)) < priority && (peek(&s) == ')' || peek(&s) == '}'|| peek(&s) == ']')){ //괄호인 경우 괄호 안 연산자 옮기기
                    while (peek(&s) != '(' || peek(&s) != '{' || peek(&s) != '['){ //괄호 속 연산자 옮기기
                        post_exp[j] = pop(&s);
                        j++;
                    }
                    push(&s, math_exp[i]);
                    
                }else{
                    push(&s, math_exp[i]); //우선순위 높을 때 연산자 바로 저장
                }
            }
        }
    }
            
    while(!is_empty(&s)){ //남은 항목 저장
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
    
    //{3*[6+10/(2+3)]}
    //(33*[4+65])
    //[13*{42+6)]
    
    int flag[3] = {-1};
    int j = 0;
       
    for (int i = 0; i<len; i++){
        ch = math_exp[i];
        
        switch(ch){
            case '[' :
                flag[j++] = 0;
                push(&s, ch);
                break;
                
            case '{' :
                flag[j++] = 1;
                push(&s, ch);
                break;
                
            case '(' :
                flag[j++] = 2;
                push(&s, ch);
                break;

            case ')':
                if (is_empty(&s)) {
                    index = -2;
                    break;
                    
                }else {
                    front = pop(&s);
                    j--;
                    if ((front != '(') || flag[j-1] > flag[j]) //(1) 괄호 안닫힘 (2) 괄호 우선순위 안맞음
                         index = -2;
                    break;
                }
                
            case '}':
                if (is_empty(&s)) {
                    index = -2;
                    break;
                    
                }else {
                    front = pop(&s);
                    j--;
                    if ((front != '{') || flag[j-1] > flag[j])
                         index = -2;
                    break;
                }
                
            case ']':
                 if (is_empty(&s)) {
                    index = -2;
                    break;
                    
                }else {
                    front = pop(&s);
                    j--;
                    if ((front != '[') || flag[j-1] > flag[j])
                         index = -2;
                    break;
                }
        }
    }
    
    if (!is_empty(&s)){
        index = -2;
        return index;
    }
    
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

