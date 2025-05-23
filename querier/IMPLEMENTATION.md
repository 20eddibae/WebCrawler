# IMPLEMENTATION Spec
# Data Structures
* `index_t` - wrapper for hashtable mapping words to counters
* `counters_t` - map docID to number of words in a certain document
* `char** word` - array of strings that are the tokenized array
# Control Flow
## main
validate amount of arguments
load index from filename
validate crawler directory
looping through the stdin:
    normalize query
    tokenize into words
    validate structure in relation to and/or
    if invalid, reprompt
    else: 
        evaluate using index
        print sorted results
clean up the memory
## evaluate
initialize result and set current counters to NULL
loop through words:
    if word == or
        unite result with current
        free current
        reset current
    else if word != word
        find counters for words
        if current is NULL
            copy counters
        else
            intersect current with the result
final unite of result and current
return result
# Functional Prototypes
## querier
```c
static void prompt(void)
static char* readline(FILE* fp);
static char** tokenize(const char* line, int* wordCount);
static char* normalize_query(const char* line);
static bool is_valid_query(char** words, int n);
static void unite(counters_t* base, counters_t* add);
static counters_t* index_find(index_t* index, const char* word);
static counters_t* evaluate(index_t* index, char** words, int count);
void print_sorted_results(counters_t* result, const char* pageDir);
```
# Error Handling
* checks that if the number of arguments is 3
* checks if the index is unreadable or fails to load
* all memory allocations are checked if NULL
* invalid queries with and/or placement

# Testing plan

## Unit Tests

* test normalize_query to ensure lowercase and single spacing
* test tokenize to make sure it correctly splits and counts words
* test is_valid_query to handle query syntax edge cases
* test evaluate so that it corrects ranking with sample indices

## Integration Tests

* Invalid inputs
* Wrong argument count
* Invalid index file
* Invalid directory
* Valid queries
* Simple single-word
* Complex Boolean logic
* Non-matching word (prints "No documents match.")

## System Testing

Create test index files with known word-docID mappings

Validate query results and rankings match expectations

Use valgrind to ensure no memory leaks
* Testing.sh in order to test these edge cases as well as letters, to scrape, wikipedia, test valgrind for memory leaks as well 
