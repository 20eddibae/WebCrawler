/*
 * Eddie Bae
 * CS 50, Spring 2025
 * pagedir_init and pagedir_save to initialize pageDirectory and save file to directory
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"


/**************** pagedir_init() ****************/
/* Initialize directory to be used as pageDirectory
 * Writes .crawler file as a crawler produced pageDirectory
 * Caller provides:
 *   pageDirectory - path to existing directory
 * We return
 *   true if directory succesfully marked with the .crawler file
 *   false otherwise (e.g directory doesn't exist or we cannot write into it )
 */
bool pagedir_init(const char* pageDirectory)
{
    char* path = malloc(strlen(pageDirectory) + strlen("/.crawler") + 1); // creates pathname for .crawler
    if (path == NULL) {
        fprintf(stderr, "Error: insufficient memory\n");
        return false;
    }

    sprintf(path, "%s/.crawler", pageDirectory); // combines the strings 
    FILE* fp = fopen(path, "w"); // opens the file for writing 
    free(path);

    if (fp == NULL) {
        fprintf(stderr, "Error: cannot write this .crawler file\n");
        return false;
    }

    fclose(fp);
    return true;
}


/**************** pagedir_save() ****************/
/*
 * Saves webpage to file in the pageDirectory, to the filename given with docID
 * Caller provides:
 *  page- pointer to webpage
 *  pageDirectory - path to directory that is saved to
 *  docID - integer file name
 */

void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID)
{
    char filename[1000];
    sprintf(filename, "%s/%d", pageDirectory, docID); // construct pathname for page file in pageDirectory 

    FILE* fp = fopen(filename, "w"); // open file for writing 
    if (fp == NULL) {
        fprintf(stderr, "Error: cannot open file %s for writing\n", filename);
        exit(1);
    }

    fprintf(fp, "%s\n", webpage_getURL(page)); // basic information on URL, Depth before printing HTML
    fprintf(fp, "%d\n", webpage_getDepth(page));
    fprintf(fp, "%s\n", webpage_getHTML(page));

    fclose(fp);
}


/**************** pagedir_validate() ****************/
/*
 * Validates if the given directory path is a crawler directory
 * Caller provides:
 *  page directory path
 * We return:
 *  boolean indicating success
 */

bool
pagedir_validate(const char* page_directory)
{
  char output[100];
  sprintf(output, "%s/.crawler", page_directory); // combines strings to check the crawler directory path
  FILE* fp = fopen(output, "r"); // checks if readable
  if (fp == NULL){
    return false;
  }
  fclose(fp);
  return true;
}

/**************** pagedir_load() ****************/
/*
 * Loads a page directory based on directory path and doc id 
 * Caller provides:
 *  doc ID - ID number of document 
 *  pageDirectory - path to directory that is saved to
 * We return:
 *  The webpage from the given directory 
 */

webpage_t* 
pagedir_load(const char* page_directory, const int doc_ID)
{
  if (page_directory == NULL){
    return NULL;
  }
  char output[1024];
  sprintf(output, "%s/%d", page_directory, doc_ID); // creates directory and doc Id pairing
  FILE* fp = fopen(output, "r"); // checks if readable 
  if (fp == NULL){
    return NULL;
  }

  char* url_out = file_readLine(fp); // reads the first line for url 
  if (url_out == NULL){
    fclose(fp);
    return NULL;
  }
  char* depth_str = file_readLine(fp); // gets the depth level 
  if (depth_str == NULL){
    free(url_out);
    fclose(fp);
    return NULL;
  }
  char* html = file_readFile(fp); // get the html 
  fclose(fp); // stop reading the file 
  if (html == NULL) {
    free(url_out);
    free(depth_str);
    return NULL;
  }

  int depth = atoi(depth_str); // gets the depth as a integer to create new webpage
  free(depth_str);

  webpage_t* page = webpage_new(url_out, depth, html); // creates new webpage to return 
  if (page == NULL) {
    free(url_out);
    free(html);
    return NULL;
  }
  return page;
}
