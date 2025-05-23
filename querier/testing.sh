#!/bin/sh


echo -e "0 command line arguments"
./querier
echo

echo -e "1 command line argument"
./querier ../
echo

echo -e "3 command line arguments"
./querier ../ ../ letters-0
echo



echo -e "Test: bag pageDirectory - not a valid .crawler"
mkdir badDir && touch badDir/1
./querier badDir ../shared/tse/output/letters-0.index
rm -r badDir
echo

echo -e "Test: Nonexistant index file"
./querier ../shared/tse/output/letters-0 doesNotExist.index
echo




echo -e "Testing on the given shared output index 0 (and beginning with and/or)"
./querier ~/cs50-dev/shared/tse/output/letters-0 ~/cs50-dev/shared/tse/output/letters-0.index <<EOF
home
tse and page
this or playground
and something something
or something something 
EOF
echo

echo -e "Testing on letters depth 1 (ending with and/or)"
./querier ../output/pages-letters-depth-0 ../indexer/output-index.txt <<EOF
playground and page
depth or biology
algorithm and notaword
yes this is wrong and
yes this is wrong too or
EOF
echo

echo -e "Testing on to scrape 0"
./querier ../output/pages-toscrape-depth-0 ../indexer/output-index-toscrape0.txt <<EOF
python
book and web
and
EOF
echo


echo -e "Testing on toscrape 1"
./querier ../output/pages-toscrape-depth-1 ../indexer/output-index-toscrape1.txt <<EOF 
python
web or spider
quotes and love
or
and
EOF
echo

echo -e "Testing on given shared output wikipedia 0"
./querier ../output/pages-wikipedia-depth-0 ../indexer/output-index-wikipedia0.txt <<EOF
dartmouth
college and new
hanover or student
EOF
echo

echo -e "Testing on given shared output wikipedia 1"
./querier ../output/pages-wikipedia-depth-1 ../indexer/output-index-wikipedia1.txt <<EOF
dartmouth
engineering or thayer
cs50 and course
and
or
EOF
echo

echo -e "Valgrind test on querier letters 0 "
valgrind ./querier ~/cs50-dev/shared/tse/output/letters-0 ~/cs50-dev/shared/tse/output/letters-0.index <<EOF
home
and
or
EOF
echo

echo -e "Valgrind test on querier letters 1 "
valgrind ./querier ../shared/tse/output/letters-0 ../indexer/output-index-letters1.txt <<EOF
playground and page
EOF
