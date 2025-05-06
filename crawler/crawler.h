/* crawler.h - fetches a webpage */

#ifndef __CRAWLER_H
#define __CRAWLER_H

#include <stdbool.h>
#include "webpage.h"

/* Start crawling from the given seedURL */
void crawl(const char* seedURL, const char* pageDirectory, const int maxDepth);

#endif // __CRAWLER_H
