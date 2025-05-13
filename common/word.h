/* =========================================================================
 * word.h - normalizes word by making it all lower case 
 *
 * Eddie Bae
 * CS 50 Spring 2025 
 * ========================================================================= 
 */

#ifndef WORD_H
#define WORD_H

/**************** normalize_word() ****************/
/*
 * Makes a word all lower case 
 * Caller provides:
 *  word - string comprised of characters
 * We return:
 *  word in all lower case  
 */

char *normalize_word(const char *word);

#endif // WORD_H
