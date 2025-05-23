# Design Spec
* User interface
* Inputs and outputs
* Functional decomposition
* Pseudocode for algorithmic flow
* Major data structures
Testing plan
# User Interface
As described in the REQUIRMENTS.md the only interactions will be from the command line 
`./querier pageDirectory indexFilename`
The pagedirectory would be where the index file is stored and the index file name would be of the indexed text file 
# Inputs and outputs
*Input* There are no input files but just the command lines, however they do assume that index files exist
*Output* 
* Standard output: ranked list of matching documents with their doc scores
* Standard error: specified error messages 
# Functional decompositions into modules 
1. main - validates arguments, loads index, calls on methods to evaluate the input and printed sorted
2. readline - reads user input one at a time
3. normalize_query - removes unnecessary characters/spaces and makes everything lowercase
4. tokenize - turns the string of words into tokens of words in an array
5. is_valid_query - checks the and/or placement to see if the query is valid 
6. evaluate - compares documents with the words using and/or precendence
7. index_load - loads the index text into the index data structure
8. print_sorted_results - ranks and prints the documents with the URL
# Pseudocode for logic/flow
main()
    validate the parameters
    create the index from the file
    prompt user for input 
    while - reading line by line
        normalizes the inputs and then tokenizes into an array
        check for validity
        if valid evaluate using the evaluate() function using intersections/unions
    cleanup the memory allocation and delete 
evaluate()
    result and current = NULL
    checks all words
        if it sees OR
            unite the result with current
            free current and set as NULL
        if it is AND
            ignore it 
        if the word is not either
            create counter for the word in the index
            intersect it with the current counter 
    unite the final result with the current
    return the result
# Major data structures
`index_t`
* Wrapper for hashtable to store the words to counters 
`counters_t`
* Map document ID to integers 
`char** words`
* The array of words that are used to tokenize the string
# Testing plan
* Using the REQUIREMENTS.md use the edge cases like non crawler directory and non readable index file
* Test using various letters, toscrape, and wikipedia indexer outputs at various depths
