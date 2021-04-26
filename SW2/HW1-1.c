#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct book_info
{
    char book_name[20];
    char author[20];
    int price;
    char date[8];
    
}book_info;

int merge_date(char* date){
    
    char new_date[7];
    int len = strlen(date);
    int j = 0;
    
    for (int i=0; i<len; i++){
        if (isdigit(date[i])){
            new_date[j] = date[i];
            j++;
        }
    }
    
    //printf("%s\n", new_date);
    
    int temp = atoi(new_date);
    
    return temp;
    
}

int classify_book(char date[]){
    
    int status;

    char temp[5];
    for(int i = 0; i < 4; i++){
        temp[i] = date[i];
    }
    temp[4] = '\0';

    if (atoi(temp)>2000){
        status = 1;
    }
    else status = 0;
    
    return status;
}


void store_book(book_info* group_a[], book_info* group_b[],book_info* bi, int status, int len_a, int len_b){

    int orig_data;
    int new_data;
    
    new_data = merge_date(bi->date);
    
    if (status == 1){
        if (len_a == 0){
            group_a[len_a] = bi;
        }
        else {
            for (int i = 0; i < len_a; i++){
                
                orig_data = merge_date(group_a[i]->date);
                                
                if (orig_data < new_data){
                    memmove(group_a+i+1, group_a+i, (len_a - i) *8);
                    group_a[i] = bi;
                    
                    break;
                }
                else {
                    group_a[len_a] = bi;
                }
            }
            
        }
    }
    else {
        if (len_b == 0){
            group_b[len_b] = bi;
        }
        else {
            for (int i = 0; i < len_b; i++){
                
                orig_data = merge_date(group_b[i]->date);
                                
                if (orig_data < new_data){
                    memmove(group_b+i+1, group_b+i, (len_b - i) *8);
                    group_b[i] = bi;
                    
                    break;
                }
                else {
                    group_b[len_b] = bi;
                }
            }
            
        }
    }

}



book_info* find_next(book_info* group_a[], book_info* group_b[], int* ptr_a, int* ptr_b, int len_a, int len_b){
    
    if (*ptr_a < len_a){
        *ptr_a += 1;
        return group_a[*ptr_a-1];
        
    }
    
    else{
        *ptr_b += 1;
        return group_b[*ptr_b-1];
    }

    
}

int main(){
    
    book_info bi[10];
    int grp;
    int len_of_a = 0, len_of_b = 0, a_idx=0, b_idx=0;
    
    book_info* group_a[10];
    book_info* group_b[10];
    book_info* latest;
    
    for (int i=0; i<10; i++){
        
        printf("------------------------------------\n");
        
        printf("책이름을 입력하세요 : ");
        scanf("%s", bi[i].book_name);

        printf("저자이름을 입력하세요 : ");
        scanf("%s", bi[i].author);

        printf("가격을 입력하세요 : ");
        scanf("%d", &bi[i].price);

        printf("출판년월을 입력하세요. 예시(2020/12) : ");
        scanf("%s", bi[i].date);
        
        printf("------------------------------------\n");

        grp = classify_book(bi[i].date);

        
        store_book(group_a, group_b, &bi[i], grp, len_of_a, len_of_b);
        
        if (grp == 1) {
            len_of_a++;
        }
        else {
            len_of_b++;
        }
        
    }
    
    for (int k=1; k<10; k++){
        latest = find_next(group_a, group_b, &a_idx, &b_idx, len_of_a, len_of_b);
        printf("%d - 책이름 : %s, 저자이름 : %s, 가격 : %d, 출판년월 : %s\n", k, latest->book_name, latest->author, latest->price, latest->date);
    }

    return 0;
}

