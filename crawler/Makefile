#Makefile 

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
LIBS = ../common/common.a ../libcs50/libcs50-given.a
OBJS = crawler.o
TARGET = crawler

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

crawler.o: crawler.c
	$(CC) $(CFLAGS) -c crawler.c

.PHONY: clean

test: $(TARGET)
	./testing.sh &> testing.out

clean:
	rm -f *.o $(TARGET)
