#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_TERMS 101
#define MAX(a, b) (((a) > (b)) ? (a):(b))

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

char compare(int a, int b){
    
    if (a>b) return '>';
    else if(a==b) return '=';
    else return '<';
}

void attach(float coef, int expon){
    
     if(avail > MAX_TERMS){
        fprintf(stderr, "항의 개수가 너무 많음\n");
        exit(1);
    }
    
    terms[avail].coef = coef;
    terms[avail++].expon = expon;
}

void poly_add(int As, int Ae, int Bs, int Be, int *Cs, int *Ce){
    
    float tempcoef;
    *Cs = avail;
    
    while (As <= Ae && Bs <= Be)
        switch (compare(terms[As].expon, terms[Bs].expon)) {
            case '>':
                attach(terms[As].coef, terms[As].coef);
                As++;
                break;
                
            case '=':
                tempcoef = terms[As].coef + terms[Bs].coef;
                if (tempcoef)
                    attach(tempcoef, terms[As].expon);
                As++;
                Bs++;
                break;
                
            case '<':
                attach(terms[Bs].coef, terms[Bs].expon);
                Bs++;
                break;
        }
    
    for(; As<=Ae; As++)
        attach(terms[As].coef, terms[As].expon);
    for(; Bs<=Be; Bs++)
        attach(terms[Bs].coef, terms[Bs].expon);
    
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
        }
        else{
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
        }
        else{
            terms[idx].expon = atoi(temp);
            flag = 0;
            idx++;
        }
        
        temp = strtok(NULL, " ");
    }
    
    Be = idx - 1;
    avail = Be + 1;
    
    poly_add(As, Ae, Bs, Be, &Cs, &Ce);
    printf("\n첫번째 다항식 : ");
    print_poly(As, Ae);
    printf("두번째 다항식 : ");
    print_poly(Bs, Be);
    printf("\n---------------------------\n");
    print_poly(Cs, Ce);
    
    return 0;
}
