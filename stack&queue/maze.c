#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0


typedef struct{
    int x;
    int y;
    unsigned short map:4;
    unsigned short dir:4;
    unsigned short star:1;
} maze;


// -------- Stack Area -------- //

int count = 0;

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



void print_maze(maze*** new_maze, int min, int min_idx){
    
    
    printf("가장 짧은 길을 표시합니다.\n(거리%d)\n", min);
    
    printf("____________________________________\n");
    for (int i=0; i<12; i++){
        for (int j=0; j<9; j++){
            
            if (new_maze[min_idx][i][j].star == 1){
                if(new_maze[min_idx][i][j].map >= 8 || new_maze[min_idx][i][j].map == 11 || new_maze[min_idx][i][j].map == 14 || new_maze[min_idx][i][j].map == 15) printf("| * ");
                else printf("  * ");
                
                
            }else{
                if(new_maze[min_idx][i][j].map >= 8 || new_maze[min_idx][i][j].map == 11 || new_maze[min_idx][i][j].map == 14 || new_maze[min_idx][i][j].map == 15) printf("|   ");
                else printf("    ");
                
            }

        }
        
        printf("|");
        printf("\n");
        
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

int find_way(maze new_maze[12][9], maze curr, maze prev){

    int avail=-1;
    unsigned short dir = 15;
    if (curr.dir > 0) avail = curr.dir;
    else if (prev.x == curr.x && prev.y == curr.y){
        if (curr.dir != 0) avail = curr.dir;
        else avail = (curr.map ^ dir);
            
    }else{
        avail = ((curr.map + prev.dir) ^ dir);
    }
    //printf("1) %d avail\n", avail);
    return avail;
    
}

int is_exist(Stack *route, maze curr_pose){
    maze temp;
    Stack temp_stack;
    init_stack(&temp_stack);
    int count=0;
    
    for (int i = 0; i < route->top; i++){
        
        push(&temp_stack, pop(route));
        count++;
        if(peek(&temp_stack).x == -1 && peek(&temp_stack).y == -1) break;
        
        if (peek(&temp_stack).x == curr_pose.x && peek(&temp_stack).y == curr_pose.y) {
            if (count == 1){
                temp = pop(&temp_stack);
                push(&temp_stack, curr_pose);
                printf("********************************%d %d\n", temp.x, temp.y);
                while (!is_empty(&temp_stack)) push(route, pop(&temp_stack));
                return TRUE;
            }else{
                for (int j = 0; j<count; j++) pop(&temp_stack);
                push(&temp_stack, curr_pose);
                printf("********************************%d %d\n", temp.x, temp.y);
                while (!is_empty(&temp_stack)) push(route, pop(&temp_stack));
                return TRUE;
            }

        }
    }
    
    while (!is_empty(&temp_stack)) push(route, pop(&temp_stack));
    
    return FALSE;

}
    

void push_loc(Stack *s, maze curr){
    
    maze temp;
    temp.x = curr.x;
    temp.y = curr.y;
    temp.map = curr.map;
    temp.dir = curr.dir;
    push(s, temp);
    printf("PUSH(%d, %d, %hd, %hd)\n", s->data[s->top].x, s->data[s->top].y, s->data[s->top].map, s->data[s->top].dir);
    
}

void find_length(maze*** revised_maze, int routes){
    
    maze curr_pos, prev_pos;
    
    int *length = malloc(sizeof(int) * routes);
    
    for (int i = 0; i<routes; i++){
        
        
        curr_pos = revised_maze[i][0][0];
        prev_pos = revised_maze[i][0][0];
        
        while (1){
            printf("%d %d %hd %hd\n", curr_pos.x, curr_pos.y, curr_pos.map, curr_pos.dir);
            if (curr_pos.dir == 4) {
                prev_pos = curr_pos;
                prev_pos.dir = 8;
                revised_maze[i][curr_pos.x][curr_pos.y].star = 1;
                curr_pos = revised_maze[i][curr_pos.x][curr_pos.y+1];
                printf("우\n");
                length[i]++;
                printf("!!!\n");
                 //printf("%d %d %hd %hd : curr data 우 \n", curr_pos.x, curr_pos.y, curr_pos.map, curr_pos.dir);
                 //printf("%d %d %hd %hd : prev data 우 \n", prev_pos.x, prev_pos.y, prev_pos.map, prev_pos.dir);
            }//좌로 이동
            else if(curr_pos.dir == 2){
                prev_pos = curr_pos;
                prev_pos.dir = 1;
                revised_maze[i][curr_pos.x][curr_pos.y].star = 1;
                curr_pos = revised_maze[i][curr_pos.x+1][curr_pos.y]; //하로 이동
                printf("하\n");
                length[i]++;
            }
            else if(curr_pos.dir == 8){
                prev_pos = curr_pos;
                prev_pos.dir = 4;
                revised_maze[i][curr_pos.x][curr_pos.y].star = 1;
                curr_pos = revised_maze[i][curr_pos.x][curr_pos.y-1];
                printf("좌\n");
                length[i]++;

                 
            }//우로 이동
            else if(curr_pos.dir == 1)  {
                prev_pos = curr_pos;
                prev_pos.dir = 2;
                revised_maze[i][curr_pos.x][curr_pos.y].star = 1;
                curr_pos = revised_maze[i][curr_pos.x-1][curr_pos.y];
                printf("상\n");
                length[i]++;

            }//상으로 이동
            
            if(curr_pos.x == 11 && curr_pos.y == 8) {
                revised_maze[i][curr_pos.x][curr_pos.y].star = 1;
                break;
            }
        }

    }
    
    int min = length[0], min_idx = 0;
    
    for (int i = 0; i<routes; i++){
        if (length[i] < min){
            min_idx = i;
            min = length[i];
        }
    }
    
    print_maze(revised_maze, min, min_idx);
    
}
    
void find_path(Stack *route, maze new_maze[12][9], int routes){
    maze temp;
    
    maze*** revised_maze = (maze***) malloc (sizeof(maze**) * routes);
     for (int i = 0; i<routes; i++){
         revised_maze[i] = (maze**)malloc(sizeof(maze*) * 12);
         
         for (int j = 0; j <12; j++){
              revised_maze[i][j] = (maze*)malloc(sizeof(maze) * 9);
         }
     }
    
    
    for (int i = 0; i<routes; i++){
        for (int x = 0; x<12; x++){
            for (int y = 0; y<9; y++){
                revised_maze[i][x][y] = new_maze[x][y];
                printf("??\n");
            }
        }
    }
    
    int i = 0;
    while (!is_empty(route)){
        temp = pop(route);
        printf("aaaaa %d %d %d %d %d %d\n", i, temp.x, temp.y, temp.map, temp.dir, temp.star);
        revised_maze[i][temp.x][temp.y].x = temp.x;
        revised_maze[i][temp.x][temp.y].y = temp.y;
        //revised_maze[i][temp.x][temp.y].map = temp.map;
        revised_maze[i][temp.x][temp.y].dir = temp.dir;
        revised_maze[i][temp.x][temp.y].star = temp.star;
        
        if (temp.x == 0 && temp.y == 0) i++;
    }
    
    find_length(revised_maze, routes);
}


int main(){
    
    Stack s, route;
    init_stack(&s);
    init_stack(&route);
    maze curr_pos, curr_pos2, prev_pos;
    int avail, routes=0;
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
    

    
    for (int i=0; i<12; i++){
        for (int j=0; j<9; j++){
            new_maze[i][j].x = i;
            new_maze[i][j].y = j;
            //printf("[%d, %d, %hd] ", new_maze[i][j].x, new_maze[i][j].y, new_maze[i][j].map);
            //if (j != 0 && j % 8 == 0)
        }
    }
    //printf("x: %d y: %d map : %d\n\n", new_maze[0][1].x, new_maze[0][1].y, new_maze[0][1].map);
    curr_pos = new_maze[0][0];
    curr_pos2 = new_maze[0][0];
    prev_pos = new_maze[0][0];
     
    while (1){
       
        //avail = find_way(new_maze, curr_pos, prev_pos);
        
        
        avail = find_way(new_maze, curr_pos, prev_pos);
        curr_pos.dir = avail;
        new_maze[curr_pos.x][curr_pos.y].dir = avail;
        //printf("%hd", curr_pos.dir);
        printf("------------\n");
        printf("(%d, %d) %hd %hd \n", curr_pos.x, curr_pos.y, curr_pos.map, curr_pos.dir);
        printf("avail front %d\n", avail);
        
        if (curr_pos.dir == 4) {
            prev_pos = curr_pos;
            prev_pos.dir = 8;
            curr_pos = new_maze[curr_pos.x][curr_pos.y+1];
            printf("우\n");
            //printf("%d %d %hd %hd : curr data 우 \n", curr_pos.x, curr_pos.y, curr_pos.map, curr_pos.dir);
            //printf("%d %d %hd %hd : prev data 우 \n", prev_pos.x, prev_pos.y, prev_pos.map, prev_pos.dir);
        }//좌로 이동
        else if(curr_pos.dir == 2){
            prev_pos = curr_pos;
            prev_pos.dir = 1;
            curr_pos = new_maze[curr_pos.x+1][curr_pos.y]; //하로 이동
            printf("하\n");
        }
        else if(curr_pos.dir == 8){
            prev_pos = curr_pos;
            prev_pos.dir = 4;
            curr_pos = new_maze[curr_pos.x][curr_pos.y-1];
            printf("좌\n");

            
        }//우로 이동
        else if(curr_pos.dir == 1)  {
            prev_pos = curr_pos;
            prev_pos.dir = 2;
            curr_pos = new_maze[curr_pos.x-1][curr_pos.y];
            printf("상\n");

        }//상으로 이동
        else{
            
            switch (curr_pos.dir) {
                case 3:
                    //printf("!3\n");
                    curr_pos2 = curr_pos;
                    curr_pos2.dir = 1;
                    curr_pos2.map = 14;
                    push_loc(&s, curr_pos2);
                    /*if (curr_pos2.x != prev_cross.x || curr_pos2.y != prev_cross.y){
                        push(&route, prev_cross);
                        printf("!");
                        printf("prev_cross (%d, %d, %hd, %hd)\n", prev_cross.x, prev_cross.y, prev_cross.map, prev_cross.dir);
                    }
                    if (curr_pos2.x != prev_cross.x || curr_pos2.y != prev_cross.y) push(&route, prev_cross);*/
                    curr_pos2.dir = 2;
                    curr_pos2.map = 13;
                    push_loc(&s, curr_pos2);
                    break;
                    
                case 5:
                    curr_pos2 = curr_pos;
                    curr_pos2.dir = 4;
                    curr_pos2.map = 11;
                    push_loc(&s, curr_pos2);
                    /*if (curr_pos2.x != prev_cross.x || curr_pos2.y != prev_cross.y){
                        push(&route, prev_cross);
                        printf("!");
                        printf("prev_cross (%d, %d, %hd, %hd)\n", prev_cross.x, prev_cross.y, prev_cross.map, prev_cross.dir);
                    }*/
                    curr_pos2.dir = 1;
                    curr_pos2.map = 14;
                    push_loc(&s, curr_pos2);
                    break;
                    
                case 6:
                    //printf("!");
                    curr_pos2 = curr_pos;
                    curr_pos2.dir = 4;
                    curr_pos2.map = 11;
                    push_loc(&s, curr_pos2);
                    /*if (curr_pos2.x != prev_cross.x || curr_pos2.y != prev_cross.y) push(&route, prev_cross);
                    if (curr_pos2.x != prev_cross.x || curr_pos2.y != prev_cross.y){
                        push(&route, prev_cross);
                        printf("!");
                        printf("prev_cross (%d, %d, %hd, %hd)\n", prev_cross.x, prev_cross.y, prev_cross.map, prev_cross.dir);
                    }*/
                    curr_pos2.dir = 2;
                    curr_pos2.map = 13;
                    push_loc(&s, curr_pos2);
                    break;
                    
                case 9:
                    curr_pos2 = curr_pos;
                    curr_pos2.dir = 8;
                    curr_pos2.map = 7;
                    push_loc(&s, curr_pos2);
                    /*if (curr_pos2.x != prev_cross.x || curr_pos2.y != prev_cross.y){
                        push(&route, prev_cross);
                        printf("!");
                        printf("prev_cross (%d, %d, %hd, %hd)\n", prev_cross.x, prev_cross.y, prev_cross.map, prev_cross.dir);
                    }
                    if (curr_pos2.x != prev_cross.x || curr_pos2.y != prev_cross.y) push(&route, prev_cross);*/
                    curr_pos2.dir = 1;
                    curr_pos2.map = 14;
                    push_loc(&s, curr_pos2);
                    break;
                    
                case 10:
                    curr_pos2 = curr_pos;
                    curr_pos2.dir = 8;
                    curr_pos2.map = 7;
                    push_loc(&s, curr_pos2);
                    /*if (curr_pos2.x != prev_cross.x || curr_pos2.y != prev_cross.y){
                        push(&route, prev_cross);
                        printf("!");
                        printf("prev_cross (%d, %d, %hd, %hd)\n", prev_cross.x, prev_cross.y, prev_cross.map, prev_cross.dir);
                    }
                    if (curr_pos2.x != prev_cross.x || curr_pos2.y != prev_cross.y) push(&route, prev_cross);*/
                    curr_pos2.dir = 2;
                    curr_pos2.map = 13;
                    push_loc(&s, curr_pos2);
                    break;
                    
                case 12:
                    curr_pos2 = curr_pos;
                    curr_pos2.dir = 4;
                    curr_pos2.map = 11;
                    push_loc(&s, curr_pos2);
                    /*if (curr_pos2.x != prev_cross.x || curr_pos2.y != prev_cross.y){
                        push(&route, prev_cross);
                        printf("!");
                        printf("prev_cross (%d, %d, %hd, %hd)\n", prev_cross.x, prev_cross.y, prev_cross.map, prev_cross.dir);
                    }*/
                    //if (curr_pos2.x != prev_cross.x || curr_pos2.y != prev_cross.y) push(&route, prev_cross);
                    curr_pos2.dir = 8;
                    curr_pos2.map = 7;
                    push_loc(&s, curr_pos2);
                    break;

            }

        }

        
        //printf("avail : %d\n", avail);
        if (avail != 1 && avail != 2 && avail != 4 && avail != 8){
              if (is_empty(&s)){
                  if (routes != 0){
                      pop(&route);
                      printf("스택활용 횟수 %d회\n", count);
                      printf("모두 %d개의 길을 찾았습니다.\n", routes);
                      printf("가장 짧은 길을 표시합니다.\n");
                      break;
                      
                  }
                  else{
                      printf("실패\n");
                      return 0;}
                      
              }else{
                  curr_pos = pop(&s);
                  if(!is_exist(&route, curr_pos)) push(&route, curr_pos);
                  printf("########################### %d %d\n", peek(&route).x, peek(&route).y);
                  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                  
                  Stack sibal;
                  init_stack(&sibal);
                  
                  while(!is_empty(&route)){
                      push(&sibal, pop(&route));
                      
                      printf("sibal (%d, %d, %hd, %hd)\n", peek(&sibal).x, peek(&sibal).y, peek(&sibal).map, peek(&sibal).dir);
                  }
                  
                  while(!is_empty(&sibal)){
                      push(&route, pop(&sibal));
                      
                  }
                  
                  
                  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                  
                  printf("POP(%d, %d, %hd, %hd)\n", curr_pos.x, curr_pos.y, curr_pos.map, curr_pos.dir);
                  //prev_cross = curr_pos;
                  
        
              }

        }
        
        if(curr_pos.x == 11 && curr_pos.y == 8){
            routes++;
            maze end = {11, 8, 6, 9};
            push(&route, end);
            if (s.top != -1){
                while(!is_empty(&s)){
                    curr_pos = pop(&s);
                }
                push(&route, curr_pos);
                printf("NEW PATH(%d, %d, %hd, %hd)\n", curr_pos.x, curr_pos.y, curr_pos.map, curr_pos.dir);
                
            }else break;
            
        }
        
    }
        
        /*
        {
            if (s.top != -1){
                for (int i = 0; i<s.top; i++){
                    curr_pos = pop(&s);
                }
                
            
            }else break;
        }

    }*/
    //printf("prev 결과 (%d, %d) %hd %hd \n", prev_pos.x, prev_pos.y, prev_pos.map, prev_pos.dir);
    //printf("결과 (%d, %d) %hd %hd \n", curr_pos.x, curr_pos.y, curr_pos.map, curr_pos.dir);
    //printf("성공!\n");
    
    find_path(&route, new_maze, routes);
    
    //print_maze(new_maze);
    
    /*
    while(!is_empty(&route)){
        maze r = pop(&route);
        printf("route (%d, %d, %hd, %hd)\n", r.x, r.y, r.map, r.dir);
    }*/


    return 0;
}

//갈림길 나타날 때 까지 가능한 곳으로 감
//현재위치 최신화
//오른쪽이면 x증가
//왼쪽이면 x감소
//아래쪽이면 y증가
//위쪽이면 y감소
//갈림길 나타나면 스택에 저장
/*
 maze new_maze[12][9] ={
     {{0,0,9}, {0,0,3}, {0,0,3}, {0,0,5}, {0,0,11}, {0,0,3}, {0,0,1}, {0,0,5}, {0,0,13}},
     {{0,0,10}, {0,0,3}, {0,0,5}, {0,0,12}, {0,0,9}, {0,0,3}, {0,0,4}, {0,0,12}, {0,0,12}},
     {{0,0,9}, {0,0,3}, {0,0,4}, {0,0,10}, {0,0,6}, {0,0,9}, {0,0,6}, {0,0,12}, {0,0,12}},
     {{0,0,12}, {0,0,13}, {0,0,14}, {0,0,13}, {0,0,13}, {0,0,14}, {0,0,9}, {0,0,2}, {0,0,4}},
     {{0,0,12}, {0,0,12}, {0,0,9}, {0,0,4}, {0,0,10}, {0,0,3}, {0,0,6}, {0,0,9}, {0,0,4}},
     {{0,0,8}, {0,0,6}, {0,0,8}, {0,0,8}, {0,0,3}, {0,0,7}, {0,0,11}, {0,0,6}, {0,0,12}},
     {{0,0,10}, {0,0,3}, {0,0,6}, {0,0,12}, {0,0,9}, {0,0,3}, {0,0,3}, {0,0,1}, {0,0,4}},
     {{0,0,13}, {0,0,9}, {0,0,3}, {0,0,6}, {0,0,12}, {0,0,9}, {0,0,3}, {0,0,6}, {0,0,10}},
     {{0,0,12}, {0,0,10}, {0,0,3}, {0,0,1}, {0,0,6}, {0,0,10}, {0,0,1}, {0,0,3}, {0,0,5}},
     {{0,0,8}, {0,0,3}, {0,0,1}, {0,0,8}, {0,0,5}, {0,0,13}, {0,0,14}, {0,0,13}, {0,0,12}},
     {{0,0,10}, {0,0,1}, {0,0,12}, {0,0,12}, {0,0,12}, {0,0,8}, {0,0,3}, {0,0,6}, {0,0,12}},
     {{0,0,11}, {0,0,6}, {0,0,10}, {0,0,6}, {0,0,10}, {0,0,6}, {0,0,11}, {0,0,3}, {0,0,6}}
 };
 */
