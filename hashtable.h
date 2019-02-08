#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct Entry{
	int frequency;
	char letter;
} Entry;

Entry** create_table();

void insert(Entry**, char);


Entry* create_entry(char);

void clear_hashtable(Entry**);

#endif

