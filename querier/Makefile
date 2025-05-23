#Makefile 
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

# Directories
COMMON_DIR = ../common
LIBCS50_DIR = ../libcs50

# Libraries
COMMON_OBJS = $(COMMON_DIR)/index.o $(COMMON_DIR)/pagedir.o
LIBS = $(COMMON_OBJS) $(LIBCS50_DIR)/libcs50-given.a

# Targets
TARGETS = querier 

$(COMMON_DIR)/index.o: $(COMMON_DIR)/index.c $(COMMON_DIR)/index.h
	$(CC) $(CFLAGS) -c $< -o $@

$(COMMON_DIR)/pagedir.o: $(COMMON_DIR)/pagedir.c $(COMMON_DIR)/pagedir.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBCS50_DIR)/counters.o: $(LIBCS50_DIR)/counters.h
	$(CC) $(CFLAGS) -c $< -o $@


# Default target
all: $(TARGETS)

querier.o: querier.c
	$(CC) $(CFLAGS) -c querier.c

# Build querier
querier: querier.o $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

# Build queriertest
queriertest: queriertest.o $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

# Test target
test: $(TARGETS)
	./testing.sh &> testing.out

# Clean up
.PHONY: all clean test
clean:
	rm -f *.o $(TARGETS)
