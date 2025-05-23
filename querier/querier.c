/*
 *Eddie Bae
 *CS 50, Spring 2025
 *Querier - ranks documents based on how many of the words that are required it has 
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "../common/pagedir.h"
#include "../common/index.h"
#include "../libcs50/counters.h"
#include "../libcs50/hashtable.h"


/* The fileno() function is provided by stdio,
 * but for some reason not declared by stdio.h, so declare here.
 */
int fileno(FILE *stream);

//struct to allow for the implicit declarations of the hashtable in index, allows for more efficient implementation
typedef struct index {
  hashtable_t* table;
} index_t;

//given function to print a prompt if the stdin is a terminal
static void
prompt(void)
{
  // print a prompt iff stdin is a tty (terminal)
  if (isatty(fileno(stdin))) {
    printf("Query? ");
    fflush(stdout);
  }
}
/**************** readline() ****************/
/*
 * Method to read a line from the user intput
 * Caller provides:
 *  fp - a file to read from, usually stdin in our situation
 */
static char* readline(FILE* fp) {
  char buffer[1000];
  if (fgets(buffer, 1000, fp) == NULL) {
    return NULL;
  }
  char* copy = malloc(strlen(buffer) + 1); // creates copy to ensure the lack of memory leak problems
  if (copy == NULL){
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }
  strcpy(copy, buffer);
  return copy;
}

/**************** normalize_query() ****************/
/*
 * Method to normalize the query by making everything lower cased and removing the spaces
 * Caller provides:
 *  line - string to be normalized 
 */
static char*
normalize_query(const char* line){
  char output[1000];
  int j = 0;
  bool inWord = false;

  for (int i = 0; line[i] != '\0'; i++) {
    if (isalpha(line[i])) { // checks if it is a character
      output[j++] = tolower(line[i]); // if so, make it lower case
      inWord = true;
    } else if (isspace(line[i]) && inWord) { // if it is a space after the word, include it, if not ignore
      output[j++] = ' '; // add single space after the word 
      inWord = false;
    }
  }

  if (j > 0 && output[j - 1] == ' ') { // remove the trailing space
    j--;
  }
  output[j] = '\0'; // cap with the ending char

  char* copy = malloc(strlen(output) + 1); // create copy to ensure memory leaks do not happen
  if (copy == NULL){
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }
  strcpy(copy, output);
  return copy;
}

/**************** tokenize() ****************/
/*
 * Method to break the array of words into an array of singular words
 * Caller provides:
 *  line - normalized sentence to be tokenized
 *  wordCount - amount of words should be in this new array 
 */

static char** 
tokenize(const char* line, int* wordCount) 
{  

  char** words = malloc(100 * sizeof(char*)); // creates the array that will hold the tokenized words
  int count = 0;
  int i = 0; 

  while (line[i] != '\0'){ // goes until the end of the line
    while (isspace(line[i])){ // ignores the spaces
      i++;
    }
    int start = i; // gets the beginning placement of the word 
    while (isalpha(line[i])){ // advances until the end 
      i++;
    }
    int end = i;
    if (end > start){ // if the word's length is not zero 
      int length = end - start;
      char* word = malloc(length + 1);
      strncpy(word, line + start, length); // copy that word into the "word" array
      word[length] = '\0'; // cap it with the ending character
      words[count++] = word;
    }
    while (line[i] != '\0' && !isalpha(line[i]) && !isspace(line[i])){
      i++; // skip unaccounted characters/symbols
    }
  }

  *wordCount = count;
  return words; // returns the array 
}

/**************** free_words() ****************/
/*
 * Method to free the tokenized words 
 * Caller provides:
 *  words - array of tokenized words
 *  n - integer that represents the amount of words 
 */

static void 
free_words(char** words, int n)
{
  for (int i = 0; i < n; i++){
    free(words[i]); // free components
  }
  free(words); // free the whole array
}

/**************** is_valid_query() ****************/
/*
 * Method to check if a given query input/request is valid, checking for beginning ands/ors
 * Caller provides:
 *  words - array of tokenized words
 *  n - number of words
 */

static bool is_valid_query(char** words, int n) {
  if (n == 0) return false; // no words is not valid 
  if (strcmp(words[0], "and") == 0) {
    fprintf(stderr, "Error: and cannot be first\n");
    return false;
  } else if (strcmp(words[0], "or") == 0) { // cannot start with and/or
    fprintf(stderr, "Error: or cannot be first\n");
    return false;
  }
  if (strcmp(words[n-1], "and") == 0){
    fprintf(stderr, "Error: and cannot be last\n");
    return false;
  } else if (strcmp(words[n-1], "or") == 0) { // cannot end with and/or
    fprintf(stderr, "Error: or cannot be last\n");
    return false;
  }
  for (int i = 0; i < n - 1; i++) {
    if ((strcmp(words[i], "and") == 0 || strcmp(words[i], "or") == 0) && // cannot be adjacent
        (strcmp(words[i+1], "and") == 0 || strcmp(words[i+1], "or") == 0)) {
      fprintf(stderr, "Error: '%s' and '%s' cannot be adjacent\n", words[i], words[i+1]);
      return false;
    }
  }
  return true;
}

// helper function that is given the counter with the count and docID to duplicate it for memory allocation purposes
void 
copy_counter_item(void* arg, const int docID, const int count) 
{
  counters_t* dst = arg;
  counters_set(dst, docID, count);
}

/**************** copy_counters() ****************/
/*
 * Method to copy counters and not deal with memory allocation complications
 * Caller provides:
 *  src - an inputted counter 
 */

static 
counters_t* copy_counters(counters_t* src) 
{
  counters_t* copy = counters_new();
  counters_iterate(src, copy, copy_counter_item); // iterates through the counters and copies them 
  return copy;
}

// helper method that is given counters, the next counter, and gets the intersection of the two counters 
void 
intersect_helper(void* arg, const int docID, const int count1) 
{
  counters_t* other = arg;
  int count2 = counters_get(other, docID); // gets the count value of the count at a certain docID
  if (count2 > 0) {
    int min = count1 < count2 ? count1 : count2;
    counters_set(other, docID, min);
  } else {
    counters_set(other, docID, 0); // Prevent false matches
  }
}

/**************** intersect() ****************/
/*
 * Method to get the intersection of counters values from two counters by iterating through the two
 * Caller provides:
 *  2 counters in which to compare the two 
 */

static void 
intersect(counters_t* base, counters_t* next) 
{
  counters_iterate(base, next, intersect_helper);
}

// helper function to help get the union of two counters when provided the counter, docID for it, and the count value
void 
union_helper(void* arg, const int docID, const int count) 
{
  counters_t* base = arg;
  int old = counters_get(base, docID);
  counters_set(base, docID, old + count);
}

/**************** unite() ****************/
/*
 * Method to get the union of the count values for the two sets 
 * Caller provides:
 *  2 counters in which get the union of 
 */

static void 
unite(counters_t* base, counters_t* add) 
{
  counters_iterate(add, base, union_helper);
}

/**************** index_load() ****************/
/*
 * Method to turn a text file into an index data structure 
 * Caller provides:
 *    name of the file in which to get the index from 
 * We return: 
 *    the index data structure given an index raw text file
 */


static index_t* 
index_load(const char* fileName)
{
  FILE* fp = fopen(fileName, "r");
  if (fp == NULL){
    fprintf(stderr, "The file is not readable\n");
    return NULL;
  }
  
  index_t* output = index_new(1000);
  if (output == NULL){
    fclose(fp);
    return NULL;
  }

  char line[1000];
  while (fgets(line, sizeof(line), fp) != NULL){
    char* ptr = line;
    while (isspace(*ptr)){
      ptr++;
    }
    char word[200];
    int offset = 0;
    sscanf(ptr, "%199s%n", word, &offset);
    ptr += offset;

    int docID;
    int count;

    while (sscanf(ptr, " %d %d%n", &docID, &count, &offset) == 2){
      index_set(output, word, docID, count);
      ptr += offset;
    }
  }
  fclose(fp);
  return output;
}

/**************** index_find() ****************/
/*
 * Finds the counter data structure for a specific word in an index
 * Caller provides:
 *  index data structure
 *  word 
 * We return:
 *  counter for that word in the index
 */

static counters_t* 
index_find(index_t* index, const char* word)
{
  if (index == NULL || word == NULL){
    return NULL;
  }
  return hashtable_find(index->table, word); 
}

/**************** evaluate() ****************/
/*
 * Using backus naur logic to get the unions and intersections of the different words/counters
 * Caller provides:
 *  2 counters in which to compare the two
 */
static counters_t* evaluate(index_t* index, char** words, int count)
{
  counters_t* result = NULL;             // final result (OR of all AND groups)
  counters_t* andGroup = NULL;           // current AND group

  for (int i = 0; i < count; i++) {
    char* word = words[i];

    if (strcmp(word, "or") == 0) {
      // OR: merge the current AND group into the result
      if (andGroup != NULL) {
        if (result == NULL) {
          result = andGroup;
        } else {
          unite(result, andGroup);
          counters_delete(andGroup);
        }
        andGroup = NULL;
      }
    }
    else if (strcmp(word, "and") == 0) {
      // AND is implicit, do nothing
      continue;
    }
    else {
      counters_t* wordCounts = index_find(index, word);
      if (wordCounts == NULL) {
        // Treat as empty set: intersect with empty -> nullifies the group
        wordCounts = counters_new();  // empty counter
      }

      if (andGroup == NULL) {
        andGroup = copy_counters(wordCounts);
      } else {
        intersect(andGroup, wordCounts);  // AND logic
      }
    }
  }

  // After loop, merge final AND group if any
  if (andGroup != NULL) {
    if (result == NULL) {
      result = andGroup;
    } else {
      unite(result, andGroup);
      counters_delete(andGroup);
    }
  }

  // If everything was empty or invalid
  if (result == NULL) {
    result = counters_new();
  }

  return result;
}
/**************** print_sorted_results() ****************/
/*
 * Method to print the valid documents that satisfy the query in a ranked way
 * Caller provides:
 *  counters that represents the total compiled counters for the words
 *  the page directory string 
 */
void print_sorted_results(counters_t* result, const char* pageDir) {
  int maxScore, docID;

  // count how many nonzero scores
  int docCount = 0;
  for (int i = 1; i < 10000; i++) {
    if (counters_get(result, i) > 0) docCount++; 
  }
  if (docCount == 0) {
    printf("No documents match.\n");
    return;
  }
  printf("Matches %d documents (ranked):\n", docCount);

  // sorted print
  for (int printed = 0; printed < docCount; printed++) { // iterate through the doc IDs
    maxScore = 0;
    docID = 0;
    for (int i = 1; i < 10000; i++) {
      int score = counters_get(result, i);
      if (score > maxScore) { // checks if this is the max score
        maxScore = score;
        docID = i;
      }
    }
    if (docID == 0) break;
    // print with URL
    char filepath[200];
    sprintf(filepath, "%s/%d", pageDir, docID);
    FILE* fp = fopen(filepath, "r");
    if (fp != NULL) { // read the url from the file path
      char url[300];
      fgets(url, sizeof(url), fp);
      url[strcspn(url, "\n")] = '\0'; // gets the url 
      printf("score\t%d doc\t%d: %s\n", maxScore, docID, url);
      fclose(fp);
    }
    counters_set(result, docID, 0);  // zero out so we can get the next one
  }
}

int  
main (int argc, char* argv[])
{
  if (argc != 3){ // checks for number of arguments
    fprintf(stderr, "Usage: %s page_directory index_filename\n", argv[0]);
    exit(1);
  }

  char* pageDir = argv[1];
  char* indexFilename = argv[2];

  if (!pagedir_validate(pageDir)){
    fprintf(stderr, "Error: %s is not a valid .crawler directory \n", pageDir);
    exit(2);
  }

  //loading index
  index_t* index = index_load(indexFilename);
  if (index == NULL){
    fprintf(stderr, "Error: cannot load index index from file %s\n", indexFilename);
    exit(3);
  }
  char* line;
  prompt();
  while ((line = readline(stdin)) != NULL) { // reads the user input
    char* norm = normalize_query(line);
    int n;
    char** words = tokenize(norm, &n); // tokenize the words 

    if (!is_valid_query(words, n)) { // checks the placement of and/or to see if it is valid
      free(norm); 
      free(line); 
      free_words(words, n); 
      prompt(); 
      continue;
    }

    printf("Query: %s\n", norm); // prints the input it received
    counters_t* result = evaluate(index, words, n); // evaluates through unions/intersects
    print_sorted_results(result, pageDir); // prints in sorted fashion
    counters_delete(result); // free and delete everything
    free_words(words, n);
    free(norm);
    free(line);
    prompt();
  }
  index_delete(index);
}
