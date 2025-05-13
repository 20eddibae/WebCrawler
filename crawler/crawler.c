/*
 *Eddie Bae
 *CS50 Spring 2025
 *Crawler that parses the argument checking for normalized URL and then crawls to given depth
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../libcs50/webpage.h"
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include "../common/pagedir.h"

// function prototypes
static void parseArgs(const int argc, char* argv[],
                      char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);

int 
main (const int argc, char* argv[])
{
   char* seedURL;
   char* pageDirectory;
   int maxDepth;
   
   parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
   crawl(seedURL, pageDirectory, maxDepth);

   exit(0);
}

/**************** parseArgs() ****************/
/* Normalize URL and check if internal
 * Initialize page directory 
 * Check if maxDepth is between 0 and 10
 * Exit nonzero if any issues
 * Caller provides:
 *   inputs of seedURL pageDirectory maxDepth
 */
static void
parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth)
{
  if (argc != 4){ // checks if there are too many parameters/inputs
    fprintf(stderr, "Useage: %s seedURL pageDirectory maxDepth\n", argv[0]);
    exit(1);
  }
  *seedURL = argv[1];
  *pageDirectory = argv[2];
  *maxDepth = atoi(argv[3]);

  if (*maxDepth < 0 || *maxDepth > 10){ // checks if the maxDepth is between 0 and 10 
    fprintf(stderr, "Error: maxDepth must be between 0 and 10\n");
    exit(2);
  }

  // normalizing URL
  char* normalized = normalizeURL(*seedURL); // normalizes the URL
  if (normalized == NULL){ // checks if normalization worked
    fprintf(stderr, "Error: seedURL is not able to be normalized \n");
    exit(1);
  }
  *seedURL = normalized; // changes to normalized 
   
  if (!isInternalURL(*seedURL)){ // checks if the URL is an internal one
    fprintf(stderr, "Error: seedURL is not internal \n");
    free(normalized); // frees as nothing happens after if not internal
    exit(1);
  }
  if(!pagedir_init(*pageDirectory)){ // checks if the page directory initialization does not work
    fprintf(stderr, "Error: trouble in initializing pageDirectory\n");
    free(normalized); // free the allocated memory 
    exit(1);
  }


}
/**************** crawl() ****************/
/* Crawl to max depth and save page in pageDirectory
 * pageScan HTML 
 * Caller provides:
 *   seedURL, pageDirectory, maxDepth
 */
static 
void crawl(char* seedURL, char* pageDirectory, const int maxDepth)
{
  hashtable_t* hashSeen = hashtable_new(200); // initialize to 200 
  if (hashSeen == NULL){ // checks if correctly allocated
    fprintf(stderr, "Hashtable new failed");
    exit(1);
  }
  bag_t* webBag = bag_new(); // bag that stores the pages
  if (webBag == NULL){
    fprintf(stderr, "Bag new failed");
    exit(1);
  }
  webpage_t* seedPage = webpage_new(seedURL, 0, NULL); // the seed page 
  if (seedPage == NULL){
    fprintf(stderr, "Webpage new failed");
    exit(1);
  }
  int docID = 1; // initializes ID number to 1
  bag_insert(webBag, seedPage); // first insert 
  webpage_t* tempPage;
  while ((tempPage = bag_extract(webBag)) != NULL){ // checks if bag extract worked
    int depth = webpage_getDepth(tempPage);  
    char* url = webpage_getURL(tempPage);

    printf("%d     Fetched: %s\n", depth, url);
    if(webpage_fetch(tempPage)){ // fetches page
      pagedir_save(tempPage, pageDirectory, docID++); // saves the page information in directory
      printf("%d    Scanning: %s\n", depth, url); 

      if (webpage_getDepth(tempPage) < maxDepth){ // checks if max depth reached
        pageScan(tempPage, webBag, hashSeen); // scans the page for URL, adds if not explored 
      }
      webpage_delete(tempPage); // deletes webpage to free memory
    } else {
      fprintf(stderr, "URL not in http.... format");
      webpage_delete(tempPage); // frees memory if unable to fetch the page
    }
  }
  hashtable_delete(hashSeen, NULL); // for no leaks in memory 
  bag_delete(webBag, NULL);
}

/**************** pageScan() ****************/
/* Extract URLs, ignoring non-internal URLs
 * If URL not seen before, add URL to hashtable and bag 
 * Caller provides:
 *  page, bag, hashtable 
 */

static 
void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen)
{
  int pos = 0;
  char* result;
  while ((result = webpage_getNextURL(page, &pos)) != NULL){ // gets the next url in the page
    char* normalized = normalizeURL(result); // gets the normalized URL
    int depth = webpage_getDepth(page); 
    printf("%d       Found: %s\n", depth, result);
    if (normalized != NULL && isInternalURL(normalized)){ // checks normalization and if URL internal
      if (hashtable_insert(pagesSeen, normalized, "")){ // inserts into hashtable
        printf("%d       Added: %s\n", depth, normalized);
        webpage_t* tempWeb = webpage_new(normalized, webpage_getDepth(page) + 1, NULL); // create new webpage
        if (tempWeb == NULL){
          fprintf(stderr, "Webpage new failed");
          free(normalized);
          free(result);
          exit(1);
        }
        bag_insert(pagesToCrawl, tempWeb); // add to bag of pages to crawl later for call function
      } else {
        printf("%d     IgnDupl: %s\n", depth, normalized);
        free(normalized); // frees the memory in case the insert fails 
      }
    } else {
      printf("%d    IgnExtrn: %s\n", depth, result);
      if (normalized != NULL){
        free(normalized);
      }
    }
    free(result);
  }
}

