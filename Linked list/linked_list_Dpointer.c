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

void insert(Node** pOfHead, Node* pre, element data){
    
    Node* new_node = malloc(sizeof(Node)); //새로운 노드 생성
    
    if (new_node == NULL)
        return;
    
    new_node-> data = data;//새로운 노드에 데이터 할당
    
    if (*pOfHead == NULL){ //아무것도 없는 상태라면(헤드가 아무것도 안 가리키면)
        new_node->link = NULL; //새 노드가 마지막임을 명시
        *pOfHead = new_node; //헤드포인터의 값(헤드)가 새 노드를 가리키도록 함
    
    }else if (pre == NULL){ //이전 노드가 없는 경우(맨 첫번째인 경우)
        new_node->link = *pOfHead;
        printf("!\n");//새로운 노드가 헤드가 가리던 곳(첫번째)를 가리키도록 함
        *pOfHead = new_node;
        printf("!!\n");//헤드가 새로운 노드를 가리키도록 함
        
    }else{ //중간이나 마지막에 추가하는 경우
        new_node->link = pre->link; //새로운 노드가 이전 노드가 가리키던 곳(지정위치의 다음)을 가리키도록 함
        pre->link = new_node; //이전 노드가 새로운 노드를 가리키도록 함
    }
}

void delete(Node** pOfHead, Node* pre){
    
    Node* removed;
    
    if (pre == NULL){ //이전에 아무것도 없을 경우(맨 앞 삭제)
        removed = (*pOfHead); //헤드가 가리키는 맨 앞의 주소를 임시 변수에 넣는다
        *pOfHead = (*pOfHead)->link; // 헤드가 맨 앞이 가리키던 주소를 가리키도록 한다
    }else{
        removed = pre->link; //이전 노드가 가리키던 곳(현재)를 삭제될 위치에 넣는다.
        pre->link = removed->link; //이전 노드가 삭제될 노드가 가리키던 곳(다음)을 가리키도록 한다
    }
    
    free(removed);
}

void print_list(Node* head){
    
    for (Node* p = head; p!= NULL; p = p->link){
        printf("%d->", p->data);
    }

    printf("NULL \n");
}

int main(){
    
    Node* head = NULL;
    
    for (int i = 0; i < 5; i++){
        insert(&head, head, i);
        print_list(head);
    }
    
    for (int i = 0; i < 4; i++){
        delete(&head, head);
        print_list(head);
    }
    
    delete(&head, NULL);
    print_list(head);
    
    return 0;
}
