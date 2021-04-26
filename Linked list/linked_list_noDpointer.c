
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct{
    element data;
    struct Node* link;
}Node;

void error(char* message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

Node* insert_first(Node* head, element data){
    
    Node* p = (Node*)malloc(sizeof(Node)); //새로운 노드의 주소 동적할당
    p->data = data; //데이터 설정
    p->link = head; //새로 추가한 데이터의 링크에 원래 헤드가 가리키는 주소 삽입
    head = p; //헤드가 새로 추가한 데이터를 가리키도록 함
    return head;
    
}

Node* insert(Node* head, Node* pre, element data){
    
    Node *p = (Node*)malloc(sizeof(Node));//새로운 노드의 주소 동적할당
    p->data = data; //데이터 설정
    p->link = pre->link; //이전 노드가 가리키던 것을 추가한 노드가 가리키도록 함
    pre->link = p; //이전 노드가 추가 노드를 가리키도록 함
    return head;
}

Node* delete_first(Node* head){
    
    Node* removed; //임시 노드 생ㅇ성
    if (head == NULL) return NULL;
    removed = head; //임시노드에 현재 맨 앞 노드 위치 저장
    head = removed->link; //헤드가 현재 맨 앞 다음 노드를 가리키도록 함
    free(removed);//임시노드 삭제
    return head;
    
}

Node* delete(Node *head, Node* pre){
    
    Node* removed;
    removed = pre->link;//임시노드에 삭제위치 위치 저장
    pre->link = removed->link;//이전노드가 삭제될 노드가 가리키는 노드를 가리키도록함(다음다음거)
    free(removed);//임시노드 삭제
    return head;
    
}


void print_list(Node* head){
    
    for (Node *p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    
    printf("NULL \n");
}


int main(){
    
    Node* head = NULL;
    
    for (int i=0; i<5; i++){
        head = insert_first(head, i);
        print_list(head);
    }
    
    for (int i=0; i<5; i++){
        head = delete_first(head);
        print_list(head);
    }
    
    return 0;
    
}

