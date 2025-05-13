/*
 * Index test - creates inverted index structure based on the output file
 *
 *Eddie Bae
 * CS 50, Spring 2025 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/index.h"

int main (const int argc, char* argv[])
{
  if (argc != 3){
    fprintf(stderr, "Usage: indextest oldIndexFilename newIndexFilename\n");
    exit(1); 
  }
  
  char* old_indexFilename = argv[1]; // old file to read from 
  char* new_indexFilename = argv[2]; // new file to write into 

  FILE* fp = fopen(old_indexFilename, "r"); // reads the old file and checks if possible 
  if (fp == NULL) {
    fprintf(stderr, "Cannot open file: %s\n", old_indexFilename);
    exit(2);
  }

  index_t* idx = index_new(200); // creates new index 
  if (idx == NULL) {
     fprintf(stderr, "Failed to create new index\n");
     fclose(fp);
     exit(3);
  }

  char word[100];
  int docID;
  int count;

  while (fscanf(fp, "%s", word) == 1) { // keeps reading until new line reached
    while (fscanf(fp, "%d %d", &docID, &count) == 2) {
      index_set(idx, word, docID, count); // sets the index to certain count
      int next = fgetc(fp); // reads the next character to check if it is the end 
      if (next == '\n' || next == EOF) {
        break;
      }
    }
  }
  fclose(fp);

  if (!index_save(idx, new_indexFilename)) { // saves the index to new file (prints it)
     fprintf(stderr, "Failed to write index to file: %s\n", new_indexFilename);
     index_delete(idx);
     exit(4);
  }

  index_delete(idx); // delete for memory purposes
  exit(0);
}
