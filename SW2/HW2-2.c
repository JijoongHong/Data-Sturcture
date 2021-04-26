#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_TERMS 101

typedef struct {
    int idx;
    int flag;
} multiply;

typedef struct{
    float coef;
    int expon;
} polynomial;

polynomial terms[MAX_TERMS];


int avail;

void attach(float coef, int expon){
    
     if(avail > MAX_TERMS){
        fprintf(stderr, "항의 개수가 너무 많음\n");
        exit(1);
    }
    
    terms[avail].coef = coef;
    terms[avail++].expon = expon;
}

multiply is_exist(int expon, int *Cs, int *Ce){
    // 중복값 검사 및 인덱스 지정
    int target, mid, first, last;
    multiply state;
    first = *Cs;
    last = *Ce;
    target = expon;
    
    while (first <= last) {
        mid = (first + last) / 2;
        // 중복되는 차수를 찾았을 때
        if (target == terms[mid].expon){
            state.flag = 0;
            state.idx = mid;
            return state;
    
        }else if (target > terms[mid].expon){
            // 차수 사이에 끼워넣어야 할 경우
            if (target < terms[mid-1].expon){
                state.flag = 1;
                state.idx = mid;
                return state;
                
            }else{
                last = mid - 1;}
                
        }else {
            if (target > terms[mid+1].expon){
                // 마지막 끝단일경우 사용하지 않은 avail 공간의 값과 비교하므로 예외처리
                if (mid+1 == avail){
                    state.flag = 1;
                    state.idx = avail;
                    return state;
                // 차수 사이에 끼워넣어야 할 경우
                }else{
                    state.flag = 1;
                    state.idx = mid+1;
                    return state;
                }

            }else {
                first = mid + 1;}
        }
    }
    
    state.flag = 1;
    state.idx = avail;
    return state;
}

void poly_mul(int As, int Ae, int Bs, int Be, int *Cs, int *Ce){
    
    float tempcoef;
    int tempexpon;
    *Cs = avail;
    *Ce = *Cs-1;
    multiply state;
    
    for (int i = 0 ; i < Ae+1; i++){
        for (int j = 0; j< Be-Bs+1; j++){

            tempcoef = terms[i].coef * terms[Bs + j].coef;
            tempexpon = terms[i].expon + terms[Bs + j].expon;

            if (i>=1){
                state = is_exist(tempexpon, Cs, Ce);

                if (state.flag == 0) {
                    // 이미 차수가 존재하는 경우
                    terms[state.idx].coef += tempcoef;
                
                }else{
                    // 중간에 끼워넣기
                    if (state.idx < *Ce) {
                        memmove(terms+state.idx+1, terms+state.idx, sizeof(terms));
                        terms[state.idx].coef = tempcoef;
                        terms[state.idx].expon = tempexpon;
                        avail ++;
                        (*Ce)++;
                    // 맨뒤에 추가하기
                    }else {
                        attach(tempcoef, tempexpon);
                        (*Ce)++;
                    }
                }
            // 초기에 추가하기
            }else {
                attach(tempcoef, tempexpon);
                (*Ce)++;
            }
        }
    }
    
    *Ce = avail -1;
}
    
void print_poly(int s, int e){
    for (int i = s; i < e; i++)
        printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);
    printf("%3.1fx^%d \n", terms[e].coef, terms[e].expon);
}

int main(){
    
    int As = 0, Ae, Bs, Be, Cs, Ce;
    char a_input[50], b_input[50];
    int flag = 0, idx = 0;
    
    printf("수식 1을 입력하세요 : ");
    scanf(" %[^\n]", a_input);
    
    char *temp = strtok(a_input, " ");
    while (temp != NULL){
        
        if (flag == 0){
            terms[idx].coef = atoi(temp);
            flag = 1;
        }else{
            terms[idx].expon = atoi(temp);
            flag = 0;
            idx++;
        }
        temp = strtok(NULL, " ");
    }

    Ae = As + idx -1;
    Bs = Ae + 1;
    
    printf("수식 2를 입력하세요 : ");
    scanf(" %[^\n]", b_input);

    idx = Bs;
    temp = strtok(b_input, " ");
    while (temp != NULL){
        
        if (flag == 0){
            terms[idx].coef = atoi(temp);
            flag = 1;
        }else{
            terms[idx].expon = atoi(temp);
            flag = 0;
            idx++;
        }
        temp = strtok(NULL, " ");
    }
    
    Be = idx - 1;
    avail = Be + 1;
    
    poly_mul(As, Ae, Bs, Be, &Cs, &Ce);
    printf("\n첫번째 다항식 : ");
    print_poly(As, Ae);
    printf("두번째 다항식 : ");
    print_poly(Bs, Be);
    printf("\n---------------------------\n");
    print_poly(Cs, Ce);
    
    return 0;
}
