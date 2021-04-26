#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int shape;

void print_matrix(int m[][shape]){  // 행렬 출력
    for (int i = 0; i<shape; i++){
        for (int j = 0; j < shape; j++){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

void add_normal(int A[][shape], int B[][shape]){ // 행렬 더하기
    
    int C[shape][shape];
    int r, c;
    for (r = 0; r < shape; r++){
        for (c = 0; c < shape; c++){
            C[r][c] = A[r][c] + B[r][c]; //A와 B의 동일위치 더한 후 대입
        }
    }
    
    print_matrix(C);  //C배열 출력
}

void multiply_normal(int A[][shape], int B[][shape]){
    int result, C[shape][shape];
    
    for (int i = 0; i < shape; i++){
        for (int j = 0; j < shape; j++){
            result = 0; // 임시저장 변수 0으로 초기화
            for (int k = 0; k < shape; k++){ // c[i][j]의 값 연산
                result += A[i][k] * B[k][j]; // 결과값 임시저장
            }
            C[i][j] = result; // 결과값 대입
        }
    }
    print_matrix(C); //C배열 출력

}

int main(){

    printf("실행의 규격을 입력하세요. ");
    scanf(" %d", &shape);
    
    int m1[shape][shape], m2[shape][shape]; // 규격에 맞춘 2차원 배열 선언
    char input[(shape*shape)*2];            // 규격에 따라 입력 문자열 선언
    
    printf("행렬 1의 데이터를 입력하세요. ");
    scanf(" %[^\n]", input);
    
    int r = 0, c = 0;
    char* temp = strtok(input, " ");        // 공백을 기준으로 분할
    while (temp != NULL){
        m1[r][c] = atoi(temp);
        c++;                                // 다음 항목
        if (c == shape){                    // c가 벽에 다다르면
            c=0;                            // 다음행으로, c초기화
            r++;
        }
        temp = strtok(NULL, " ");
    }
    
    printf("행렬 2의 데이터를 입력하세요. ");       // 공백을 기준으로 분할
    scanf(" %[^\n]", input);
    temp = strtok(input, " ");
    c = 0;
    r = 0;
    while (temp != NULL){
        
        m2[r][c] = atoi(temp);
        c++;                                // 다음 항목
        if (c == shape){                    // c가 벽에 다다르면
            c=0;                            // 다음행으로, c초기화
            r++;
        }
        temp = strtok(NULL, " ");
    }
    
    printf("\n방식1: ");
    printf("\n행렬1(%d)\n", shape*shape);     // 행렬 1출력
    print_matrix(m1);
    printf("\n행렬2(%d)\n", shape*shape);     // 행렬 2출력
    print_matrix(m2);
    printf("\n행렬 1+2(%d)\n", shape*shape);  // 덧셈결과 출력
    add_normal(m1, m2);
    printf("\n행렬 1*2(%d)\n", shape*shape);  // 곱셈결과 출력
    multiply_normal(m1, m2);
    
    return 0;
}
