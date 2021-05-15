#include <stdio.h>
#include <time.h>

typedef struct TreeNode{
    int data;
    struct TreeNode *left, *right;
}TreeNode;

int main(){
    int mode, random;
    TreeNode *root, *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8, *n9;
    srand(time(NULL));
    
    root = (TreeNode*)malloc(sizeof(TreeNode));s
    root->data = rand()%100 + 1;
    
    for(int i = 0; i < 9; i++){
        mode = rand()%2 + 1;
        random = rand()%100 + 1;
        
        if (mode == 1){
            
            
        }else{
            
            
            
        }
        
    
    }
    
}
