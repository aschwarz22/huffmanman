#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>

#include "htable.c"

#include "get_letters.c"

int CODETABLE[256][256];


Hnode_queue_entry** fill_queue(int f, char* name){
	unsigned char* str;
	int fsize;
	Entry** tab;
	int i;
	Hnode * start;
	Hnode_queue_entry *new;
	Hnode_queue_entry** queue = NULL;
	str = read_long_line(f);
	close(f);
	open(name, O_RDONLY);
	fsize = (int)lseek(f, 0, SEEK_END);
	close(f);
	open(name, O_RDONLY);
	tab = fill_table(str, fsize);
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

Hnode* build_tree(int f, char* fname){
	Hnode_queue_entry** queue;
	Hnode_queue_entry* start;
	Hnode* tree;
	Hnode* left;
	Hnode* right;
	queue = fill_queue(f, fname);
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


/*int main(int argc, char ** argv){
	int *arr;
	int top;
	FILE* f;
	Hnode* tree;
	null_table();
	arr = malloc(sizeof(int)*100);
	top = 0;
	f = fopen(argv[1], "r");
	tree = build_tree(f);
	printCodes(tree, arr, top);
	free(arr);
	free_table(tree);
	
	return 0;
}
*/




