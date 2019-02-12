#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "build_tree.c"

int CODETABLE[256][256];
int freqtable[256];
int unique = 0;


void printArr(int arr[], int n, unsigned char letter, int frequency) 
{ 
    int i;
    int idx = (int)letter;
    letter = (unsigned char) letter;
    for (i = 0; i < n; ++i){ 
    	CODETABLE[idx][i] = arr[i];
  	}
  	freqtable[idx] = (uint32_t)frequency;
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
		freqtable[i] = 0;
		for (j = 0; j < 256; j++){
			CODETABLE[i][j] = -1;
		}
	}
}

void write_code(int in, int out){
	int i;
	uint8_t letr;
	char c;
	int idx;
	uint8_t byte_out; 
	int bitno;
	int count = 0;
	byte_out = 0;
	bitno = 0;
	write(out, (void*)&unique, 4);
	for(i = 0; i < 256; i++){
		if (freqtable[i] != 0){
			letr = (uint8_t)i;
			write(out, (void*)&letr, 1);
			write(out, (void*)&freqtable[i], 4);
		}
	}
	while ((read(in, &c, 1)) >0){
		c = (unsigned char) c;
		idx = (uint8_t)c;
		while(CODETABLE[idx][count] != -1){

			
			if (CODETABLE[idx][count] == 1){
				byte_out |= (((uint8_t)1)<<(7-bitno));	
			}
		
			if (bitno > 6){
				write(out,  (void*)&byte_out, 1);
				bitno = 0;
				byte_out = 0;
				count ++;
				continue;
			}
			bitno++;
			count++;
		}
		
		count = 0;
	}
	if (bitno != 0){
		write(out, (void*)&byte_out, 1);
	}
	i = -1;
	write(out, (void*)&i, 1);
}

int check_full(int input){
	off_t fsize;
	fsize = lseek(input, 0, SEEK_END);
	close(input);
	return (int)fsize;
}

int main(int argc, char ** argv){
	int *arr;
	int empty;
	char* message;
	int top, in, out;
	Hnode* tree;
	null_table();
	arr = malloc(sizeof(int)*100);
	top = 0;
	if (argc > 1){
		in = open(argv[1], O_RDONLY);
	}
	else{
		message = "Usage error: hencode infile [outfile]";
		write(STDERR_FILENO, (void*)message, sizeof(strlen(message)));
		exit(EXIT_FAILURE);
	}
	if (in == -1){
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	if (argc > 2){
		out = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
		if (out == -1){
			perror(argv[2]);
		}
	}
	else{
		out = STDOUT_FILENO;
	}	
	empty = check_full(in);
	if (empty != 0){

		in = open(argv[1], O_RDONLY);
		tree = build_tree(in, argv[1]);
		printCodes(tree, arr, top);
		close(in);
		in = open(argv[1], O_RDONLY);
		if (in == -1){
			perror(argv[1]);
			exit(EXIT_FAILURE);

		}
		write_code(in, out);
		free(arr);
		free_table(tree);
	}
	else{
		write(out, (void*)&empty, 4);
	}
	close(in);
	close(out);
	
	return 0;
}

