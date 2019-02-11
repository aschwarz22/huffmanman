CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
MAIN1 = hencode
MAIN2 = hdecode
all : $(MAIN1) $(MAIN2)

$(MAIN1) : hencode.c
	$(CC) $(CFLAGS) -o hencode hencode.c

$(MAIN2) : hdecode.c
	$(CC) $(CFLAGS) -o hdecode hdecode.c

clean :
	rm *.o $(MAIN1) $(MAIN2) core

