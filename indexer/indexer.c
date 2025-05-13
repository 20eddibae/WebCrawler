/*
 * Eddie Bae, CS 50 Spring 2025
 *
 *Indexer.c, builds an index based on 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/index.h"
#include "../common/pagedir.h"
#include "../libcs50/webpage.h"
#include "../common/word.h"

int main (const int argc, char* argv[]);
void index_build (char *pageDirectory, index_t *index);
void index_page (webpage_t* page, const int doc_ID, index_t* index);

int 
main (const int argc, char* argv[]){
  if (argc != 3){
    fprintf(stderr, "Usage: [indexer] [pageDirectory] [indexFilename]");
    exit(1);
  }
  char* page_directory = argv[1];
  char* index_filename = argv[2];

  if(!pagedir_validate(page_directory)){
    fprintf(stderr, "Invalid crawler directory: %s", page_directory);
    exit(2);
  }

  FILE* fp = fopen(index_filename, "w");
  if (fp == NULL) {
    fprintf(stderr, "%s: Cannot open output file %s\n", argv[0], index_filename);
    exit(3);
  }
  fclose(fp);

  index_t* temp_index = index_new(500);
  if (temp_index == NULL) {
    fprintf(stderr, "%s: Error creating index structure\n", argv[0]);
    exit(4);
  }

  index_build(page_directory, temp_index);

  if (!index_save(temp_index, index_filename)) {
    fprintf(stderr, "%s: Error saving index to %s\n", argv[0], index_filename);
    index_delete(temp_index);
    exit(5);
  }

  index_delete(temp_index);

  exit(0);
}

/**************** index_build() ****************/
/*
 * Given directory and an index, builds the index by loading in webpage and using index functions
 * Caller provides:
 *  page-directory - path to the page to build index 
 *  index_t* index - index in which the index values of the page directory are written to 
 */
void 
index_build (char *page_directory, index_t* index)
{
   if (page_directory == NULL || index == NULL) {
    return;
  }

  for (int i = 1;; i++) {
    webpage_t* input = pagedir_load(page_directory, i);
    if (input == NULL) {
      break;  // No more pages to process
    }

    // Process this page
    index_page(input, i, index);

    // Free the webpage and all its resources
    webpage_delete(input);
  }
}
/**************** index_page() ****************/
/*
 * Method to help build the index by going through the words and incrementing or creating counter
 * Caller provides:
 *  webpage - webpage generated in index build to build index off of 
 *  doc ID - document ID from which to read from
 *  index_t* index - index to write into/change
 */
void 
index_page (webpage_t* page, const int doc_ID, index_t* index)
{
  int pos = 0;
  char* word;
  while ((word = webpage_getNextWord(page, &pos)) != NULL){ // goes through every word
    if (strlen(word) >= 3){ // only goes through words greater than or equal to length 3
      char* normalized = normalize_word(word); // normalizes word 
      if (normalized != NULL) {
        index_insert(index, normalized, doc_ID); // insert into index 
        free(normalized); // free after insertion
      }
    }
    free(word);
  }
}
