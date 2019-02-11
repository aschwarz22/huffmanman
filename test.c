#include <stdio.h>
#include <stdlib.h>
#include "htable.c"
#include "hashtable.c"

int main(){
	Hnode* first;
	first = create_leaf(3, 'a');
	printf("%d",first->frequency);
	return 0;
}