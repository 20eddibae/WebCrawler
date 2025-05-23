#!/bin/bash

rm -f output1.txt output2.txt readonly.txt

touch output1.txt output2.txt

echo -e "No argument"
./indexer
echo

echo -e "One argument"
./indexer ../output/pages-letters-depth-1 
echo

echo -e "Three or more arguments"
./indexer ../output/pages-letters-depth-1 output1.txt output2.txt
echo

echo -e "Non-existant path for pageDirectory"
./indexer ../output/no/dir output1.txt
echo

echo -e "Non-crawler directory for pageDirectory"
mkdir tmpdir
touch tmpdir/1
./indexer tmpdir output1.txt
rm -r tmpdir
echo

echo -e "Non-existant path for indexFile"
./indexer ../output/pages-letters-depth-1 ../no/path/output1.txt
echo

echo -e "Read-only directory for indexFile"
mkdir readonlydir
chmod 444 readonlydir
./indexer ../output/pages-letters-depth-1 readonlydir/output1.txt
chmod 755 readonlydir
rm -r readonlydir
echo 

echo -e "indexFile being read only"
touch readonly.txt
chmod 444 readonly.txt
./indexer ../output/pages-letters-depth-1 readonly.txt
chmod 644 readonly.txt
rm readonly.txt
echo 

INDEXDIR0=../output/pages-letters-depth-0
OUTFILE0=output-index0.txt
COPYFILE0=output-index-copy0.txt

echo "Depth 0: Run indexer on valid directory '$INDEXDIR0'"
./indexer "$INDEXDIR0" "$OUTFILE0"
echo

echo "Depth 0: Show first 10 lines of generated index"
head "$OUTFILE0"
echo

echo "Depth 0: Run indextest to load and save the index"
./indextest "$OUTFILE0" "$COPYFILE0"
echo

echo "Depth 0: Compare output and copy using indexcmp"
~/cs50-dev/shared/tse/indexcmp "$OUTFILE0" "$COPYFILE0"
INDEXDIR=../output/pages-letters-depth-1
OUTFILE=output-index.txt
COPYFILE=output-index-copy.txt

echo "Depth 1: Run indexer on valid directory '$INDEXDIR'"
./indexer "$INDEXDIR" "$OUTFILE"
echo

echo "Depth 1: Show first 10 lines of generated index"
head "$OUTFILE"
echo

echo "Depth 1: Run indextest to load and save the index"
./indextest "$OUTFILE" "$COPYFILE"
echo

echo "Depth 1: Compare output and copy using indexcmp"
~/cs50-dev/shared/tse/indexcmp "$OUTFILE" "$COPYFILE"
echo



echo "Depth 0: Compare output and copy using indexcmp"
~/cs50-dev/shared/tse/indexcmp "$OUTFILE0" "$COPYFILE0"

touch output-index-toscrape0.txt

echo "Depth 1: Run toscrape on valid directory '$INDEXDIR'"
./indexer ../output/pages-toscrape-depth-0 output-index-toscrape0.txt
echo


touch output-index-toscrape1.txt

echo "Depth 0: Run wikipedia on valid directory '$INDEXDIR'"
./indexer ../output/pages-toscrape-depth-1 output-index-toscrape1.txt


touch output-index-wikipedia0.txt

echo "Depth 0: Run wikipedia on valid directory '$INDEXDIR'"
./indexer ../output/pages-wikipedia-depth-0 output-index-wikipedia0.txt

touch output-index-wikipedia1.txt

echo "Depth 1: Run wikipedia on valid directory '$INDEXDIR'"
./indexer ../output/pages-wikipedia-depth-1 output-index-wikipedia1.txt

echo "Depth 1: Show first 10 lines of generated index"
head "$OUTFILE"
echo



echo "Valgrind: indexer "
valgrind ./indexer ../output/pages-letters-depth-1 output1.txt
echo

echo "Valgrind: indextest"
valgrind ./indextest output1.txt output2.txt
echo
