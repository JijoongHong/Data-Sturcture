#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAX_NUM 100
#define TRUE 1
#define FALSE 0

typedef int Data;

typedef struct Stack{
    Data *stackArray;
    int topIndex;
} stack;


void stackInit(stack* pstack){
    pstack->stackArray = (Data*)malloc(sizeof(Data)*MAX_NUM);
    pstack->topIndex = -1;
}

int isFull(stack* pstack){
    if(pstack->topIndex >= MAX_NUM-1){
        return  TRUE;
    } else return FALSE;
}

void push(stack* pstack, Data input){
    if(isFull(pstack)){
        printf("ERROR");
        exit(-1);
    }
    pstack->topIndex += 1;
    pstack->stackArray[pstack->topIndex] = input;
}

Data pop(stack* pstack){
    int rIdx;
    rIdx = pstack->topIndex;
    pstack->topIndex -= 1;
    return pstack->stackArray[rIdx];
}

int isEmpty(stack* pstack){
    if(pstack->topIndex == -1){
        return TRUE;
    } else return FALSE;
}

Data peek(stack* pstack){
    if(isEmpty(pstack)){
        printf("ERROR");
        exit(-1);
    }
    return pstack->stackArray[pstack->topIndex];
}



int Operator(char op){ // 연산자에 우선순위 두기
    switch (op) {
        case '^':
            return 7;
        case '%': case '*':
            return 5;
        case '+': case '-':
            return 3;
        case '(':
            return 1;
    }
    return -1;
}

int whoPrecede(char op1, char op2){ //어떤 연산자가 우선순위 인지비교 함수
    if(Operator(op1)> Operator(op2)){
        return 1;
    } else if (Operator(op1)< Operator(op2)) {
        return -1;
    } else {
        return 0;
    }
}

void postfix(char* input, char* operator){
    
    char* result = (char*)malloc(sizeof(char)*strlen(input)*2); //문자열 공간을 하나 마련해준다.
    memset(result, 0, sizeof(char)*strlen(input)*2); // 문자열 공간 초기화
    
    stack postfix;
    stackInit(&postfix);

    int rindex=0; //문자열 공간의 index
    Data popData;
    
    for(int index=0;index<strlen(input);index++){
        if(isdigit(input[index])){ // 숫자라면
            result[rindex++] = input[index];
            if(isdigit(input[index+1])){ //현재 input[index]의 다음 문자가 숫자라면 다시 처음으로
                continue;
            }
            result[rindex++] = ' '; // 그렇지 않다면 띄어쓰기로 1자리 숫자와 2~3자리 숫자를 구분
        } else {
            switch (input[index]) {
                case '+': case '-': case '*': case '^': case '%': //연산자라면
                    while(!isEmpty(&postfix) && whoPrecede(peek(&postfix),input[index]) >= 0){ // 스택 안에있는 연산자가 우선순위가 더 높거나 같다면,
                        if(isEmpty(&postfix)){
                            printf("ERROR");
                            exit(-1);
                        }
                        result[rindex++] = pop(&postfix);
                        result[rindex++] = ' ';
                    }
                    push(&postfix, input[index]); // 다뺀다음에 스택에 집어넣는다.OR 스택 안에 연산자가 더 낮다면 스택에 넣기
                    break;
                case '(': // 괄호가 열렸다면, 스택에 넣고
                    push(&postfix, input[index]);
                    break;
                case ')': //닫기 괄호가 왔다면
                    while(1){ //안에 열기 괄호가 있는지 확인
                        if(isEmpty(&postfix)){
                            printf("ERROR");
                            exit(-1);
                        }
                        popData = pop(&postfix);
                        if(popData == '('){ //있다면?
                            break;
                        }
                        result[rindex++] = popData; //연산자를 열기 괄호 나오기 전까지 빼낸다.
                        result[rindex++] = ' ';
                    }
            }
        }
    }
    while(!isEmpty(&postfix)){ //연산자 스택이 비지 않았다면 마지막에 다 빼준다.
        if(isEmpty(&postfix)){
            printf("ERROR");
            exit(-1);
        }
        result[rindex++] = pop(&postfix);
        result[rindex++] = ' ';
    }
    strcpy(input, result); //result를 input에 다시 복사해준다.
    free(result);
}

int PostfixCalculator(char* input){
    stack stack;
    stackInit(&stack);
    
    char temp[100];
    strcpy(temp, input); //strtok를 위해 input을 temp에 복사
    char* result[100]; //strtok로 나눈 값은 result에 저장
    int rindex = 0; // result의 index
    char* tok;
    int op2, op1; // 스택에서 나온 숫자2, 숫자1
    
    tok = strtok(temp, " ");
    while(tok != NULL){
        result[rindex++] = tok;
        tok = strtok(NULL, " ");
    }
    
    for(int i=0;i<rindex;i++){
        if(atoi(result[i])>0 && strcmp(result[i],"0")){ //result[i]가 숫자라면
            push(&stack, atoi(result[i]));
        }
        else if (!strcmp(result[i],"0")){ //result[i]가 0이라면
            push(&stack, atoi(result[i]));
        }else { //result[i]가 operator라면
            op2 = pop(&stack);
            op1 = pop(&stack);
            switch (result[i][0]) {
                case '+':
                    push(&stack, op1+op2);
                    break;
                case '-':
                    push(&stack, op1-op2);
                    break;
                case '*':
                    push(&stack, op1*op2);
                    break;
                case '%':
                    push(&stack, op1%op2);
                    break;
                case '^':
                    push(&stack, (int)pow(op1,op2));
                    break;
            }
        }
    }
    return pop(&stack);
}

int checkError(char* input){
    stack check;
    stackInit(&check);
    int len = strlen(input);
    int i=0;
    Data compare;
    for(i=0;i<len;i++){
        switch (input[i]) {
            case '+': case '-': case '*': case '%': case '^': //부호라면
                if(i == 0) return i; // 부호가 처음 들어가면 오류
                else if(input[i-1]=='+' || input[i-1]=='-' || input[i-1]=='*' || input[i-1]=='%' || input[i-1]=='^'){ //부호 다음에 부호도 오류
                    return i;
                }
                break;
            case '(':
                push(&check, input[i]);
                break;
            case ')':
                compare = pop(&check);
                if(compare != '(' || isEmpty(&check)){ //닫힌 괄호가 나왔을때, check 스택안에 열린괄호가 없다면 오류
                    return i;
                }
                break;
        }
    }
    if(!isEmpty(&check)){ //stck이 비지 않았다면? -> ( 만 있을 경우 오류
        return i-1;
    }
    return MAX_NUM+1; //오류가 없다면
}

int main(int argc, const char * argv[]) {
    char* operator = "()^*%+-"; //우선순위순
    char input[100];
    int location = 0;
    fgets(input, 100, stdin);
    if(checkError(input)>MAX_NUM){ //오류가 없다면
        postfix(input,operator);
        printf("%s\n", input);
        printf("%d\n", PostfixCalculator(input));
    } else {
        location = checkError(input);
        for(int i=0; i<location; i++){
            printf(" ");
        }
        printf("^이위치에 오류존재\n");
    }
    return 0;
}
