//
//  maze.c
//  hw1
//
//  Created by Jijoong Hong on 2021/03/24.
//  Copyright © 2021 Jijoong Hong. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 6








typedef struct{
    short r;
    short c;
}element;

element here = {1 , 0}, entry = {1,0};

char maze[MAZE_SIZE][MAZE_SIZE] ={
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,1,1,1,1,1},
};

void push_loc(
