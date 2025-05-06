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
    fprintf(fp, "o%s\n", webpage_getHTML(page));

    fclose(fp);
}

