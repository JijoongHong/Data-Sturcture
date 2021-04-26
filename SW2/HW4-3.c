#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

typedef char element;

typedef struct{
    char data[MAX_SIZE];
    int top;
} Stack;


/// Stack Area
void init_stack(Stack *s){
    s->top = -1;
}

int is_full(Stack *s){
    
    return (s->top == (MAX_SIZE)-1);
}

void push(Stack *s, element item){
    
    if(is_full(s)){
        
        printf("스택 포화 에러\n");
        return;
    }else{
        (s->top)++;
        s->data[(s->top)] = item;
    }
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

/// Stack Area


int check_matching(char* mex){
    
    Stack s;
    init_stack(&s);
    int len = strlen(mex);
    char ch, front;
    
    for (int i = 0; i<len; i++){
        ch = mex[i];
        
        switch (ch){
            case '(': case '[': case '{':
                push(&s, ch);
                break;

            case ')': case ']': case '}':
                if (is_empty(&s)) return 0;
                else {
                    front = pop(&s);
                    if ((front == '(' && ch != ')') ||  (front == '[' && ch != ']') ||  (front == '{' && ch != '}')){
                        return 0;
                    }
                    break;
                }
        }
        
    }
    
    if (!is_empty(&s)) return 0;
    
    return 1;;
    
}

int main(){

    char input[MAX_SIZE];
    printf("수식을 입력하세요: ");
    scanf(" %[^\n]", input);

    
    if (check_matching(input) == 1){
        printf("%s : 괄호검사 성공\n", input);
        
    }else printf("%s : 괄호검사 실패\n", input);
    
    return 0;
    
    
    
    
    
}
