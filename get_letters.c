#include <unistd.h>
#include <stdlib.h>
#include "hashtable.c"

char *read_long_line(int fd){
	int limit = 10*sizeof(char);
	char *str = malloc(limit);
	int i=0;
	char c;
	while((read(fd, (void*)&c, 1)) > 0){
		if (i == limit-1){ 
			limit = limit*limit;
			str = realloc(str, limit);
		}

		str[i] = c;
		i++;
	}
	if (i == limit-1){ 
			limit = limit+1;
			str = realloc(str, limit);
		}
	str[i] = '\0';
	return str;
}

Entry** fill_table(char* str){
	int i;
	Entry** tab;
	tab = create_table();
	i = 0;
	while (str[i] != '\0'){
		insert(tab, str[i]);
		i++;
	}
	free(str);
	return tab;

}
