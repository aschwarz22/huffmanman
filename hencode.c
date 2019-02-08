#include <stdio.h>
#include <stdlib.h>
#include "build_tree.c"

int CODETABLE[256][256];
int unique = 0;


void printArr(int arr[], int n, char letter, int frequency) 
{ 
    int i;
    int idx = (int)letter; 
    for (i = 0; i < n; ++i){ 
        /*printf("%d", arr[i]);*/
    	CODETABLE[idx][i] = arr[i];
  	}
  	CODETABLE[idx][i+1] = frequency;
  	unique += 1;
} 

void printCodes(Hnode* root, int arr[], int top) 
  
{ 
  
    if (root->left) { 
  
        arr[top] = 0; 
        printCodes(root->left, arr, top + 1); 
    } 

    if (root->right) { 
  
        arr[top] = 1; 
        printCodes(root->right, arr, top + 1); 
    } 
  
 
    if (root->isleaf == 1) { 
  
        printArr(arr, top, root->letter, root->frequency); 
    } 
} 

void null_table(){
	int i;
	int j;
	for (i = 0; i < 256; i++){
		for (j = 0; j < 256; j++){
			CODETABLE[i][j] = -1;
		}
	}
}

void write_code(FILE* in, FILE* out){

}

int main(int argc, char ** argv){
	int *arr;
	int top;
	FILE* f;
	FILE* out;
	Hnode* tree;
	null_table();
	arr = malloc(sizeof(int)*100);
	top = 0;
	f = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	tree = build_tree(f);
	printCodes(tree, arr, top);
	free(arr);
	free_table(tree);
	
	return 0;
}

