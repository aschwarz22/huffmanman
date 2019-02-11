#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

Node *create_node(char letter, int frequency){      
    Node *new = (Node*)malloc(sizeof(struct Node));		/* allocate space for element */
	new->letter = letter;
	new->frequency = frequency;
	return new;
}

/* peeks at occurance of top of priority queue */
int peek_frequency(Node** head) 
{ 
    return (*head)->frequency; 
} 

/* peeks at word of top of priority queue */
char peek_word(Node** head){
	return (*head)->letter;
}


/* inserts element into priority queue based on occurance */
void push(Node** head, char letter, int frequency){
	Node *new = create_node(letter, frequency);				/* Node to push into queue */
	Node *start = *head;									/* Gets head element of queue */

	if (*head == NULL){
		
	}
	if (new->frequency < start->frequency){					/* add element to front of list if lower priority than current head */
		new->next = start;									/* set next of node to add to head of current queue */
		*head = new;										/* set the head to point to the new element */
	}
	else{																			/* finds where in queue new node should be inserted */
		while (start->next != NULL && new->frequency > start->next->frequency){
			start = start->next;													/* iterates through queue */
		}
		

		new->next = start->next;		/* insert new node into proper list location */
		start->next = new;
	}
}

/* pops head of queue */
/* head should have lowest occurance */
void pop(Node** head){
	Node* temp = *head; 
    (*head) = (*head)->next; 		/* set head to next queue element */
    free(temp); 					/* delete previous head */
}

void clear_queue(Node** head){
	while (*head){
		pop(head);
	}
}