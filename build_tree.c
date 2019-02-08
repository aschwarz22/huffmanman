#include <stdio.h>
#include <stdlib.h>
#include "htable.c"

#include "get_letters.c"


Hnode_queue_entry** fill_queue(FILE* f){
	char* str;
	Entry** tab;
	int i;
	Hnode * start;
	Hnode_queue_entry *new;
	Hnode_queue_entry** queue = NULL;
	str = read_long_line(f);
	tab = fill_table(str);
	for(i = 0; i < 256; i++){
		if(tab[i]){
			start = create_leaf(tab[i]->frequency, tab[i]->letter);
			if (queue == NULL){
				new = create_queue(start);
				new->next = NULL;
				queue = &new;
			}
			else{
				push(queue, start);
			}
		}
	}
	clear_hashtable(tab);
	return queue;
}

Hnode* build_tree(FILE* f){
	Hnode_queue_entry** queue;
	Hnode_queue_entry* start;
	Hnode* tree;
	Hnode* left;
	Hnode* right;
	queue = fill_queue(f);
	start = *queue;
	while(start->next){
		left = start->current;
		pop(&start);
		right = start->current;
		pop(&start);
		tree = create_tree(left, right);
		if (start == NULL){
			push(&start, tree);
			break;
		}
		push(&start, tree);
	}	
	tree = start->current;
	free(start);
	return tree;
}



void printArr(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        printf("%d", arr[i]); 
  
    printf("\n"); 
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
  
        printf("%c: ", root->letter); 
        printArr(arr, top); 
    } 
} 

int main(int argc, char ** argv){
	int *arr;
	int top;
	FILE* f;
	Hnode* tree;
	arr = malloc(sizeof(int)*100);
	top = 0;
	f = fopen(argv[1], "r");
	tree = build_tree(f);
	printCodes(tree, arr, top);
	free(arr);
	free_table(tree);
	
	return 0;
}





