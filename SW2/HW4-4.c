#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

typedef char element;
typedef struct{
    element *data;
    int capacity;
    int top;
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
                if (is_empty(&s)) {
                    return 0;}
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
    
    return 1;
    
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

// 프리엠프티는 체크만 하기 때문에 주소를 안 넘겨도 될 것 같고 푸시나 팝은 값을 변경하기 때문에 주소를 넘겨줘야 한다고 답변을 했다
// 엠프티나 풀도 주소를 넘겨줘야 한다
// 왜냐하면 엠프티의 탑은 현재 구성되어있는 스택의 탑 값을 보내는거
// 밸류로 보내면 로컬 스택 변수가 될 뿐임
    
