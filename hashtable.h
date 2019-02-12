#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct Entry{
	int frequency;
	unsigned char letter;
} Entry;

Entry** create_table();

void insert(Entry**, unsigned char);


Entry* create_entry(unsigned char);

void clear_hashtable(Entry**);

#endif

