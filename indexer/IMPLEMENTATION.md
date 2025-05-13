## Implementation Spec

# Data structures
- index_t used hashtable to map strings/keys to counters_t* values
- counters_t* mapped document IDs to frequency counts 
- These used the libcs50 counters, hashtable, and set modules

# General Synopsys
- indexer.c
main parses command line arguments, validates directory, creates index, and saves the index
index build goes over filenames, uses pagedir to load them up, and passes through index page
index page extracts words and stores into index 
- indextest.c
parses lines, calls index set to update index, writes the index into file with index save


# Functions
- Indexer.c
int main(const int argc, char* argv[]);
void index_build(char* pageDirectory, index_t* index);
void index_page(webpage_t* page, const int doc_ID, index_t* index);
- Indextest.c
int main(const int argc, char* argv[]);

# Error Handling
- Accounted for the given possible errors on the command line
- Exits non zero if: output file cannot be opened, directory not crawler produced, memory allocation fails
- index_load skips invalid lines and prints warnings
- indextest handles malformed inputs

#Testing Plan
- Use index functions on given/produced data sets
- Compare using indexcmp given 
- Use indextest to save a given index into a file 
- Use valgrind (in the testing.sh script)


