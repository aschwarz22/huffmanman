#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

Entry** create_table(){
	int i;
	Entry** table = malloc(sizeof(struct Entry)*256);
	for (i = 0; i < 256; i++){
		table[i] = NULL;
	}
	return table;
}

Entry* create_entry(char letter){
	Entry* new = malloc(sizeof(struct Entry));
	new->letter = letter;
	new->frequency = 1;
	return new;
}

void clear_hashtable(Entry** table){
	int i;
	for (i = 0; i < 255; i++){
		if (table[i] != 0){
			free(table[i]);
		}
	}
	free(table);
}

void insert(Entry** table, char letter){
	Entry *new;
	int index;
	new = create_entry(letter); 

	index = (int) letter;
	if (table[index] == 0){
		table[index] = new;
	}
	else{
		free(new);
		table[index]->frequency += 1;
	}
}