#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 3
#define COLS 3
#define MAX_TERMS 10

typedef struct {
    int row; // 행의 정보
    int col; // 열의 정보
    int value; // 행렬의 값
}term;

typedef struct {
    term *data;
    int rows; //행의 개수
    int cols; // 열의 개수
    int terms; //항의 개수
}SparseMatrix;

void sparse_matrix_add(SparseMatrix* a, SparseMatrix* b, SparseMatrix* c){

    int ca = 0, cb = 0, cc = 0; //각 배열의 항목을 가리키는 인덱스
    
    //배열 a와 b의 크기가 같은지 확인
    if (a->rows != b->rows || a->cols != b->cols){
        fprintf(stderr, "희소행렬 크기 에러\n");
        exit(1);
    }
    
    c->rows = a->rows;
    c->cols = a->cols;
    
    while (ca < a->terms && cb < b->terms){
        // 각 항목의 순차적 번호 계산
        int a_idx = a->data[ca].row * a->cols + a->data[ca].col;
        int b_idx = b->data[cb].row * b->cols + b->data[cb].col;
        
        if (a_idx < b_idx){
            c->data[cc++] = a->data[ca++];
        }else if (a_idx == b_idx){
            if((a->data[ca].value + b->data[cb].value)!=0){
                c->data[cc].row = a->data[ca].row;
                c->data[cc].col = a->data[ca].col;
                c->data[cc++].value = a->data[ca++].value + b->data[cb++].value;
            }else {
                ca++;
                cb++;
            }
        }else c->data[cc++] = b->data[cb++];
    }
    
    for (;ca < a->terms;)
        c->data[cc++] = a->data[ca++];
    for (;cb < b->terms;)
        c->data[cc++] = b->data[cb++];
    c->terms = cc;
    
}

void print_matrix(SparseMatrix* m){
    for (int i =0 ;i<m->terms;i++){
        printf("(%d, %d, %d)\n", m->data[i].row, m->data[i].col, m->data[i].value);
    }
}


int main(){
    
    SparseMatrix* m1 = (SparseMatrix*)calloc(1, sizeof(SparseMatrix));
    SparseMatrix* m2 = (SparseMatrix*)calloc(1, sizeof(SparseMatrix));
    SparseMatrix* m3 = (SparseMatrix*)calloc(1, sizeof(SparseMatrix));
    
    printf("행렬 1의 실행의 규격을 입력하세요. ");
    scanf(" %d %d", &m1->rows, &m1->cols);
    m3->cols = m1->cols;
    m3->rows = m1->rows;
    m3->data = (term *)calloc(m3->cols*m3->rows,sizeof(term));
    char input[(m1->rows*m1->cols)*2], temp_input[(m1->rows*m1->cols)*2];
   
    printf("행렬 1의 데이터를 입력하세요. ");
    scanf(" %[^\n]", input);
    int r = 0, c = 0, data_idx = 0;
    
    strcpy(temp_input, input);
    char* temp = strtok(input, " ");
    while (temp != NULL){
       if (atoi(temp) != 0)
           data_idx++;
       temp = strtok(NULL, " ");
       
    }
    
    m1->data = (term *)malloc(sizeof(term)*data_idx);
    
    temp = strtok(temp_input, " ");
    data_idx = 0;
    printf("%s", temp_input);
    while (temp != NULL){
        if (atoi(temp) != 0){
            m1->data[data_idx].row = r;
            m1->data[data_idx].col = c;
            m1->data[data_idx].value = atoi(temp);
            m1->terms++;
            data_idx++;
       }
        
        c++;
        if (c == m1->cols){
            c=0;
            r++;
       }
       temp = strtok(NULL, " ");
    }
    
    r = 0;
    c = 0;
    data_idx = 0;
    
    
    printf("행렬 2의 실행의 규격을 입력하세요. ");
    scanf(" %d %d", &m2->rows, &m2->cols);

    char input2[(m2->rows*m2->cols)*2];
    
    printf("행렬 2의 데이터를 입력하세요. ");
    scanf(" %[^\n]", input2);
    
    strcpy(temp_input, input2);
    temp = strtok(input2, " ");
    
    while (temp != NULL){
       if (atoi(temp) != 0)
           data_idx++;
       temp = strtok(NULL, " ");
    }
    m2->data = (term *)malloc(sizeof(term)*data_idx);
    data_idx = 0;
    temp = strtok(temp_input, " ");
    while (temp != NULL){
        if (atoi(temp) != 0){
            m2->data[data_idx].row = r;
            m2->data[data_idx].col = c;
            m2->data[data_idx].value = atoi(temp);
            m2->terms++;
            data_idx++;
        }
        c++;
        if (c == m2->cols){
            c=0;
            r++;
        }
        temp = strtok(NULL, " ");
    }
    
    sparse_matrix_add(m1, m2, m3);
    printf("\n방식2:\n");
    printf("\n행렬1 (%d개)\n", m1->terms*3);
    print_matrix(m1);
    printf("\n행렬2 (%d개)\n", m2->terms*3);
    print_matrix(m2);
    printf("\n행렬1+2 (%d개)\n", m3->terms*3);
    print_matrix(m3);
    
    free(m1->data);
    free(m1);
    free(m2->data);
    free(m2);
    free(m3->data);
    free(m3);
    
    return 0;
}
    
