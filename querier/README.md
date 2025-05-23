# Eddie Bae (git username: 20eddibae)
```
******************
* EXTENSION USED *
****************** 
```

## Querier
Querier takes the indexed files and then finds the documents that have the words in the query that are separated by and/or statements
and statements indicate that both of those words are needed while or indicates that either can be
The querier is interacted through with the command line where the page directory path and filename are given 
Then, the querier asks for the words and then prints things based on the doc id score 
The querier is the third part of the the TSE project 

## Functional Decomposition
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

