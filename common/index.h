/* =========================================================================
 * index.h - index struct that is used to keep track of numbers and their counts
 *
 * Eddie Bae
 * CS 50 Spring 2025 
 * ========================================================================= 
 */

#ifndef INDEX_H
#define INDEX_H

#include <stdbool.h>

typedef struct index index_t;

/**************** index_new() ****************/
/*
 * Creates new index struct based on number of slots they want 
 * Caller provides:
 *  num slots - the amount of index value/pairings they want
 * We return:
 *  index struct 
 */
  
index_t* index_new(const int num_slots);

/**************** index_insert() ****************/
/*
 * Given index and its doc ID, increments the value of the counter 
 * Caller provides:
 *  index - index to change 
 *  doc ID  - ID number to identify the document 
 * We return:
 *  true/false based on whether the insert was successful 
 */

bool index_insert(index_t* input, const char* key, const int docID);

/**************** index_save() ****************/
/*
 * Saves the index/prints the values to a file to see how it looks 
 * Caller provides:
 *  index_t - index to output
 *  fileName - name of file to print to 
 * We return:
 *  boolean based on whether the writing to the file was successful 
 */

bool index_save(index_t* index, const char* fileName);

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

bool index_set(index_t* input, const char* word, const int doc_ID, const int count);

/**************** index_delete() ****************/
/*
 * Deletes the index 
 * Caller provides:
 *  index_t* input - the index to delete
 */

void index_delete (index_t* input);


#endif // INDEX_H
