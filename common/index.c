/*
 *Index - data structure to keep track of words and their counts 
 *
 * Eddie Bae
 * CS 50, Spring 2025 
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "index.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/file.h"


index_t* index_new(const int num_slots);

bool index_set(index_t* input, const char* word, const int doc_ID, const int count);

bool index_insert(index_t* input, const char* key, const int docID);

bool index_save(index_t* index, const char* fileName);

static void index_save_helper(void* fp, const char* key, void* item);

static void counter_helper(void* file, const int doc_ID, const int count);

void index_delete (index_t* input);

static void index_delete_helper(void* item);


typedef struct index{
  hashtable_t* table;
}index_t;

/**************** index_new() ****************/
/*
 * Creates new index struct based on number of slots they want 
 * Caller provides:
 *  num slots - the amount of index value/pairings they want
 * We return:
 *  index struct 
 */
index_t* 
index_new(const int num_slots)
{
  if (num_slots <= 0){
    return NULL;
  }
 
  index_t* new_index = malloc(sizeof(index_t)); // allocates memory for new index 
  if (new_index == NULL){
    return NULL;
  }
  new_index->table = hashtable_new(num_slots); // creates hashtable in index that will store the counters
  if (new_index->table == NULL){
    free(new_index);
    return NULL;
  }

  return new_index;

}

/**************** index_insert() ****************/
/*
 * Given index and its doc ID, increments the value of the counter
 * Caller provides:
 *  index - index to change
 *  doc ID  - ID number to identify the document
 * We return:
 *  true/false based on whether the insert was successful
 */

bool 
index_insert(index_t* input, const char* key, const int doc_ID)
{
  if (input == NULL || key == NULL || doc_ID <= 0){
    return false;
  } 
  
  counters_t* check_counter = hashtable_find(input->table, key); // gets the counter at for the specific word  

  if (check_counter == NULL){
    check_counter = counters_new(); // if no counter, initializes it 
    if (check_counter == NULL){
      return false;
    }
    if (!hashtable_insert(input->table, key, check_counter)) { // inserts the key and counter 
      counters_delete(check_counter);  
      return false;                    
    }
  }
  counters_add(check_counter, doc_ID); // if not, increments 
  return true;

}

/**************** index_save() ****************/
/*
 * Saves the index/prints the values to a file to see how it looks
 * Caller provides:
 *  index_t - index to output
 *  fileName - name of file to print to
 * We return:
 *  boolean based on whether the writing to the file was successful
 */


bool
index_set(index_t* input, const char* word, const int doc_ID, const int count){
  if (input == NULL || word == NULL || doc_ID <= 0 || count <= 0) {
    return false;
  }

  counters_t* ctrs = hashtable_find(input->table, word); // finds the counter at a word 
  if (ctrs == NULL) {
    ctrs = counters_new();
    if (ctrs == NULL) {
      return false;
    }
    if (!hashtable_insert(input->table, word, ctrs)) { // creates counter if not existant
      counters_delete(ctrs);
      return false;
    }
  }
  counters_set(ctrs, doc_ID, count); // sets the count at that word 
  return true;
}

/**************** index_set() ****************/
/*
 * Given specific parameters sets the word, doc id and count in a given index
 * Caller provides:
 *  doc ID - ID number of document
 *  count - data structure to keep track of a certain word's number count
 *  word - the word to modify/put in index
 *  index_t* - input index to modify
 *
 * We return:
 *  true/false based on whether the set was succesful
 */

bool 
index_save(index_t* index, const char* file_name)
{
  if (index == NULL || file_name == NULL){
    return false;
  }
  FILE* fp = fopen(file_name, "w"); // open file for writing 
  if (fp == NULL){
    return false;
  }

  hashtable_iterate(index->table, fp, index_save_helper); // iterate through hashtable with helper
  fclose(fp);
  return true;
}
// helper method to go through the index 
static void
index_save_helper(void* fp, const char* key, void* item){
  counters_t* counters = item;
  FILE* file = fp;
  fprintf(file, "%s", key); // prints the key/word to the file 
  counters_iterate(counters, file, counter_helper); // iterates through the counters in hashtable 
  fprintf(file, "\n");
}

// helper method to print the doc ID and count of the counters to the file 
static void
counter_helper(void* file, const int doc_ID, const int count){
  fprintf((FILE*) file, " %d %d", doc_ID, count);
}

// helper method to help delete counters from the hashtable in index 
static void
index_delete_helper(void* item)
{
  counters_delete(item);     
}
/**************** index_delete() ****************/
/*
 * Deletes the index 
 * Caller provides:
 *  index_t* input - the index to delete
 */

void
index_delete(index_t* input)
{
  if (input != NULL){
    hashtable_delete(input->table, index_delete_helper); // deletes with the help of helper function
    free(input);
  }
}
