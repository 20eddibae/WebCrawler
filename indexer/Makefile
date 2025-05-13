#Makefile 
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

# Directories
COMMON_DIR = ../common
LIBCS50_DIR = ../libcs50

# Libraries
LIBS = $(COMMON_DIR)/common.a $(LIBCS50_DIR)/libcs50-given.a

# Targets
TARGETS = indexer indextest

# Default target
all: $(TARGETS)

# Build indexer
indexer: indexer.o $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

# Build indextest
indextest: indextest.o $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

# Test target
test: $(TARGETS)
	./testing.sh &> testing.out

# Clean up
.PHONY: all clean test
clean:
	rm -f *.o $(TARGETS)

