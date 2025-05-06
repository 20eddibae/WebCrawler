#Makefile that will build the common.a library

CC = gcc 
CFLAGS = -Wall -pedantic -std=c11 -ggdb

OBJS = pagedir.o
LIB = common.a

$(LIB): $(OBJS)
		ar rcs $(LIB) $(OBJS)

pagedir.o: pagedir.c pagedir.h
	$(CC) $(CFLAGS) -c pagedir.c

.PHONY: clean

clean:
	rm -f *.o $(LIB)
