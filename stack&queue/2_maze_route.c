#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0


typedef struct{
    int x; //x좌표
    int y; //y좌표
    unsigned short map:4; //막혀있는 곳 (1:상 2:하 4:우 8:좌)
    unsigned short dir:4; //진행해야 하는 방향 (1:상 2:하 4:우 8:좌)
    unsigned short star:1; //좌표가 미로경로에 해당하면 1, 아니면 0
} maze;


// -------- Stack Area -------- //

int count = 0; // 스택 사용횟수

typedef maze element;

typedef struct{
    element* data;
    int top;
    int capacity;
} Stack;

void init_stack(Stack *s){
    s->top = -1;
    s->capacity = 1;
    s->data = (element*)malloc(s->capacity * sizeof(element));
}

int is_full(Stack *s){
    
    return (s->top == (s->capacity - 1));
}

void push(Stack *s, element item){
    
    if(is_full(s)){
        
        s->capacity *= 2;
        s->data = (element*)realloc(s->data, s->capacity * sizeof(element));

    }
    (s->top)++;
    s->data[(s->top)] = item;
    count++;
    printf("PUSH(%d, %d, %hd, %hd, %hd)\n",s->data[s->top].x, s->data[s->top].y, s->data[s->top].map ,s->data[s->top].dir,s->data[s->top].star);
    
}

int is_empty(Stack *s){
    return (s->top == -1);
}

element pop(Stack *s){
    
    if (is_empty(s)){
        
        printf("스택 공백 에러\n");
        exit(1);
        
    }else {
        count++;
        printf("POP(%d, %d, %hd, %hd, %hd)\n",s->data[s->top].x, s->data[s->top].y, s->data[s->top].map ,s->data[s->top].dir,s->data[s->top].star);
        return s->data[(s->top)--];
    }
    
}

element peek(Stack *s){
    
    if (is_empty(s)){
        
        printf("스택 공백 에러\n");
        exit(1);
        
    }else return s->data[s->top];
}

// -------- End of Stack Area -------- //

int find_way(maze new_maze[12][9], maze curr, maze prev){ //현재위치에서 진행방향을 알려주는 함수

    int avail;
    unsigned short dir = 15;
    if (curr.dir > 0) avail = curr.dir; //이미 방향이 지정되어있는 경우
    else if (prev.x == curr.x && prev.y == curr.y){ //시작위치 초기화
        if (curr.dir != 0) avail = curr.dir; //두번째 경로 탐색 이후
        else avail = (curr.map ^ dir); //15와 xor연산 후 방향지정
            
    }else{
        avail = ((curr.map + prev.dir) ^ dir); //일반 경로에 대한 방향지정
    }
    return avail;
    
}


void print_maze(maze*** new_maze, int min, int min_idx, int routes){ //미로와 최단경로를 표시하는 함수
    
    printf("\n스택활용 횟수 %d회\n", count);
    printf("모두 %d개의 길을 찾았습니다.\n", routes);
    printf("가장 짧은 길을 표시합니다.\n(거리%d)\n", min);
    
    printf("____________________________________\n");
    for (int i=0; i<12; i++){
        for (int j=0; j<9; j++){
            //상단
            if (new_maze[min_idx][i][j].star == 1){ //경로에 해당하는 좌표면
                if(new_maze[min_idx][i][j].map >= 8 || new_maze[min_idx][i][j].map == 11 || new_maze[min_idx][i][j].map == 14 || new_maze[min_idx][i][j].map == 15) printf("| * ");
                else printf("  * ");
                
                
            }else{ //경로에 해당하는 좌표가 아니면
                if(new_maze[min_idx][i][j].map >= 8 || new_maze[min_idx][i][j].map == 11 || new_maze[min_idx][i][j].map == 14 || new_maze[min_idx][i][j].map == 15) printf("|   ");
                else printf("    ");
            }
        }
        
        printf("|");
        printf("\n");
        
        //하단
        for (int j=0; j<9; j++){
            if(new_maze[min_idx][i][j].map == 10 || new_maze[min_idx][i][j].map == 11 || new_maze[min_idx][i][j].map == 14 || new_maze[min_idx][i][j].map == 15) printf("|___");
            else if(new_maze[min_idx][i][j].map == 8 || new_maze[min_idx][i][j].map == 12 || new_maze[min_idx][i][j].map == 9 || new_maze[min_idx][i][j].map == 13) printf("|   ");
                
            else if((new_maze[min_idx][i][j].map % 2 == 1 && new_maze[min_idx][i][j].map != 5 && new_maze[min_idx][i][j].map != 1)|| i == 11 || new_maze[min_idx][i][j].map ==6 || new_maze[min_idx][i][j].map ==2) printf("____");
            else printf("    ");
        }
        printf("|");
        printf("\n");
        
    }

    printf("\n");
}


void find_length(maze*** revised_maze, int routes){ //각 경로별 좌표정보로 경로의 길이를 구하는 함수
    
    maze curr_pos, prev_pos;
    
    int *length = malloc(sizeof(int) * routes); //각 경로별 길이 저장용 배열
    
    for (int i = 0; i<routes; i++){ //경로별로 길이 및 이동경로 저장
        
        
        curr_pos = revised_maze[i][0][0];
        prev_pos = revised_maze[i][0][0];
        
        while (1){
            if (curr_pos.dir == 4) { //좌로 이동
                prev_pos = curr_pos;
                prev_pos.dir = 8;
                revised_maze[i][curr_pos.x][curr_pos.y].star = 1; //이동경로 표시
                curr_pos = revised_maze[i][curr_pos.x][curr_pos.y+1];
                length[i]++; //길이 최신화

            }
            else if(curr_pos.dir == 2){ //하로 이동
                prev_pos = curr_pos;
                prev_pos.dir = 1;
                revised_maze[i][curr_pos.x][curr_pos.y].star = 1;
                curr_pos = revised_maze[i][curr_pos.x+1][curr_pos.y];
                length[i]++;
            }
            else if(curr_pos.dir == 8){ //우로 이동
                prev_pos = curr_pos;
                prev_pos.dir = 4;
                revised_maze[i][curr_pos.x][curr_pos.y].star = 1;
                curr_pos = revised_maze[i][curr_pos.x][curr_pos.y-1];
                length[i]++;
            }
            else if(curr_pos.dir == 1){ //상으로 이동
                prev_pos = curr_pos;
                prev_pos.dir = 2;
                revised_maze[i][curr_pos.x][curr_pos.y].star = 1;
                curr_pos = revised_maze[i][curr_pos.x-1][curr_pos.y];
                length[i]++;

            }
            
            if(curr_pos.x == 11 && curr_pos.y == 8) { // 도착 시 다음 경로로 넘어감
                revised_maze[i][curr_pos.x][curr_pos.y].star = 1;
                break;
            }
        }

    }
    
    //가장 짧은 경로와 그의 길이 찾기
    int min = length[0], min_idx = 0;
    for (int i = 0; i<routes; i++){
        if (length[i] < min){
            min_idx = i;
            min = length[i];
        }
    }
    
    print_maze(revised_maze, min, min_idx, routes);
    free(length);
    
}


    
void find_path(Stack *route, maze new_maze[12][9], int routes){ // 각 경로별 좌표정보를 생성해주는 함수
    maze temp;
    
    maze*** revised_maze = (maze***) malloc (sizeof(maze**) * routes); //경로의 개수만큼 좌표정보 생성
     for (int i = 0; i<routes; i++){
         revised_maze[i] = (maze**)malloc(sizeof(maze*) * 12);
         
         for (int j = 0; j <12; j++){
              revised_maze[i][j] = (maze*)malloc(sizeof(maze) * 9);
         }
     }
    
    
    for (int i = 0; i<routes; i++){ //기존 좌표정보 넣기
        for (int x = 0; x<12; x++){
            for (int y = 0; y<9; y++){
                revised_maze[i][x][y] = new_maze[x][y];
            }
        }
    }
    
    int i = 0;
    while (!is_empty(route)){ //각 경로별로 옳은 갈림길 정보 넣기
        temp = pop(route);
        revised_maze[i][temp.x][temp.y].x = temp.x;
        revised_maze[i][temp.x][temp.y].y = temp.y;
        revised_maze[i][temp.x][temp.y].dir = temp.dir;
        revised_maze[i][temp.x][temp.y].star = temp.star;
        
        if (temp.x == 0 && temp.y == 0) i++;
    }
    
    find_length(revised_maze, routes);
    free(revised_maze);
}

int is_exist(Stack *route, maze curr_pose){ //옳은 갈림길만을 저장하도록 중복을 체크하고 삭제해주는 함수
    maze temp;
    Stack temp_stack;
    init_stack(&temp_stack);
    int count=0;
    
    for (int i = 0; i < route->top; i++){
        
        push(&temp_stack, pop(route));
        count++; //팝한 횟수
        
        if (peek(&temp_stack).x == curr_pose.x && peek(&temp_stack).y == curr_pose.y) { //동일한 좌표가 존재하면
            if (count == 1){ //바로 직전에 실패했을 경우 실패한 갈림길 정보 삭제
                temp = pop(&temp_stack);
                push(&temp_stack, curr_pose);
                while (!is_empty(&temp_stack)) push(route, pop(&temp_stack));
                return TRUE;
            }else{//갈림길을 선택하고 중간에 헤맨 경우 헤맨 경로 까지 삭제
                for (int j = 0; j<count; j++) pop(&temp_stack);
                push(&temp_stack, curr_pose);
                while (!is_empty(&temp_stack)) push(route, pop(&temp_stack));
                return TRUE;
            }
        }
    }
    
    while (!is_empty(&temp_stack)) push(route, pop(&temp_stack)); //동일한 좌표가 없음, 빼낸 정보 다시 집어넣기
    free(temp_stack.data);
    return FALSE;

}


int main(){
    
    Stack s, route;
    init_stack(&s); //갈림길 저장용 유동스택
    init_stack(&route); //찾은 경로의 옳은 갈림길 저장 스택
    maze curr_pos, curr_pos2, prev_pos; //현재위치, 임시현재위치(원본손상막음), 이전위치
    int avail, routes=0; //이동방향, 옳은 경로의 개수
    maze new_maze[12][9] ={
        {{0,0,9,0,0}, {0,0,3,0,0}, {0,0,3,0,0}, {0,0,5,0,0}, {0,0,11,0,0}, {0,0,3,0,0}, {0,0,1,0,0}, {0,0,5,0,0}, {0,0,13,0,0}},
        {{0,0,10,0,0}, {0,0,3,0,0}, {0,0,5,0,0}, {0,0,12,0,0}, {0,0,9,0,0}, {0,0,3,0,0}, {0,0,4,0,0}, {0,0,12,0,0}, {0,0,12,0,0}},
        {{0,0,9,0,0}, {0,0,3,0,0}, {0,0,4,0,0}, {0,0,10,0,0}, {0,0,6,0,0}, {0,0,9,0,0}, {0,0,6,0,0}, {0,0,12,0,0}, {0,0,12,0,0}},
        {{0,0,12,0,0}, {0,0,13,0,0}, {0,0,14,0,0}, {0,0,13,0,0}, {0,0,13,0,0}, {0,0,14,0,0}, {0,0,9,0,0}, {0,0,2,0,0}, {0,0,4,0,0}},
        {{0,0,12,0,0}, {0,0,12,0,0}, {0,0,9,0,0}, {0,0,4,0,0}, {0,0,10,0,0}, {0,0,3,0,0}, {0,0,6,0,0}, {0,0,9,0,0}, {0,0,4,0,0}},
        {{0,0,8,0,0}, {0,0,6,0,0}, {0,0,12,0,0}, {0,0,8,0,0}, {0,0,3,0,0}, {0,0,7,0,0}, {0,0,11,0,0}, {0,0,6,0,0}, {0,0,12,0,0}},
        {{0,0,10,0,0}, {0,0,3,0,0}, {0,0,6,0,0}, {0,0,12,0,0}, {0,0,9,0,0}, {0,0,3,0,0}, {0,0,3,0,0}, {0,0,1,0,0}, {0,0,4,0,0}},
        {{0,0,13,0,0}, {0,0,9,0,0}, {0,0,3,0,0}, {0,0,6,0,0}, {0,0,12,0,0}, {0,0,9,0,0}, {0,0,3,0,0}, {0,0,6,0,0}, {0,0,10,0,0}},
        {{0,0,12,0,0}, {0,0,10,0,0}, {0,0,3,0,0}, {0,0,1,0,0}, {0,0,6,0,0}, {0,0,10,0,0}, {0,0,1,0,0}, {0,0,3,0,0}, {0,0,5,0,0}},
        {{0,0,8,0,0}, {0,0,3,0,0}, {0,0,5,0,0}, {0,0,8,0,0}, {0,0,5,0,0}, {0,0,13,0,0}, {0,0,14,0,0}, {0,0,13,0,0}, {0,0,12,0,0}},
        {{0,0,10,0,0}, {0,0,5,0,0}, {0,0,12,0,0}, {0,0,12,0,0}, {0,0,12,0,0}, {0,0,8,0,0}, {0,0,3,0,0}, {0,0,6,0,0}, {0,0,12,0,0}},
        {{0,0,11,0,0}, {0,0,6,0,0}, {0,0,10,0,0}, {0,0,6,0,0}, {0,0,10,0,0}, {0,0,6,0,0}, {0,0,11,0,0}, {0,0,3,0,0}, {0,0,6,0,0}}
    };
    
    for (int i=0; i<12; i++){ //좌표 설정
        for (int j=0; j<9; j++){
            new_maze[i][j].x = i;
            new_maze[i][j].y = j;
        }
    }

    curr_pos = new_maze[0][0];
    curr_pos2 = new_maze[0][0];
    prev_pos = new_maze[0][0];
     
    while (1){

        avail = find_way(new_maze, curr_pos, prev_pos); //이동방향 찾기
        curr_pos.dir = avail;
        new_maze[curr_pos.x][curr_pos.y].dir = avail; //원본 배열에 진행방향 넣어주기

        //단방향
        if (curr_pos.dir == 4) { //좌로 이동
            prev_pos = curr_pos;
            prev_pos.dir = 8; //왔던 길 막기
            curr_pos = new_maze[curr_pos.x][curr_pos.y+1];
        }
        else if(curr_pos.dir == 2){ //하로 이동
            prev_pos = curr_pos;
            prev_pos.dir = 1; //왔던 길 막기
            curr_pos = new_maze[curr_pos.x+1][curr_pos.y];
        }
        else if(curr_pos.dir == 8){ //우로 이동
            prev_pos = curr_pos;
            prev_pos.dir = 4; //왔던 길 막기
            curr_pos = new_maze[curr_pos.x][curr_pos.y-1];
        }
        else if(curr_pos.dir == 1){ //상으로 이동
            prev_pos = curr_pos;
            prev_pos.dir = 2; //왔던 길 막기
            curr_pos = new_maze[curr_pos.x-1][curr_pos.y];
        
        //갈림길
        }else{
            switch (curr_pos.dir) { // 갈림길 방향 분리 후 스택에 저장 후 다시시행
                case 3:
                    curr_pos2 = curr_pos;
                    curr_pos2.dir = 1;
                    curr_pos2.map = 14;
                    push(&s, curr_pos2);
                    curr_pos2.dir = 2;
                    curr_pos2.map = 13;
                    push(&s, curr_pos2);
                    break;
                    
                case 5:
                    curr_pos2 = curr_pos;
                    curr_pos2.dir = 4;
                    curr_pos2.map = 11;
                    push(&s, curr_pos2);
                    curr_pos2.dir = 1;
                    curr_pos2.map = 14;
                    push(&s, curr_pos2);
                    break;
                    
                case 6:
                    curr_pos2 = curr_pos;
                    curr_pos2.dir = 4;
                    curr_pos2.map = 11;
                    push(&s, curr_pos2);
                    curr_pos2.dir = 2;
                    curr_pos2.map = 13;
                    push(&s, curr_pos2);
                    break;
                    
                case 9:
                    curr_pos2 = curr_pos;
                    curr_pos2.dir = 8;
                    curr_pos2.map = 7;
                    push(&s, curr_pos2);
                    curr_pos2.dir = 1;
                    curr_pos2.map = 14;
                    push(&s, curr_pos2);
                    break;
                    
                case 10:
                    curr_pos2 = curr_pos;
                    curr_pos2.dir = 8;
                    curr_pos2.map = 7;
                    push(&s, curr_pos2);
                    curr_pos2.dir = 2;
                    curr_pos2.map = 13;
                    push(&s, curr_pos2);
                    break;
                    
                case 12:
                    curr_pos2 = curr_pos;
                    curr_pos2.dir = 4;
                    curr_pos2.map = 11;
                    push(&s, curr_pos2);
                    curr_pos2.dir = 8;
                    curr_pos2.map = 7;
                    push(&s, curr_pos2);
                    break;
            }
        }

        if (avail != 1 && avail != 2 && avail != 4 && avail != 8){ //더이상 갈 수 있는 곳이 없을 때
              if (is_empty(&s)){
                  if (routes != 0){ //경로를 다 찾은 경우
                      pop(&route); //옳은 갈림길 저장 스택 내 쓰레기값 제거
                      break; //가능한 경로 찾기 종료
                  }else{
                      printf("실패\n"); //경로 없음
                      return 0;}
                      
              }else{ //이전위치로 돌아가기
                  curr_pos = pop(&s);
                  if(!is_exist(&route, curr_pos)) push(&route, curr_pos); //스택에 중복값 제거 후 삽입
              }
        }
        
        if(curr_pos.x == 11 && curr_pos.y == 8){ //목표지점 도달
            routes++; //가능한 경로 개수 증가
            maze end = {11, 8, 6, 9};
            push(&route, end); //갈림길 저장 스택에 마지막 위치 저장
            if (s.top != -1){ //스택의 가장 하단의 경로를 현재위치로 설정한 후 다시 경로찾기
                while(!is_empty(&s)) curr_pos = pop(&s);
                push(&route, curr_pos);
                
            }else break; //추가경로 가능성 없으므로 종료
        }
    }
    
    find_path(&route, new_maze, routes); //옳은 갈림길 정보를 바탕으로 각 경로 탐색
    free(s.data);
    free(route.data);

    return 0;
}
