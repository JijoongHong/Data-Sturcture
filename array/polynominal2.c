
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX_TERMS 44
#define MAX(a, b) (((a) > (b)) ? (a):(b))

typedef struct { //is_exist 함수에서 두개의 값을 리턴하기 위한 구조체
    int idx;  // 값이 추가될 인덱스
    int flag; // 값이 맨 마지막에 추가되는가, 중간에 끼워넣어지는가를 알려주는 플래그
} multiply;

typedef struct{
    int coef;  //항의 계수
    int expon; //항의 차수
} polynomial;

polynomial terms[MAX_TERMS];

int avail; //새로운 수식의 시작위치를 나타내는 변수

char compare(int a, int b){ //지수 비교
    
    if (a>b) return '>';
    else if(a==b) return '=';
    else return '<';
}

void attach(int coef, int expon){  //항 추가 및 avail 값 조정
    
     if(avail > MAX_TERMS){
        fprintf(stderr, "항의 개수가 너무 많음\n");
        exit(1);
    }
    
    terms[avail].coef = coef;
    terms[avail++].expon = expon;
}

void poly_add2(int As, int Ae, int Bs, int Be, int *Cs, int *Ce){
    
    int tempcoef;  // 임시계수 선언
    *Cs = avail;   // 시작위치 지정
    
    while (As <= Ae && Bs <= Be)
        switch (compare(terms[As].expon, terms[Bs].expon)) {    // 지수의 값 비교
            case '>':                                           // a의 지수가 클 경우
                attach(terms[As].coef, terms[As].expon);        // a의 값 추가
                As++;                                           // a의 시작위치 증가
                break;
                
            case '=':                                           // 지수가 동일할 경우
                tempcoef = terms[As].coef + terms[Bs].coef;     // a와 b를 더한 값이 0이 아니면 추가
                if (tempcoef)                                   // a와 b의 시작위치 증가
                    attach(tempcoef, terms[As].expon);
                As++;
                Bs++;
                break;
                
            case '<':                                           // b의 지수가 클 경우
                attach(terms[Bs].coef, terms[Bs].expon);        // b의 값 추가
                Bs++;                                           // b의 시작위치 증가
                break;
        }
    
    for(; As<=Ae; As++)                                         // 남아있는 값을 추가함
        attach(terms[As].coef, terms[As].expon);
    for(; Bs<=Be; Bs++)
        attach(terms[Bs].coef, terms[Bs].expon);
    
    *Ce = avail -1; // 종료위치 지정
}


multiply is_exist(int expon, int *Cs, int *Ce){
    
    int target, mid, first, last;
    
    
    multiply state;
    
    
    first = *Cs;
    last = *Ce;
    target = expon;
    
    while (first <= last) {                     // 이진탐색
        mid = (first + last) / 2;               // 중앙값 설정


        if (target == terms[mid].expon){        // 찾고자 하는 값(지수)가 존재할 경우
            state.flag = 0;                     // 해당 지수에 계수 값을 더하도록 함
            state.idx = mid;                    // 해당 지수의 위치
            return state;                       // 위 정보 반환
            
        }else if (target > terms[mid].expon){   // 찾고자 하는 값(지수)가 중앙값보다 클 경우
            if (target < terms[mid-1].expon){   // 찾고자 하는 값이 없음(끼워넣기)
                state.flag = 1;                 // 플래그 지정
                state.idx = mid;                // 추가해야할 곳의 위치
                return state;                   // 위 정보 반환
                
            }else{                              // 이진탐색 진행
                last = mid - 1;}                // 탐색 범위를 앞쪽 그룹으로 바꿔줌
                
        }else {                                 // 찾고자 하는 값(지수)가 중앙값보다 작을 경우
            if (target > terms[mid+1].expon){   // 찾고자 하는 값이 없음
                if (mid+1 == avail){            // 중앙값이 C의 마지막일 경우
                    state.flag = 1;             // 마지막에 추가
                    state.idx = avail;          // 추가해야할 곳의 위치
                    return state;               // 위 정보 반환
                }else{
                    state.flag = 1;             // 중간에 끼워 넣기
                    state.idx = mid+1;          // 추가해야할 곳의 위치
                    return state;               // 위 정보 반환
                }
            }else {                             // 이진탐색 진행
                first = mid + 1;}               // 탐색 범위를 뒷쪽 그룹으로 바꿔줌
        }
    }
    
    state.flag = 1;     // 찾고자 하는 값(지수)가 없음, 마지막에 추가
    state.idx = avail;  // 추가해야할 곳의 위치
    return state;       // 위 정보 반환
}


void poly_mul2(int As, int Ae, int Bs, int Be, int *Ds, int *De){
    
    float tempcoef;
    int tempexpon;
    *Ds = avail;
    *De = *Ds-1;
    multiply state;
    
    for (int i = 0 ; i < Ae+1; i++){
        for (int j = 0; j< Be-Bs+1; j++){

            tempcoef = terms[i].coef * terms[Bs + j].coef;
            tempexpon = terms[i].expon + terms[Bs + j].expon;
            
            if (i>=1){  // 첫번째 추가 이후
                state = is_exist(tempexpon, Ds, De);
                
                if (state.flag == 0) {
                    // 이미 차수가 존재하는 경우
                    terms[state.idx].coef += tempcoef;
                
                }else{
                    if (state.idx < *De) { // 중간에 끼워넣기
                        memmove(terms+state.idx+1, terms+state.idx, sizeof(terms)); // 메모리 한칸 이동
                        terms[state.idx].coef = tempcoef; // 값 추가
                        terms[state.idx].expon = tempexpon;
                        avail ++;
                        (*De)++;
                    
                    }else { // 맨뒤에 추가하기
                        attach(tempcoef, tempexpon);
                        (*De)++;
                        
                    }
            
                }
            }else {   // 첫번째 추가
                attach(tempcoef, tempexpon);
                (*De)++;
            }
        }
    }
}
    

void print_poly(int s, int e){
    for (int i = s; i < e; i++)
        printf("%dx^%d +" , terms[i].coef, terms[i].expon);
    
    printf("%dx^%d" , terms[e].coef, terms[e].expon);
}


int main(){
    
    int As = 0, Ae=0, Bs, Be, Cs, Ce, Ds, De; // 각 수식의 시작과 끝
    char a_input[12], b_input[12]; // 데이터 입력받을
    int flag = 0, idx = 0;
    
    printf("수식 1을 입력하세요 : ");
    scanf(" %[^\n]", a_input);
    
    char *temp = strtok(a_input, " ");
    while (temp != NULL){
        
        if(idx > 6){
            fprintf(stderr, "항의 개수가 너무 많음\n");
            exit(1);
        }
        
        if (flag == 0){
            terms[idx].coef = atoi(temp);
            flag = 1;
        }
        else{
            terms[idx].expon = atoi(temp);
            flag = 0;
            idx++;
        }

        temp = strtok(NULL, " ");
    }

    Ae = As + idx -1;
    
    if(Ae > 5){
        fprintf(stderr, "항의 개수가 너무 많음\n");
        exit(1);
    }
    
    Bs = Ae + 1;
    
    printf("수식 2를 입력하세요 : ");
    scanf(" %[^\n]", b_input);

    idx = Bs;
    char *temp2 = strtok(b_input, " ");
    while (temp2 != NULL){
        
        if(idx > 6){
            fprintf(stderr, "항의 개수가 너무 많음\n");
            exit(1);
        }
        
        if (flag == 0){
            terms[idx].coef = atoi(temp2);
            flag = 1;
        }
        else{
            terms[idx].expon = atoi(temp2);
            flag = 0;
            idx++;
        }
        
        temp2 = strtok(NULL, " ");
    }
    
    Be = idx - 1;
    
    avail = Be + 1;
    
    poly_add2(As, Ae, Bs, Be, &Cs, &Ce);
    poly_mul2(As, Ae, Bs, Be, &Ds, &De);

    printf("\n수식 1+2는 ");
    print_poly(Cs, Ce);
    printf("\n수식 1*2는 ");
    print_poly(Ds, De);
    printf("\n\n");
    
    char input[4];
    printf("수식에 값을 넣으세요 ");
    scanf(" %[^\n]", input);
    
    int mode, x, result=0;
    
    mode = atoi(&input[0]);
    x = atoi(&input[2]);
    
    switch(mode){
        case 1:
            for (int i = 0; i < Ae; i++)
                result += terms[i].coef * pow(x, terms[i].expon);
            result += terms[Ae].coef;
            break;
            
        case 2:
            for (int i = Bs; i < Be; i++)
                result += terms[i].coef * pow(x, terms[i].expon);
            result += terms[Be].coef;
            break;
            
        case 3:
            for (int i = Cs; i < Ce; i++)
                result += terms[i].coef * pow(x, terms[i].expon);
            result += terms[Ce].coef;
            break;
            
        case 4:
            for (int i = Ds; i < De; i++)
                result += terms[i].coef * pow(x, terms[i].expon);
            result += terms[De].coef;
            break;
    }
    
    printf("결과값은 %d \n", result);
        
    
    return 0;
}
