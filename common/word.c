#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "word.h"


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
    finalWord[i] = tolower(word[i]);
  }
  finalWord[word_size] = '\0';
  return finalWord;
}
