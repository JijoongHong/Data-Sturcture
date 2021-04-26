#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct book_info
{
    char book_name[20];
    char keyword[4];
    char author[20];
    int price;
    char date[8];
    
}book_info;


int classify_book(char keyword[]){
    
    int status;
    
    if (strcmp("IS", keyword) == 0)
        status = 1;
    
    else if (strcmp("CS", keyword) == 0)
        status = 2;
    
    else if (strcmp("MS", keyword) == 0)
        status = 3;
    
    else status = 4;
    
    return status;

}


void store_book(book_info* group[], book_info* bi, int status, int len){

    char* orig_data;
    char* new_data;
    int result;
    
    if (len == 0){
        group[len] = bi;
    }
    else {
        for (int i = 0; i < len; i++){
            
            orig_data = group[i]->author;
            new_data = bi[i].author;
            result = strcmp(orig_data, new_data);
            
            if (result > 0){
                memmove(group+i+1, group+i, (len - i) *8);
                group[i] = bi;
                
                break;
            }
            else {
                group[len] = bi;
            }
        }
    }
}
            


int find_author(book_info* is[], book_info* cs[], book_info* ms[], book_info* eee[], int len_is, int len_cs,int len_ms,int len_eee){
    int idx = 0, flag = 0, idx2 = 0;
    char* overlapped[10];
    char* overlapped2[10];
    
    //IS 분야에서 cs, ms, eee 분야의 중복 저자를 찾고, 찾으면 중단(이후의 중복은 고려하지 않음)
    for(int i=0; i<len_is; i++){
        for(int j=0; j<len_cs; j++){
            
            if (strcmp(is[i]->author, cs[j]->author) == 0){
                overlapped[idx] = cs[j]->author;
                idx++;
                flag = 1;
                break;
            }
        }
        
        if(flag == 1){
            flag = 0;
            continue;
            }
            
        for(int k=0; k<len_ms; k++){
            
            if (strcmp(is[i]->author, ms[k]->author) == 0){
                overlapped[idx] = ms[k]->author;
                idx++;
                flag = 1;
                break;
            }
        }
        
        if(flag == 1){
            flag = 0;
            continue;
            }
        
        for(int l=0; l<len_eee; l++){
            
            if (strcmp(is[i]->author, eee[l]->author) == 0){
                overlapped[idx] = eee[l]->author;
                idx++;
                break;
            }
        }
    }
        
    //CS 분야에서 ms, eee 분야의 중복 저자를 찾고, 찾으면 중단(이후의 중복은 고려하지 않음)
    for(int i=0; i<len_cs; i++){
        for(int j=0; j<len_ms; j++){
            
            if (strcmp(cs[i]->author, ms[j]->author) == 0){
                overlapped[idx] = ms[j]->author;
                idx++;
                flag = 1;
                break;
            }
        }
        
        if(flag == 1){
            flag = 0;
            continue;
            }
            
        for(int k=0; k<len_eee; k++){
            
            if (strcmp(cs[i]->author, eee[k]->author) == 0){
                overlapped[idx] = eee[k]->author;
                idx++;
                flag = 1;
                break;
            }
        }
        
        if(flag == 1){
            flag = 0;
            continue;
            }
    }
    
    //MS 분야에서 eee 분야의 중복 저자를 찾고, 찾으면 중단(이후의 중복은 고려하지 않음)
    for(int i=0; i<len_ms; i++){
        for(int j=0; j<len_eee; j++){
            
            if (strcmp(ms[i]->author, eee[j]->author) == 0){
                overlapped[idx] = eee[j]->author;
                idx++;
                break;
            }
        }
    }
    
    for(int i = idx; i>0; i--){
        if(strcmp(overlapped[i], overlapped[i-1]) > 0){
            char* temp;
            temp = overlapped[i];
            overlapped[i] = overlapped[i-1];
            overlapped[i-1] = temp;
        } else break;
    }
    
    overlapped2[0] = overlapped[0];
    
    for(int i=1; i<idx; i++){
        if(overlapped[i] != overlapped[idx2])
            overlapped2[idx2++] = overlapped[i];
    }
    
    return idx2;
}

    
    
int main(){
    
    book_info bi[100];
    int grp;
    int len_is = 0, len_cs = 0, len_ms = 0, len_eee = 0, num_of_author=0;
    
    book_info* is[25];
    book_info* cs[25];
    book_info* ms[25];
    book_info* eee[25];

    
    for (int i=0; i<10; i++){
        
        printf("---------------------------------------\n");
        
        printf("책이름을 입력하세요 : ");
        scanf(" %s", bi[i].book_name);
        
        printf("키워드를 입력하세요 : ");
        scanf(" %s", bi[i].keyword);

        printf("저자이름을 입력하세요 : ");
        scanf(" %s", bi[i].author);

        printf("가격을 입력하세요 : ");
        scanf(" %d", &bi[i].price);

        printf("출판년월을 입력하세요. 예시(2020/12) : ");
        scanf(" %s", bi[i].date);
        
        printf("---------------------------------------\n");

        grp = classify_book(bi[i].keyword);

        
        
        if (grp == 1) {
            store_book(is, &bi[i], grp, len_is);
            len_is++;
        }
        else if (grp == 2 ) {
            store_book(cs, &bi[i], grp, len_cs);
            len_cs++;
        }else if (grp == 3) {
            store_book(ms, &bi[i], grp, len_ms);
            len_ms++;
        }else {
            store_book(eee, &bi[i], grp, len_eee);
            len_eee++;
        }
    }
    
        
    num_of_author = find_author(is, cs, ms, eee, len_is, len_cs, len_ms, len_eee);
    printf("중복된 저자 수 : %d\n", num_of_author);
    return 0;
}





//strstr
//enumeration type : 심볼 값 만을 가져옴
// 
