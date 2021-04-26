#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a,b) a>b?a:b
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


void sparse_matrix_fast_transpose(SparseMatrix* a, SparseMatrix* b){
    
    int max = MAX(a->cols, b->cols), i, j;
    int row_terms[a->cols], start_pos[max];
    int num_cols = a->cols, num_terms = a->terms;
    

    b->terms = a->terms;
    
    if (num_terms > 0){
        for(i = 0; i < num_cols; i++)
            row_terms[i] = 0;
        
        for (i = 0; i < num_terms; i++)
            row_terms[a->data[i].col]++;
        
        start_pos[0] = 0;
    
        for (i = 1; i < num_cols; i++)
            start_pos[i] = start_pos[i-1] + row_terms[i-1];
            
        for(i=0; i < num_terms; i++){
            j = start_pos[a->data[i].col]++;
            b->data[j].row = a->data[i].col;
            b->data[j].col = a->data[i].row;
            b->data[j].value = a->data[i].value;
        }
    }
}

void sparse_matrix_transpose(SparseMatrix* a, SparseMatrix* b){
    
    int b_idx;
    b->terms = a->terms;
    
    if(a->terms > 0){
        b_idx = 0;
        for (int c = 0; c < a->cols; c++){
            for(int i = 0; i < a->terms; i++){
                if (a->data[i].col == c){
                    b->data[b_idx].row = a->data[i].col;
                    b->data[b_idx].col = a->data[i].row;
                    b->data[b_idx].value = a->data[i].value;
                    b_idx++;
                }
            }
        }
    }
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
    m2->cols = m1->rows;
    m2->rows = m1->cols;
    m2->data = (term *)calloc(m2->cols*m2->rows,sizeof(term));
    m3->rows = m1->cols;
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
    
    
    sparse_matrix_fast_transpose(m1, m2);
    sparse_matrix_fast_transpose(m1, m3);
    printf("\n원본희소행렬\n");
    print_matrix(m1);
    printf("\n전치희소행렬1\n");
    print_matrix(m2);
    printf("\n전치희소행렬2\n");
    print_matrix(m3);


    free(m1->data);
    free(m1);
    free(m2->data);
    free(m2);

    
    return 0;
}
    
