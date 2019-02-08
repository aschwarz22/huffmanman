#ifndef HTABLE_H
#define HTABLE_H

typedef struct Hnode{
	int frequency;
	int isleaf;
	struct Hnode *left;
	struct Hnode *right;
	char letter;

} Hnode;

typedef struct Hnode_queue_entry{
	struct Hnode *current;
	struct Hnode_queue_entry *next;
} Hnode_queue_entry;



Hnode* create_leaf(int, char);

Hnode* create_tree(Hnode*, Hnode*);


Hnode_queue_entry *create_queue(Hnode*);

/* peeks at occurance of top of priority queue */
int peek_frequency(Hnode_queue_entry*);

/* peeks at word of top of priority queue */
char peek_word(Hnode_queue_entry*);




/* inserts element into priority queue based on occurance */
void push(Hnode_queue_entry** , Hnode* );

/* pops head of queue */
/* head should have lowest occurance */
void pop(Hnode_queue_entry**);

void free_table(Hnode*);

#endif



