#Makefile that will build the common.a library

CC = gcc 
CFLAGS = -Wall -pedantic -std=c11 -ggdb

OBJS = pagedir.o word.o index.o
LIB = common.a

$(LIB): $(OBJS)
		ar rcs $(LIB) $(OBJS)

pagedir.o: pagedir.c pagedir.h
	$(CC) $(CFLAGS) -c pagedir.c

word.o: word.c word.h
	$(CC) $(CFLAGS) -c word.c

index.o: index.c index.h
	$(CC) $(CFLAGS) -c index.c

.PHONY: clean

clean:
	rm -f *.o $(LIB)
