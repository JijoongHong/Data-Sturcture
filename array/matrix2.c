#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TERMS 10

typedef struct {
    int row; // 행의 정보
    int col; // 열의 정보
    int value; // 행렬의 값
}term;

int shape;

typedef struct {
    term data[MAX_TERMS];
    int rows; // 행의 개수
    int cols; // 열의 개수
    int terms; // 항의 개수
}SparseMatrix;

SparseMatrix add_sparse(SparseMatrix a, SparseMatrix b){
    SparseMatrix c = {0};
    int ca = 0, cb = 0, cc = 0; //각 배열의 항목을 가리키는 인덱스
    
    c.rows = a.rows;
    c.cols = a.cols;
    
    while (ca < a.terms && cb < b.terms){
        // 각 항목의 실제 행렬에서의 순차적 번호 계산
        int a_idx = a.data[ca].row * a.cols + a.data[ca].col;
        int b_idx = b.data[cb].row * b.cols + b.data[cb].col;
        
        if (a_idx < b_idx){                 // a의 항목이 앞서는 경우
            c.data[cc++] = a.data[ca++];    // a의 항목 추가
            
        }else if (a_idx == b_idx){          // a와 b가 동일 위치에 있는 경우
            if((a.data[ca].value + b.data[cb].value)!=0){   //0이 아닌 값만 저장하며 0인 경우 다음으로 넘어감
                c.data[cc].row = a.data[ca].row;
                c.data[cc].col = a.data[ca].col;
                c.data[cc++].value = a.data[ca++].value + b.data[cb++].value;
            }else {
                ca++;
                cb++;
            }
            
        }else c.data[cc++] = b.data[cb++]; // b의 항목이 앞서는 경우 b의 항목 추가
    }
    
    
    for (;ca < a.terms;)                   // 각 배열에 남아있는 항들을 결과 행렬에 추가
        c.data[cc++] = a.data[ca++];
    for (;cb < b.terms;)
        c.data[cc++] = b.data[cb++];
    c.terms = cc;                          // 결과 행렬의 항의 개수 저장
    return c;
    
}


SparseMatrix sort_matrix(SparseMatrix c){
    
    term temp;
    for (int i = 0; i< c.terms; i++){
        for (int j = 0; j < c.terms - 1 - i; j++){
    
            if (c.data[j].row * c.cols + c.data[j].col > c.data[j+1].row * c.cols + c.data[j+1].col){
                temp = c.data[j];
                c.data[j] = c.data[j+1];
                c.data[j+1] = temp;
            }
        }
    }

    return c;
}
                
SparseMatrix multiply_sparse(SparseMatrix a, SparseMatrix b){
    SparseMatrix c={0};
    int ca = 0, cb = 0, cc = 0, a_idx, b_idx, b_start, b_end;
    c.rows = a.rows;
    c.cols = a.cols;


    for (int i = 0; i < a.terms; i++){
        a_idx = a.data[i].row * a.cols + a.data[i].col; // a 항목의 실제 행렬에서의 순차적 번호 계산

        cb = 0; //b의 희소행렬 인덱스 초기화
        for (int j = cb; j < b.terms; j++){
            
            b_idx = b.data[cb].row * b.cols + b.data[cb].col; // b 항목의 실제 행렬에서의 순차적 번호 계산
            b_start = (a_idx % shape) * shape; //a의 항이 행렬 곱셈 수행 시 곱해지는 b의 범위 지정
            b_end = b_start + shape - 1;
            
                
            if (b_start <= b_idx && b_idx <= b_end){ //b 항목이 범위 안에 있을 경우
                    c.data[cc].row = a.data[ca].row; //결과 행렬 항목의 행은 a와 같음
                    c.data[cc].col = b.data[cb].col; //결과 행렬 항목의 열은 b와 같음
                    c.data[cc++].value += a.data[ca].value * b.data[cb++].value; //a항목의 값과 b항목의 곱한 값을 결과행렬의 값으로 넣고, b희소행렬의 인덱스 증가

            }else if (b_idx < b_start){ //b 항목이 범위보다 전에 있을 경우 다음 항목으로 넘어감
                cb++;
                continue;
                
            }else break; //b 항목이 범위를 벗어나면 다음 a항목으로 넘어감
        }
        ca++;
    }

    c.terms = cc;
    c = sort_matrix(c);
    
    return c;
    
}

void print_matrix(SparseMatrix m){
    for (int i =0 ;i<m.terms;i++){
        printf("%d %d %d\n", m.data[i].row, m.data[i].col, m.data[i].value);
    }
}


int main(){
    
    SparseMatrix m1, m2, m3, m4;    // 행렬 구조체 선언
    
    printf("행렬의 규격을 입력하세요. ");  // 행렬의 규격 입력 후 전역변수에 저장
    scanf(" %d", &shape);
    
    m1.rows = shape;                // 구조체의 값 일부 초기화, terms에 쓰레기 값이 들어가는 경우가 있어 초기화 필요
    m1.cols = shape;
    m1.terms = 0;
    m2.rows = shape;
    m2.cols = shape;
    m2.terms = 0;
    m3.rows = shape;
    m3.cols = shape;
    m3.terms = 0;
    m4.rows = shape;
    m4.cols = shape;
    m4.terms = 0;

    char input[(shape*shape)*2];        // 띄어쓰기 포함하여 행렬의 값을 입력받는 문자열 형성
   
    printf("행렬 1의 데이터를 입력하세요. ");
    scanf(" %[^\n]", input);
    
    int r = 0, c = 0, data_idx = 0;     // 저장에 필요한 행, 열, 인덱스 변수 선언
    
    char* temp = strtok(input, " ");    // 공백을 기준으로 분할하여 저장        
       if (atoi(temp) != 0){
           m1.data[data_idx].row = r;   // 행의 정보 저장
           m1.data[data_idx].col = c;   // 열의 정보 저장
           m1.data[data_idx].value = atoi(temp); //항의 값 저장
           m1.terms++;                  // 항의 개수 저장
           data_idx++;                  // 다음 인덱스로
       }
       c++;                             // 다음 열로
       if (c == shape){                 // 열이 규격에 달하면 다음 행으로
           c=0;
           r++;
       }
       temp = strtok(NULL, " ");
    }
    
    r = 0;
    c = 0;
    data_idx = 0;                       // 저장에 필요한 행, 열, 인덱스 변수 초기화
    printf("행렬 2의 데이터를 입력하세요. ");
    scanf(" %[^\n]", input);
    temp = strtok(input, " ");          // 공백을 기준으로 분할하여 저장
    
    while (temp != NULL){
        if (atoi(temp) != 0){
            m2.data[data_idx].row = r;  // 행의 정보 저장
            m2.data[data_idx].col = c;  // 열의 정보 저장
            m2.data[data_idx].value = atoi(temp); // 항의 값 저장
            m2.terms++;                 // 항의 개수 저장
            data_idx++;                 // 다음 인덱스로
        }
        c++;
        if (c == shape){                // 다음 열로
            c=0;                        // 열이 규격에 달하면 다음 행으로
            r++;
        }
        temp = strtok(NULL, " ");
    }
    
    //행렬의 크기가 같은지 확인
    if (m1.rows != m2.rows || m1.cols != m2.cols){
        fprintf(stderr, "희소행렬 크기 에러\n");
        exit(1);
    }
    
    m3 = add_sparse(m1, m2);
    m4 = multiply_sparse(m1, m2);
    printf("\n방식2:\n");
    printf("\n행렬3 (%d개)\n", m1.terms*3);
    print_matrix(m1);
    printf("\n행렬4 (%d개)\n", m2.terms*3);
    print_matrix(m2);
    printf("\n행렬3+4 (%d개)\n", m3.terms*3);
    print_matrix(m3);
    printf("\n행렬3*4 (%d개)\n", m4.terms*3);
    print_matrix(m4);

    
    return 0;
}
