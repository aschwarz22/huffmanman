#include <stdio.h>
#include <stdlib.h>
#include "checkit.h"
#include "htable.h"


void test_leaf(){
	Hnode* leaf = create_leaf(1, 'a');
	checkit_int(leaf->frequency, 1);
	checkit_char(leaf->letter, 'a');
	checkit_int(leaf->isleaf, 1);
	free(leaf);
}

void test_tree(){
	Hnode* new;
	Hnode* left= create_leaf(1, 'a');
	Hnode* right = create_leaf(4, 'c');
	Hnode* table = create_tree(left, right);
	checkit_int(table->frequency, 5);
	checkit_char(table->left->letter, 'a');
	new = create_leaf(10, 'x');
	table = create_tree(table, new);
	checkit_int(table->frequency, 15);
	checkit_char(table->right->letter, 'x');
	free_table(table);

}

void test_table(){
	test_leaf();
	test_tree();
}

int main(){
	test_table();
	return 0;
}