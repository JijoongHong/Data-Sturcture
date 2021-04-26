#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX_DEGREE 11
#define MAX(a, b) (((a) > (b)) ? (a):(b))

typedef struct{             // 구조체 타입 선언
    int degree;             // 다항식의 차수
    int coef[MAX_DEGREE];   // 다항식의 계수
} polynominal;

polynominal poly_add1(polynominal A, polynominal B){
    
    polynominal C = {0, };              // 결과다항식
    int Apos = 0, Bpos = 0, Cpos = 0;   // 배열 인덱스 변수
    int degree_a = A.degree;
    int degree_b = B.degree;
    
    C.degree = MAX(A.degree, B.degree); // 결과다항식 차수
    
    while(Apos <= A.degree && Bpos <= B.degree){    // 각 배열의 모든 인덱스에 접근할 때 까지 반복
        if(degree_a > degree_b){                    // 수식 1의 차수가 더 큰 경우
            C.coef[Cpos++] = A.coef[Apos++];        // 수식 1의 계수를 결과에 대입하고, 각 배열의 인덱스 +1
            degree_a--;                             // 수식 1의 차수 -1
            
        }else if(degree_a == degree_b){             // 수식1과 2의 차수가 동일한 경우
            C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++]; // 수식 1,2 의 계수를 결과에 대입하고, 각 배열의 인덱스 +1
            degree_a--; degree_b--;                 // 수식 1, 2의 차수 -1
            
        }else{                                      // 수식 2의 차수가 더 큰 경우
            C.coef[Cpos++] = B.coef[Bpos++];        // 수식 2의 계수를 결과에 대입하고, 각 배열의 인덱스 +1
            degree_b--;                             // 수식 2의 차수 -1
        }
    }
    return C; // 결과 반환
}

polynominal poly_mul1(polynominal A, polynominal B){
    
    polynominal C = {0, };              // 결과다항식
    
    int degree_a = A.degree;
    int degree_b = B.degree;
    
    int tempcoef, tempexpon, max_degree, count=0; // 임시계수, 임시지수, 결과의 최대차수, 중복 카운트용
    max_degree = A.degree + B.degree;
    
    for (int i = 0; i < A.degree+1; i++){
        degree_b = B.degree;
        for (int j = 0; j < B.degree+1; j++){
            tempcoef = A.coef[i] * B.coef[j];   // 결과의 임시계수 계산
            tempexpon = degree_a + degree_b;    // 결과의 임시지수 계산
            if ((tempcoef != 0 && C.coef[max_degree - tempexpon] != 0) || tempcoef == 0) count++;
            // 이미 해당 지수에 값이 있어 겹치는 경우, 계수가 0인 경우 카운트 증가
            // 계수가 0인 경우 -> 예) 수식1의 계수가 0인 경우에 0값이 추가됨
            // 연산이 되었음에도 계수가 0인 관계로 연산횟수에 포함되지 않아 이를 추가적으로 고려해줌
            // count가 추가되는 경우 괄호로 표현한 결과:
            // 21x^5 + 15x^4 + 3x^3 + (0x^4) + (0x^3) + (0x^2) + (42x^3) + 30x^2 + 6x + (21x^2) + (15x) + 3
            C.coef[max_degree - tempexpon] += tempcoef; // 앞에서부터 계수 저장
            degree_b --; //수식2의 차수 -1
        }
        degree_a --; //수식1의 차수 -1
    }
    C.degree = (A.degree+1) * (B.degree+1) - count -1 ; // 중복 값 제거
    return C;
    
}

int main(){

    char a_input[12], b_input[12];              // 입력 값 배열 (최대 차수가 5이므로 항은 6개, 띄어쓰기 포함 12개 선언)
    int a_len=0, b_len=0;                       // 항의 개수 저장용 배열 선언
    polynominal a, b;                           // 수식1, 2에 대한 구조체 선언
    
    
    printf("수식 1을 입력하세요 ");
    scanf("%[^\n]", a_input);
    
    char *temp = strtok(a_input, " ");          // 공백을 기준으로 분할하여 저장
    int i = 0;
    while (temp != NULL){
        if(a_len > 6){                          // 5차항을 초과하면 에러 발생
            fprintf(stderr, "항의 개수가 너무 많음\n");
            exit(1);}
        
        a.coef[i] = atoi(temp);
        temp = strtok(NULL, " ");
        a_len++;
        i++;
    }
    
    a.degree = a_len -1 ;

    
    printf("수식 2을 입력하세요 ");
    scanf(" %[^\n]", b_input);
    
    temp = strtok(b_input, " ");                // 공백을 기준으로 분할하여 저장
    i = 0;
    while (temp != NULL){
        if(b_len > 6){                          // 5차항을 초과하면 에러 발생
            fprintf(stderr, "항의 개수가 너무 많음\n");
            exit(1);}
        
        b.coef[i] = atoi(temp);
        temp = strtok(NULL, " ");
        b_len++;
        i++;
    }
    b.degree = b_len - 1;
    
    
    polynominal c_add, c_mul; // 결과 다항식 선언

    c_add = poly_add1(a, b);
    c_mul = poly_mul1(a, b);
    
    int c1_len = c_add.degree, c2_len = c_mul.degree; // 구조체 값이 변경되어서는 안되므로 임시 차수 변수 선언
    
    
    printf("\n수식 1 + 2는 ");                             // 결과물 출력
    for (int i = 0; i < (c_add.degree); i++){
        printf("%dx^%d + ", c_add.coef[i], c1_len--);
    }
    printf("%dx^%d", c_add.coef[c_add.degree], c1_len);
    printf("\n");
    
    printf("수식 1 * 2는 ");
    for (int i = 0; i < (c_mul.degree); i++){
        printf("%dx^%d + ", c_mul.coef[i], c2_len--);
    }
    printf("%dx^%d", c_mul.coef[c_mul.degree], c2_len);
    printf("\n");
    
    
    int mode, x, result=0;
    printf("\n수식에 값을 넣으세요 ");
    scanf(" %d %d", &mode, &x);
    
    c1_len = c_add.degree;  // 구조체 값이 변경되어서는 안되므로 0이 된 임시 차수 변수에 값 다시 넣기
    c2_len = c_mul.degree;
    
    switch(mode){           // 입력 값에 따라 수식 계산
        case 1:
            for (int i = 0; i < a.degree; i++)
                result += a.coef[i] * pow(x, a_len--);
            result += a.coef[a.degree];
            break;
            
        case 2:
            for (int i = 0; i < b.degree; i++)
                result += b.coef[i] * pow(x, b_len--);
            result += b.coef[b.degree];
            break;
            
        case 3:
            for (int i = 0; i < c_add.degree; i++)
                result += c_add.coef[i] * pow(x, c1_len--);
            result += c_add.coef[c_add.degree];
            break;
            
        case 4:
            for (int i = 0; i < c_mul.degree; i++)
                result += c_mul.coef[i] * pow(x, c2_len--);
            result += c_mul.coef[c_mul.degree];
            break;
    }
    
    printf("결과값은 %d \n", result);
        
        
        
    return 0;
}
