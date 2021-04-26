#include <stdio.h>
#include <stdlib.h>

typedef int element;

struct node{ //노드구조 정의
    element data;
    struct node *next;
};

int main(){
    
    struct node *head, *temp, *oldtemp;
    int i;
    
    temp = malloc(sizeof(struct node)); //헤드 노드 생성
    temp->data = 0;
    oldtemp = temp;
    head = temp;
    
    for (i = 0; i<100; i++){ //99개 생성
        temp = malloc(sizeof(struct node));
        temp->data = i;
        oldtemp->next = temp; //바로 이전 포문에서 사용한 주소에 새로 생성한 주소 집어넣기
        oldtemp = temp; //현재 노드를 이전 노드화 하기
    }
    
    temp->next = NULL; //마지막 노드
    
    temp = head;
    
    for (i = 0; i<100; i++){
        printf("%d ", temp->data);
        temp = temp->next; //다음 노드로 이동
        
    }
    
    while (temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next; //다음 노드로 이동
        
    }
    
    //2~3개의 변수로 수많은 데이터 처리 가능
}
