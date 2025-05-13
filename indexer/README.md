Eddie Bae, CS 50 Spring 2025 


Indexer gets a file from crawler and breaks it down into word to count to doc ID pairings to keep track of how many words there are using counter data structure 


- Indexer.c
int main(const int argc, char* argv[]);
void index_build(char* pageDirectory, index_t* index);
void index_page(webpage_t* page, const int doc_ID, index_t* index);
- Indextest.c
int main(const int argc, char* argv[]);


To run: make clean, make all, make test and cat testing.out in Indexer
