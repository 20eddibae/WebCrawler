/* =========================================================================
 * word.c - normalizes word by making it all lower case 
 *
 * Eddie Bae
 * CS 50 Spring 2025 
 * ========================================================================= 
 */

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "word.h"

// normalizes the word by making it all lower case 
char*
normalize_word(const char* word)
{
  if (word == NULL){
    fprintf(stderr, "Error: the inputted word is null");
    return NULL;
  }
  int word_size = strlen(word);

  char* finalWord = malloc(word_size + 1);
  if (finalWord == NULL){
    fprintf(stderr, "Error: trouble allocating memory for final word");
    return NULL;
  }

  for (int i = 0; i < word_size; i++){
    if (!isalpha(word[i])){
      free(finalWord);
      return NULL;
    }
    finalWord[i] = tolower(word[i]); // makes letters lower case 
  }
  finalWord[word_size] = '\0'; // adds end character 
  return finalWord;
}
