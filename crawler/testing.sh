#!/bin/bash

#Eddie Bae CS50 Spring 2025, Testing Script

rm -rf ../output
mkdir -p  ../output/pages-letters ../output/pages-toscrape

echo "TESTING: Invalid Arguments"

echo -e "No argument"
./crawler

echo -e "One argument"
./crawler something.com

echo -e "Two argument"
./crawler something.com here/

echo -e "Four argument"
./crawler something.com here/ 1 wrong

echo -e "Invalid maxdepth (out of the number range)"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../output/pages-letters 15

echo -e "Invalid maxdepth (non-numerical input) - no specific error message"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../output/pages-letters notvalid

echo -e "Non-normalized URL"
./crawler cs50tse.cs.dartmouth.edu/tse/letters/index.html ../output/pages-letters 10

echo -e "Non internal URL"
./crawler http://google.com ../output/pages-toscrape 10

echo -e "Nonexistent page directory - ../data/nothere"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/nonexistant 10

echo "TESTING: Valid Arguments"

mkdir -p ../output/pages-letters-depth-0 ../output/pages-letters-depth-1 ../output/pages-letters-depth-2 ../output/pages-letters-depth-3 ../output/pages-letters-depth-10
mkdir -p ../output/pages-toscrape-depth-0 ../output/pages-toscrape-depth-1 ../output/pages-toscrape-depth-2 ../output/pages-wikipedia-depth-0 ../output/pages-wikipedia-depth-1 ../output/pages-wikipedia-depth-2 ../output/valgrind-test

echo -e "Crawling to letters, max depth: 0\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../output/pages-letters-depth-0 0


echo -e "Crawling to letters, max depth: 1\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../output/pages-letters-depth-1 1

echo -e "Crawling to letters, max depth: 2\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../output/pages-letters-depth-2 2

echo -e "Crawling to letters, max depth: 3\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../output/pages-letters-depth-3 3


echo -e "Crawling to letters, max depth: 10\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../output/pages-letters-depth-10 10

echo -e "Crawling to toscrape, max depth: 0\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html ../output/pages-toscrape-depth-0 0

echo -e "Crawling to toscrapes, max depth: 1\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html ../output/pages-toscrape-depth-1 1

#echo -e "Crawling to toscrapes, max depth: 2\n"
#./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html ../output/pages-toscrape-depth-2 2

echo -e "Crawling to wikipedia, max depth: 0\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html ../output/pages-wikipedia-depth-0 0 

echo -e "Crawling to wikipedia, max depth: 1\n"
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html ../output/pages-wikipedia-depth-1 1

#echo -e "Crawling to wikipedia, max depth: 2\n"
#./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html ../output/pages-wikipedia-depth-2 2

echo -e "Running valgrind test with letters...\n"
valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../output/valgrind-test 1

echo -e "Running valgrind test with to scrape...\n"
valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html ../output/valgrind-test 1

echo -e "END OF ALL TESTS"
