#include <stdio.h>
#include <stdlib.h>
#include "build_tree.c"

void fillArr(char letter, char ** codeTable, int *codeArr, int n) 
{ 
    int *code;
    int i;
    code = malloc(sizeof(int)*256);
    for(i = 0; i < n; i++){
    	code[i] = (char)codeArr[i];
    }
    codeTable[(int)letter] = code;
} 

void get_codes(Hnode* root, char ** codeTable, int *arr, int top) 
  
{ 
  
    if (root->left) { 
  
        arr[top] = 0; 
        get_codes(root->left, codeTable, arr, top + 1); 
    } 

    if (root->right) { 
  
        arr[top] = 1; 
        get_codes(root->right, codeTable, arr, top + 1); 
    } 
  
 
    if (root->isleaf == 1) { 
  
         
        fillArr(root->letter, codeTable, arr, top); 
    } 
} 

int main(int argc, char ** argv){
	int *codeArr;
	char codeTable[256][256];
	int i;
	int j;
	int top;
	FILE* f;
	Hnode* tree;
	codeArr = malloc(sizeof(int)*256);
	for (i = 0; i < 256; i++){
		for (j = 0; j<256; j++){
			codeTable[i][j] = NULL;
		}
	}
	top = 0;
	f = fopen(argv[1], "r");
	tree = build_tree(f);
	get_codes(tree, codeTable, codeArr, top);

	free_table(tree);
	
	return 0;
}
