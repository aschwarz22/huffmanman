#ifndef PQUEUE_H
#define PQUEUE_H


typedef struct Node{
	int frequency;
	char letter;
	struct Node* next;
} Node;


Node* create_node(char, int);

int peek_frequency(Node**);

char peek_word(Node**);

void push(Node**, char, int);

void pop(Node**);

void clear_queue(Node**);
#endif