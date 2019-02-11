#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "htable.c"

Hnode_queue_entry** make_nodes(int infile){
	int file_byte;
	int unique;
	int i;
	char letter;
	int frequency;
	Hnode* start;
	Hnode_queue_entry* new;
	Hnode_queue_entry **queue = NULL;
	read(infile, &file_byte, 4);
	unique = (int)file_byte;

	for (i = 0; i < unique; i++){
		read(infile, (void*)&letter, 1);
		read(infile, (void*)&frequency, 4);
		start = create_leaf(frequency, letter);
		if(queue == NULL){
				new = create_queue(start);
				new->next = NULL;
				queue = &new;
		}
		else{
			push(queue, start);
		}
	}
	return queue;

}

Hnode* build_tree(int f){
	Hnode_queue_entry** queue;
	Hnode_queue_entry* start;
	Hnode* tree;
	Hnode* left;
	Hnode* right;
	queue = make_nodes(f);
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

void decode(int infile, int outfile){
	Hnode* tree;
	Hnode** head;
	Hnode* start;
	int bitno;
	int total_letters;
	uint8_t byte_out;
	uint8_t comp;
	int letters_in = 0;
	bitno = 10;
	tree= build_tree(infile);
	head = &tree;
	start = tree;
	total_letters = tree->frequency;
	while(letters_in < total_letters){
		if (bitno > 7 ){
			read(infile, (void*)&byte_out, 1);
			bitno = 0;
		}
		comp = ((uint8_t)1<<(7-bitno));
		comp &= byte_out;
		if (start->isleaf == 1){
			write(outfile, (void*)&(start->letter), 1);
			start = *head;
			letters_in++;
		}
		if (comp == 0){
			start = start->left;
		}
		else{
			start = start->right;
		}
		bitno++;

	}
	free_table(tree);

}


int main(int argc, char** argv){
	int infile;
	int outfile;
	char* message;
	if (argc > 0){
		infile = open(argv[1], O_RDONLY);
	}
	else{
		message = "Usage error: hencode infile [outfile]";
		write(STDERR_FILENO, (void*)message, sizeof(strlen(message)));
		exit(EXIT_FAILURE);
	}
	if (infile == -1){
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	if (argc > 1){
		outfile = open(argv[2], O_WRONLY | O_TRUNC);
		if (outfile == -1){
			perror(argv[2]);
		}
	}
	else{
		outfile = STDOUT_FILENO;
	}	
	decode(infile, outfile);
	close(infile);
	close(outfile);
	return 0;
}
