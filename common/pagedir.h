#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdio.h>
#include "../libcs50/webpage.h"


/**************** pagedir_init() ****************/
/* Initialize directory to be used as pageDirectory
 * Writes .crawler file as a crawler produced pageDirectory
 * Caller provides:
 *   pageDirectory - path to existing directory
 * We return
 *   true if directory succesfully marked with the .crawler file 
 *   false otherwise (e.g directory doesn't exist or we cannot write into it )
 */
bool pagedir_init(const char* pageDirectory);



/**************** pagedir_save() ****************/
/* 
 * Saves webpage to file in the pageDirectory, to the filename given with docID
 * Caller provides:
 *  page- pointer to webpage
 *  pageDirectory - path to directory that is saved to 
 *  docID - integer file name
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

/**************** pagedir_validate() ****************/
/*
 * Validates if the given directory path is a crawler directory
 * Caller provides:
 *  page directory path 
 * We return:
 *  boolean indicating success
 */

bool pagedir_validate(const char* page_directory);

/**************** pagedir_load() ****************/
/*
 * Loads a page directory based on directory path and doc id 
 * Caller provides:
 *  doc ID - ID number of document 
 *  pageDirectory - path to directory that is saved to
 * We return:
 *  The webpage from the given directory 
 */

webpage_t* pagedir_load(const char* page_directory, const int doc_ID);

#endif // __PAGEDIR_H
