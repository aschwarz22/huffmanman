#include <stdio.h>
#include <stdlib.h>
#include "htable.h"

Hnode* create_leaf(int frequency, char letter){
	Hnode* newleaf = malloc(sizeof(struct Hnode));
	newleaf->letter = letter;
	newleaf->frequency = frequency;
	newleaf->isleaf = 1;
	newleaf->left = NULL;
	newleaf->right = NULL;

	return newleaf;
}

Hnode* create_tree(Hnode* left, Hnode* right){
	Hnode* head = malloc(sizeof(struct Hnode));

	int newfreq = left->frequency + right->frequency;
	head->frequency = newfreq;

	head->isleaf = 0;

	head->left = left;
	head->right = right;
	if ((int)(left->letter) < (int)(right->letter)){
		head->letter = left->letter;
	}
	else{
		head->letter = right->letter;
	}


	return head;
}

Hnode_queue_entry *create_queue(Hnode* new){      
    Hnode_queue_entry *queue = (Hnode_queue_entry*)malloc(sizeof(struct Hnode_queue_entry));		/* allocate space for element */
	queue->current = new;
	return queue;
}

/* peeks at occurance of top of priority queue */
int peek_frequency(Hnode_queue_entry *queue) 
{ 
    return queue->current->frequency; 
} 

/* peeks at word of top of priority queue */
char peek_word(Hnode_queue_entry *queue){
	return queue->current->letter;
}




/* inserts element into priority queue based on occurance */
void push(Hnode_queue_entry **queue, Hnode* new){
	Hnode_queue_entry *start;
	Hnode_queue_entry *newnode = create_queue(new);
	start = *queue;
	if (start == NULL){
		*queue = newnode;
	}

	else if (new->frequency < start->current->frequency){					/* add element to front of list if lower priority than current head */
		newnode->next = start;									/* set next of node to add to head of current queue */
		*queue = newnode;										
	}
	else{																			/* finds where in queue new node should be inserted */
		while (start->next != NULL && newnode->current->frequency >= start->next->current->frequency){
			if (newnode->current->frequency == start->next->current->frequency){
				if ((int)(newnode->current->letter) < (int)(start->next->current->letter)){
					break;
				}
			}
			start = start->next;													/* iterates through queue */
		}
		

		newnode->next = start->next;		/* insert new node into proper list location */
		start->next = newnode;
	}
}

/* pops head of queue */
/* head should have lowest occurance */
void pop(Hnode_queue_entry** head){
	Hnode_queue_entry* temp = *head; 
    (*head) = (*head)->next; 		/* set head to next queue element */
    free(temp); 					/* delete previous head */
}

void clear_queue(Hnode_queue_entry** head){
	while (*head){
		pop(head);
	}
}

void free_table(Hnode* node){
    if ((node) == NULL){
        return;
    }

    
    free_table(node->left);
    free_table(node->right);

    free(node);
}