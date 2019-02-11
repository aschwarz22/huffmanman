#include <stdio.h>
#include "checkit.h"
#include "pqueue.h"

void test_node(){
	Node* new = create_node('a', 10);
	checkit_int(new->frequency, 10);
	checkit_char(new->letter, 'a');
	clear_queue(&new);
}

void test_peek(){
	Node* new = create_node('c', 10);
	Node* new2 = create_node('d', 9);
	new->next = new2;
	checkit_int(peek_frequency(&new), 10);
	checkit_char(peek_word(&new), 'c');
	clear_queue(&new);
}




void test_push_front(){


	Node* new; 
	new = create_node('a', 10);
	push(&new, 'b', 9);
	checkit_int(new->frequency, 9);
	checkit_char(new->letter, 'b')
	push(&new, 'f', 4);
	checkit_int(new->frequency, 4);
	checkit_char(new->letter, 'f')
	clear_queue(&new);
	
}

void test_push_mid(){
	Node* new; 
	new = create_node('n', 10);
	push(&new, 'x', 9);
	push(&new, 'f', 4);
	push(&new, 'v', 5);
	checkit_int(new->next->frequency, 5);
	checkit_char(new->next->letter, 'v')
	clear_queue(&new);
	
}

void test_push_back(){
	Node* new; 
	new = create_node('n', 10);
	push(&new, 'x', 9);
	push(&new, 'f', 4);
	push(&new, 'v', 5);
	push(&new, 's', 14);
	checkit_int(new->next->next->next->next->frequency, 14);
	checkit_char(new->next->next->next->next->letter, 's');
	clear_queue(&new);
	
}

void test_pop(){
	Node* new; 
	new = create_node('n', 10);
	push(&new, 'x', 9);
	push(&new, 'f', 4);
	push(&new, 'v', 5);
	push(&new, 's', 14);
	pop(&new);
	checkit_int(new->frequency, 5);
	checkit_char(new->letter, 'v')
	clear_queue(&new);
	
}


void test_queue(){
	test_node();
	test_peek();
	test_push_front();
	test_push_mid();
	test_push_back();
	test_pop();
}

int main(void){
	test_queue();
	return 0;
}

