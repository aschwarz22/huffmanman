#include <stdio.h>
#include <stdlib.h>
#include "checkit.h"
#include "hashtable.h"


void test_entry(){
	Entry* entry = create_entry('a');
	checkit_int(entry->frequency, 1);
	checkit_char(entry->letter, 'a');
	free(entry);
}

void test_htable(){
	int index;
	Entry** table = create_table();
	Entry* new = create_entry('a');
	index = (int)(new->letter);
	table[index] = new;
	checkit_char(table[index]->letter, 'a');
	checkit_int(table[index]->frequency, 1);
	clear_hashtable(table);

}

void test_insert(){
	int index;
	Entry** tab = create_table();
	index = 97;
	insert(tab, 'a');
	checkit_char(tab[index]->letter, 'a');
	checkit_int(tab[index]->frequency, 1)
	insert(tab, 'a');
	checkit_char(tab[index]->letter, 'a');
	checkit_int(tab[index]->frequency, 2);
	insert(tab, 'd');
	index = 100;
	checkit_char(tab[index]->letter, 'd');
	checkit_int(tab[index]->frequency, 1)
	clear_hashtable(tab);

}

void test_table(){
	test_entry();
	test_htable();
	test_insert();
}

int main(){
	test_table();
	return 0;
}