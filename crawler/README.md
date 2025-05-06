# Tiny Search Engine: Crawler

## Description: 
# First module of Tiny Search Engine, begins at seedURL, explores page, recursively explore internal pages until maximum depth

## Assumptions (from instructions that the program is able to pass over)
- seedURL is internal
- pageDirectory exists and is writable
- max depth between 0 and 10
- do not retry page fetches (work or they dont)
- ordering of the crawl is not always consistent
- "" empty string as placeholder for hashtable

## No Major Deviations from Spec

## Known Bugs/Limitations (allowed by the instructions)
- edge cases like non-HTTP URLs that the program passes over
- Memory allocation fails, prints error and exists non-zero value
- for test file specifically, the non internal but normalized URL prints the error message for un normalized

## Files
- 'crawler.c' - crawl through web 
- 'Makefile' - builds executable
- 'testing.sh' - script to run and validate crawl
- 'testing.out' - stores output of testing script

## Note
- make test automatically updates into the testing.out
- I also did not print the progress printf in the testing.out, had it commented out and then removed the comments for submission (like said in slack)
- I also had additional tests for toscrape and wikipedia for depth 2 that I commented out but had it there in case we wanted to use it (as said in slack that we did not have to go above depth 1)
